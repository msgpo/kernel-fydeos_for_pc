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

#ifndef ANDROID_WHITELISTS_H
#define ANDROID_WHITELISTS_H

/*
 * NOTE: the purpose of this header is only to pull out the definition of this
 * array from alt-syscall.c for the purposes of readability. It should not be
 * included in other .c files.
 */

#include "alt-syscall.h"

/*
 * Syscall overrides for android.
 */

/*
 * Reflect the priority adjustment done by android_setpriority.
 * Note that the prio returned by getpriority has been offset by 20.
 * (returns 40..1 instead of -20..19)
 */
static asmlinkage long android_getpriority(int which, int who);
/* Android does not get to call keyctl. */
static asmlinkage long android_keyctl(int cmd, unsigned long arg2,
                                      unsigned long arg3, unsigned long arg4,
                                      unsigned long arg5);
/* Make sure nothing sets a nice value more favorable than -10. */
static asmlinkage long android_setpriority(int which, int who, int niceval);
static asmlinkage long
android_sched_setscheduler(pid_t pid, int policy,
                           struct sched_param __user *param);
static asmlinkage long android_sched_setparam(pid_t pid,
                                              struct sched_param __user *param);
static asmlinkage int __maybe_unused
android_socket(int domain, int type, int socket);
static asmlinkage long
android_perf_event_open(struct perf_event_attr __user *attr_uptr,
                        pid_t pid, int cpu, int group_fd, unsigned long flags);
static asmlinkage long android_adjtimex(struct timex __user *buf);
static asmlinkage long android_clock_adjtime(const clockid_t which_clock,
                                             struct timex __user *buf);
static asmlinkage long android_getcpu(unsigned __user *cpu,
                                      unsigned __user *node,
                                      struct getcpu_cache __user *tcache);
#ifdef CONFIG_COMPAT
static asmlinkage long android_compat_adjtimex(struct compat_timex __user *buf);
static asmlinkage long
android_compat_clock_adjtime(const clockid_t which_clock,
                             struct compat_timex __user *buf);
#endif /* CONFIG_COMPAT */

