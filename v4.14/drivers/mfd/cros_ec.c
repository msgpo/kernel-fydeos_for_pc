/*
 * ChromeOS EC multi-function device
 *
 * Copyright (C) 2012 Google, Inc
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * The ChromeOS EC multi function device is used to mux all the requests
 * to the EC device for its multiple features: keyboard controller,
 * battery charging and regulator control, firmware update.
 */

#include <linux/of_platform.h>
#include <linux/interrupt.h>
#include <linux/slab.h>
#include <linux/module.h>
#include <linux/mfd/core.h>
#include <linux/mfd/cros_ec.h>
#include <linux/suspend.h>
#include <asm/unaligned.h>

#define CROS_EC_DEV_EC_INDEX 0
#define CROS_EC_DEV_PD_INDEX 1

static struct cros_ec_platform ec_p = {
	.ec_name = CROS_EC_DEV_NAME,
	.cmd_offset = EC_CMD_PASSTHRU_OFFSET(CROS_EC_DEV_EC_INDEX),
};

static struct cros_ec_platform pd_p = {
	.ec_name = CROS_EC_DEV_PD_NAME,
	.cmd_offset = EC_CMD_PASSTHRU_OFFSET(CROS_EC_DEV_PD_INDEX),
};

static const struct mfd_cell ec_cell = {
	.name = "cros-ec-dev",
	.platform_data = &ec_p,
	.pdata_size = sizeof(ec_p),
};

static const struct mfd_cell ec_pd_cell = {
	.name = "cros-ec-dev",
	.platform_data = &pd_p,
	.pdata_size = sizeof(pd_p),
};

s64 cros_ec_get_time_ns(void)
{
	return ktime_get_boot_ns();
}
EXPORT_SYMBOL(cros_ec_get_time_ns);

static irqreturn_t ec_irq_handler(int irq, void *data) {
	struct cros_ec_device *ec_dev = data;

	ec_dev->last_event_time = cros_ec_get_time_ns();

	return IRQ_WAKE_THREAD;
}

static bool ec_handle_event(struct cros_ec_device *ec_dev)
{
	bool wake_event = true;
	bool ec_has_more_events = false;
	int ret = cros_ec_get_next_event(ec_dev, &wake_event);

	if (ec_dev->mkbp_event_supported) {
		ec_has_more_events = (ret > 0) &&
			(ec_dev->event_data.event_type &
				EC_MKBP_HAS_MORE_EVENTS);
	}

	if (device_may_wakeup(ec_dev->dev) && wake_event)
		pm_wakeup_event(ec_dev->dev, 0);

	if (ret > 0)
		blocking_notifier_call_chain(&ec_dev->event_notifier,
					0, ec_dev);

	return ec_has_more_events;

}

static irqreturn_t ec_irq_thread(int irq, void *data)
{
	struct cros_ec_device *ec_dev = data;
	bool ec_has_more_events;

	do {
		ec_has_more_events = ec_handle_event(ec_dev);
	} while (ec_has_more_events);

	return IRQ_HANDLED;
}

static int cros_ec_sleep_event(struct cros_ec_device *ec_dev, u8 sleep_event)
{
	struct {
		struct cros_ec_command msg;
		struct ec_params_host_sleep_event req;
	} __packed buf;

	memset(&buf, 0, sizeof(buf));

	buf.req.sleep_event = sleep_event;

	buf.msg.command = EC_CMD_HOST_SLEEP_EVENT;
	buf.msg.version = 0;
	buf.msg.outsize = sizeof(buf.req);

	return cros_ec_cmd_xfer(ec_dev, &buf.msg);
}

