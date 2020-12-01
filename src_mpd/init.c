/* mpd_init() -- initialize a decimal number */

#include "mpd-impl.h"

void mpd_init (mpd_ptr x){
  /* Set x with the default precision */
  mpd_init2(x,__mpd_default_init_decimal_precision);
}