static struct syscall_whitelist_entry android_whitelist[] = {
	SYSCALL_ENTRY_ALT(adjtimex, android_adjtimex),
	SYSCALL_ENTRY(brk),
	SYSCALL_ENTRY(capget),
	SYSCALL_ENTRY(capset),
	SYSCALL_ENTRY(chdir),
	SYSCALL_ENTRY_ALT(clock_adjtime, android_clock_adjtime),
	SYSCALL_ENTRY(clock_getres),
	SYSCALL_ENTRY(clock_gettime),
	SYSCALL_ENTRY(clock_nanosleep),
	SYSCALL_ENTRY(clock_settime),
	SYSCALL_ENTRY(clone),
	SYSCALL_ENTRY(close),
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
	SYSCALL_ENTRY(fchdir),
	SYSCALL_ENTRY(fchmod),
	SYSCALL_ENTRY(fchmodat),
	SYSCALL_ENTRY(fchownat),
	SYSCALL_ENTRY(fcntl),
	SYSCALL_ENTRY(fdatasync),
	SYSCALL_ENTRY(fgetxattr),
	SYSCALL_ENTRY(flistxattr),
	SYSCALL_ENTRY(flock),
	SYSCALL_ENTRY(fremovexattr),
	SYSCALL_ENTRY(fsetxattr),
	SYSCALL_ENTRY(fstat),
	SYSCALL_ENTRY(fstatfs),
	SYSCALL_ENTRY(fsync),
	SYSCALL_ENTRY(ftruncate),
	SYSCALL_ENTRY(futex),
	SYSCALL_ENTRY_ALT(getcpu, android_getcpu),
	SYSCALL_ENTRY(getcwd),
	SYSCALL_ENTRY(getdents64),
	SYSCALL_ENTRY(getpgid),
	SYSCALL_ENTRY(getpid),
	SYSCALL_ENTRY(getppid),
	SYSCALL_ENTRY_ALT(getpriority, android_getpriority),
        SYSCALL_ENTRY(getrandom),
	SYSCALL_ENTRY(getrlimit),
	SYSCALL_ENTRY(getrusage),
	SYSCALL_ENTRY(getsid),
	SYSCALL_ENTRY(gettid),
	SYSCALL_ENTRY(gettimeofday),
	SYSCALL_ENTRY(getxattr),
	SYSCALL_ENTRY(inotify_add_watch),
	SYSCALL_ENTRY(inotify_init1),
	SYSCALL_ENTRY(inotify_rm_watch),
	SYSCALL_ENTRY(ioctl),
        SYSCALL_ENTRY(io_destroy),
        SYSCALL_ENTRY(io_getevents),
        SYSCALL_ENTRY(io_setup),
        SYSCALL_ENTRY(io_submit),
	SYSCALL_ENTRY(ioprio_set),
        SYSCALL_ENTRY_ALT(keyctl, android_keyctl),
	SYSCALL_ENTRY(kill),
	SYSCALL_ENTRY(lgetxattr),
	SYSCALL_ENTRY(linkat),
	SYSCALL_ENTRY(listxattr),
	SYSCALL_ENTRY(llistxattr),
	SYSCALL_ENTRY(lremovexattr),
	SYSCALL_ENTRY(lseek),
	SYSCALL_ENTRY(lsetxattr),
	SYSCALL_ENTRY(madvise),
        SYSCALL_ENTRY(memfd_create),
	SYSCALL_ENTRY(mincore),
	SYSCALL_ENTRY(mkdirat),
	SYSCALL_ENTRY(mknodat),
	SYSCALL_ENTRY(mlock),
	SYSCALL_ENTRY(mlockall),
	SYSCALL_ENTRY(munlock),
	SYSCALL_ENTRY(munlockall),
	SYSCALL_ENTRY(mount),
	SYSCALL_ENTRY(mprotect),
	SYSCALL_ENTRY(mremap),
	SYSCALL_ENTRY(msync),
	SYSCALL_ENTRY(munmap),
	SYSCALL_ENTRY(name_to_handle_at),
	SYSCALL_ENTRY(nanosleep),
	SYSCALL_ENTRY(open_by_handle_at),
	SYSCALL_ENTRY(openat),
	SYSCALL_ENTRY_ALT(perf_event_open, android_perf_event_open),
	SYSCALL_ENTRY(personality),
	SYSCALL_ENTRY(pipe2),
	SYSCALL_ENTRY(ppoll),
	SYSCALL_ENTRY_ALT(prctl, alt_sys_prctl),
	SYSCALL_ENTRY(pread64),
	SYSCALL_ENTRY(preadv),
	SYSCALL_ENTRY(prlimit64),
	SYSCALL_ENTRY(process_vm_readv),
	SYSCALL_ENTRY(process_vm_writev),
	SYSCALL_ENTRY(pselect6),
	SYSCALL_ENTRY(ptrace),
	SYSCALL_ENTRY(pwrite64),
	SYSCALL_ENTRY(pwritev),
	SYSCALL_ENTRY(read),
	SYSCALL_ENTRY(readahead),
	SYSCALL_ENTRY(readv),
	SYSCALL_ENTRY(readlinkat),
	SYSCALL_ENTRY(recvmmsg),
	SYSCALL_ENTRY(remap_file_pages),
	SYSCALL_ENTRY(removexattr),
	SYSCALL_ENTRY(renameat),
	SYSCALL_ENTRY(restart_syscall),
	SYSCALL_ENTRY(rt_sigaction),
	SYSCALL_ENTRY(rt_sigpending),
	SYSCALL_ENTRY(rt_sigprocmask),
	SYSCALL_ENTRY(rt_sigqueueinfo),
	SYSCALL_ENTRY(rt_sigreturn),
	SYSCALL_ENTRY(rt_sigsuspend),
	SYSCALL_ENTRY(rt_sigtimedwait),
	SYSCALL_ENTRY(rt_tgsigqueueinfo),
	SYSCALL_ENTRY(sched_get_priority_max),
	SYSCALL_ENTRY(sched_get_priority_min),
	SYSCALL_ENTRY(sched_getaffinity),
	SYSCALL_ENTRY(sched_getparam),
	SYSCALL_ENTRY(sched_getscheduler),
	SYSCALL_ENTRY(sched_setaffinity),
        SYSCALL_ENTRY_ALT(sched_setparam, android_sched_setparam),
	SYSCALL_ENTRY_ALT(sched_setscheduler, android_sched_setscheduler),
	SYSCALL_ENTRY(sched_yield),
	SYSCALL_ENTRY(seccomp),
	SYSCALL_ENTRY(sendfile),
	SYSCALL_ENTRY(sendmmsg),
        SYSCALL_ENTRY(setdomainname),
	SYSCALL_ENTRY(set_robust_list),
	SYSCALL_ENTRY(set_tid_address),
	SYSCALL_ENTRY(setitimer),
	SYSCALL_ENTRY(setns),
	SYSCALL_ENTRY(setpgid),
	SYSCALL_ENTRY_ALT(setpriority, android_setpriority),
	SYSCALL_ENTRY(setrlimit),
	SYSCALL_ENTRY(setsid),
	SYSCALL_ENTRY(settimeofday),
	SYSCALL_ENTRY(setxattr),
	SYSCALL_ENTRY(signalfd4),
	SYSCALL_ENTRY(sigaltstack),
	SYSCALL_ENTRY(splice),
	SYSCALL_ENTRY(statfs),
	SYSCALL_ENTRY(symlinkat),
        SYSCALL_ENTRY(sync),
        SYSCALL_ENTRY(syncfs),
	SYSCALL_ENTRY(sysinfo),
	SYSCALL_ENTRY(syslog),
	SYSCALL_ENTRY(tee),
	SYSCALL_ENTRY(tgkill),
	SYSCALL_ENTRY(tkill),
	SYSCALL_ENTRY(timer_create),
	SYSCALL_ENTRY(timer_delete),
	SYSCALL_ENTRY(timer_gettime),
	SYSCALL_ENTRY(timer_getoverrun),
	SYSCALL_ENTRY(timer_settime),
	SYSCALL_ENTRY(timerfd_create),
	SYSCALL_ENTRY(timerfd_gettime),
	SYSCALL_ENTRY(timerfd_settime),
	SYSCALL_ENTRY(times),
	SYSCALL_ENTRY(truncate),
	SYSCALL_ENTRY(umask),
	SYSCALL_ENTRY(umount2),
	SYSCALL_ENTRY(uname),
	SYSCALL_ENTRY(unlinkat),
	SYSCALL_ENTRY(unshare),
	SYSCALL_ENTRY(utimensat),
	SYSCALL_ENTRY(vmsplice),
	SYSCALL_ENTRY(wait4),
	SYSCALL_ENTRY(waitid),
	SYSCALL_ENTRY(write),
	SYSCALL_ENTRY(writev),

