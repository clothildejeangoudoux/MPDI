/* mpd_signbit -- Signbit of a MPD number */

#include "mpd-impl.h"

int mpd_signbit (mpd_srcptr x) {

  if (MPD_CLASS(x) == MPD_CLASS_NEG_ZERO) {
    MPD_RET(-1);
  }

  if (MPD_CLASS(x) == MPD_CLASS_POS_ZERO) {
    MPD_RET(1);
  }

  MPD_RET(MPD_SIGN(x));
}
