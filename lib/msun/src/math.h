/*
 * ====================================================
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 *
 * Developed at SunPro, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice
 * is preserved.
 * ====================================================
 */

/*
 */

#ifndef _MATH_H_
#define	_MATH_H_

#include <sys/cdefs.h>
#include <sys/_types.h>
#include <machine/_limits.h>

/*
 * ANSI/POSIX
 */
extern __raw const union __infinity_un {
	unsigned char	__uc[8];
	double		__ud;
} __infinity;

extern __raw const union __nan_un {
	unsigned char	__uc[sizeof(float)];
	float		__uf;
} __nan;

#define	__MATH_BUILTIN_CONSTANTS
#define	__MATH_BUILTIN_RELOPS

#ifdef __MATH_BUILTIN_CONSTANTS
#define	HUGE_VAL	__builtin_huge_val()
#else
#define	HUGE_VAL	(__infinity.__ud)
#endif

#if __ISO_C_VISIBLE >= 1999
#define	FP_ILOGB0	(-__INT_MAX)
#define	FP_ILOGBNAN	__INT_MAX

#ifdef __MATH_BUILTIN_CONSTANTS
#define	HUGE_VALF	__builtin_huge_valf()
#define	HUGE_VALL	__builtin_huge_vall()
#define	INFINITY	__builtin_inff()
#define	NAN		__builtin_nanf("")
#else
#define	HUGE_VALF	(float)HUGE_VAL
#define	HUGE_VALL	(long double)HUGE_VAL
#define	INFINITY	HUGE_VALF
#define	NAN		(__nan.__uf)
#endif /* __MATH_BUILTIN_CONSTANTS */

#define	MATH_ERRNO	1
#define	MATH_ERREXCEPT	2
#define	math_errhandling	MATH_ERREXCEPT

#define	FP_FAST_FMAF	1

/* Symbolic constants to classify floating point numbers. */
#define	FP_INFINITE	0x01
#define	FP_NAN		0x02
#define	FP_NORMAL	0x04
#define	FP_SUBNORMAL	0x08
#define	FP_ZERO		0x10

#if __STDC_VERSION__ >= 201112L || __has_extension(c_generic_selections)
#define	__fp_type_select(x, f, d, ld) __extension__ _Generic((x),	\
    float: f,								\
    double: d,								\
    long double: ld)(x)
#elif !defined(__cplusplus)
#define	__fp_type_select(x, f, d, ld) __builtin_choose_expr(		\
    __builtin_types_compatible_p(__typeof(x), long double), ld(x),	\
    __builtin_choose_expr(						\
    __builtin_types_compatible_p(__typeof(x), double), d(x),		\
    __builtin_choose_expr(						\
    __builtin_types_compatible_p(__typeof(x), float), f(x), (void)0)))
#else
#define	 __fp_type_select(x, f, d, ld)					\
    ((sizeof(x) == sizeof(float)) ? f(x)				\
    : (sizeof(x) == sizeof(double)) ? d(x)				\
    : ld(x))
#endif

#define	fpclassify(x) \
	__fp_type_select(x, __fpclassifyf, __fpclassifyd, __fpclassifyl)
#define	isfinite(x) __fp_type_select(x, __isfinitef, __isfinite, __isfinitel)
#define	isinf(x) __fp_type_select(x, __isinff, __isinf, __isinfl)
#define	isnan(x) \
	__fp_type_select(x, __inline_isnanf, __inline_isnan, __inline_isnanl)
#define	isnormal(x) __fp_type_select(x, __isnormalf, __isnormal, __isnormall)