	/*
	 * Deprecated syscalls which are not wired up on new architectures
	 * such as ARM64.
	 */
#ifndef CONFIG_ARM64
	SYSCALL_ENTRY(access),
	SYSCALL_ENTRY(chmod),
	SYSCALL_ENTRY(open),
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
	SYSCALL_ENTRY(link),
	SYSCALL_ENTRY(lstat),
	SYSCALL_ENTRY(mkdir),
	SYSCALL_ENTRY(mknod),
	SYSCALL_ENTRY(pipe),
	SYSCALL_ENTRY(poll),
	SYSCALL_ENTRY(readlink),
	SYSCALL_ENTRY(rename),
	SYSCALL_ENTRY(rmdir),
	SYSCALL_ENTRY(stat),
	SYSCALL_ENTRY(symlink),
	SYSCALL_ENTRY(time),
	SYSCALL_ENTRY(unlink),
	SYSCALL_ENTRY(ustat),
	SYSCALL_ENTRY(utimes),
	SYSCALL_ENTRY(vfork),
#endif

	/*
	 * waitpid(2) is deprecated on most architectures, but still exists
	 * on IA32.
	 */
#ifdef CONFIG_X86_32
	SYSCALL_ENTRY(waitpid),
#endif

	/* IA32 uses the common socketcall(2) entrypoint for socket calls. */
#ifdef CONFIG_X86_32
	SYSCALL_ENTRY(socketcall),
#else
	SYSCALL_ENTRY(accept),
	SYSCALL_ENTRY(accept4),
	SYSCALL_ENTRY(bind),
	SYSCALL_ENTRY(connect),
	SYSCALL_ENTRY(getpeername),
	SYSCALL_ENTRY(getsockname),
	SYSCALL_ENTRY(getsockopt),
	SYSCALL_ENTRY(listen),
	SYSCALL_ENTRY(recvfrom),
	SYSCALL_ENTRY(recvmsg),
	SYSCALL_ENTRY(sendmsg),
	SYSCALL_ENTRY(sendto),
	SYSCALL_ENTRY(setsockopt),
	SYSCALL_ENTRY(shutdown),
	SYSCALL_ENTRY_ALT(socket, android_socket),
	SYSCALL_ENTRY(socketpair),
	/*
	 * recv(2)/send(2) are officially deprecated, but their entry-points
	 * still exist on ARM.
	 */
#ifdef CONFIG_ARM
	SYSCALL_ENTRY(recv),
	SYSCALL_ENTRY(send),
#endif
#endif

	/*
	 * posix_fadvise(2) and sync_file_range(2) have ARM-specific wrappers
	 * to deal with register alignment.
	 */
#ifdef CONFIG_ARM
	SYSCALL_ENTRY(arm_fadvise64_64),
	SYSCALL_ENTRY(sync_file_range2),
#else
#ifdef CONFIG_X86_32
	SYSCALL_ENTRY(fadvise64_64),
#endif
	SYSCALL_ENTRY(fadvise64),
	SYSCALL_ENTRY(sync_file_range),
#endif

