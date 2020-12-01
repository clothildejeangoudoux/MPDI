/* include file for internal MPD types and definitions. */

#ifndef __MPD_IMPL_H__
#define __MPD_IMPL_H__


/******************************************************
 ****************** Include files *********************
 ******************************************************/

/* Let's include some standard headers unconditionally as they are
   already needed by several source files. */
#if defined (__cplusplus)
#include <cstdio>
#include <cstring>
#else
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#endif
#include <limits.h>
#include <math.h>

#if _MPFR_EXP_FORMAT == 4
/* mpfr_exp_t will be defined as intmax_t */
# include "mpfr-intmax.h"
#endif

/* config.h est généré automatiquement lors de l'installation de GMP
 * l'inclure dans MPD-IMPL.H ? */
/* Include 'config.h' before using ANY configure macros if needed
   NOTE: It isn't MPD 'config.h', but GMP's one! */
/*#ifdef HAVE_CONFIG_H
  # include "config.h"
  #endif */

#ifndef __GMP_H__
#include "gmp.h"
#endif
#ifndef __MPFR_H__
#include "mpfr.h"
#endif
#ifndef __MPD_H__
#include "mpd.h"
#endif


/******************************************************
 ************* Global Internal Variables *************
 ******************************************************/    

/******************************************************
 ************** mpd_t properties ********************
 ******************************************************/

#define MPD_MANT(x) ((x) -> _mpd_mant)
#define MPD_EXP(x) ((x) -> _mpd_exp)
#define MPD_CLASS(x) ((x) -> _mpd_class) 
#define MPD_PREC(x) ((x) -> _mpd_prec) 

/******************************************************
 **************** class properties *****************
 ******************************************************/

#define MPD_SIGN(x) (MPD_IS_ZERO(x) || (MPD_CLASS(x) == MPD_CLASS_NAN)  ? 0 : ((MPD_CLASS(x) == MPD_CLASS_NEG_INF) || (MPD_CLASS(x) == MPD_CLASS_NEG_NUMBER) ? -1 : 1))

/******************************************************
 **************** exponent properties ***************
 ******************************************************/

/* Limits of the mpd_exp_t type (NOT those of valid exponent values).
   These macros can be used in preprocessor directives. */
# define MPD_EXP_MAX (LONG_MAX) 
# define MPD_EXP_MIN (LONG_MIN)

/* Definition of the exponent limits for MPD numbers.
 * These limits are chosen so that if e is such an exponent, then 
 10e-1 and 10e+1 are representable. This is useful for intermediate 
 computations, in particular the multiplication. */
#undef MPD_EMIN
#undef MPD_EMAX
#define MPD_EMIN (MPD_EXP_MIN+1)
#define MPD_EMAX (MPD_EXP_MAX-1)


/* Use MPD_GET_EXP and MPD_SET_EXP instead of MPD_EXP directly, unless when the exponent may be out-of-range. */

# define MPD_GET_EXP(x)          (mpd_get_exp) (x)
# define MPD_SET_EXP(x, exp)     (mpd_set_exp ((x), (exp)))


/******************************************************
 ******************** Flags ***************************
 ******************************************************/    

/* Definition of flags */
typedef enum {
  MPD_FLAG_UNDERFLOW = 1,
  MPD_FLAG_OVERFLOW = 2,
  MPD_FLAG_NAN = 4,
  MPD_FLAG_INEXACT = 8,
  MPD_FLAG_INVALID = 16,
  MPD_FLAG_DIVBYZERO = 32,
  MPD_FLAG_ALL = 63
} mpd_flags_t;


extern mpd_flags_t __mpd_flags;
extern mpd_prec_t __mpd_default_decimal_precision;
extern mpd_prec_t __mpd_default_init_decimal_precision;
extern mpd_rnd_t __mpd_default_rounding_mode;

#define MPD_FLAGS (__mpd_flags)

/* Replace some common functions for direct access to the global vars */
#define mpd_get_default_rounding_mode() (__mpd_default_rounding_mode + 0)
#define mpd_get_default_prec() (__mpd_default_decimal_precision + 0)

#define mpd_clear_flags()  ((void) (MPD_FLAGS = 0))

#define mpd_clear_underflow() ((void) (MPD_FLAGS &= MPD_FLAG_ALL ^ MPD_FLAG_UNDERFLOW))
#define mpd_clear_overflow() ((void) (MPD_FLAGS &= MPD_FLAG_ALL ^ MPD_FLAG_OVERFLOW))
#define mpd_clear_nanflag() ((void) (MPD_FLAGS &= MPD_FLAG_ALL ^ MPD_FLAG_NAN))
#define mpd_clear_inexflag() ((void) (MPD_FLAGS &= MPD_FLAG_ALL ^ MPD_FLAG_INEXACT))
#define mpd_clear_invalidflag() ((void) (MPD_FLAGS &= MPD_FLAG_ALL ^ MPD_FLAG_INVALID))
#define mpd_clear_divbyzero() ((void) (MPD_FLAGS &= MPD_FLAG_ALL ^ MPD_FLAG_DIVBYZERO))

