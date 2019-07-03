/*
 * mt6797-afe-common.h  --  Mediatek 6797 audio driver definitions
 *
 * Copyright (c) 2018 MediaTek Inc.
 * Author: KaiChieh Chuang <kaichieh.chuang@mediatek.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#ifndef _MT_6797_AFE_COMMON_H_
#define _MT_6797_AFE_COMMON_H_

#include <sound/soc.h>
#include <linux/regmap.h>
#include "../common/mtk-base-afe.h"

enum {
	MT6797_MEMIF_DL1,
	MT6797_MEMIF_DL2,
	MT6797_MEMIF_DL3,
	MT6797_MEMIF_VUL,
	MT6797_MEMIF_AWB,
	MT6797_MEMIF_VUL12,
	MT6797_MEMIF_DAI,
	MT6797_MEMIF_MOD_DAI,
	MT6797_MEMIF_NUM,
	MT6797_DAI_ADDA = MT6797_MEMIF_NUM,
	MT6797_DAI_NUM,
};

enum {
	MT6797_IRQ_1,
	MT6797_IRQ_2,
	MT6797_IRQ_3,
	MT6797_IRQ_4,
	MT6797_IRQ_7,
	MT6797_IRQ_NUM,
};

struct clk;

struct mt6797_afe_private {
	struct clk **clk;
};

unsigned int mt6797_general_rate_transform(struct device *dev,
					   unsigned int rate);
unsigned int mt6797_rate_transform(struct device *dev,
				   unsigned int rate, int aud_blk);
#endif
