/* mpd_set_d() -- copy a decimal number */

#include "mpd-impl.h"


int mpd_set_d (mpd_ptr x, const double d, mpd_rnd_t rnd_mode) {

  mpfr_t fr;
  int inex1, inex2;
  mpd_prec_t temp_prec;
  
  /* Check for singular values */
  /* NaN */
  if (isnan(d)) {
    MPD_SET_NAN(x);
    MPD_RET_NAN;
  }

  /* Infinity */
  if (d == INFINITY) {
    MPD_SET_POS_INF(x);
    MPD_RET(0);
  }
  if (d == -INFINITY) {
    MPD_SET_NEG_INF(x);
    MPD_RET(0);
  }

  /* Zero */
  if (d == 0.0) {
    MPD_SET_ZERO(x);
    MPD_RET(0);
  }
  
  /* Set the double into a decimal with mpfr */
  temp_prec = mpd_precinbase2(MPD_PREC(x));
  mpfr_init2(fr,temp_prec);
  inex1 = mpfr_set_d(fr,d,rnd_mode); 
  inex2 = mpd_set_fr(x,fr,rnd_mode);
  
  mpfr_clear(fr);
  
  MPD_RET(INEX(inex1,inex2));
}
