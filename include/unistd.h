/*-
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Copyright (c) 1991, 1993, 1994
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#ifndef _UNISTD_H_
#define	_UNISTD_H_

#include <sys/types.h>			/* XXX adds too much pollution. */
#include <sys/unistd.h>
#include <sys/_null.h>
#include <sys/_types.h>

#if !defined(_STANDALONE) && defined(_FORTIFY_SOURCE) && _FORTIFY_SOURCE > 0
#include <ssp/unistd.h>
#endif

#ifndef _GID_T_DECLARED
typedef	__gid_t		gid_t;
#define	_GID_T_DECLARED
#endif

#ifndef _OFF_T_DECLARED
typedef	__off_t		off_t;
#define	_OFF_T_DECLARED
#endif

#ifndef _PID_T_DECLARED
typedef	__pid_t		pid_t;
#define	_PID_T_DECLARED
#endif

#ifndef _SIZE_T_DECLARED
typedef	__size_t	size_t;
#define	_SIZE_T_DECLARED
#endif

#ifndef _SSIZE_T_DECLARED
typedef	__ssize_t	ssize_t;
#define	_SSIZE_T_DECLARED
#endif

#ifndef _UID_T_DECLARED
typedef	__uid_t		uid_t;
#define	_UID_T_DECLARED
#endif

#ifndef _USECONDS_T_DECLARED
typedef	__useconds_t	useconds_t;
#define	_USECONDS_T_DECLARED
#endif

#define	STDIN_FILENO	0	/* standard input file descriptor */
#define	STDOUT_FILENO	1	/* standard output file descriptor */
#define	STDERR_FILENO	2	/* standard error file descriptor */

#if __XSI_VISIBLE || __POSIX_VISIBLE >= 200112
#define	F_ULOCK		0	/* unlock locked section */
#define	F_LOCK		1	/* lock a section for exclusive use */
#define	F_TLOCK		2	/* test and lock a section for exclusive use */
#define	F_TEST		3	/* test a section for locks by other procs */
#endif

/*
 * POSIX options and option groups we unconditionally do or don't
 * implement.  This list includes those options which are exclusively
 * implemented (or not) in user mode.  Please keep this list in
 * alphabetical order.
 *
 * Anything which is defined as zero below **must** have an
 * implementation for the corresponding sysconf() which is able to
 * determine conclusively whether or not the feature is supported.
 * Anything which is defined as other than -1 below **must** have
 * complete headers, types, and function declarations as specified by
 * the POSIX standard; however, if the relevant sysconf() function
 * returns -1, the functions may be stubbed out.
 */
#define	_POSIX_BARRIERS			200112L
#define	_POSIX_CPUTIME			200112L
#define	_POSIX_READER_WRITER_LOCKS	200112L
#define	_POSIX_REGEXP			1
#define	_POSIX_SHELL			1
#define	_POSIX_SPAWN			200112L
#define	_POSIX_SPIN_LOCKS		200112L
#define	_POSIX_THREAD_ATTR_STACKADDR	200112L
#define	_POSIX_THREAD_ATTR_STACKSIZE	200112L
#define	_POSIX_THREAD_CPUTIME		200112L
#define	_POSIX_THREAD_PRIO_INHERIT	200112L
#define	_POSIX_THREAD_PRIO_PROTECT	200112L
#define	_POSIX_THREAD_PRIORITY_SCHEDULING 200112L
#define	_POSIX_THREAD_PROCESS_SHARED	200112L
#define	_POSIX_THREAD_SAFE_FUNCTIONS	-1
#define	_POSIX_THREAD_SPORADIC_SERVER	-1
#define	_POSIX_THREADS			200112L
#define	_POSIX_TRACE			-1
#define	_POSIX_TRACE_EVENT_FILTER	-1
#define	_POSIX_TRACE_INHERIT		-1
#define	_POSIX_TRACE_LOG		-1
#define	_POSIX2_C_BIND			200112L	/* mandatory */
#define	_POSIX2_C_DEV			-1 /* need c99 utility */
#define	_POSIX2_CHAR_TERM		1
#define	_POSIX2_FORT_DEV		-1 /* need fort77 utility */
#define	_POSIX2_FORT_RUN		200112L
#define	_POSIX2_LOCALEDEF		-1
#define	_POSIX2_PBS			-1
#define	_POSIX2_PBS_ACCOUNTING		-1
#define	_POSIX2_PBS_CHECKPOINT		-1
#define	_POSIX2_PBS_LOCATE		-1
#define	_POSIX2_PBS_MESSAGE		-1
#define	_POSIX2_PBS_TRACK		-1
#define	_POSIX2_SW_DEV			-1 /* XXX ??? */
#define	_POSIX2_UPE			200112L
#define	_V6_ILP32_OFF32			-1
#define	_V6_ILP32_OFFBIG		0
#define	_V6_LP64_OFF64			0
#define	_V6_LPBIG_OFFBIG		-1

