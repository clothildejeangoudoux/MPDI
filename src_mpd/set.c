/* mpd_set() -- copy a decimal number */

#include "mpd-impl.h"

int  mpd_set (mpd_ptr x, mpd_srcptr y, mpd_rnd_t rnd_mode){

  int cmp, inex;
  size_t sizeX, sizeY;
  /* int inex1, inex2; */
  /* mpfr_t fr; */
  
  /* Singular values */
  /* NaN */
  if (MPD_IS_NAN(y)){
    MPD_SET_NAN(x);
    MPD_RET_NAN;
  }

  /* Infinity */
  if (MPD_IS_INF(y)){
    if (MPD_IS_NEG(y)) {
      MPD_SET_NEG_INF(x);
    } else {
      MPD_SET_POS_INF(x);
    }
    MPD_RET(0); /* exact */
  }

  /* Zero */
  if (MPD_IS_ZERO(y)) {
    if (MPD_CLASS(y) == MPD_CLASS_NEG_ZERO) {
      MPD_SET_NEG_ZERO(x);
    } else {
      MPD_SET_POS_ZERO(x);
    }
  }

  /* Check the precision of x */
  if (MPD_PREC(x) >= MPD_PREC(y)) {
    /* No rounding, set y to x with GMP set function */
    MPD_SET(x,y);
    MPD_RET(0);
  } else {
    /* prec(x) < prec(y) 
       Round y into x */
    inex = mpd_round (MPD_MANT(x), MPD_MANT(y), MPD_PREC(x), rnd_mode);
   
    sizeX = mpd_sizeinbase10(MPD_MANT(x));
    sizeY = mpd_sizeinbase10(MPD_MANT(y));
    MPD_SET_EXP(x,MPD_EXP(y)+sizeY-sizeX);
   
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
