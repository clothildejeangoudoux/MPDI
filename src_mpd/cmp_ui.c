/* mpd_cmp_ui() -- compare a decimal mpd number with an unsigned machine integer */

#include "mpd-impl.h"

int mpd_cmp_ui (mpd_srcptr a, unsigned long i) {

  mpd_t ii;
  
  /* Singular numbers */
  /* NaN */
  if (MPD_IS_NAN(a)) {
    mpd_set_invalidflag();
    MPD_RET(0);
  }

  /* Infinity */
  if (MPD_IS_INF(a)) {
    MPD_RET(MPD_SIGN(a));
  }

  /* Zero */
  if (MPD_IS_ZERO(a)) {
    if (i == 0) {
      MPD_RET(0);
    } else {
      MPD_RET(-1);
    }
  }

  /* a is a negative number */
  if (MPD_IS_NEG(a)) {
    MPD_RET(-1);
  }
  /* a is a positive number */
  if (i==0) {
    MPD_RET(1);
  }

  /* a and i are both strictly positive numbers */
  mpd_init2(ii,MPD_MAX_PREC_UINT);
  mpd_set_ui(ii,i,MPD_RNDN);

  MPD_RET(mpd_cmp(a,ii));
}