	/* 64-bit only syscalls. */
#if defined(CONFIG_X86_64) || defined(CONFIG_ARM64)
	SYSCALL_ENTRY(fchown),
	SYSCALL_ENTRY(getegid),
	SYSCALL_ENTRY(geteuid),
	SYSCALL_ENTRY(getgid),
	SYSCALL_ENTRY(getgroups),
	SYSCALL_ENTRY(getresgid),
	SYSCALL_ENTRY(getresuid),
	SYSCALL_ENTRY(getuid),
	SYSCALL_ENTRY(newfstatat),
	SYSCALL_ENTRY(mmap),
	SYSCALL_ENTRY(setgid),
	SYSCALL_ENTRY(setgroups),
	SYSCALL_ENTRY(setregid),
	SYSCALL_ENTRY(setresgid),
	SYSCALL_ENTRY(setresuid),
	SYSCALL_ENTRY(setreuid),
	SYSCALL_ENTRY(setuid),
	/*
	 * chown(2), lchown(2), and select(2) are deprecated and not wired up
	 * on ARM64.
	 */
#ifndef CONFIG_ARM64
	SYSCALL_ENTRY(chown),
	SYSCALL_ENTRY(lchown),
	SYSCALL_ENTRY(select),
#endif
#endif

	/* 32-bit only syscalls. */
#if defined(CONFIG_ARM) || defined(CONFIG_X86_32)
	SYSCALL_ENTRY(chown32),
	SYSCALL_ENTRY(fchown32),
	SYSCALL_ENTRY(fcntl64),
	SYSCALL_ENTRY(fstat64),
	SYSCALL_ENTRY(fstatat64),
	SYSCALL_ENTRY(fstatfs64),
	SYSCALL_ENTRY(ftruncate64),
	SYSCALL_ENTRY(getegid32),
	SYSCALL_ENTRY(geteuid32),
	SYSCALL_ENTRY(getgid32),
	SYSCALL_ENTRY(getgroups32),
	SYSCALL_ENTRY(getresgid32),
	SYSCALL_ENTRY(getresuid32),
	SYSCALL_ENTRY(getuid32),
	SYSCALL_ENTRY(lchown32),
	SYSCALL_ENTRY(lstat64),
	SYSCALL_ENTRY(mmap2),
	SYSCALL_ENTRY(_newselect),
	SYSCALL_ENTRY(_llseek),
	SYSCALL_ENTRY(sigaction),
	SYSCALL_ENTRY(sigpending),
	SYSCALL_ENTRY(sigprocmask),
	SYSCALL_ENTRY(sigreturn),
	SYSCALL_ENTRY(sigsuspend),
	SYSCALL_ENTRY(sendfile64),
	SYSCALL_ENTRY(setgid32),
	SYSCALL_ENTRY(setgroups32),
	SYSCALL_ENTRY(setregid32),
	SYSCALL_ENTRY(setresgid32),
	SYSCALL_ENTRY(setresuid32),
	SYSCALL_ENTRY(setreuid32),
	SYSCALL_ENTRY(setuid32),
	SYSCALL_ENTRY(stat64),
	SYSCALL_ENTRY(statfs64),
	SYSCALL_ENTRY(truncate64),
	SYSCALL_ENTRY(ugetrlimit),
#endif

	/* X86-specific syscalls. */
#ifdef CONFIG_X86
	SYSCALL_ENTRY(modify_ldt),
	SYSCALL_ENTRY(set_thread_area),
#endif

#ifdef CONFIG_X86_64
	SYSCALL_ENTRY(arch_prctl),
#endif
}; /* end android_whitelist */