#if __XSI_VISIBLE
#define	_XOPEN_CRYPT			-1 /* XXX ??? */
#define	_XOPEN_ENH_I18N			-1 /* mandatory in XSI */
#define	_XOPEN_LEGACY			-1
#define	_XOPEN_REALTIME			-1
#define	_XOPEN_REALTIME_THREADS		-1
#define	_XOPEN_UNIX			-1
#endif

/* Define the POSIX.2 version we target for compliance. */
#define	_POSIX2_VERSION		199212L

/*
 * POSIX-style system configuration variable accessors (for the
 * sysconf function).  The kernel does not directly implement the
 * sysconf() interface; rather, a C library stub translates references
 * to sysconf() into calls to sysctl() using a giant switch statement.
 * Those that are marked `user' are implemented entirely in the C
 * library and never query the kernel.  pathconf() is implemented
 * directly by the kernel so those are not defined here.
 */
#define	_SC_ARG_MAX		 1
#define	_SC_CHILD_MAX		 2
#define	_SC_CLK_TCK		 3
#define	_SC_NGROUPS_MAX		 4
#define	_SC_OPEN_MAX		 5
#define	_SC_JOB_CONTROL		 6
#define	_SC_SAVED_IDS		 7
#define	_SC_VERSION		 8
#define	_SC_BC_BASE_MAX		 9 /* user */
#define	_SC_BC_DIM_MAX		10 /* user */
#define	_SC_BC_SCALE_MAX	11 /* user */
#define	_SC_BC_STRING_MAX	12 /* user */
#define	_SC_COLL_WEIGHTS_MAX	13 /* user */
#define	_SC_EXPR_NEST_MAX	14 /* user */
#define	_SC_LINE_MAX		15 /* user */
#define	_SC_RE_DUP_MAX		16 /* user */
#define	_SC_2_VERSION		17 /* user */
#define	_SC_2_C_BIND		18 /* user */
#define	_SC_2_C_DEV		19 /* user */
#define	_SC_2_CHAR_TERM		20 /* user */
#define	_SC_2_FORT_DEV		21 /* user */
#define	_SC_2_FORT_RUN		22 /* user */
#define	_SC_2_LOCALEDEF		23 /* user */
#define	_SC_2_SW_DEV		24 /* user */
#define	_SC_2_UPE		25 /* user */
#define	_SC_STREAM_MAX		26 /* user */
#define	_SC_TZNAME_MAX		27 /* user */