#ifdef __MATH_BUILTIN_RELOPS
#define	isgreater(x, y)		__builtin_isgreater((x), (y))
#define	isgreaterequal(x, y)	__builtin_isgreaterequal((x), (y))
#define	isless(x, y)		__builtin_isless((x), (y))
#define	islessequal(x, y)	__builtin_islessequal((x), (y))
#define	islessgreater(x, y)	__builtin_islessgreater((x), (y))
#define	isunordered(x, y)	__builtin_isunordered((x), (y))
#else
#define	isgreater(x, y)		(!isunordered((x), (y)) && (x) > (y))
#define	isgreaterequal(x, y)	(!isunordered((x), (y)) && (x) >= (y))
#define	isless(x, y)		(!isunordered((x), (y)) && (x) < (y))
#define	islessequal(x, y)	(!isunordered((x), (y)) && (x) <= (y))
#define	islessgreater(x, y)	(!isunordered((x), (y)) && \
					((x) > (y) || (y) > (x)))
#define	isunordered(x, y)	(isnan(x) || isnan(y))
#endif /* __MATH_BUILTIN_RELOPS */

#define	signbit(x) __fp_type_select(x, __signbitf, __signbit, __signbitl)

typedef	__double_t	double_t;
typedef	__float_t	float_t;
#endif /* __ISO_C_VISIBLE >= 1999 */

/*
 * XOPEN/SVID
 */
#if __BSD_VISIBLE || __XSI_VISIBLE
#define	M_E		2.7182818284590452354	/* e */
#define	M_LOG2E		1.4426950408889634074	/* log 2e */
#define	M_LOG10E	0.43429448190325182765	/* log 10e */
#define	M_LN2		0.69314718055994530942	/* log e2 */
#define	M_LN10		2.30258509299404568402	/* log e10 */
#define	M_PI		3.14159265358979323846	/* pi */
#define	M_PI_2		1.57079632679489661923	/* pi/2 */
#define	M_PI_4		0.78539816339744830962	/* pi/4 */
#define	M_1_PI		0.31830988618379067154	/* 1/pi */
#define	M_2_PI		0.63661977236758134308	/* 2/pi */
#define	M_2_SQRTPI	1.12837916709551257390	/* 2/sqrt(pi) */
#define	M_SQRT2		1.41421356237309504880	/* sqrt(2) */
#define	M_SQRT1_2	0.70710678118654752440	/* 1/sqrt(2) */

#if __BSD_VISIBLE || __XSI_VISIBLE >= 800
#define	M_El		2.718281828459045235360287471352662498L	/* e */
#define	M_LOG2El	1.442695040888963407359924681001892137L	/* log_2 e */
#define	M_LOG10El	0.434294481903251827651128918916605082L	/* log_10 e */
#define	M_LN2l		0.693147180559945309417232121458176568L	/* log_e 2 */
#define	M_LN10l		2.302585092994045684017991454684364208L	/* log_e 10 */
#define	M_PIl		3.141592653589793238462643383279502884L	/* pi */
#define	M_PI_2l		1.570796326794896619231321691639751442L	/* pi/2 */
#define	M_PI_4l		0.785398163397448309615660845819875721L	/* pi/4 */
#define	M_1_PIl		0.318309886183790671537767526745028724L	/* 1/pi */
#define	M_2_PIl		0.636619772367581343075535053490057448L	/* 2/pi */
#define	M_2_SQRTPIl	1.128379167095512573896158903121545172L	/* 2/sqrt(pi) */
#define	M_SQRT2l	1.414213562373095048801688724209698079L	/* sqrt(2) */
#define	M_SQRT1_2l	0.707106781186547524400844362104849039L	/* 1/sqrt(2) */
#endif /* __BSD_VISIBLE || __XSI_VISIBLE >= 800 */

#define	MAXFLOAT	((float)3.40282346638528860e+38)
extern int signgam;
#endif /* __BSD_VISIBLE || __XSI_VISIBLE */

#if __BSD_VISIBLE
#if 0
/* Old value from 4.4BSD-Lite math.h; this is probably better. */
#define	HUGE		HUGE_VAL
#else
#define	HUGE		MAXFLOAT
#endif
#endif /* __BSD_VISIBLE */

/*
 * Most of these functions depend on the rounding mode and have the side
 * effect of raising floating-point exceptions, so they are not declared
 * as __pure2.  In C99, FENV_ACCESS affects the purity of these functions.
 */
