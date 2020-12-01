/* mpfd.h -- include file for mpfd */

#ifndef __MPD_H__
#define __MPD_H__

/* GMP inlusion */
#ifndef __GMP_H__
# include <gmp.h>
#endif

/* MPFR inlusion */
#ifndef __MPFR_H__
# include <mpfr.h>
#endif

#include <stdint.h>

/*******************************************
 ********** Type definition ***************
 *******************************************/

/* Definition of decimal class */
typedef enum {
  MPD_CLASS_NAN = 0,
  MPD_CLASS_NEG_INF = 1,
  MPD_CLASS_NEG_NUMBER = 2,
  MPD_CLASS_NEG_ZERO = 3,
  MPD_CLASS_POS_ZERO = 4,
  MPD_CLASS_POS_NUMBER = 5,
  MPD_CLASS_POS_INF = 6,
} mpd_class_t;

/* Definition of rounding modes */
typedef enum {
  MPD_RNDN = 0,  /* round to nearest, with ties to even */
  MPD_RNDZ = 1,    /* round toward zero */
  MPD_RNDU = 2,    /* round toward +Inf */
  MPD_RNDD = 3,    /* round toward -Inf */
  MPD_RNDA = 4  /* round away from zero */
} mpd_rnd_t;

/* Generical types for precision and exponent */
typedef uint64_t mpd_prec_t;
typedef int64_t mpd_exp_t;

#define MPD_PREC_MIN 2
#define MPD_PREC_MAX ((mpd_prec_t)(~(mpd_prec_t)0)>>1)

/* Definition of the main structure */
typedef struct {
  mpz_t _mpd_mant;   /* mantisse (base 10, signée) */
  mpd_exp_t _mpd_exp;      /* exposant */
  mpd_class_t _mpd_class;  /* class */
  mpd_prec_t _mpd_prec; /* precision */
} __mpd_struct;

typedef __mpd_struct mpd_t[1];
typedef __mpd_struct *mpd_ptr;
typedef const __mpd_struct *mpd_srcptr;