#if __POSIX_VISIBLE >= 199309
#define	_SC_ASYNCHRONOUS_IO	28
#define	_SC_MAPPED_FILES	29
#define	_SC_MEMLOCK		30
#define	_SC_MEMLOCK_RANGE	31
#define	_SC_MEMORY_PROTECTION	32
#define	_SC_MESSAGE_PASSING	33
#define	_SC_PRIORITIZED_IO	34
#define	_SC_PRIORITY_SCHEDULING	35
#define	_SC_REALTIME_SIGNALS	36
#define	_SC_SEMAPHORES		37
#define	_SC_FSYNC		38
#define	_SC_SHARED_MEMORY_OBJECTS 39
#define	_SC_SYNCHRONIZED_IO	40
#define	_SC_TIMERS		41
#define	_SC_AIO_LISTIO_MAX	42
#define	_SC_AIO_MAX		43
#define	_SC_AIO_PRIO_DELTA_MAX	44
#define	_SC_DELAYTIMER_MAX	45
#define	_SC_MQ_OPEN_MAX		46
#define	_SC_PAGESIZE		47
#define	_SC_RTSIG_MAX		48
#define	_SC_SEM_NSEMS_MAX	49
#define	_SC_SEM_VALUE_MAX	50
#define	_SC_SIGQUEUE_MAX	51
#define	_SC_TIMER_MAX		52
#endif

#if __POSIX_VISIBLE >= 200112
#define	_SC_2_PBS		59 /* user */
#define	_SC_2_PBS_ACCOUNTING	60 /* user */
#define	_SC_2_PBS_CHECKPOINT	61 /* user */
#define	_SC_2_PBS_LOCATE	62 /* user */
#define	_SC_2_PBS_MESSAGE	63 /* user */
#define	_SC_2_PBS_TRACK		64 /* user */
#define	_SC_ADVISORY_INFO	65
#define	_SC_BARRIERS		66 /* user */
#define	_SC_CLOCK_SELECTION	67
#define	_SC_CPUTIME		68
#define	_SC_FILE_LOCKING	69
#define	_SC_GETGR_R_SIZE_MAX	70 /* user */
#define	_SC_GETPW_R_SIZE_MAX	71 /* user */
#define	_SC_HOST_NAME_MAX	72
#define	_SC_LOGIN_NAME_MAX	73
#define	_SC_MONOTONIC_CLOCK	74
#define	_SC_MQ_PRIO_MAX		75
#define	_SC_READER_WRITER_LOCKS	76 /* user */
#define	_SC_REGEXP		77 /* user */
#define	_SC_SHELL		78 /* user */
#define	_SC_SPAWN		79 /* user */
#define	_SC_SPIN_LOCKS		80 /* user */
#define	_SC_SPORADIC_SERVER	81
#define	_SC_THREAD_ATTR_STACKADDR 82 /* user */
#define	_SC_THREAD_ATTR_STACKSIZE 83 /* user */
#define	_SC_THREAD_CPUTIME	84 /* user */
#define	_SC_THREAD_DESTRUCTOR_ITERATIONS 85 /* user */
#define	_SC_THREAD_KEYS_MAX	86 /* user */
#define	_SC_THREAD_PRIO_INHERIT	87 /* user */
#define	_SC_THREAD_PRIO_PROTECT	88 /* user */
#define	_SC_THREAD_PRIORITY_SCHEDULING 89 /* user */
#define	_SC_THREAD_PROCESS_SHARED 90 /* user */
#define	_SC_THREAD_SAFE_FUNCTIONS 91 /* user */
#define	_SC_THREAD_SPORADIC_SERVER 92 /* user */
#define	_SC_THREAD_STACK_MIN	93 /* user */
#define	_SC_THREAD_THREADS_MAX	94 /* user */
#define	_SC_TIMEOUTS		95 /* user */
#define	_SC_THREADS		96 /* user */
#define	_SC_TRACE		97 /* user */
#define	_SC_TRACE_EVENT_FILTER	98 /* user */
#define	_SC_TRACE_INHERIT	99 /* user */
#define	_SC_TRACE_LOG		100 /* user */
#define	_SC_TTY_NAME_MAX	101 /* user */
#define	_SC_TYPED_MEMORY_OBJECTS 102
#define	_SC_V6_ILP32_OFF32	103 /* user */
#define	_SC_V6_ILP32_OFFBIG	104 /* user */
#define	_SC_V6_LP64_OFF64	105 /* user */
#define	_SC_V6_LPBIG_OFFBIG	106 /* user */
#define	_SC_IPV6		118
#define	_SC_RAW_SOCKETS		119
#define	_SC_SYMLOOP_MAX		120
#endif

