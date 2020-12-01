/* mpd_set_z() -- copy a gmp */

#include "mpd-impl.h"

int  mpd_set_z (mpd_ptr x, mpz_srcptr y, mpd_rnd_t rnd_mode){
  int cmp,inex;
  size_t size;
  
  cmp = mpz_cmp_si(y,0);

  /* Singular value zero */
  if (cmp == 0) {
    MPD_SET_ZERO(x);
    MPD_RET(0);
  }

  /* set mpd class */
  if (cmp < 0) {
    MPD_CLASS(x) = MPD_CLASS_NEG_NUMBER;
  } else {
    MPD_CLASS(x) = MPD_CLASS_POS_NUMBER;
  }

  size = mpd_sizeinbase10(y);
  
  if (MPD_PREC(x) >= size) {
    /* No rounding necessary */
    /* set mpd exponent and mantissa*/
    MPD_SET_EXP(x,0);
    mpz_set(MPD_MANT(x),y);
    MPD_RET(0);
  } else {
    /* Round the value of y in x */
    /* Avoid all the different cases by using MPFR */
    inex = mpd_round (MPD_MANT(x), y, MPD_PREC(x), rnd_mode);
  
    MPD_SET_EXP(x,size-MPD_PREC(x));

    cmp = mpz_cmp_ui(MPD_MANT(x),0);
    if (cmp > 0) {
      MPD_CLASS(x) = MPD_CLASS_POS_NUMBER;
    } else if (cmp < 0) {
      MPD_CLASS(x) = MPD_CLASS_NEG_NUMBER;
    } else {
      MPD_CLASS(x) = MPD_CLASS_POS_ZERO;
    }
    MPD_RET(inex);
  }
}
