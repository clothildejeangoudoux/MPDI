#include "mpdi-impl.h"

int
mpdi_set_d (mpdi_ptr a, const double b)
{
  int inexact_left, inexact_right, inexact=0;
  
  inexact_left = mpd_set_d (&(a->left), b, MPD_RNDD);
  inexact_right = mpd_set_d (&(a->right), b, MPD_RNDU);

  if ( MPDI_IS_NAN (a) )
    MPDI_RET_NAN;

  if (inexact_left)
    inexact += 1;
  if (inexact_right)
    inexact += 2;

  return inexact;
}
