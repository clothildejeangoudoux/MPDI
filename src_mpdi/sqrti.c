/* sqrt.c -- Square root of an interval.  */

#include "mpdi-impl.h"

int mpdi_sqrt (mpdi_ptr a, mpdi_srcptr b) {
  int inexact_left, inexact_right, inexact=0;

  /* if b is (partially) negative, the left bound will be a NaN */
  /* it is handled by MPD */
  inexact_left = mpd_sqrt (&(a->left), &(b->left), MPDI_RNDD);
  inexact_right = mpd_sqrt (&(a->right), &(b->right), MPDI_RNDU);

  if ( MPDI_IS_NAN (a) ){
    MPDI_RET_NAN;
  }

  if (inexact_left)
    inexact += 1;
  if (inexact_right)
    inexact += 2;

  return inexact;
}
