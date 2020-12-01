/* mpfr_set_inf -- set a number to plus or minus infinity.  */

#include "mpd-impl.h"

void mpd_set_inf (mpd_ptr x, int sign) {
  if (sign >= 0){
    MPD_SET_POS_INF(x);
  }else{
    MPD_SET_NEG_INF(x);
  }
}

int mpd_inf_p(mpd_srcptr x)
{ 
  return MPD_IS_INF(x);
}
