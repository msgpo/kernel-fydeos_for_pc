/*
 * Linux Security Module for Chromium OS
 *
 * Copyright 2018 Google LLC. All Rights Reserved
 *
 * Authors:
 *      Micah Morton <mortonm@chromium.org>
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#ifndef COMPLETE_WHITELISTS_H
#define COMPLETE_WHITELISTS_H

/*
 * NOTE: the purpose of this header is only to pull out the definition of this
 * array from alt-syscall.c for the purposes of readability. It should not be
 * included in other .c files.
 */

#include "alt-syscall.h"

static struct syscall_whitelist_entry complete_whitelist[] = {
	/* Syscalls wired up on ARM32/ARM64 and x86_64. */
	SYSCALL_ENTRY(accept),
	SYSCALL_ENTRY(accept4),
	SYSCALL_ENTRY(acct),
	SYSCALL_ENTRY(add_key),
	SYSCALL_ENTRY(adjtimex),
	SYSCALL_ENTRY(bind),
	SYSCALL_ENTRY(brk),
	SYSCALL_ENTRY(capget),
	SYSCALL_ENTRY(capset),
	SYSCALL_ENTRY(chdir),
	SYSCALL_ENTRY(chroot),
	SYSCALL_ENTRY(clock_adjtime),
	SYSCALL_ENTRY(clock_getres),
	SYSCALL_ENTRY(clock_gettime),
	SYSCALL_ENTRY(clock_nanosleep),
	SYSCALL_ENTRY(clock_settime),
	SYSCALL_ENTRY(clone),
	SYSCALL_ENTRY(close),
	SYSCALL_ENTRY(connect),
	SYSCALL_ENTRY(copy_file_range),
	SYSCALL_ENTRY(delete_module),
	SYSCALL_ENTRY(dup),
	SYSCALL_ENTRY(dup3),
	SYSCALL_ENTRY(epoll_create1),
	SYSCALL_ENTRY(epoll_ctl),
	SYSCALL_ENTRY(epoll_pwait),
	SYSCALL_ENTRY(eventfd2),
	SYSCALL_ENTRY(execve),
	SYSCALL_ENTRY(exit),
	SYSCALL_ENTRY(exit_group),
	SYSCALL_ENTRY(faccessat),
	SYSCALL_ENTRY(fallocate),
	SYSCALL_ENTRY(fanotify_init),
	SYSCALL_ENTRY(fanotify_mark),
	SYSCALL_ENTRY(fchdir),
	SYSCALL_ENTRY(fchmod),
	SYSCALL_ENTRY(fchmodat),
	SYSCALL_ENTRY(fchown),
	SYSCALL_ENTRY(fchownat),
	SYSCALL_ENTRY(fcntl),
	SYSCALL_ENTRY(fdatasync),
	SYSCALL_ENTRY(fgetxattr),
	SYSCALL_ENTRY(finit_module),
	SYSCALL_ENTRY(flistxattr),
	SYSCALL_ENTRY(flock),
	SYSCALL_ENTRY(fremovexattr),
	SYSCALL_ENTRY(fsetxattr),
	SYSCALL_ENTRY(fstatfs),
	SYSCALL_ENTRY(fsync),
	SYSCALL_ENTRY(ftruncate),
	SYSCALL_ENTRY(futex),
	SYSCALL_ENTRY(getcpu),
	SYSCALL_ENTRY(getcwd),
	SYSCALL_ENTRY(getdents64),
	SYSCALL_ENTRY(getegid),
	SYSCALL_ENTRY(geteuid),
	SYSCALL_ENTRY(getgid),
	SYSCALL_ENTRY(getgroups),
	SYSCALL_ENTRY(getitimer),
	SYSCALL_ENTRY(get_mempolicy),
	SYSCALL_ENTRY(getpeername),
	SYSCALL_ENTRY(getpgid),
	SYSCALL_ENTRY(getpid),
	SYSCALL_ENTRY(getppid),
	SYSCALL_ENTRY(getpriority),
	SYSCALL_ENTRY(getrandom),
	SYSCALL_ENTRY(getresgid),
	SYSCALL_ENTRY(getresuid),
	SYSCALL_ENTRY(getrlimit),
	SYSCALL_ENTRY(get_robust_list),
	SYSCALL_ENTRY(getrusage),
	SYSCALL_ENTRY(getsid),
	SYSCALL_ENTRY(getsockname),
	SYSCALL_ENTRY(getsockopt),
	SYSCALL_ENTRY(gettid),
	SYSCALL_ENTRY(gettimeofday),
	SYSCALL_ENTRY(getuid),
	SYSCALL_ENTRY(getxattr),
	SYSCALL_ENTRY(init_module),
	SYSCALL_ENTRY(inotify_add_watch),
	SYSCALL_ENTRY(inotify_init1),
	SYSCALL_ENTRY(inotify_rm_watch),
	SYSCALL_ENTRY(io_cancel),
	SYSCALL_ENTRY(ioctl),
	SYSCALL_ENTRY(io_destroy),
	SYSCALL_ENTRY(io_getevents),
	SYSCALL_ENTRY(ioprio_get),
	SYSCALL_ENTRY(ioprio_set),
	SYSCALL_ENTRY(io_setup),
	SYSCALL_ENTRY(io_submit),
	SYSCALL_ENTRY(kcmp),
	SYSCALL_ENTRY(kexec_load),
	SYSCALL_ENTRY(keyctl),
	SYSCALL_ENTRY(kill),
	SYSCALL_ENTRY(lgetxattr),
	SYSCALL_ENTRY(linkat),
	SYSCALL_ENTRY(listen),
	SYSCALL_ENTRY(listxattr),
	SYSCALL_ENTRY(llistxattr),
	SYSCALL_ENTRY(lookup_dcookie),
	SYSCALL_ENTRY(lremovexattr),
	SYSCALL_ENTRY(lseek),
	SYSCALL_ENTRY(lsetxattr),
	SYSCALL_ENTRY(madvise),
	SYSCALL_ENTRY(mbind),
	SYSCALL_ENTRY(memfd_create),
	SYSCALL_ENTRY(mincore),
	SYSCALL_ENTRY(mkdirat),
	SYSCALL_ENTRY(mknodat),
	SYSCALL_ENTRY(mlock),
	SYSCALL_ENTRY(mlockall),
	SYSCALL_ENTRY(mount),
	SYSCALL_ENTRY(move_pages),
	SYSCALL_ENTRY(mprotect),
	SYSCALL_ENTRY(mq_getsetattr),
	SYSCALL_ENTRY(mq_notify),
	SYSCALL_ENTRY(mq_open),
	SYSCALL_ENTRY(mq_timedreceive),
	SYSCALL_ENTRY(mq_timedsend),
	SYSCALL_ENTRY(mq_unlink),
	SYSCALL_ENTRY(mremap),
	SYSCALL_ENTRY(msgctl),
	SYSCALL_ENTRY(msgget),
	SYSCALL_ENTRY(msgrcv),
	SYSCALL_ENTRY(msgsnd),
	SYSCALL_ENTRY(msync),
	SYSCALL_ENTRY(munlock),
	SYSCALL_ENTRY(munlockall),
	SYSCALL_ENTRY(munmap),
	SYSCALL_ENTRY(name_to_handle_at),
	SYSCALL_ENTRY(nanosleep),
	SYSCALL_ENTRY(openat),
	SYSCALL_ENTRY(open_by_handle_at),
	SYSCALL_ENTRY(perf_event_open),
	SYSCALL_ENTRY(personality),
	SYSCALL_ENTRY(pipe2),
	SYSCALL_ENTRY(pivot_root),
	SYSCALL_ENTRY(pkey_alloc),
	SYSCALL_ENTRY(pkey_free),
	SYSCALL_ENTRY(pkey_mprotect),
	SYSCALL_ENTRY(ppoll),
	SYSCALL_ENTRY_ALT(prctl, alt_sys_prctl),
	SYSCALL_ENTRY(pread64),
	SYSCALL_ENTRY(preadv),
	SYSCALL_ENTRY(preadv2),
	SYSCALL_ENTRY(pwritev2),
	SYSCALL_ENTRY(prlimit64),
	SYSCALL_ENTRY(process_vm_readv),
	SYSCALL_ENTRY(process_vm_writev),
	SYSCALL_ENTRY(pselect6),
	SYSCALL_ENTRY(ptrace),
	SYSCALL_ENTRY(pwrite64),
	SYSCALL_ENTRY(pwritev),
	SYSCALL_ENTRY(quotactl),
	SYSCALL_ENTRY(read),
	SYSCALL_ENTRY(readahead),
	SYSCALL_ENTRY(readlinkat),
	SYSCALL_ENTRY(readv),
	SYSCALL_ENTRY(reboot),
	SYSCALL_ENTRY(recvfrom),
	SYSCALL_ENTRY(recvmmsg),
	SYSCALL_ENTRY(recvmsg),
	SYSCALL_ENTRY(remap_file_pages),
	SYSCALL_ENTRY(removexattr),
	SYSCALL_ENTRY(renameat),
	SYSCALL_ENTRY(request_key),
	SYSCALL_ENTRY(restart_syscall),
	SYSCALL_ENTRY(rt_sigaction),
	SYSCALL_ENTRY(rt_sigpending),
	SYSCALL_ENTRY(rt_sigprocmask),
	SYSCALL_ENTRY(rt_sigqueueinfo),
	SYSCALL_ENTRY(rt_sigsuspend),
	SYSCALL_ENTRY(rt_sigtimedwait),
	SYSCALL_ENTRY(rt_tgsigqueueinfo),
	SYSCALL_ENTRY(sched_getaffinity),
	SYSCALL_ENTRY(sched_getattr),
	SYSCALL_ENTRY(sched_getparam),
	SYSCALL_ENTRY(sched_get_priority_max),
	SYSCALL_ENTRY(sched_get_priority_min),
	SYSCALL_ENTRY(sched_getscheduler),
	SYSCALL_ENTRY(sched_rr_get_interval),
	SYSCALL_ENTRY(sched_setaffinity),
	SYSCALL_ENTRY(sched_setattr),
	SYSCALL_ENTRY(sched_setparam),
	SYSCALL_ENTRY(sched_setscheduler),
	SYSCALL_ENTRY(sched_yield),
	SYSCALL_ENTRY(seccomp),
	SYSCALL_ENTRY(semctl),
	SYSCALL_ENTRY(semget),
	SYSCALL_ENTRY(semop),
	SYSCALL_ENTRY(semtimedop),
	SYSCALL_ENTRY(sendfile),
	SYSCALL_ENTRY(sendmmsg),
	SYSCALL_ENTRY(sendmsg),
	SYSCALL_ENTRY(sendto),
	SYSCALL_ENTRY(setdomainname),
	SYSCALL_ENTRY(setfsgid),
	SYSCALL_ENTRY(setfsuid),
	SYSCALL_ENTRY(setgid),
	SYSCALL_ENTRY(setgroups),
	SYSCALL_ENTRY(sethostname),
	SYSCALL_ENTRY(setitimer),
	SYSCALL_ENTRY(set_mempolicy),
	SYSCALL_ENTRY(setns),
	SYSCALL_ENTRY(setpgid),
	SYSCALL_ENTRY(setpriority),
	SYSCALL_ENTRY(setregid),
	SYSCALL_ENTRY(setresgid),
	SYSCALL_ENTRY(setresuid),
	SYSCALL_ENTRY(setreuid),
	SYSCALL_ENTRY(setrlimit),
	SYSCALL_ENTRY(set_robust_list),
	SYSCALL_ENTRY(setsid),
	SYSCALL_ENTRY(setsockopt),
	SYSCALL_ENTRY(set_tid_address),
	SYSCALL_ENTRY(settimeofday),
	SYSCALL_ENTRY(setuid),
	SYSCALL_ENTRY(setxattr),
	SYSCALL_ENTRY(shmat),
	SYSCALL_ENTRY(shmctl),
	SYSCALL_ENTRY(shmdt),
	SYSCALL_ENTRY(shmget),
	SYSCALL_ENTRY(shutdown),
	SYSCALL_ENTRY(sigaltstack),
	SYSCALL_ENTRY(signalfd4),
	SYSCALL_ENTRY(socket),
	SYSCALL_ENTRY(socketpair),
	SYSCALL_ENTRY(splice),
	SYSCALL_ENTRY(statfs),
	SYSCALL_ENTRY(statx),
	SYSCALL_ENTRY(swapoff),
	SYSCALL_ENTRY(swapon),
	SYSCALL_ENTRY(symlinkat),
	SYSCALL_ENTRY(sync),
	SYSCALL_ENTRY(syncfs),
	SYSCALL_ENTRY(sysinfo),
	SYSCALL_ENTRY(syslog),
	SYSCALL_ENTRY(tee),
	SYSCALL_ENTRY(tgkill),
	SYSCALL_ENTRY(timer_create),
	SYSCALL_ENTRY(timer_delete),
	SYSCALL_ENTRY(timerfd_create),
	SYSCALL_ENTRY(timerfd_gettime),
	SYSCALL_ENTRY(timerfd_settime),
	SYSCALL_ENTRY(timer_getoverrun),
	SYSCALL_ENTRY(timer_gettime),
	SYSCALL_ENTRY(timer_settime),
	SYSCALL_ENTRY(times),
	SYSCALL_ENTRY(tkill),
	SYSCALL_ENTRY(truncate),
	SYSCALL_ENTRY(umask),
	SYSCALL_ENTRY(unlinkat),
	SYSCALL_ENTRY(unshare),
	SYSCALL_ENTRY(utimensat),
	SYSCALL_ENTRY(vhangup),
	SYSCALL_ENTRY(vmsplice),
	SYSCALL_ENTRY(wait4),
	SYSCALL_ENTRY(waitid),
	SYSCALL_ENTRY(write),
	SYSCALL_ENTRY(writev),

