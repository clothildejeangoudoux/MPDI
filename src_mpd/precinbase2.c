/* mpd_precinbase2 -- takes a precision in base 10 and return the
 precision needed to compute in base 2*/

#include "mpd-impl.h"

mpd_prec_t mpd_precinbase2 (mpd_prec_t k) {
  mpfr_t t;
  mpd_prec_t p;

  mpfr_init_set_ui(t,10,MPFR_RNDN);
  mpfr_log2(t,t,MPFR_RNDN);
  mpfr_mul_si(t,t,k,MPFR_RNDN);
  p = mpfr_get_si(t,MPFR_RNDN);

  mpfr_clear(t);
  return p;
}





