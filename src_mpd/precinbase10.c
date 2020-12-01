/* mpd_precinbase10 -- takes a precision in base 2 and return the
 precision needed to compute in base 10*/

#include "mpd-impl.h"

mpd_prec_t mpd_precinbase10 (mpd_prec_t p) {
  mpfr_t t;
  mpd_prec_t k;

  mpfr_init_set_ui(t,2,MPFR_RNDN);
  mpfr_log10(t,t,MPFR_RNDU);
  mpfr_mul_si(t,t,p+2,MPFR_RNDU);
  k = mpfr_get_si(t,MPFR_RNDU);

  mpfr_clear(t);
  return k;
}