	/* Exist for x86_64 and ARM32 but not ARM64. */
#ifndef CONFIG_ARM64
	SYSCALL_ENTRY(access),
	SYSCALL_ENTRY(alarm),
	SYSCALL_ENTRY(chmod),
	SYSCALL_ENTRY(chown),
	SYSCALL_ENTRY(creat),
	SYSCALL_ENTRY(dup2),
	SYSCALL_ENTRY(epoll_create),
	SYSCALL_ENTRY(epoll_wait),
	SYSCALL_ENTRY(eventfd),
	SYSCALL_ENTRY(fork),
	SYSCALL_ENTRY(futimesat),
	SYSCALL_ENTRY(getdents),
	SYSCALL_ENTRY(getpgrp),
	SYSCALL_ENTRY(inotify_init),
	SYSCALL_ENTRY(lchown),
	SYSCALL_ENTRY(link),
	SYSCALL_ENTRY(mkdir),
	SYSCALL_ENTRY(mknod),
	SYSCALL_ENTRY(open),
	SYSCALL_ENTRY(pause),
	SYSCALL_ENTRY(pipe),
	SYSCALL_ENTRY(poll),
	SYSCALL_ENTRY(readlink),
	SYSCALL_ENTRY(rename),
	SYSCALL_ENTRY(rmdir),
	SYSCALL_ENTRY(select),
	SYSCALL_ENTRY(signalfd),
	SYSCALL_ENTRY(symlink),
	SYSCALL_ENTRY(sysfs),
	SYSCALL_ENTRY(time),
	SYSCALL_ENTRY(unlink),
	SYSCALL_ENTRY(ustat),
	SYSCALL_ENTRY(utime),
	SYSCALL_ENTRY(utimes),
	SYSCALL_ENTRY(vfork),
#endif

