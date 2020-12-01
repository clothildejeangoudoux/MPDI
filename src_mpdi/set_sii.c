
#include "mpdi-impl.h"

int
mpdi_set_si (mpdi_ptr a, const long b)
{
  int inexact_left, inexact_right, inexact=0;

  inexact_left = mpd_set_si (&(a->left), b, MPD_RNDD);
  inexact_right = mpd_set_si (&(a->right), b, MPD_RNDU);

  if (inexact_left)
    inexact += 1;
  if (inexact_right)
    inexact += 2;

  return inexact;
}
