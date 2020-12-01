/* mpdi-impl.h -- Include dile for mpdi. */

#ifndef __MPDI_IMPL_H__
#define __MPDI_IMPL_H__

#include "mpdi.h"

#define MPDI_IS_POS(x) ((mpd_sgn((&(x->left)))>=0) && (mpd_sgn((&(x->right)))>0))
#define MPDI_IS_STRICTLY_POS(x) ((mpd_sgn((&(x->left)))>0) && (mpd_sgn((&(x->right)))>0))
#define MPDI_IS_NONNEG(x) ((mpd_sgn((&(x->left)))>=0) && (mpd_sgn((&(x->right)))>=0))
#define MPDI_IS_NEG(x) ((mpd_sgn((&(x->left)))<0) && (mpd_sgn((&(x->right)))<=0))
#define MPDI_IS_STRICTLY_NEG(x) ((mpd_sgn((&(x->left)))<0) && (mpd_sgn((&(x->right)))<0))
#define MPDI_IS_NONPOS(x) ((mpd_sgn((&(x->left)))<=0) && (mpd_sgn((&(x->right)))<=0))
#define MPDI_IS_NULL(x) ((mpd_sgn((&(x->left)))==0) && (mpd_sgn((&(x->right)))==0))
#define MPDI_HAS_ZERO(x) ((mpd_sgn((&(x->left)))<0) && (mpd_sgn((&(x->right)))>0))
#define MPDI_HAS_ZERO_NONSTRICT(x) ((mpd_sgn((&(x->left)))<=0) && (mpd_sgn((&(x->right)))>=0))

#define MPDI_SET_NAN(x)						\
  mpd_set_nan(&(x->left));					\
  mpd_set_nan(&(x->right));

/* from MPFI code */
#define MPDI_RET_NAN do {return 0;} while (0)

#define MPDI_IS_NAN(x)  (mpd_nan_p(&(x->left)) || mpd_nan_p(&(x->right)))
#define MPDI_IS_ZERO(x) ((mpd_cmp_ui(&(x->left),0)==0) && (mpd_cmp_ui(&(x->right),0)==0))
#define MPDI_IS_INF(x)  (mpd_inf_p(&(x->left)) && mpd_inf_p(&(x->right)))

/* Internal functions */

#if defined (__cplusplus)
extern "C" {
#endif


mp_prec_t mpdi_quadrant (mpz_ptr, mpd_srcptr);
int     mpdi_cmp_sym_pi (mpz_srcptr, mpd_srcptr, mpd_srcptr, mp_prec_t);

/* default comparison functions */
int    	mpdi_cmp_default    (mpdi_srcptr, mpdi_srcptr);
int    	mpdi_cmp_d_default  (mpdi_srcptr, const double);
int    	mpdi_cmp_ui_default (mpdi_srcptr, const unsigned long);
int    	mpdi_cmp_si_default (mpdi_srcptr, const long);
int    	mpdi_cmp_z_default  (mpdi_srcptr, mpz_srcptr);
int    	mpdi_cmp_q_default  (mpdi_srcptr, mpq_srcptr);
  //int    	mpdi_cmp_d_default (mpdi_srcptr, mpd_srcptr);

int    	mpdi_is_pos_default          (mpdi_srcptr);
int    	mpdi_is_nonneg_default       (mpdi_srcptr);
int    	mpdi_is_neg_default          (mpdi_srcptr);
int    	mpdi_is_nonpos_default       (mpdi_srcptr);
int    	mpdi_is_zero_default         (mpdi_srcptr);
int    	mpdi_is_strictly_neg_default (mpdi_srcptr);
int    	mpdi_is_strictly_pos_default (mpdi_srcptr);

#if defined (__cplusplus)
}
#endif

/* Debug macros */
#ifdef WARN_IF_REVERTED_ENDPOINTS
/* include stdio.h when using this macro */
# define WARNING_REVERTED_ENDPOINTS(a, fname)                           \
  do {									\
  fprintf (stdout, "Pb endpoints in reverse order in %s\n", fname);     \
  mpdi_out_str (stdout, 10, 0, a);                                      \
  fprintf (stdout, "\n");						\
  } while (0)
#else
# define WARNING_REVERTED_ENDPOINTS(a, fname)
#endif

#endif /* __MPDI_IMPL_H__ */