#ifdef CONFIG_COMPAT
static struct syscall_whitelist_entry android_compat_whitelist[] = {
	COMPAT_SYSCALL_ENTRY(access),
	COMPAT_SYSCALL_ENTRY_ALT(adjtimex, android_compat_adjtimex),
	COMPAT_SYSCALL_ENTRY(brk),
	COMPAT_SYSCALL_ENTRY(capget),
	COMPAT_SYSCALL_ENTRY(capset),
	COMPAT_SYSCALL_ENTRY(chdir),
	COMPAT_SYSCALL_ENTRY(chmod),
	COMPAT_SYSCALL_ENTRY_ALT(clock_adjtime, android_compat_clock_adjtime),
	COMPAT_SYSCALL_ENTRY(clock_getres),
	COMPAT_SYSCALL_ENTRY(clock_gettime),
	COMPAT_SYSCALL_ENTRY(clock_nanosleep),
	COMPAT_SYSCALL_ENTRY(clock_settime),
	COMPAT_SYSCALL_ENTRY(clone),
	COMPAT_SYSCALL_ENTRY(close),
	COMPAT_SYSCALL_ENTRY(creat),
	COMPAT_SYSCALL_ENTRY(dup),
	COMPAT_SYSCALL_ENTRY(dup2),
	COMPAT_SYSCALL_ENTRY(dup3),
	COMPAT_SYSCALL_ENTRY(epoll_create),
	COMPAT_SYSCALL_ENTRY(epoll_create1),
	COMPAT_SYSCALL_ENTRY(epoll_ctl),
	COMPAT_SYSCALL_ENTRY(epoll_wait),
	COMPAT_SYSCALL_ENTRY(epoll_pwait),
	COMPAT_SYSCALL_ENTRY(eventfd),
	COMPAT_SYSCALL_ENTRY(eventfd2),
	COMPAT_SYSCALL_ENTRY(execve),
	COMPAT_SYSCALL_ENTRY(exit),
	COMPAT_SYSCALL_ENTRY(exit_group),
	COMPAT_SYSCALL_ENTRY(faccessat),
	COMPAT_SYSCALL_ENTRY(fallocate),
	COMPAT_SYSCALL_ENTRY(fchdir),
	COMPAT_SYSCALL_ENTRY(fchmod),
	COMPAT_SYSCALL_ENTRY(fchmodat),
	COMPAT_SYSCALL_ENTRY(fchownat),
	COMPAT_SYSCALL_ENTRY(fcntl),
	COMPAT_SYSCALL_ENTRY(fdatasync),
	COMPAT_SYSCALL_ENTRY(fgetxattr),
	COMPAT_SYSCALL_ENTRY(flistxattr),
	COMPAT_SYSCALL_ENTRY(flock),
	COMPAT_SYSCALL_ENTRY(fork),
	COMPAT_SYSCALL_ENTRY(fremovexattr),
	COMPAT_SYSCALL_ENTRY(fsetxattr),
	COMPAT_SYSCALL_ENTRY(fstat),
	COMPAT_SYSCALL_ENTRY(fstatfs),
	COMPAT_SYSCALL_ENTRY(fsync),
	COMPAT_SYSCALL_ENTRY(ftruncate),
	COMPAT_SYSCALL_ENTRY(futex),
	COMPAT_SYSCALL_ENTRY(futimesat),
	COMPAT_SYSCALL_ENTRY_ALT(getcpu, android_getcpu),
	COMPAT_SYSCALL_ENTRY(getcwd),
	COMPAT_SYSCALL_ENTRY(getdents),
	COMPAT_SYSCALL_ENTRY(getdents64),
	COMPAT_SYSCALL_ENTRY(getpgid),
	COMPAT_SYSCALL_ENTRY(getpgrp),
	COMPAT_SYSCALL_ENTRY(getpid),
	COMPAT_SYSCALL_ENTRY(getppid),
	COMPAT_SYSCALL_ENTRY_ALT(getpriority, android_getpriority),
        COMPAT_SYSCALL_ENTRY(getrandom),
	COMPAT_SYSCALL_ENTRY(getrusage),
	COMPAT_SYSCALL_ENTRY(getsid),
	COMPAT_SYSCALL_ENTRY(gettid),
	COMPAT_SYSCALL_ENTRY(gettimeofday),
	COMPAT_SYSCALL_ENTRY(getxattr),
	COMPAT_SYSCALL_ENTRY(inotify_add_watch),
	COMPAT_SYSCALL_ENTRY(inotify_init),
	COMPAT_SYSCALL_ENTRY(inotify_init1),
	COMPAT_SYSCALL_ENTRY(inotify_rm_watch),
	COMPAT_SYSCALL_ENTRY(ioctl),
        COMPAT_SYSCALL_ENTRY(io_destroy),
        COMPAT_SYSCALL_ENTRY(io_getevents),
        COMPAT_SYSCALL_ENTRY(io_setup),
        COMPAT_SYSCALL_ENTRY(io_submit),
	COMPAT_SYSCALL_ENTRY(ioprio_set),
        COMPAT_SYSCALL_ENTRY_ALT(keyctl, android_keyctl),
	COMPAT_SYSCALL_ENTRY(kill),
	COMPAT_SYSCALL_ENTRY(lgetxattr),
	COMPAT_SYSCALL_ENTRY(link),
	COMPAT_SYSCALL_ENTRY(linkat),
	COMPAT_SYSCALL_ENTRY(listxattr),
	COMPAT_SYSCALL_ENTRY(llistxattr),
	COMPAT_SYSCALL_ENTRY(lremovexattr),
	COMPAT_SYSCALL_ENTRY(lseek),
	COMPAT_SYSCALL_ENTRY(lsetxattr),
	COMPAT_SYSCALL_ENTRY(lstat),
	COMPAT_SYSCALL_ENTRY(madvise),
        COMPAT_SYSCALL_ENTRY(memfd_create),
	COMPAT_SYSCALL_ENTRY(mincore),
	COMPAT_SYSCALL_ENTRY(mkdir),
	COMPAT_SYSCALL_ENTRY(mkdirat),
	COMPAT_SYSCALL_ENTRY(mknod),
	COMPAT_SYSCALL_ENTRY(mknodat),
	COMPAT_SYSCALL_ENTRY(mlock),
	COMPAT_SYSCALL_ENTRY(mlockall),
	COMPAT_SYSCALL_ENTRY(munlock),
	COMPAT_SYSCALL_ENTRY(munlockall),
	COMPAT_SYSCALL_ENTRY(mount),
	COMPAT_SYSCALL_ENTRY(mprotect),
	COMPAT_SYSCALL_ENTRY(mremap),
	COMPAT_SYSCALL_ENTRY(msync),
	COMPAT_SYSCALL_ENTRY(munmap),
	COMPAT_SYSCALL_ENTRY(name_to_handle_at),
	COMPAT_SYSCALL_ENTRY(nanosleep),
	COMPAT_SYSCALL_ENTRY(open),
	COMPAT_SYSCALL_ENTRY(open_by_handle_at),
	COMPAT_SYSCALL_ENTRY(openat),
	COMPAT_SYSCALL_ENTRY_ALT(perf_event_open, android_perf_event_open),
	COMPAT_SYSCALL_ENTRY(personality),
	COMPAT_SYSCALL_ENTRY(pipe),
	COMPAT_SYSCALL_ENTRY(pipe2),
	COMPAT_SYSCALL_ENTRY(poll),
	COMPAT_SYSCALL_ENTRY(ppoll),
	COMPAT_SYSCALL_ENTRY_ALT(prctl, alt_sys_prctl),
	COMPAT_SYSCALL_ENTRY(pread64),
	COMPAT_SYSCALL_ENTRY(preadv),
	COMPAT_SYSCALL_ENTRY(prlimit64),
	COMPAT_SYSCALL_ENTRY(process_vm_readv),
	COMPAT_SYSCALL_ENTRY(process_vm_writev),
	COMPAT_SYSCALL_ENTRY(pselect6),
	COMPAT_SYSCALL_ENTRY(ptrace),
	COMPAT_SYSCALL_ENTRY(pwrite64),
	COMPAT_SYSCALL_ENTRY(pwritev),
	COMPAT_SYSCALL_ENTRY(read),
	COMPAT_SYSCALL_ENTRY(readahead),
	COMPAT_SYSCALL_ENTRY(readv),
	COMPAT_SYSCALL_ENTRY(readlink),
	COMPAT_SYSCALL_ENTRY(readlinkat),
	COMPAT_SYSCALL_ENTRY(recvmmsg),
	COMPAT_SYSCALL_ENTRY(remap_file_pages),
	COMPAT_SYSCALL_ENTRY(removexattr),
	COMPAT_SYSCALL_ENTRY(rename),
	COMPAT_SYSCALL_ENTRY(renameat),
	COMPAT_SYSCALL_ENTRY(restart_syscall),
	COMPAT_SYSCALL_ENTRY(rmdir),
	COMPAT_SYSCALL_ENTRY(rt_sigaction),
	COMPAT_SYSCALL_ENTRY(rt_sigpending),
	COMPAT_SYSCALL_ENTRY(rt_sigprocmask),
	COMPAT_SYSCALL_ENTRY(rt_sigqueueinfo),
	COMPAT_SYSCALL_ENTRY(rt_sigreturn),
	COMPAT_SYSCALL_ENTRY(rt_sigsuspend),
	COMPAT_SYSCALL_ENTRY(rt_sigtimedwait),
	COMPAT_SYSCALL_ENTRY(rt_tgsigqueueinfo),
	COMPAT_SYSCALL_ENTRY(sched_get_priority_max),
	COMPAT_SYSCALL_ENTRY(sched_get_priority_min),
	COMPAT_SYSCALL_ENTRY(sched_getaffinity),
	COMPAT_SYSCALL_ENTRY(sched_getparam),
	COMPAT_SYSCALL_ENTRY(sched_getscheduler),
	COMPAT_SYSCALL_ENTRY(sched_setaffinity),
        COMPAT_SYSCALL_ENTRY_ALT(sched_setparam,
                                 android_sched_setparam),
	COMPAT_SYSCALL_ENTRY_ALT(sched_setscheduler,
				 android_sched_setscheduler),
	COMPAT_SYSCALL_ENTRY(sched_yield),
	COMPAT_SYSCALL_ENTRY(seccomp),
	COMPAT_SYSCALL_ENTRY(sendfile),
	COMPAT_SYSCALL_ENTRY(sendfile64),
	COMPAT_SYSCALL_ENTRY(sendmmsg),
        COMPAT_SYSCALL_ENTRY(setdomainname),
	COMPAT_SYSCALL_ENTRY(set_robust_list),
	COMPAT_SYSCALL_ENTRY(set_tid_address),
	COMPAT_SYSCALL_ENTRY(setitimer),
	COMPAT_SYSCALL_ENTRY(setns),
	COMPAT_SYSCALL_ENTRY(setpgid),
	COMPAT_SYSCALL_ENTRY_ALT(setpriority, android_setpriority),
	COMPAT_SYSCALL_ENTRY(setrlimit),
	COMPAT_SYSCALL_ENTRY(setsid),
	COMPAT_SYSCALL_ENTRY(settimeofday),
	COMPAT_SYSCALL_ENTRY(setxattr),
	COMPAT_SYSCALL_ENTRY(signalfd4),
	COMPAT_SYSCALL_ENTRY(sigaltstack),
	COMPAT_SYSCALL_ENTRY(splice),
	COMPAT_SYSCALL_ENTRY(stat),
	COMPAT_SYSCALL_ENTRY(statfs),
	COMPAT_SYSCALL_ENTRY(symlink),
	COMPAT_SYSCALL_ENTRY(symlinkat),
        COMPAT_SYSCALL_ENTRY(sync),
        COMPAT_SYSCALL_ENTRY(syncfs),
	COMPAT_SYSCALL_ENTRY(sysinfo),
	COMPAT_SYSCALL_ENTRY(syslog),
	COMPAT_SYSCALL_ENTRY(tgkill),
	COMPAT_SYSCALL_ENTRY(tee),
	COMPAT_SYSCALL_ENTRY(tkill),
	COMPAT_SYSCALL_ENTRY(timer_create),
	COMPAT_SYSCALL_ENTRY(timer_delete),
	COMPAT_SYSCALL_ENTRY(timer_gettime),
	COMPAT_SYSCALL_ENTRY(timer_getoverrun),
	COMPAT_SYSCALL_ENTRY(timer_settime),
	COMPAT_SYSCALL_ENTRY(timerfd_create),
	COMPAT_SYSCALL_ENTRY(timerfd_gettime),
	COMPAT_SYSCALL_ENTRY(timerfd_settime),
	COMPAT_SYSCALL_ENTRY(times),
	COMPAT_SYSCALL_ENTRY(truncate),
	COMPAT_SYSCALL_ENTRY(umask),
	COMPAT_SYSCALL_ENTRY(umount2),
	COMPAT_SYSCALL_ENTRY(uname),
	COMPAT_SYSCALL_ENTRY(unlink),
	COMPAT_SYSCALL_ENTRY(unlinkat),
	COMPAT_SYSCALL_ENTRY(unshare),
	COMPAT_SYSCALL_ENTRY(ustat),
	COMPAT_SYSCALL_ENTRY(utimensat),
	COMPAT_SYSCALL_ENTRY(utimes),
	COMPAT_SYSCALL_ENTRY(vfork),
	COMPAT_SYSCALL_ENTRY(vmsplice),
	COMPAT_SYSCALL_ENTRY(wait4),
	COMPAT_SYSCALL_ENTRY(waitid),
	COMPAT_SYSCALL_ENTRY(write),
	COMPAT_SYSCALL_ENTRY(writev),
	COMPAT_SYSCALL_ENTRY(chown32),
	COMPAT_SYSCALL_ENTRY(fchown32),
	COMPAT_SYSCALL_ENTRY(fcntl64),
	COMPAT_SYSCALL_ENTRY(fstat64),
	COMPAT_SYSCALL_ENTRY(fstatat64),
	COMPAT_SYSCALL_ENTRY(fstatfs64),
	COMPAT_SYSCALL_ENTRY(ftruncate64),
	COMPAT_SYSCALL_ENTRY(getegid),
	COMPAT_SYSCALL_ENTRY(getegid32),
	COMPAT_SYSCALL_ENTRY(geteuid),
	COMPAT_SYSCALL_ENTRY(geteuid32),
	COMPAT_SYSCALL_ENTRY(getgid),
	COMPAT_SYSCALL_ENTRY(getgid32),
	COMPAT_SYSCALL_ENTRY(getgroups32),
	COMPAT_SYSCALL_ENTRY(getresgid32),
	COMPAT_SYSCALL_ENTRY(getresuid32),
	COMPAT_SYSCALL_ENTRY(getuid),
	COMPAT_SYSCALL_ENTRY(getuid32),
	COMPAT_SYSCALL_ENTRY(lchown32),
	COMPAT_SYSCALL_ENTRY(lstat64),
	COMPAT_SYSCALL_ENTRY(mmap2),
	COMPAT_SYSCALL_ENTRY(_newselect),
	COMPAT_SYSCALL_ENTRY(_llseek),
	COMPAT_SYSCALL_ENTRY(sigaction),
	COMPAT_SYSCALL_ENTRY(sigpending),
	COMPAT_SYSCALL_ENTRY(sigprocmask),
	COMPAT_SYSCALL_ENTRY(sigreturn),
	COMPAT_SYSCALL_ENTRY(sigsuspend),
	COMPAT_SYSCALL_ENTRY(setgid32),
	COMPAT_SYSCALL_ENTRY(setgroups32),
	COMPAT_SYSCALL_ENTRY(setregid32),
	COMPAT_SYSCALL_ENTRY(setresgid32),
	COMPAT_SYSCALL_ENTRY(setresuid32),
	COMPAT_SYSCALL_ENTRY(setreuid32),
	COMPAT_SYSCALL_ENTRY(setuid32),
	COMPAT_SYSCALL_ENTRY(stat64),
	COMPAT_SYSCALL_ENTRY(statfs64),
	COMPAT_SYSCALL_ENTRY(truncate64),
	COMPAT_SYSCALL_ENTRY(ugetrlimit),

