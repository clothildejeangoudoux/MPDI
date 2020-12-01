/* mpd_neg -- change the sign of a mpd number */

#include "mpd-impl.h"

int mpd_neg(mpd_ptr x, mpd_srcptr a, mpd_rnd_t rnd){

  /* NaN */
  if (MPD_IS_NAN(a)) {
    MPD_SET_NAN(x);
    MPD_RET_NAN;
  }

  /* Infinity */
  if (MPD_IS_INF(a)) {
    if (MPD_SIGN(a)) {
      MPD_CLASS(x) = MPD_CLASS_NEG_INF;
    } else {
      MPD_CLASS(x) = MPD_CLASS_POS_INF;
    }
    MPD_RET(0); /* exact */
  }

  /* Zero */
  if (MPD_IS_ZERO(a)) {
    if (MPD_SIGN(a)) {
      MPD_CLASS(x) = MPD_CLASS_NEG_ZERO;
    } else {
      MPD_CLASS(x) = MPD_CLASS_POS_ZERO;
    }
    MPD_RET(0); /* exact */
  }

  /* Real Number */
  mpz_t mant;
  int inex;
  
  mpz_init2(mant,MPD_PREC(a));
  mpz_neg(mant,MPD_MANT(a));
  inex = mpd_set_z(x,mant,rnd);  /* rounding may occur */
  MPD_SET_EXP(x,MPD_EXP(a));

  mpz_clear(mant);
  return inex;
}