#if __XSI_VISIBLE
#define	_SC_ATEXIT_MAX		107 /* user */
#define	_SC_IOV_MAX		56
#define	_SC_PAGE_SIZE		_SC_PAGESIZE
#define	_SC_XOPEN_CRYPT		108 /* user */
#define	_SC_XOPEN_ENH_I18N	109 /* user */
#define	_SC_XOPEN_LEGACY	110 /* user */
#define	_SC_XOPEN_REALTIME	111
#define	_SC_XOPEN_REALTIME_THREADS 112
#define	_SC_XOPEN_SHM		113
#define	_SC_XOPEN_STREAMS	114
#define	_SC_XOPEN_UNIX		115
#define	_SC_XOPEN_VERSION	116
#define	_SC_XOPEN_XCU_VERSION	117 /* user */
#endif

#if __BSD_VISIBLE
#define	_SC_NPROCESSORS_CONF	57
#define	_SC_NPROCESSORS_ONLN	58
#define	_SC_CPUSET_SIZE		122
#define	_SC_UEXTERR_MAXLEN	123 /* user */
#endif

#if __POSIX_VISIBLE >= 202405
#define	_SC_NSIG		124
#endif

/* Extensions found in Solaris and Linux. */
#define	_SC_PHYS_PAGES		121

/* Keys for the confstr(3) function. */
#if __POSIX_VISIBLE >= 199209
#define	_CS_PATH		1	/* default value of PATH */
#endif

#if __POSIX_VISIBLE >= 200112
#define	_CS_POSIX_V6_ILP32_OFF32_CFLAGS		2
#define	_CS_POSIX_V6_ILP32_OFF32_LDFLAGS	3
#define	_CS_POSIX_V6_ILP32_OFF32_LIBS		4
#define	_CS_POSIX_V6_ILP32_OFFBIG_CFLAGS	5
#define	_CS_POSIX_V6_ILP32_OFFBIG_LDFLAGS	6
#define	_CS_POSIX_V6_ILP32_OFFBIG_LIBS		7
#define	_CS_POSIX_V6_LP64_OFF64_CFLAGS		8
#define	_CS_POSIX_V6_LP64_OFF64_LDFLAGS		9
#define	_CS_POSIX_V6_LP64_OFF64_LIBS		10
#define	_CS_POSIX_V6_LPBIG_OFFBIG_CFLAGS	11
#define	_CS_POSIX_V6_LPBIG_OFFBIG_LDFLAGS	12
#define	_CS_POSIX_V6_LPBIG_OFFBIG_LIBS		13
#define	_CS_POSIX_V6_WIDTH_RESTRICTED_ENVS	14
#endif