int cros_ec_register(struct cros_ec_device *ec_dev)
{
	struct device *dev = ec_dev->dev;
	int err = 0;

	BLOCKING_INIT_NOTIFIER_HEAD(&ec_dev->event_notifier);

	ec_dev->max_request = sizeof(struct ec_params_hello);
	ec_dev->max_response = sizeof(struct ec_response_get_protocol_info);
	ec_dev->max_passthru = 0;

	ec_dev->din = devm_kzalloc(dev, ec_dev->din_size, GFP_KERNEL);
	if (!ec_dev->din)
		return -ENOMEM;

	ec_dev->dout = devm_kzalloc(dev, ec_dev->dout_size, GFP_KERNEL);
	if (!ec_dev->dout)
		return -ENOMEM;

	mutex_init(&ec_dev->lock);

	err = cros_ec_query_all(ec_dev);
	if (err) {
		dev_err(dev, "Cannot identify the EC: error %d\n", err);
		return err;
	}

	if (ec_dev->irq > 0) {
		err = devm_request_threaded_irq(dev, ec_dev->irq,
				ec_irq_handler, ec_irq_thread,
				IRQF_TRIGGER_LOW | IRQF_ONESHOT,
				"chromeos-ec", ec_dev);
		if (err) {
			dev_err(dev, "Failed to request IRQ %d: %d",
				ec_dev->irq, err);
			return err;
		}
	}

	err = mfd_add_devices(ec_dev->dev, PLATFORM_DEVID_AUTO, &ec_cell, 1,
			      NULL, ec_dev->irq, NULL);
	if (err) {
		dev_err(dev,
			"Failed to register Embedded Controller subdevice %d\n",
			err);
		return err;
	}

	if (ec_dev->max_passthru) {
		/*
		 * Register a PD device as well on top of this device.
		 * We make the following assumptions:
		 * - behind an EC, we have a pd
		 * - only one device added.
		 * - the EC is responsive at init time (it is not true for a
		 *   sensor hub.
		 */
		err = mfd_add_devices(ec_dev->dev, PLATFORM_DEVID_AUTO,
				      &ec_pd_cell, 1, NULL, ec_dev->irq, NULL);
		if (err) {
			dev_err(dev,
				"Failed to register Power Delivery subdevice %d\n",
				err);
			return err;
		}
	}

	if (IS_ENABLED(CONFIG_OF) && dev->of_node) {
		err = devm_of_platform_populate(dev);
		if (err) {
			mfd_remove_devices(dev);
			dev_err(dev, "Failed to register sub-devices\n");
			return err;
		}
	}

	/*
	 * Clear sleep event - this will fail harmlessly on platforms that
	 * don't implement the sleep event host command.
	 */
	err = cros_ec_sleep_event(ec_dev, 0);
	if (err < 0)
		dev_dbg(ec_dev->dev, "Error %d clearing sleep event to ec",
			err);

	dev_info(dev, "Chrome EC device registered\n");

	return 0;
}
EXPORT_SYMBOL(cros_ec_register);

int cros_ec_remove(struct cros_ec_device *ec_dev)
{
	mfd_remove_devices(ec_dev->dev);

	return 0;
}
EXPORT_SYMBOL(cros_ec_remove);

#ifdef CONFIG_PM_SLEEP
int cros_ec_suspend(struct cros_ec_device *ec_dev)
{
	struct device *dev = ec_dev->dev;
	int ret;
	u8 sleep_event;

	sleep_event = (!IS_ENABLED(CONFIG_ACPI) || pm_suspend_via_firmware()) ?
		      HOST_SLEEP_EVENT_S3_SUSPEND :
		      HOST_SLEEP_EVENT_S0IX_SUSPEND;

	ret = cros_ec_sleep_event(ec_dev, sleep_event);
	if (ret < 0)
		dev_dbg(ec_dev->dev, "Error %d sending suspend event to ec",
			ret);

	if (device_may_wakeup(dev))
		ec_dev->wake_enabled = !enable_irq_wake(ec_dev->irq);

	disable_irq(ec_dev->irq);
	ec_dev->was_wake_device = ec_dev->wake_enabled;
	ec_dev->suspended = true;

	return 0;
}
EXPORT_SYMBOL(cros_ec_suspend);

static void cros_ec_report_events_during_suspend(struct cros_ec_device *ec_dev)
{
	while (cros_ec_get_next_event(ec_dev, NULL) > 0)
		blocking_notifier_call_chain(&ec_dev->event_notifier,
					     1, ec_dev);
}

int cros_ec_resume(struct cros_ec_device *ec_dev)
{
	int ret;
	u8 sleep_event;

	ec_dev->suspended = false;
	enable_irq(ec_dev->irq);

	sleep_event = (!IS_ENABLED(CONFIG_ACPI) || pm_suspend_via_firmware()) ?
		      HOST_SLEEP_EVENT_S3_RESUME :
		      HOST_SLEEP_EVENT_S0IX_RESUME;

	ret = cros_ec_sleep_event(ec_dev, sleep_event);
	if (ret < 0)
		dev_dbg(ec_dev->dev, "Error %d sending resume event to ec",
			ret);

	if (ec_dev->wake_enabled) {
		disable_irq_wake(ec_dev->irq);
		ec_dev->wake_enabled = 0;
	}
	/*
	 * Let the mfd devices know about events that occur during
	 * suspend. This way the clients know what to do with them.
	 */
	cros_ec_report_events_during_suspend(ec_dev);


	return 0;
}
EXPORT_SYMBOL(cros_ec_resume);

#endif

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("ChromeOS EC core driver");