#ifdef __cplusplus
extern "C" {
#endif
  
  /* Initialization and destruction*/
  void    mpd_init       (mpd_ptr);
  void    mpd_init2      (mpd_ptr, mpd_prec_t);
  void    mpd_clear      (mpd_ptr);
  
  /* Precision related functions */
  void mpd_set_default_prec (mpd_prec_t);
  void mpd_set_prec(mpd_ptr,mpd_prec_t);
  mpd_prec_t mpd_get_prec (mpd_srcptr);

  /* Exponent related functions */
  int mpd_set_exp (mpd_ptr, mpd_exp_t);
  mpd_exp_t mpd_get_exp (mpd_srcptr);
  
  /* assignment functions */
  int     mpd_set        (mpd_ptr, mpd_srcptr, mpd_rnd_t);
  int     mpd_set_si     (mpd_ptr, const long,mpd_rnd_t);
  int     mpd_set_ui     (mpd_ptr, const unsigned long,mpd_rnd_t);
  int     mpd_set_d      (mpd_ptr, const double, mpd_rnd_t);
  int     mpd_set_z      (mpd_ptr, mpz_srcptr,mpd_rnd_t);
  int     mpd_set_fr     (mpd_ptr, mpfr_srcptr,mpd_rnd_t); 
  int     mpd_set_str    (mpd_ptr, const char *,mpd_rnd_t);
  
  /* Conversions                                  */
  double  mpd_get_d      (mpd_srcptr);
  int     mpd_get_fr     (mpfr_ptr, mpd_srcptr,mpd_rnd_t);
  
  /* Basic arithmetic operations                  */
 
  /* arithmetic operations between two mult. prec. decimals */
  int     mpd_add        (mpd_ptr, mpd_srcptr, mpd_srcptr,mpd_rnd_t);
  int     mpd_add_loop        (mpd_ptr, mpd_srcptr, mpd_srcptr,mpd_rnd_t);
  int     mpd_sub        (mpd_ptr, mpd_srcptr, mpd_srcptr, mpd_rnd_t);
  int     mpd_mul        (mpd_ptr, mpd_srcptr, mpd_srcptr,mpd_rnd_t);
  int     mpd_mul_loop        (mpd_ptr, mpd_srcptr, mpd_srcptr,mpd_rnd_t);
  int     mpd_div        (mpd_ptr, mpd_srcptr, mpd_srcptr,mpd_rnd_t);
  int     mpd_sqrt        (mpd_ptr, mpd_srcptr, mpd_rnd_t);
  
  /* arithmetic operations between a mult. prec. decimal and a double prec. floating-point */
  void     mpd_add_d      (mpd_ptr, mpd_srcptr, const double);
  void     mpd_sub_d      (mpd_ptr, mpd_srcptr, const double);
  void     mpd_d_sub      (mpd_ptr, const double, mpd_srcptr);
  void     mpd_mul_d      (mpd_ptr, mpd_srcptr, const double);
  void     mpd_div_d      (mpd_ptr, mpd_srcptr, const double);
  void     mpd_d_div      (mpd_ptr, const double, mpd_srcptr);
  
  /* arithmetic operations between an mult. prec. decimal and an unsigned long integer */
  void     mpd_add_ui     (mpd_ptr, mpd_srcptr, const unsigned long);
  void     mpd_sub_ui     (mpd_ptr, mpd_srcptr, const unsigned long);
  void     mpd_ui_sub     (mpd_ptr, const unsigned long, mpd_srcptr);
  void     mpd_mul_ui     (mpd_ptr, mpd_srcptr, const unsigned long);
  void     mpd_div_ui     (mpd_ptr, mpd_srcptr, const unsigned long);
  void     mpd_ui_div     (mpd_ptr, const unsigned long, mpd_srcptr);
  
  /* arithmetic operations between an mult. prec. decimal and a long integer */
  void     mpd_add_si     (mpd_ptr, mpd_srcptr, const long);
  void     mpd_sub_si     (mpd_ptr, mpd_srcptr, const long);
  void     mpd_si_sub     (mpd_ptr, const long, mpd_srcptr);
  void     mpd_mul_si     (mpd_ptr, mpd_srcptr, const long);
  void     mpd_div_si     (mpd_ptr, mpd_srcptr, const long);
  void     mpd_si_div     (mpd_ptr, const long, mpd_srcptr);
  
  /* arithmetic operations between a mult. prec. decimal and a multiple prec. integer */
  void     mpd_add_z      (mpd_ptr, mpd_srcptr, mpz_srcptr);
  void     mpd_sub_z      (mpd_ptr, mpd_srcptr, mpz_srcptr);
  void     mpd_z_sub      (mpd_ptr, mpz_srcptr, mpd_srcptr);
  void     mpd_mul_z      (mpd_ptr, mpd_srcptr, mpz_srcptr);
  void     mpd_div_z      (mpd_ptr, mpd_srcptr, mpz_srcptr);
  void     mpd_z_div      (mpd_ptr, mpz_srcptr, mpd_srcptr);

  /* arithmetic operations between a mult. prec. decimal and a mult. prec. floating-pt nb */
  void     mpd_add_fr     (mpd_ptr, mpd_srcptr, mpfr_srcptr);
  void     mpd_sub_fr     (mpd_ptr, mpd_srcptr, mpfr_srcptr);
  void     mpd_fr_sub     (mpd_ptr, mpfr_srcptr, mpd_srcptr);
  void     mpd_mul_fr     (mpd_ptr, mpd_srcptr, mpfr_srcptr);
  void     mpd_div_fr     (mpd_ptr, mpd_srcptr, mpfr_srcptr);
  void     mpd_fr_div     (mpd_ptr, mpfr_srcptr, mpd_srcptr);

  /* Special functions                                        */
  int     mpd_log        (mpd_ptr, mpd_srcptr,mpd_rnd_t);
  int     mpd_exp        (mpd_ptr, mpd_srcptr,mpd_rnd_t);
  int     mpd_exp2       (mpd_ptr, mpd_srcptr,mpd_rnd_t);
  
  int     mpd_cos        (mpd_ptr, mpd_srcptr,mpd_rnd_t);
  int     mpd_sin        (mpd_ptr, mpd_srcptr,mpd_rnd_t);
  int     mpd_tan        (mpd_ptr, mpd_srcptr,mpd_rnd_t);
  int     mpd_acos       (mpd_ptr, mpd_srcptr,mpd_rnd_t);
  int     mpd_asin       (mpd_ptr, mpd_srcptr,mpd_rnd_t);
  int     mpd_atan       (mpd_ptr, mpd_srcptr,mpd_rnd_t);
  int     mpd_atan2      (mpd_ptr, mpd_srcptr, mpd_srcptr,mpd_rnd_t);
  
  int     mpd_sec        (mpd_ptr, mpd_srcptr,mpd_rnd_t);
  int     mpd_csc        (mpd_ptr, mpd_srcptr,mpd_rnd_t);
  int     mpd_cot        (mpd_ptr, mpd_srcptr,mpd_rnd_t);
  
  int     mpd_cosh       (mpd_ptr, mpd_srcptr,mpd_rnd_t);
  int     mpd_sinh       (mpd_ptr, mpd_srcptr,mpd_rnd_t);
  int     mpd_tanh       (mpd_ptr, mpd_srcptr,mpd_rnd_t);
  int     mpd_acosh      (mpd_ptr, mpd_srcptr,mpd_rnd_t);
  int     mpd_asinh      (mpd_ptr, mpd_srcptr,mpd_rnd_t);
  int     mpd_atanh      (mpd_ptr, mpd_srcptr,mpd_rnd_t);
  
  int     mpd_sech       (mpd_ptr, mpd_srcptr,mpd_rnd_t);
  int     mpd_csch       (mpd_ptr, mpd_srcptr,mpd_rnd_t);
  int     mpd_coth       (mpd_ptr, mpd_srcptr,mpd_rnd_t);
  
  int     mpd_log1p      (mpd_ptr, mpd_srcptr,mpd_rnd_t);
  int     mpd_expm1      (mpd_ptr, mpd_srcptr,mpd_rnd_t);
  
  int     mpd_log2       (mpd_ptr, mpd_srcptr,mpd_rnd_t);
  int     mpd_log10      (mpd_ptr, mpd_srcptr,mpd_rnd_t);
  
  int     mpd_hypot      (mpd_ptr, mpd_srcptr, mpd_srcptr,mpd_rnd_t);
  
  int     mpd_const_log2         (mpd_ptr,mpd_rnd_t);
  int     mpd_const_pi           (mpd_ptr,mpd_rnd_t);
  int     mpd_const_euler        (mpd_ptr,mpd_rnd_t);
  int     mpd_const_catalan      (mpd_ptr,mpd_rnd_t);
  
  /* Comparison functions                                     */
  int    mpd_cmp       (mpd_srcptr, mpd_srcptr);

  int    mpd_cmp_d     (mpd_srcptr, const double);
  int    mpd_cmp_ui    (mpd_srcptr, const unsigned long);
  int    mpd_cmp_si    (mpd_srcptr, const long);
  int    mpd_cmp_z     (mpd_srcptr, mpz_srcptr);
  int    mpd_cmp_fr    (mpd_srcptr, mpfr_srcptr);

  /* Reduction function */
  int mpd_reduce   (mpd_ptr, mpd_srcptr);
  int mpd_scale (mpd_ptr, mpd_ptr, mpd_srcptr,mpd_srcptr);

  /* Other functions */
  int mpd_neg(mpd_ptr,mpd_srcptr,mpd_rnd_t);
  mpd_prec_t mpd_precinbase2(mpd_prec_t);
  mpd_prec_t mpd_precinbase10(mpd_prec_t);
  int mpd_sgn(mpd_srcptr);
  int mpd_signbit(mpd_srcptr);
  void mpd_swap(mpd_ptr,mpd_ptr);
  size_t mpd_sizeinbase10 (mpz_srcptr);
  int mpd_round (mpz_ptr, mpz_srcptr, mpd_prec_t, mpd_rnd_t);
  
  /* class functions */
  void mpd_set_nan (mpd_ptr);
  void mpd_set_inf (mpd_ptr,int);
  int mpd_nan_p (mpd_srcptr);
  int mpd_zero_p (mpd_srcptr);
  int mpd_inf_p (mpd_srcptr);
  void  mpd_set_nanflag();
  
#ifdef __cplusplus
}
#endif

  
#endif /* __MPD_H__ */
