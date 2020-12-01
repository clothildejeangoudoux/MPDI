/* mpd_set_default_prec()  */

#include "mpd-impl.h"

/* default is the decimal equivalent of IEEE double precision -> 53 bits */
/* 53*log10(2) ~ 15.955 */
mpd_prec_t __mpd_default_decimal_precision = 16;
mpd_prec_t __mpd_default_init_decimal_precision = 16;
mpd_flags_t __mpd_flags = 0;

void mpd_set_default_prec (mpd_prec_t prec) {
  if (prec >= MPD_PREC_MIN && prec <= MPD_PREC_MAX) {
    __mpd_default_decimal_precision = prec;
  }
}

