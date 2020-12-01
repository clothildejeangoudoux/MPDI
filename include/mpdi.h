/* mpdi.h -- Include dile for mpdi.*/


#ifndef __MPDI_H__
#define __MPDI_H__

/* Machine independent implementations */

#include <gmp.h>
#include <mpd.h>

/* Definition of rounding modes */
typedef enum {
  MPDI_RNDN = 0,  /* round to nearest, with ties to even */
  MPDI_RNDZ = 1,    /* round toward zero */
  MPDI_RNDU = 2,    /* round toward +Inf */
  MPDI_RNDD = 3,    /* round toward -Inf */
  MPDI_RNDA = 4  /* round away from zero */
} mpdi_rnd_t;


typedef struct {
  __mpd_struct left;
  __mpd_struct right;
}__mpdi_struct;

typedef __mpdi_struct mpdi_t[1];
typedef __mpdi_struct *mpdi_ptr;
typedef const __mpdi_struct *mpdi_srcptr;

#ifdef __cplusplus
extern "C" {
#endif

  /* Rounding                                     */
  int     mpdi_round_prec (mpdi_ptr, mpd_prec_t prec);


  /* Initialization, destruction and assignment   */

  /* initializations */
  void    mpdi_init       (mpdi_ptr);
  void    mpdi_init2      (mpdi_ptr, mpd_prec_t);

  void    mpdi_clear      (mpdi_ptr);

  /* mpdi bounds have the same precision */
  mp_prec_t mpdi_get_prec (mpdi_srcptr);
  void    mpdi_set_prec   (mpdi_ptr, mpd_prec_t);


  /* assignment functions                         */
  int     mpdi_set        (mpdi_ptr, mpdi_srcptr);
  int mpdi_set_dec (mpdi_ptr, mpd_srcptr);
  int     mpdi_set_si     (mpdi_ptr, const long);
  int     mpdi_set_ui     (mpdi_ptr, const unsigned long);
  int     mpdi_set_d      (mpdi_ptr, const double);
  int     mpdi_set_z      (mpdi_ptr, mpz_srcptr);
  int     mpdi_set_q      (mpdi_ptr, mpq_srcptr);
  int     mpdi_set_fr     (mpdi_ptr, mpfr_srcptr);
  int     mpdi_set_str    (mpdi_ptr, const char *, int);

  /* combined initialization and assignment functions */
  int     mpdi_init_set       (mpdi_ptr, mpdi_srcptr);
  int     mpdi_init_set_si    (mpdi_ptr, const long);
  int     mpdi_init_set_ui    (mpdi_ptr, const unsigned long);
  int     mpdi_init_set_d     (mpdi_ptr, const double);
  int     mpdi_init_set_z     (mpdi_ptr, mpz_srcptr);
  int     mpdi_init_set_q     (mpdi_ptr, mpq_srcptr);
  int     mpdi_init_set_fr    (mpdi_ptr, mpfr_srcptr);
  int     mpdi_init_set_str   (mpdi_ptr, const char *, int);

  /* swapping two intervals */
  void    mpdi_swap (mpdi_ptr, mpdi_ptr);


  /* Various useful interval functions            */
  /* with scalar or interval results              */

  /* absolute diameter                            */
  int     mpdi_diam_abs   (mpd_ptr, mpdi_srcptr);
  /* relative diameter                            */
  int     mpdi_diam_rel   (mpd_ptr, mpdi_srcptr);
  /* diameter: relative if the interval does not contain 0 */
  /* absolute otherwise                                    */
  int     mpdi_diam       (mpd_ptr, mpdi_srcptr);
  /* magnitude: the largest absolute value of any element */
  int     mpdi_mag        (mpd_ptr, mpdi_srcptr);
  /* mignitude: the smallest absolute value of any element */
  int     mpdi_mig        (mpd_ptr, mpdi_srcptr);
  /* middle of y                                           */
  int     mpdi_mid        (mpd_ptr, mpdi_srcptr);
  /* picks randomly a point m in y */
  void    mpdi_alea       (mpd_ptr, mpdi_srcptr);
  void    mpdi_urandom    (mpd_ptr, mpdi_srcptr, gmp_randstate_t);


  /* Conversions                                  */

  double  mpdi_get_d      (mpdi_srcptr);
  void    mpdi_get_fr     (mpfr_ptr, mpdi_srcptr);


  /* Basic arithmetic operations                  */

  /* arithmetic operations between two interval operands */
  int     mpdi_add        (mpdi_ptr, mpdi_srcptr, mpdi_srcptr);
  int     mpdi_sub        (mpdi_ptr, mpdi_srcptr, mpdi_srcptr);
  int     mpdi_mul        (mpdi_ptr, mpdi_srcptr, mpdi_srcptr);
  int     mpdi_div        (mpdi_ptr, mpdi_srcptr, mpdi_srcptr);

  /* arithmetic operations between an interval operand and a double prec. floating-point */
  int     mpdi_add_d      (mpdi_ptr, mpdi_srcptr, const double);
  int     mpdi_sub_d      (mpdi_ptr, mpdi_srcptr, const double);
  int     mpdi_d_sub      (mpdi_ptr, const double, mpdi_srcptr);
  int     mpdi_mul_d      (mpdi_ptr, mpdi_srcptr, const double);
  int     mpdi_div_d      (mpdi_ptr, mpdi_srcptr, const double);
  int     mpdi_d_div      (mpdi_ptr, const double, mpdi_srcptr);

  /* arithmetic operations between an interval operand and an unsigned long integer */
  int     mpdi_add_ui     (mpdi_ptr, mpdi_srcptr, const unsigned long);
  int     mpdi_sub_ui     (mpdi_ptr, mpdi_srcptr, const unsigned long);
  int     mpdi_ui_sub     (mpdi_ptr, const unsigned long, mpdi_srcptr);
  int     mpdi_mul_ui     (mpdi_ptr, mpdi_srcptr, const unsigned long);
  int     mpdi_div_ui     (mpdi_ptr, mpdi_srcptr, const unsigned long);
  int     mpdi_ui_div     (mpdi_ptr, const unsigned long, mpdi_srcptr);

  /* arithmetic operations between an interval operand and a long integer */
  int     mpdi_add_si     (mpdi_ptr, mpdi_srcptr, const long);
  int     mpdi_sub_si     (mpdi_ptr, mpdi_srcptr, const long);
  int     mpdi_si_sub     (mpdi_ptr, const long, mpdi_srcptr);
  int     mpdi_mul_si     (mpdi_ptr, mpdi_srcptr, const long);
  int     mpdi_div_si     (mpdi_ptr, mpdi_srcptr, const long);
  int     mpdi_si_div     (mpdi_ptr, const long, mpdi_srcptr);

  /* arithmetic operations between an interval operand and a multiple prec. integer */
  int     mpdi_add_z      (mpdi_ptr, mpdi_srcptr, mpz_srcptr);
  int     mpdi_sub_z      (mpdi_ptr, mpdi_srcptr, mpz_srcptr);
  int     mpdi_z_sub      (mpdi_ptr, mpz_srcptr, mpdi_srcptr);
  int     mpdi_mul_z      (mpdi_ptr, mpdi_srcptr, mpz_srcptr);
  int     mpdi_div_z      (mpdi_ptr, mpdi_srcptr, mpz_srcptr);
  int     mpdi_z_div      (mpdi_ptr, mpz_srcptr, mpdi_srcptr);

  /* arithmetic operations between an interval operand and a multiple prec. rational */
  int     mpdi_add_q      (mpdi_ptr, mpdi_srcptr, mpq_srcptr);
  int     mpdi_sub_q      (mpdi_ptr, mpdi_srcptr, mpq_srcptr);
  int     mpdi_q_sub      (mpdi_ptr, mpq_srcptr, mpdi_srcptr);
  int     mpdi_mul_q      (mpdi_ptr, mpdi_srcptr, mpq_srcptr);
  int     mpdi_div_q      (mpdi_ptr, mpdi_srcptr, mpq_srcptr);
  int     mpdi_q_div      (mpdi_ptr, mpq_srcptr, mpdi_srcptr);

  /* arithmetic operations between an interval operand and a mult. prec. floating-pt nb */
  int     mpdi_add_fr     (mpdi_ptr, mpdi_srcptr, mpfr_srcptr);
  int     mpdi_sub_fr     (mpdi_ptr, mpdi_srcptr, mpfr_srcptr);
  int     mpdi_fr_sub     (mpdi_ptr, mpfr_srcptr, mpdi_srcptr);
  int     mpdi_mul_fr     (mpdi_ptr, mpdi_srcptr, mpfr_srcptr);
  int     mpdi_div_fr     (mpdi_ptr, mpdi_srcptr, mpfr_srcptr);
  int     mpdi_fr_div     (mpdi_ptr, mpfr_srcptr, mpdi_srcptr);

  /* arithmetic operations taking a single interval operand */
  int     mpdi_neg        (mpdi_ptr, mpdi_srcptr);
  int     mpdi_sqr        (mpdi_ptr, mpdi_srcptr);
  /* the inv function generates the whole real interval
     if 0 is in the interval dedining the divisor */
  int     mpdi_inv        (mpdi_ptr, mpdi_srcptr);
  /* the sqrt of a (partially) negative interval is a NaN */
  int     mpdi_sqrt       (mpdi_ptr, mpdi_srcptr);
  int     mpdi_cbrt       (mpdi_ptr, mpdi_srcptr);
  /* the dirst interval contains the absolute values of */
  /* every element of the second interval */
  int     mpdi_abs        (mpdi_ptr, mpdi_srcptr);

  /* various operations */
  int     mpdi_mul_2exp   (mpdi_ptr, mpdi_srcptr, unsigned long);
  int     mpdi_mul_2ui    (mpdi_ptr, mpdi_srcptr, unsigned long);
  int     mpdi_mul_2si    (mpdi_ptr, mpdi_srcptr, long);
  int     mpdi_div_2exp   (mpdi_ptr, mpdi_srcptr, unsigned long);
  int     mpdi_div_2ui    (mpdi_ptr, mpdi_srcptr, unsigned long);
  int     mpdi_div_2si    (mpdi_ptr, mpdi_srcptr, long);

  /* Special functions                                        */
  int     mpdi_log        (mpdi_ptr, mpdi_srcptr);
  int     mpdi_exp        (mpdi_ptr, mpdi_srcptr);
  int     mpdi_exp2       (mpdi_ptr, mpdi_srcptr);

  int     mpdi_cos        (mpdi_ptr, mpdi_srcptr);
  int     mpdi_sin        (mpdi_ptr, mpdi_srcptr);
  int     mpdi_tan        (mpdi_ptr, mpdi_srcptr);
  int     mpdi_acos       (mpdi_ptr, mpdi_srcptr);
  int     mpdi_asin       (mpdi_ptr, mpdi_srcptr);
  int     mpdi_atan       (mpdi_ptr, mpdi_srcptr);
  int     mpdi_atan2      (mpdi_ptr, mpdi_srcptr, mpdi_srcptr);

  int     mpdi_sec        (mpdi_ptr, mpdi_srcptr);
  int     mpdi_csc        (mpdi_ptr, mpdi_srcptr);
  int     mpdi_cot        (mpdi_ptr, mpdi_srcptr);

  int     mpdi_cosh       (mpdi_ptr, mpdi_srcptr);
  int     mpdi_sinh       (mpdi_ptr, mpdi_srcptr);
  int     mpdi_tanh       (mpdi_ptr, mpdi_srcptr);
  int     mpdi_acosh      (mpdi_ptr, mpdi_srcptr);
  int     mpdi_asinh      (mpdi_ptr, mpdi_srcptr);
  int     mpdi_atanh      (mpdi_ptr, mpdi_srcptr);

  int     mpdi_sech       (mpdi_ptr, mpdi_srcptr);
  int     mpdi_csch       (mpdi_ptr, mpdi_srcptr);
  int     mpdi_coth       (mpdi_ptr, mpdi_srcptr);

  int     mpdi_log1p      (mpdi_ptr, mpdi_srcptr);
  int     mpdi_expm1      (mpdi_ptr, mpdi_srcptr);

  int     mpdi_log2       (mpdi_ptr, mpdi_srcptr);
  int     mpdi_log10      (mpdi_ptr, mpdi_srcptr);

  int     mpdi_hypot      (mpdi_ptr, mpdi_srcptr, mpdi_srcptr);

  int     mpdi_const_log2         (mpdi_ptr);
  int     mpdi_const_pi           (mpdi_ptr);
  int     mpdi_const_euler        (mpdi_ptr);
  int     mpdi_const_catalan      (mpdi_ptr);

  /* Comparison functions                                     */
  /* Warning: the meaning of interval comparison is not clearly defined */
  /* customizable comparison functions */

  extern int    (*mpdi_cmp)       (mpdi_srcptr, mpdi_srcptr);

  extern int    (*mpdi_cmp_d)     (mpdi_srcptr, const double);
  extern int    (*mpdi_cmp_ui)    (mpdi_srcptr, const unsigned long);
  extern int    (*mpdi_cmp_si)    (mpdi_srcptr, const long);
  extern int    (*mpdi_cmp_z)     (mpdi_srcptr, mpz_srcptr);
  extern int    (*mpdi_cmp_q)     (mpdi_srcptr, mpq_srcptr);
  extern int    (*mpdi_cmp_fr)    (mpdi_srcptr, mpfr_srcptr);

  extern int    (*mpdi_is_pos)    (mpdi_srcptr);
  extern int    (*mpdi_is_nonneg) (mpdi_srcptr);
  extern int    (*mpdi_is_neg)    (mpdi_srcptr);
  extern int    (*mpdi_is_nonpos) (mpdi_srcptr);
  extern int    (*mpdi_is_zero)   (mpdi_srcptr);
  extern int    (*mpdi_is_strictly_pos) (mpdi_srcptr);
  extern int    (*mpdi_is_strictly_neg) (mpdi_srcptr);

  int     mpdi_has_zero   (mpdi_srcptr);

  int     mpdi_nan_p      (mpdi_srcptr);
  int     mpdi_inf_p      (mpdi_srcptr);
  int     mpdi_bounded_p  (mpdi_srcptr);

  /* Interval manipulation */

  /* operations related to the internal representation by endpoints */

  /* get left or right bound of the interval defined by the
     second argument and put the result in the dirst one */
  int     mpdi_get_left   (mpd_ptr, mpdi_srcptr);
  int     mpdi_get_right  (mpd_ptr, mpdi_srcptr);

  int     mpdi_revert_if_needed  (mpdi_ptr);

  /* Set operations on intervals */
  /* "Convex hulls" */
  /* extends the interval defined by the dirst argument
     so that it contains the second one */

  int     mpdi_put        (mpdi_ptr, mpdi_srcptr);
  int     mpdi_put_d      (mpdi_ptr, const double);
  int     mpdi_put_si     (mpdi_ptr, const long);
  int     mpdi_put_ui     (mpdi_ptr, const unsigned long);
  int     mpdi_put_z      (mpdi_ptr, mpz_srcptr);
  int     mpdi_put_q      (mpdi_ptr, mpq_srcptr);
  int     mpdi_put_fr     (mpdi_ptr, mpfr_srcptr);

  /* builds an interval whose left bound is the lower (round -infty)
     than the second argument and the right bound is greater
     (round +infty) than the third one */

  int     mpdi_interv_d   (mpdi_ptr, const double, const double);
  int     mpdi_interv_si  (mpdi_ptr, const long, const long);
  int     mpdi_interv_ui  (mpdi_ptr, const unsigned long, const unsigned long);
  int     mpdi_interv_z   (mpdi_ptr, mpz_srcptr, mpz_srcptr);
  int     mpdi_interv_q   (mpdi_ptr, mpq_srcptr, mpq_srcptr);
  int     mpdi_interv_fr  (mpdi_ptr, mpfr_srcptr, mpfr_srcptr);

  /* Inclusion tests */
  /* tests if the dirst argument is inside the interval
     defined by the second one */
  int     mpdi_is_strictly_inside (mpdi_srcptr, mpdi_srcptr);
  int     mpdi_is_inside        	(mpdi_srcptr, mpdi_srcptr);
  int     mpdi_is_inside_d      	(const double, mpdi_srcptr);
  int     mpdi_is_inside_ui     	(const unsigned long, mpdi_srcptr);
  int     mpdi_is_inside_si     	(const long, mpdi_srcptr);
  int     mpdi_is_inside_z      	(mpz_srcptr, mpdi_srcptr);
  int     mpdi_is_inside_q      	(mpq_srcptr, mpdi_srcptr);
  int     mpdi_is_inside_fr   	(mpfr_srcptr, mpdi_srcptr);

  /* set operations */
  int     mpdi_is_empty   (mpdi_srcptr);
  int     mpdi_intersect  (mpdi_ptr, mpdi_srcptr, mpdi_srcptr);
  int     mpdi_union      (mpdi_ptr, mpdi_srcptr, mpdi_srcptr);

  /* complement... : to do later */


  /* Miscellaneous */

  /* adds the second argument to the right bound of the dirst one
     and subtracts the second argument to the left bound of
     the dirst one */
  int     mpdi_increase   (mpdi_ptr, mpd_srcptr);
  /* keeps the same center and multiply the radius by 2*(1+fact) */
  int     mpdi_blow       (mpdi_ptr, mpdi_srcptr, double);
  /* splits the interval into 2 halves */
  int     mpdi_bisect     (mpdi_ptr, mpdi_ptr, mpdi_srcptr);

  const char * mpdi_get_version (void);

  /* Error handling */

  extern int mpdi_error;
  void    mpdi_reset_error (void);
  void    mpdi_set_error   (const int);
  int     mpdi_is_error    (void);
#ifdef __cplusplus
}
#endif

#define MPDI_ERROR(s)                           \
  do {                                          \
    if(!mpdi_error) {                           \
      mpdi_error = 1;                           \
      fprintf(stderr, "\n%s\n", s);             \
    }                                           \
  } while (0)

#define MPDI_FLAGS_BOTH_ENDPOINTS_EXACT       0
#define MPDI_FLAGS_LEFT_ENDPOINT_INEXACT      1
#define MPDI_FLAGS_RIGHT_ENDPOINT_INEXACT     2
#define MPDI_FLAGS_BOTH_ENDPOINTS_INEXACT     3

#define MPDI_BOTH_ARE_EXACT(x) ( (int)(x) == 0 )
#define MPDI_LEFT_IS_INEXACT(x) ( (int)(x)%2 )
#define MPDI_RIGHT_IS_INEXACT(x) ( (int)(x)/2 )
#define MPDI_BOTH_ARE_INEXACT(x) ( (int)(x) == 3 )

#define MPDI_REVERT_INEXACT_FLAGS(x)		\
  ( ((x)==1) ? 2 : ((x)==2) ? 1 : x )

#endif /* __MPDI_H__ */
