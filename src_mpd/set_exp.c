/* mpd_set_exp() - set the exponent of a MPD number */

#include "mpd-impl.h"

int mpd_set_exp (mpd_ptr x, mpd_exp_t exponent) {
  if (exponent >= MPD_EMIN  && exponent <= MPD_EMAX)
    {
      MPD_EXP(x) = exponent; /* do not use MPD_SET_EXP of course... */
      return 0;
    }
  else
    {
      return 1;
    }
}

mpd_exp_t mpd_get_exp (mpd_srcptr x) {
  return MPD_EXP(x); /* do not use MPD_GET_EXP of course... */
}