	/* Exist for x86_64 and ARM64 but not ARM32 */
#if !defined(CONFIG_ARM) && (defined(CONFIG_ARM64) || defined(CONFIG_X86_64))
	SYSCALL_ENTRY(fadvise64),
	SYSCALL_ENTRY(fstat),
	SYSCALL_ENTRY(migrate_pages),
	SYSCALL_ENTRY(mmap),
	SYSCALL_ENTRY(rt_sigreturn),
	SYSCALL_ENTRY(sync_file_range),
	SYSCALL_ENTRY(umount2),
	SYSCALL_ENTRY(uname),
#endif

	/* Unique to ARM32. */
#if defined(CONFIG_ARM) && !defined(CONFIG_ARM64)
	SYSCALL_ENTRY(arm_fadvise64_64),
	SYSCALL_ENTRY(bdflush),
	SYSCALL_ENTRY(fcntl64),
	SYSCALL_ENTRY(fstat64),
	SYSCALL_ENTRY(fstatat64),
	SYSCALL_ENTRY(ftruncate64),
	SYSCALL_ENTRY(ipc),
	SYSCALL_ENTRY(lstat64),
	SYSCALL_ENTRY(mmap2),
	SYSCALL_ENTRY(nice),
	SYSCALL_ENTRY(pciconfig_iobase),
	SYSCALL_ENTRY(pciconfig_read),
	SYSCALL_ENTRY(pciconfig_write),
	SYSCALL_ENTRY(recv),
	SYSCALL_ENTRY(send),
	SYSCALL_ENTRY(sendfile64),
	SYSCALL_ENTRY(sigaction),
	SYSCALL_ENTRY(sigpending),
	SYSCALL_ENTRY(sigprocmask),
	SYSCALL_ENTRY(sigsuspend),
	SYSCALL_ENTRY(socketcall),
	SYSCALL_ENTRY(stat64),
	SYSCALL_ENTRY(stime),
	SYSCALL_ENTRY(syscall),
	SYSCALL_ENTRY(truncate64),
	SYSCALL_ENTRY(umount),
	SYSCALL_ENTRY(uselib),
#endif

