/* exp.c -- Exponential of an interval.  */

#include "mpdi-impl.h"

/* Computes the exp of an interval              */
int mpdi_exp (mpdi_ptr a, mpdi_srcptr b) {
  int inexact_left, inexact_right, inexact=0;

  inexact_left = mpd_exp (&(a->left), &(b->left), MPDI_RNDD);
  inexact_right = mpd_exp (&(a->right), &(b->right), MPDI_RNDU);

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