__BEGIN_DECLS
/*
 * ANSI/POSIX
 */
__raw int	__fpclassifyd(double) __pure2;
__raw int	__fpclassifyf(float) __pure2;
__raw int	__fpclassifyl(long double) __pure2;
__raw int	__isfinitef(float) __pure2;
__raw int	__isfinite(double) __pure2;
__raw int	__isfinitel(long double) __pure2;
__raw int	__isinff(float) __pure2;
__raw int	__isinf(double) __pure2;
__raw int	__isinfl(long double) __pure2;
__raw int	__isnormalf(float) __pure2;
__raw int	__isnormal(double) __pure2;
__raw int	__isnormall(long double) __pure2;
__raw int	__signbit(double) __pure2;
__raw int	__signbitf(float) __pure2;
__raw int	__signbitl(long double) __pure2;

static __inline int
__inline_isnan(const double __x)
{

	return (__x != __x);
}

static __inline int
__inline_isnanf(const float __x)
{

	return (__x != __x);
}

static __inline int
__inline_isnanl(const long double __x)
{

	return (__x != __x);
}

/*
 * Define the following aliases, for compatibility with glibc and CUDA.
 */
#define __isnan __inline_isnan
#define __isnanf __inline_isnanf

/*
 * Version 2 of the Single UNIX Specification (UNIX98) defined isnan() and
 * isinf() as functions taking double.  C99, and the subsequent POSIX revisions
 * (SUSv3, POSIX.1-2001, define it as a macro that accepts any real floating
 * point type.  If we are targeting SUSv2 and C99 or C11 (or C++11) then we
 * expose the newer definition, assuming that the language spec takes
 * precedence over the operating system interface spec.
 */
#if	__XSI_VISIBLE > 0 && __XSI_VISIBLE < 600 && __ISO_C_VISIBLE < 1999
#undef isinf
#undef isnan
__raw int	isinf(double);
__raw int	isnan(double);
#endif

__raw double	acos(double);
__raw double	asin(double);
__raw double	atan(double);
__raw double	atan2(double, double);
__raw double	cos(double);
__raw double	sin(double);
__raw double	tan(double);

__raw double	cosh(double);
__raw double	sinh(double);
__raw double	tanh(double);

__raw double	exp(double);
__raw double	frexp(double, int *);	/* fundamentally !__pure2 */
__raw double	ldexp(double, int);
__raw double	log(double);
__raw double	log10(double);
__raw double	modf(double, double *);	/* fundamentally !__pure2 */

__raw double	pow(double, double);
__raw double	sqrt(double);

__raw double	ceil(double);
__raw double	fabs(double) __pure2;
__raw double	floor(double);
__raw double	fmod(double, double);

/*
 * These functions are not in C90.
 */
#if __BSD_VISIBLE || __ISO_C_VISIBLE >= 1999 || __XSI_VISIBLE
__raw double	acosh(double);
__raw double	asinh(double);
__raw double	atanh(double);
__raw double	cbrt(double);
__raw double	erf(double);
__raw double	erfc(double);
__raw double	exp2(double);
__raw double	expm1(double);
__raw double	fma(double, double, double);
__raw double	hypot(double, double);
__raw int	ilogb(double) __pure2;
__raw double	lgamma(double);
__raw long long llrint(double);
__raw long long llround(double);
__raw double	log1p(double);
__raw double	log2(double);
__raw double	logb(double);
__raw long	lrint(double);
__raw long	lround(double);
__raw double	nan(const char *) __pure2;
__raw double	nextafter(double, double);
__raw double	remainder(double, double);
__raw double	remquo(double, double, int *);
__raw double	rint(double);
#endif /* __BSD_VISIBLE || __ISO_C_VISIBLE >= 1999 || __XSI_VISIBLE */