__BEGIN_DECLS
/* 1003.1-1990 */
__raw void	 _exit(int) __dead2;
__raw int	 access(const char *, int);
__raw unsigned int	 alarm(unsigned int);
__raw int	 chdir(const char *);
__raw int	 chown(const char *, uid_t, gid_t);
__raw int	 close(int);
__raw void	 closefrom(int);
__raw int	 dup(int);
__raw int	 dup2(int, int);
__raw int	 execl(const char *, const char *, ...) __null_sentinel;
__raw int	 execle(const char *, const char *, ...);
__raw int	 execlp(const char *, const char *, ...) __null_sentinel;
__raw int	 execv(const char *, char * const *);
__raw int	 execve(const char *, char * const *, char * const *);
__raw int	 execvp(const char *, char * const *);
__raw pid_t	 fork(void);
__raw long	 fpathconf(int, int);
char	* __raw getcwd(char *, size_t);
__raw gid_t	 getegid(void);
__raw uid_t	 geteuid(void);
__raw gid_t	 getgid(void);
__raw int	 getgroups(int, gid_t []);
char	* __raw getlogin(void);
__raw pid_t	 getpgrp(void);
__raw pid_t	 getpid(void);
__raw pid_t	 getppid(void);
__raw uid_t	 getuid(void);
__raw int	 isatty(int);
__raw int	 link(const char *, const char *);
#ifndef _LSEEK_DECLARED
#define	_LSEEK_DECLARED
__raw off_t	 lseek(int, off_t, int);
#endif
__raw long	 pathconf(const char *, int);
__raw int	 pause(void);
__raw int	 pipe(int *);
__raw ssize_t	 read(int, void *, size_t);
__raw int	 rmdir(const char *);
__raw int	 setgid(gid_t);
__raw int	 setpgid(pid_t, pid_t);
__raw pid_t	 setsid(void);
__raw int	 setuid(uid_t);
__raw unsigned int	 sleep(unsigned int);
__raw long	 sysconf(int);
__raw pid_t	 tcgetpgrp(int);
__raw int	 tcsetpgrp(int, pid_t);
char	* __raw ttyname(int);
__raw int	ttyname_r(int, char *, size_t);
__raw int	 unlink(const char *);
__raw ssize_t	 write(int, const void *, size_t);

/* 1003.2-1992 */
#if __POSIX_VISIBLE >= 199209 || __XSI_VISIBLE
__raw size_t	 confstr(int, char *, size_t);
#ifndef _GETOPT_DECLARED
#define	_GETOPT_DECLARED
__raw int	 getopt(int, char * const [], const char *);

extern char * __raw optarg;			/* getopt(3) external variables */
extern __raw int optind, opterr, optopt;
#endif /* _GETOPT_DECLARED */
#endif

/* ISO/IEC 9945-1: 1996 */
#if __POSIX_VISIBLE >= 199506 || __XSI_VISIBLE
__raw int	 fsync(int);
__raw int	 fdatasync(int);

/*
 * ftruncate() was in the POSIX Realtime Extension (it's used for shared
 * memory), but truncate() was not.
 */
#ifndef _FTRUNCATE_DECLARED
#define	_FTRUNCATE_DECLARED
__raw int	 ftruncate(int, off_t);
#endif
#endif

#if __POSIX_VISIBLE >= 199506
__raw int	 getlogin_r(char *, size_t);
#endif

/* 1003.1-2001 */
#if __POSIX_VISIBLE >= 200112 || __XSI_VISIBLE
__raw int	 fchown(int, uid_t, gid_t);
__raw ssize_t	 readlink(const char * __restrict, char * __restrict, size_t);
#endif
#if __POSIX_VISIBLE >= 200112
__raw int	 gethostname(char *, size_t);
__raw int	 setegid(gid_t);
__raw int	 seteuid(uid_t);
#endif

/* 1003.1-2008 */
#if __POSIX_VISIBLE >= 200809 || __XSI_VISIBLE
__raw int	 getsid(pid_t _pid);
__raw int	 fchdir(int);
__raw int	 getpgid(pid_t _pid);
__raw int	 lchown(const char *, uid_t, gid_t);
__raw ssize_t	 pread(int, void *, size_t, off_t);
__raw ssize_t	 pwrite(int, const void *, size_t, off_t);

/* See comment at ftruncate() above. */
#ifndef _TRUNCATE_DECLARED
#define	_TRUNCATE_DECLARED
__raw int	 truncate(const char *, off_t);
#endif
#endif /* __POSIX_VISIBLE >= 200809 || __XSI_VISIBLE */

