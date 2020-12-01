/* mpd_init() -- initialize a decimal number */

#include "mpd-impl.h"

void mpd_init2 (mpd_ptr x, mpd_prec_t prec){
   /* Initialisation et allocation de la mantisse */
  mpz_init(MPD_MANT(x));
  /* Initialisation à zéro */
  MPD_CLASS(x) = MPD_CLASS_POS_ZERO;
  MPD_EXP(x) = 0;
  MPD_PREC(x) = prec;
  mpz_set_si(MPD_MANT(x),0);
}

