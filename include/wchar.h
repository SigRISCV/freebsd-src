/*-
 * SPDX-License-Identifier: (BSD-2-Clause)
 *
 * Copyright (c)1999 Citrus Project,
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

/*-
 * Copyright (c) 1999, 2000 The NetBSD Foundation, Inc.
 * All rights reserved.
 *
 * This code is derived from software contributed to The NetBSD Foundation
 * by Julian Coleman.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE NETBSD FOUNDATION, INC. AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 *	$NetBSD: wchar.h,v 1.8 2000/12/22 05:31:42 itojun Exp $
 */

#ifndef _WCHAR_H_
#define _WCHAR_H_

#include <sys/cdefs.h>
#include <sys/_null.h>
#include <sys/_types.h>
#include <machine/_limits.h>
#include <_ctype.h>

#ifndef _MBSTATE_T_DECLARED
typedef	__mbstate_t	mbstate_t;
#define	_MBSTATE_T_DECLARED
#endif

#ifndef _SIZE_T_DECLARED
typedef	__size_t	size_t;
#define	_SIZE_T_DECLARED
#endif

#if __POSIX_VISIBLE >= 200809 || __XSI_VISIBLE
#ifndef _VA_LIST_DECLARED
typedef	__builtin_va_list	va_list;
#define	_VA_LIST_DECLARED
#endif
#endif

#ifndef	__cplusplus
#ifndef _WCHAR_T_DECLARED
typedef	___wchar_t	wchar_t;
#define	_WCHAR_T_DECLARED
#endif
#endif

#ifndef _WINT_T_DECLARED
typedef	__wint_t	wint_t;
#define	_WINT_T_DECLARED
#endif

#define	WCHAR_MIN	__WCHAR_MIN
#define	WCHAR_MAX	__WCHAR_MAX

#ifndef WEOF
#define	WEOF 	((wint_t)-1)
#endif

#ifndef _STDFILE_DECLARED
#define _STDFILE_DECLARED
typedef struct __sFILE FILE;
#endif
struct tm;

__BEGIN_DECLS
__raw size_t	wcslen(const wchar_t *) __pure;
__END_DECLS

#if !defined(_STANDALONE) && defined(_FORTIFY_SOURCE) && _FORTIFY_SOURCE > 0
#include <ssp/wchar.h>
#endif

__BEGIN_DECLS
__raw wint_t	btowc(int);
__raw wint_t	fgetwc(FILE *);
wchar_t	* __raw
	fgetws(wchar_t * __restrict, int, FILE * __restrict);
__raw wint_t	fputwc(wchar_t, FILE *);
__raw int	fputws(const wchar_t * __restrict, FILE * __restrict);
__raw int	fwide(FILE *, int);
__raw int	fwprintf(FILE * __restrict, const wchar_t * __restrict, ...);
__raw int	fwscanf(FILE * __restrict, const wchar_t * __restrict, ...);
__raw wint_t	getwc(FILE *);
__raw wint_t	getwchar(void);
__raw size_t	mbrlen(const char * __restrict, size_t, mbstate_t * __restrict);
__raw size_t	mbrtowc(wchar_t * __restrict, const char * __restrict, size_t,
	    mbstate_t * __restrict);
__raw int	mbsinit(const mbstate_t *);
__raw size_t	mbsrtowcs(wchar_t * __restrict, const char ** __restrict, size_t,
	    mbstate_t * __restrict);
__raw wint_t	putwc(wchar_t, FILE *);
__raw wint_t	putwchar(wchar_t);
__raw int	swprintf(wchar_t * __restrict, size_t n, const wchar_t * __restrict,
	    ...);
__raw int	swscanf(const wchar_t * __restrict, const wchar_t * __restrict, ...);
__raw wint_t	ungetwc(wint_t, FILE *);
__raw int	vfwprintf(FILE * __restrict, const wchar_t * __restrict,
	    __va_list);
__raw int	vswprintf(wchar_t * __restrict, size_t n, const wchar_t * __restrict,
	    __va_list);
__raw int	vwprintf(const wchar_t * __restrict, __va_list);
__raw size_t	wcrtomb(char * __restrict, wchar_t, mbstate_t * __restrict);
wchar_t	* __raw wcscat(wchar_t * __restrict, const wchar_t * __restrict);
wchar_t	* __raw wcschr(const wchar_t *, wchar_t) __pure;
__raw int	wcscmp(const wchar_t *, const wchar_t *) __pure;
__raw int	wcscoll(const wchar_t *, const wchar_t *);
wchar_t	* __raw wcscpy(wchar_t * __restrict, const wchar_t * __restrict);
__raw size_t	wcscspn(const wchar_t *, const wchar_t *) __pure;
__raw size_t	wcsftime(wchar_t * __restrict, size_t, const wchar_t * __restrict,
	    const struct tm * __restrict);
wchar_t	* __raw wcsncat(wchar_t * __restrict, const wchar_t * __restrict,
	    size_t);
