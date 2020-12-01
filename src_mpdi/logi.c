/* log.c -- Logarithm of an interval. */

#include "mpdi-impl.h"

/* Computes the log of an interval              */
/* Special cases are handled by mpd_log        */

int mpdi_log (mpdi_ptr a, mpdi_srcptr b) {
  int inexact_left, inexact_right, inexact=0;

  inexact_left = mpd_log (&(a->left), &(b->left), MPDI_RNDD);
  inexact_right = mpd_log (&(a->right), &(b->right), MPDI_RNDU);

  /* do not allow +0 as upper bound */
  if (mpd_zero_p (&(a->right)) && !mpd_signbit (&(a->right))) {
    mpd_neg (&(a->right), &(a->right), MPDI_RNDD);
  }

  if ( MPDI_IS_NAN (b) ){
    MPDI_SET_NAN(a);
    MPDI_RET_NAN;
  }

  if (inexact_left)
    inexact += 1;
  if (inexact_right)
    inexact += 2;

  return inexact;
}
