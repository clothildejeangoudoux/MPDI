/* mpd_set_prec -- reset the precision of a MPD number */

#include "mpd-impl.h"

void mpd_set_prec (mpd_ptr x, mpd_prec_t k) {
  /* check if k is correct */
  if ((k >= MPD_PREC_MIN) && (k <= MPD_PREC_MAX)) {
    MPD_PREC (x) = k;
    MPD_CLASS(x) = MPD_CLASS_POS_ZERO;	
    MPD_EXP(x) = 0;				
    
  }
}

#undef mpd_get_prec
mpd_prec_t mpd_get_prec (mpd_srcptr x) {
  return MPD_PREC(x);
}
