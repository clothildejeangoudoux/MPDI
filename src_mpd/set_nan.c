/* mpfr_set_nan -- set a number to NaN.  */


#include "mpd-impl.h"

void mpd_set_nan (mpd_ptr x)
{
  MPD_SET_NAN (x);
  mpd_set_nanflag();
}

int mpd_nan_p(mpd_srcptr x)
{
  return MPD_IS_NAN(x);
}

int mpd_zero_p(mpd_srcptr x)
{ 
  return MPD_IS_ZERO(x);
}

void
mpd_set_nanflag()
{
  MPD_FLAGS |= MPD_FLAG_NAN;
}