#if __BSD_VISIBLE || __XSI_VISIBLE
__raw double	j0(double);
__raw double	j1(double);
__raw double	jn(int, double);
__raw double	y0(double);
__raw double	y1(double);
__raw double	yn(int, double);

#if __XSI_VISIBLE <= 500 || __BSD_VISIBLE
__raw double	gamma(double);
#endif

#if __XSI_VISIBLE <= 600 || __BSD_VISIBLE
__raw double	scalb(double, double);
#endif
#endif /* __BSD_VISIBLE || __XSI_VISIBLE */

#if __BSD_VISIBLE || __ISO_C_VISIBLE >= 1999
__raw double	copysign(double, double) __pure2;
__raw double	fdim(double, double);
__raw double	fmax(double, double) __pure2;
__raw double	fmin(double, double) __pure2;
__raw double	nearbyint(double);
__raw double	round(double);
__raw double	scalbln(double, long);
__raw double	scalbn(double, int);
__raw double	tgamma(double);
__raw double	trunc(double);
#endif

/*
 * BSD math library entry points
 */
#if __BSD_VISIBLE
__raw double	drem(double, double);
__raw int	finite(double) __pure2;
__raw int	isnanf(float) __pure2;

/*
 * Reentrant version of gamma & lgamma; passes signgam back by reference
 * as the second argument; user must allocate space for signgam.
 */
__raw double	gamma_r(double, int *);
__raw double	lgamma_r(double, int *);

/*
 * IEEE Test Vector
 */
__raw double	significand(double);
#endif /* __BSD_VISIBLE */

/* float versions of ANSI/POSIX functions */
#if __ISO_C_VISIBLE >= 1999
__raw float	acosf(float);
__raw float	asinf(float);
__raw float	atanf(float);
__raw float	atan2f(float, float);
__raw float	cosf(float);
__raw float	sinf(float);
__raw float	tanf(float);

__raw float	coshf(float);
__raw float	sinhf(float);
__raw float	tanhf(float);

__raw float	exp2f(float);
__raw float	expf(float);
__raw float	expm1f(float);
__raw float	frexpf(float, int *);	/* fundamentally !__pure2 */
__raw int	ilogbf(float) __pure2;
__raw float	ldexpf(float, int);
__raw float	log10f(float);
__raw float	log1pf(float);
__raw float	log2f(float);
__raw float	logf(float);
__raw float	modff(float, float *);	/* fundamentally !__pure2 */

__raw float	powf(float, float);
__raw float	sqrtf(float);

__raw float	ceilf(float);
__raw float	fabsf(float) __pure2;
__raw float	floorf(float);
__raw float	fmodf(float, float);
__raw float	roundf(float);

__raw float	erff(float);
__raw float	erfcf(float);
__raw float	hypotf(float, float);
__raw float	lgammaf(float);
__raw float	tgammaf(float);

__raw float	acoshf(float);
__raw float	asinhf(float);
__raw float	atanhf(float);
__raw float	cbrtf(float);
__raw float	logbf(float);
__raw float	copysignf(float, float) __pure2;
__raw long long llrintf(float);
__raw long long llroundf(float);
__raw long	lrintf(float);
__raw long	lroundf(float);
__raw float	nanf(const char *) __pure2;
__raw float	nearbyintf(float);
__raw float	nextafterf(float, float);
__raw float	remainderf(float, float);
__raw float	remquof(float, float, int *);
__raw float	rintf(float);
__raw float	scalblnf(float, long);
__raw float	scalbnf(float, int);
__raw float	truncf(float);

__raw float	fdimf(float, float);
__raw float	fmaf(float, float, float);
__raw float	fmaxf(float, float) __pure2;
__raw float	fminf(float, float) __pure2;
#endif

/*
 * float versions of BSD math library entry points
 */
#if __BSD_VISIBLE
__raw float	dremf(float, float);
__raw int	finitef(float) __pure2;
__raw float	gammaf(float);
__raw float	j0f(float);
__raw float	j1f(float);
__raw float	jnf(int, float);
__raw float	scalbf(float, float);
__raw float	y0f(float);
__raw float	y1f(float);
__raw float	ynf(int, float);