#if __POSIX_VISIBLE >= 200809
__raw int	faccessat(int, const char *, int, int);
__raw int	fchownat(int, const char *, uid_t, gid_t, int);
__raw int	fexecve(int, char *const [], char *const []);
__raw int	linkat(int, const char *, int, const char *, int);
__raw ssize_t	readlinkat(int, const char * __restrict, char * __restrict, size_t);
__raw int	symlinkat(const char *, int, const char *);
__raw int	unlinkat(int, const char *, int);
#endif /* __POSIX_VISIBLE >= 200809 */

/*
 * symlink() was originally in POSIX.1a, which was withdrawn after
 * being overtaken by events (1003.1-2001).  It was in XPG4.2, and of
 * course has been in BSD since 4.2.
 */
#if __POSIX_VISIBLE >= 200112 || __XSI_VISIBLE >= 402
__raw int	 symlink(const char * __restrict, const char * __restrict);
#endif

/* X/Open System Interfaces */
#if __XSI_VISIBLE
char	* __raw crypt(const char *, const char *);
__raw long	 gethostid(void);
__raw int	 lockf(int, int, off_t);
__raw int	 nice(int);
__raw int	 setregid(gid_t, gid_t);
__raw int	 setreuid(uid_t, uid_t);

#ifndef _SWAB_DECLARED
#define _SWAB_DECLARED
__raw void	 swab(const void * __restrict, void * __restrict, ssize_t);
#endif /* _SWAB_DECLARED */

__raw void	 sync(void);

#endif /* __XSI_VISIBLE */

#if (__XSI_VISIBLE && __XSI_VISIBLE <= 500) || __BSD_VISIBLE
__raw int	 brk(const void *);
__raw int	 chroot(const char *);
__raw int	 getdtablesize(void);
__raw int	 getpagesize(void) __pure2;
char	* __raw getpass(const char *);
void	* __raw sbrk(intptr_t);
#endif

#if (__XSI_VISIBLE && __XSI_VISIBLE <= 600) || __BSD_VISIBLE
char	* __raw getwd(char *);			/* obsoleted by getcwd() */
__raw useconds_t
	 ualarm(useconds_t, useconds_t);
__raw int	 usleep(useconds_t);
__raw pid_t	 vfork(void) __returns_twice;
#endif

#if __BSD_VISIBLE
struct timeval;				/* select(2) */

struct crypt_data {
	int	initialized;	/* For compatibility with glibc. */
	char	__buf[256];	/* Buffer returned by crypt_r(). */
};

__raw int	 acct(const char *);
__raw int	 async_daemon(void);
__raw int	 check_utility_compat(const char *);
__raw int	 close_range(unsigned int, unsigned int, int);
__raw ssize_t	 copy_file_range(int, off_t *, int, off_t *, size_t, unsigned int);
const char * __raw
	 crypt_get_format(void);
