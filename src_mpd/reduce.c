/* mpd_reduce.c() -- reduce the trailing zeros of a MPD mantissa number */

#include "mpd-impl.h"

/* Returns 0 if the number a didn't need reducing
   Returns a positive number otherwise */

int mpd_reduce (mpd_ptr r, mpd_srcptr a) {

  mpz_t n, q;
  mpd_exp_t exp;
  unsigned int reduce = 0;
  
  /* Singular values */
  /* NaN */
  if (MPD_IS_NAN(a)) {
    MPD_SET_NAN(r);
    MPD_RET_NAN;
  }

  /* Infinity */
  if (MPD_IS_INF(a)) {
    if (MPD_IS_NEG(a)) {
      MPD_SET_NEG_INF(r);
    } else {
      MPD_SET_POS_INF(r);
    }
    MPD_RET(0);
  }

  /* Zero */
  if (MPD_IS_ZERO(a)) {
    if (MPD_CLASS(a) == MPD_CLASS_NEG_ZERO) {
      MPD_SET_NEG_ZERO(r);
    } else {
      MPD_SET_POS_ZERO(r);
    }
    MPD_RET(0);
  }

  mpz_init_set(n,MPD_MANT(a));
  mpz_init(q);
  exp = MPD_EXP(a);

  /* Reduce MPD numbers */
  while (mpz_tdiv_q_ui (q,n,10)==0){
    mpz_set(n,q);
    exp += 1; /* Attention dépassement de capacité */
    reduce += 1;
  }

  /* Set the number */
  MPD_SET(r,a);
  MPD_PREC(r) = MPD_PREC(a);

  /* Return */
  MPD_RET(reduce);
}