__raw int	wcsncmp(const wchar_t *, const wchar_t *, size_t) __pure;
wchar_t	* __raw wcsncpy(wchar_t * __restrict , const wchar_t * __restrict, size_t);
wchar_t	* __raw wcspbrk(const wchar_t *, const wchar_t *) __pure;
wchar_t	* __raw wcsrchr(const wchar_t *, wchar_t) __pure;
__raw size_t	wcsrtombs(char * __restrict, const wchar_t ** __restrict, size_t,
	    mbstate_t * __restrict);
__raw size_t	wcsspn(const wchar_t *, const wchar_t *) __pure;
wchar_t	* __raw wcsstr(const wchar_t * __restrict, const wchar_t * __restrict)
	    __pure;
__raw size_t	wcsxfrm(wchar_t * __restrict, const wchar_t * __restrict, size_t);
__raw int	wctob(wint_t);
__raw double	wcstod(const wchar_t * __restrict, wchar_t ** __restrict);
wchar_t	* __raw wcstok(wchar_t * __restrict, const wchar_t * __restrict,
	    wchar_t ** __restrict);
__raw long	 wcstol(const wchar_t * __restrict, wchar_t ** __restrict, int);
__raw unsigned long
	 wcstoul(const wchar_t * __restrict, wchar_t ** __restrict, int);
wchar_t	* __raw wmemchr(const wchar_t *, wchar_t, size_t) __pure;
__raw int	wmemcmp(const wchar_t *, const wchar_t *, size_t) __pure;
wchar_t	* __raw wmemcpy(wchar_t * __restrict, const wchar_t * __restrict, size_t);
wchar_t	* __raw wmemmove(wchar_t *, const wchar_t *, size_t);
#if __BSD_VISIBLE
wchar_t	* __raw wmempcpy(wchar_t * __restrict, const wchar_t * __restrict, size_t);
#endif
wchar_t	* __raw wmemset(wchar_t *, wchar_t, size_t);
__raw int	wprintf(const wchar_t * __restrict, ...);
__raw int	wscanf(const wchar_t * __restrict, ...);

#ifndef _STDSTREAM_DECLARED
extern FILE * __raw __stdinp;
extern FILE * __raw __stdoutp;
extern FILE * __raw __stderrp;
#define	_STDSTREAM_DECLARED
#endif

#define	getwc(fp)	fgetwc(fp)
#define	getwchar()	fgetwc(__stdinp)
#define	putwc(wc, fp)	fputwc(wc, fp)
#define	putwchar(wc)	fputwc(wc, __stdoutp)

#if __ISO_C_VISIBLE >= 1999
__raw int	vfwscanf(FILE * __restrict, const wchar_t * __restrict,
	    __va_list);
__raw int	vswscanf(const wchar_t * __restrict, const wchar_t * __restrict,
	    __va_list);
__raw int	vwscanf(const wchar_t * __restrict, __va_list);
__raw float	wcstof(const wchar_t * __restrict, wchar_t ** __restrict);
__raw long double
	wcstold(const wchar_t * __restrict, wchar_t ** __restrict);
#ifdef __LONG_LONG_SUPPORTED
/* LONGLONG */
__raw long long
	wcstoll(const wchar_t * __restrict, wchar_t ** __restrict, int);
/* LONGLONG */
__raw unsigned long long
	 wcstoull(const wchar_t * __restrict, wchar_t ** __restrict, int);
#endif
#endif	/* __ISO_C_VISIBLE >= 1999 */

#if __XSI_VISIBLE
__raw int	wcswidth(const wchar_t *, size_t);
__raw int	wcwidth(wchar_t);
#define	wcwidth(_c)	__wcwidth(_c)
#endif

#if __POSIX_VISIBLE >= 200809
__raw size_t	mbsnrtowcs(wchar_t * __restrict, const char ** __restrict, size_t,
	    size_t, mbstate_t * __restrict);
FILE	* __raw open_wmemstream(wchar_t **, size_t *);
wchar_t	* __raw wcpcpy(wchar_t * __restrict, const wchar_t * __restrict);
wchar_t	* __raw wcpncpy(wchar_t * __restrict, const wchar_t * __restrict, size_t);
wchar_t	* __raw wcsdup(const wchar_t *) __malloc_like;
__raw int	wcscasecmp(const wchar_t *, const wchar_t *);
__raw int	wcsncasecmp(const wchar_t *, const wchar_t *, size_t n);
__raw size_t	wcsnlen(const wchar_t *, size_t) __pure;
__raw size_t	wcsnrtombs(char * __restrict, const wchar_t ** __restrict, size_t,
	    size_t, mbstate_t * __restrict);
#endif

#if __BSD_VISIBLE
wchar_t	* __raw fgetwln(FILE * __restrict, size_t * __restrict);
__raw size_t	wcslcat(wchar_t *, const wchar_t *, size_t);
__raw size_t	wcslcpy(wchar_t *, const wchar_t *, size_t);
#endif

#if __POSIX_VISIBLE >= 200809 || defined(_XLOCALE_H_)
#include <xlocale/_wchar.h>
#endif
__END_DECLS

#endif /* !_WCHAR_H_ */