#define mpd_set_underflow() ((void) (MPD_FLAGS |= MPD_FLAG_UNDERFLOW))
#define mpd_set_overflow() ((void) (MPD_FLAGS |= MPD_FLAG_OVERFLOW))
#define mpd_set_inexflag() ((void) (MPD_FLAGS |= MPD_FLAG_INEXACT))
#define mpd_set_invalidflag() ((void) (MPD_FLAGS |= MPD_FLAG_INVALID))
#define mpd_set_divbyzero() ((void) (MPD_FLAGS |= MPD_FLAG_DIVBYZERO))


/******************************************************
 ****** Singular Values (NAN, INF, ZERO) ********
 ******************************************************/

#define MPD_IS_SINGULAR(x) ((MPD_CLASS(x) != MPD_CLASS_NEG_NUMBER) || ( MPD_CLASS(x) != MPD_CLASS_POS_NUMBER))
#define MPD_IS_NAN(x) (MPD_CLASS(x) == MPD_CLASS_NAN)
#define MPD_IS_INF(x) ((MPD_CLASS(x) == MPD_CLASS_NEG_INF) || (MPD_CLASS(x) == MPD_CLASS_POS_INF))
#define MPD_IS_ZERO(x) ((MPD_CLASS(x) == MPD_CLASS_NEG_ZERO) || (MPD_CLASS(x) == MPD_CLASS_POS_ZERO))
#define MPD_NOTZERO(x) (!MPD_IS_ZERO(x))

/******************************************************
 ***************** Sign Macros **********************
 ******************************************************/

#define MPD_MULT_SIGN(a,b) (MPD_IS_NEG(a) ? (MPD_IS_NEG(b) ? 1 : -1) : (MPD_IS_NEG(b) ? -1 : 1))


/******************************************************
 ***************** Ternary Value Macros ***************
 ******************************************************/

#define IS_EXACT(i) ((i) == 0 ? 1 : 0)
#define IS_INEXACT(i) (!IS_EXACT(i))

/* Macros for functions returning two inexact values in an 'int' */
#define INEXPOS(y) ((y) == 0 ? 0 : (((y) > 0) ? 1 : 2))
#define INEX(y,z) (INEXPOS(y) | (INEXPOS(z) << 2))
#define INEX3(x,y,z) (INEXPOS(x) | (INEXPOS(y) << 2) | (INEXPOS(z) << 4))

/* When returning the ternary inexact value, ALWAYS use one of the
   following two macros, unless the flag comes from another function
   returning the ternary inexact value */
#define MPD_RET(I) return (I) ? ((MPD_FLAGS |= MPD_FLAG_INEXACT), (I)) : 0
#define MPD_RET_NAN return(MPD_FLAGS |= MPD_FLAG_NAN), 0

/*****************************************************
 ************* Inline Assignment *******************
 *****************************************************/

#define MPD_SET_POS_ZERO(x)				\
  MPD_CLASS(x) = MPD_CLASS_POS_ZERO;		\
  mpz_set_ui(MPD_MANT(x),0);			\
  MPD_EXP(x) = 0;				

#define MPD_SET_NEG_ZERO(x)			\
  MPD_CLASS(x) = MPD_CLASS_NEG_ZERO;		\
  mpz_set_ui(MPD_MANT(x),0);			\
  MPD_EXP(x) = 0;				

#define MPD_SET_ZERO(x)				\
  MPD_CLASS(x) = MPD_CLASS_POS_ZERO;		\
  mpz_set_ui(MPD_MANT(x),0);			\
  MPD_EXP(x) = 0;				


#define MPD_SET_POS_INF(x)				\
  MPD_CLASS(x) = MPD_CLASS_POS_INF;		\
  mpz_set_ui(MPD_MANT(x),0);			\
  MPD_EXP(x) = 0;				

#define MPD_SET_NEG_INF(x)				\
  MPD_CLASS(x) = MPD_CLASS_NEG_INF;		\
  mpz_set_ui(MPD_MANT(x),0);			\
  MPD_EXP(x) = 0;				

#define MPD_SET_NAN(x)						\
  MPD_CLASS(x) = MPD_CLASS_NAN;						\
  mpz_set_ui(MPD_MANT(x),0);						\
  MPD_EXP(x) = 0;				

#define MPD_SET(x,y)				\
  MPD_CLASS(x) = MPD_CLASS(y);			\
  mpz_set(MPD_MANT(x),MPD_MANT(y));		\
  mpd_set_exp(x,MPD_EXP(y));