char	* __raw crypt_r(const char *, const char *, struct crypt_data *);
__raw int	 crypt_set_format(const char *);
__raw int	 dup3(int, int, int);
__raw int	 eaccess(const char *, int);
__raw void	 endusershell(void);
__raw int	 exect(const char *, char * const *, char * const *);
__raw int	 execvP(const char *, const char *, char * const *);
__raw int	 execvpe(const char *, char * const *, char * const *);
__raw int	 feature_present(const char *);
__raw int	 fchroot(int);
char	* __raw fflagstostr(u_long);
__raw int	 getdomainname(char *, int);
__raw int	 getentropy(void *, size_t);
__raw int	 getgrouplist(const char *, gid_t, gid_t *, int *);
__raw int	 getloginclass(char *, size_t);
__raw mode_t	 getmode(const void *, mode_t);
__raw int	 getosreldate(void);
__raw int	 getpeereid(int, uid_t *, gid_t *);
__raw int	 getresgid(gid_t *, gid_t *, gid_t *);
__raw int	 getresuid(uid_t *, uid_t *, uid_t *);
char	* __raw getusershell(void);
__raw int	 initgroups(const char *, gid_t);
__raw int	 iruserok(unsigned long, int, const char *, const char *);
__raw int	 iruserok_sa(const void *, int, int, const char *, const char *);
__raw int	 issetugid(void);
__raw void	__FreeBSD_libc_enter_restricted_mode(void);
__raw int	 kcmp(pid_t pid1, pid_t pid2, int type, uintptr_t idx1, uintptr_t idx2);
__raw long	 lpathconf(const char *, int);
#ifndef _MKDTEMP_DECLARED
char	* __raw mkdtemp(char *);
#define	_MKDTEMP_DECLARED
#endif
#ifndef	_MKNOD_DECLARED
__raw int	 mknod(const char *, mode_t, dev_t);
#define	_MKNOD_DECLARED
#endif
#ifndef _MKSTEMP_DECLARED
__raw int	 mkstemp(char *);
#define	_MKSTEMP_DECLARED
#endif
__raw int	 mkstemps(char *, int);
#ifndef _MKTEMP_DECLARED
char	* __raw mktemp(char *);
#define	_MKTEMP_DECLARED
#endif
__raw int	 nfssvc(int, void *);
__raw int	 nlm_syscall(int, int, int, char **);
__raw int	 pipe2(int *, int);
__raw int	 profil(char *, size_t, vm_offset_t, int);
__raw int	 rcmd(char **, int, const char *, const char *, const char *, int *);
__raw int	 rcmd_af(char **, int, const char *,
		const char *, const char *, int *, int);
__raw int	 rcmdsh(char **, int, const char *,
		const char *, const char *, const char *);
char	* __raw re_comp(const char *);
__raw int	 re_exec(const char *);
__raw int	 reboot(int);
__raw int	 revoke(const char *);
__raw pid_t	 rfork(int) __returns_twice;
__raw pid_t	 rfork_thread(int, void *, int (*)(void *), void *);
__raw int	 rresvport(int *);
__raw int	 rresvport_af(int *, int);
__raw int	 ruserok(const char *, int, const char *, const char *);
#ifndef _SELECT_DECLARED
#define	_SELECT_DECLARED
__raw int	 select(int, fd_set *, fd_set *, fd_set *, struct timeval *);
#endif
__raw int	 setdomainname(const char *, int);
__raw int	 setgroups(int, const gid_t *);
__raw void	 sethostid(long);
__raw int	 sethostname(const char *, int);
__raw int	 setlogin(const char *);
__raw int	 setloginclass(const char *);
void	* __raw setmode(const char *);
__raw int	 setpgrp(pid_t, pid_t);			/* obsoleted by setpgid() */
__raw void	 setproctitle(const char *_fmt, ...) __printf0like(1, 2);
__raw void	 setproctitle_fast(const char *_fmt, ...) __printf0like(1, 2);
__raw int	 setresgid(gid_t, gid_t, gid_t);
__raw int	 setresuid(uid_t, uid_t, uid_t);
__raw int	 setrgid(gid_t);
__raw int	 setruid(uid_t);
__raw void	 setusershell(void);
__raw int	 strtofflags(char **, u_long *, u_long *);
__raw int	 swapon(const char *);
__raw int	 swapoff(const char *, u_int);
__raw int	 syscall(int, ...);
__raw off_t	 __syscall(quad_t, ...);
__raw int	 undelete(const char *);
__raw int	 unwhiteout(const char *);
void	* __raw valloc(size_t);			/* obsoleted by malloc() */
__raw int	 funlinkat(int, const char *, int, int);
__raw pid_t	 _Fork(void);

#ifndef _OPTRESET_DECLARED
#define	_OPTRESET_DECLARED
extern __raw int optreset;			/* getopt(3) external variable */
#endif
#endif /* __BSD_VISIBLE */
__END_DECLS

#endif /* !_UNISTD_H_ */