	/* Unique to x86_64. */
#ifdef CONFIG_X86_64
	SYSCALL_ENTRY(arch_prctl),
	SYSCALL_ENTRY(ioperm),
	SYSCALL_ENTRY(iopl),
	SYSCALL_ENTRY(kexec_file_load),
	SYSCALL_ENTRY(lstat),
	SYSCALL_ENTRY(modify_ldt),
	SYSCALL_ENTRY(newfstatat),
	SYSCALL_ENTRY(stat),
	SYSCALL_ENTRY(_sysctl),
#endif

	/* Unique to ARM64. */
#if defined(CONFIG_ARM64) && !defined(CONFIG_ARM)
	SYSCALL_ENTRY(nfsservctl),
	SYSCALL_ENTRY(renameat2),
#endif
}; /* end complete_whitelist */

#ifdef CONFIG_COMPAT
/*
 * For now not adding a 32-bit-compatible version of the complete whitelist.
 * Since we are not whitelisting any compat syscalls here, a call into the
 * compat section of this "complete" alt syscall table will be redirected to
 * block_syscall() (unless the permissive mode is used in which case the call
 * will be redirected to warn_compat_syscall()).
 */
static struct syscall_whitelist_entry complete_compat_whitelist[] = {};
#endif /* CONFIG_COMPAT */

#endif /* COMPLETE_WHITELISTS_H */