/******************************************************
 ******************* Sign Macros ********************
 ******************************************************/

#define MPD_SIGN_POS (1)
#define MPD_SIGN_NEG (-1)
  
#define MPD_IS_NEG(x) (MPD_SIGN(x) < 0)
#define MPD_IS_POS(x) (MPD_SIGN(x) > 0)

/******************************************************
 ******************* Double Macros *****************
 ******************************************************/

/* Note: In the past, there was specific code for _GMP_IEEE_FLOATS, which
   was based on NaN and Inf memory representations. This code was breaking
   the aliasing rules (see ISO C99, 6.5#6 and 6.5#7 on the effective type)
   and for this reason it did not behave correctly with GCC 4.5.0 20091119.
   The code needed a memory transfer and was probably not better than the
   macros below with a good compiler (a fix based on the NaN / Inf memory
   representation would be even worse due to C limitations), and this code
   could be selected only when MPFR was built with --with-gmp-build, thus
   introducing a difference (bad for maintaining/testing MPFR); therefore
   it has been removed. The old code required that the argument x be an
   lvalue of type double. We still require that, in case one would need
   to change the macros below, e.g. for some broken compiler. But the
   LVALUE(x) condition could be removed if really necessary. */
/* Below, the &(x) == &(x) || &(x) != &(x) allows to make sure that x
   is a lvalue without (probably) any warning from the compiler.  The
   &(x) != &(x) is needed to avoid a failure under Mac OS X 10.4.11
   (with Xcode 2.4.1, i.e. the latest one). */
#define LVALUE(x) (&(x) == &(x) || &(x) != &(x))
#define DOUBLE_ISINF(x) (LVALUE(x) && ((x) > DBL_MAX || (x) < -DBL_MAX))

/* The DOUBLE_ISNAN(x) macro is also valid on long double x
   (assuming that the compiler isn't too broken). */
# define DOUBLE_ISNAN(x) (LVALUE(x) && (x) != (x))

/*****************************************************
 ************* precision macros ********************
 *****************************************************/
#define MPD_MAX_PREC_INT 5
#define MPD_MAX_PREC_UINT 5
#define MPD_MAX_PREC_LONG 10
#define MPD_MAX_PREC_ULONG 10


/******************************************************
 ******************* MPFR Macros *****************
 ******************************************************/

#define MPFR_EXP(x)       ((x)->_mpfr_exp)
#define MPFR_SIGN(x)       ((x)->_mpfr_sign)

/* Limits of the mpfr_exp_t type (NOT those of valid exponent values).
   These macros can be used in preprocessor directives. */
#if   _MPFR_EXP_FORMAT == 1
# define MPFR_EXP_MAX (SHRT_MAX)
# define MPFR_EXP_MIN (SHRT_MIN)
#elif _MPFR_EXP_FORMAT == 2
# define MPFR_EXP_MAX (INT_MAX)
# define MPFR_EXP_MIN (INT_MIN)
#elif _MPFR_EXP_FORMAT == 3
# define MPFR_EXP_MAX (LONG_MAX)
# define MPFR_EXP_MIN (LONG_MIN)
#elif _MPFR_EXP_FORMAT == 4
# define MPFR_EXP_MAX (MPFR_INTMAX_MAX)
# define MPFR_EXP_MIN (MPFR_INTMAX_MIN)
#else
# error "Invalid MPFR Exp format"
#endif

/* Enum special value of exponent. */
# define MPFR_EXP_ZERO (MPFR_EXP_MIN+1)
# define MPFR_EXP_NAN  (MPFR_EXP_MIN+2)
# define MPFR_EXP_INF  (MPFR_EXP_MIN+3)

#define MPFR_IS_NAN(x)   (MPFR_EXP(x) == MPFR_EXP_NAN)
#define MPFR_SET_NAN(x)  (MPFR_EXP(x) =  MPFR_EXP_NAN)
#define MPFR_IS_INF(x)   (MPFR_EXP(x) == MPFR_EXP_INF)
#define MPFR_SET_INF(x)  (MPFR_EXP(x) =  MPFR_EXP_INF)
#define MPFR_IS_ZERO(x)  (MPFR_EXP(x) == MPFR_EXP_ZERO)
#define MPFR_SET_ZERO(x) (MPFR_EXP(x) =  MPFR_EXP_ZERO)
#define MPFR_NOTZERO(x)  (MPFR_EXP(x) != MPFR_EXP_ZERO)

/* from MPFI code */
#define MPFR_RET_NAN do {mpfr_set_nanflag(); return 0;} while (0)

#define MPFR_SET_SIGN(x, s) ( MPFR_SIGN(x) = s)

#endif /* __MPD_IMPL_H__ */