/*
 * Float versions of reentrant version of gamma & lgamma; passes
 * signgam back by reference as the second argument; user must
 * allocate space for signgam.
 */
__raw float	gammaf_r(float, int *);
__raw float	lgammaf_r(float, int *);

/*
 * float version of IEEE Test Vector
 */
__raw float	significandf(float);
#endif	/* __BSD_VISIBLE */

/*
 * long double versions of ISO/POSIX math functions
 */
#if __ISO_C_VISIBLE >= 1999
__raw long double	acoshl(long double);
__raw long double	acosl(long double);
__raw long double	asinhl(long double);
__raw long double	asinl(long double);
__raw long double	atan2l(long double, long double);
__raw long double	atanhl(long double);
__raw long double	atanl(long double);
__raw long double	cbrtl(long double);
__raw long double	ceill(long double);
__raw long double	copysignl(long double, long double) __pure2;
__raw long double	coshl(long double);
__raw long double	cosl(long double);
__raw long double	erfcl(long double);
__raw long double	erfl(long double);
__raw long double	exp2l(long double);
__raw long double	expl(long double);
__raw long double	expm1l(long double);
__raw long double	fabsl(long double) __pure2;
__raw long double	fdiml(long double, long double);
__raw long double	floorl(long double);
__raw long double	fmal(long double, long double, long double);
__raw long double	fmaxl(long double, long double) __pure2;
__raw long double	fminl(long double, long double) __pure2;
__raw long double	fmodl(long double, long double);
__raw long double	frexpl(long double, int *); /* fundamentally !__pure2 */
__raw long double	hypotl(long double, long double);
__raw int		ilogbl(long double) __pure2;
__raw long double	ldexpl(long double, int);
__raw long double	lgammal(long double);
__raw long long	llrintl(long double);
__raw long long	llroundl(long double);
__raw long double	log10l(long double);
__raw long double	log1pl(long double);
__raw long double	log2l(long double);
__raw long double	logbl(long double);
__raw long double	logl(long double);
__raw long		lrintl(long double);
__raw long		lroundl(long double);
__raw long double	modfl(long double, long double *); /* fundamentally !__pure2 */
__raw long double	nanl(const char *) __pure2;
__raw long double	nearbyintl(long double);
__raw long double	nextafterl(long double, long double);
__raw double		nexttoward(double, long double);
__raw float		nexttowardf(float, long double);
__raw long double	nexttowardl(long double, long double);
__raw long double	powl(long double, long double);
__raw long double	remainderl(long double, long double);
__raw long double	remquol(long double, long double, int *);
__raw long double	rintl(long double);
__raw long double	roundl(long double);
__raw long double	scalblnl(long double, long);
__raw long double	scalbnl(long double, int);
__raw long double	sinhl(long double);
__raw long double	sinl(long double);
__raw long double	sqrtl(long double);
__raw long double	tanhl(long double);
__raw long double	tanl(long double);
__raw long double	tgammal(long double);
__raw long double	truncl(long double);
#endif /* __ISO_C_VISIBLE >= 1999 */

#if __BSD_VISIBLE
__raw long double	lgammal_r(long double, int *);
__raw void		sincos(double, double *, double *);
__raw void		sincosf(float, float *, float *);
__raw void		sincosl(long double, long double *, long double *);
#endif /* __BSD_VISIBLE */

#if __ISO_C_VISIBLE >= 2023
__raw double		cospi(double);
__raw float		cospif(float);
__raw long double 	cospil(long double);
__raw double		sinpi(double);
__raw float		sinpif(float);
__raw long double 	sinpil(long double);
__raw double		tanpi(double);
__raw float		tanpif(float);
__raw long double	tanpil(long double);
#endif /* __ISO_C_VISIBLE >= 2023 */

__END_DECLS

#endif /* !_MATH_H_ */