	/*
	 * waitpid(2) is deprecated on most architectures, but still exists
	 * on IA32.
	 */
#ifdef CONFIG_X86
	COMPAT_SYSCALL_ENTRY(waitpid),
#endif

	/*
	 * posix_fadvise(2) and sync_file_range(2) have ARM-specific wrappers
	 * to deal with register alignment.
	 */
#ifdef CONFIG_ARM64
	COMPAT_SYSCALL_ENTRY(arm_fadvise64_64),
	COMPAT_SYSCALL_ENTRY(sync_file_range2),
#else
	COMPAT_SYSCALL_ENTRY(fadvise64_64),
	COMPAT_SYSCALL_ENTRY(fadvise64),
	COMPAT_SYSCALL_ENTRY(sync_file_range),
#endif

	/* IA32 uses the common socketcall(2) entrypoint for socket calls. */
#ifdef CONFIG_X86
	COMPAT_SYSCALL_ENTRY(socketcall),
#else
	COMPAT_SYSCALL_ENTRY(accept),
	COMPAT_SYSCALL_ENTRY(accept4),
	COMPAT_SYSCALL_ENTRY(bind),
	COMPAT_SYSCALL_ENTRY(connect),
	COMPAT_SYSCALL_ENTRY(getpeername),
	COMPAT_SYSCALL_ENTRY(getsockname),
	COMPAT_SYSCALL_ENTRY(getsockopt),
	COMPAT_SYSCALL_ENTRY(listen),
	COMPAT_SYSCALL_ENTRY(recvfrom),
	COMPAT_SYSCALL_ENTRY(recvmsg),
	COMPAT_SYSCALL_ENTRY(sendmsg),
	COMPAT_SYSCALL_ENTRY(sendto),
	COMPAT_SYSCALL_ENTRY(setsockopt),
	COMPAT_SYSCALL_ENTRY(shutdown),
	COMPAT_SYSCALL_ENTRY(socket),
	COMPAT_SYSCALL_ENTRY(socketpair),
	COMPAT_SYSCALL_ENTRY(recv),
	COMPAT_SYSCALL_ENTRY(send),
#endif

	/*
	 * getrlimit(2) and time(2) are deprecated and not wired in the ARM
         * compat table on ARM64.
	 */
#ifndef CONFIG_ARM64
	COMPAT_SYSCALL_ENTRY(getrlimit),
        COMPAT_SYSCALL_ENTRY(time),
#endif

	/* x86-specific syscalls. */
#ifdef CONFIG_X86
	COMPAT_SYSCALL_ENTRY(modify_ldt),
	COMPAT_SYSCALL_ENTRY(set_thread_area),
#endif
}; /* end android_compat_whitelist */
#endif /* CONFIG_COMPAT */

#endif /* ANDROID_WHITELISTS_H */
