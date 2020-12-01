/* mpd_clear() -- free the memory space allocated for a decimal 
number */

#include "mpd-impl.h"

void mpd_clear (mpd_ptr x){

  /* Libération de la mantisse */
  mpz_clear(MPD_MANT(x));
}
