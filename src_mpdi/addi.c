/* add.c -- Add two intervals. */

#include "mpdi-impl.h"

int
mpdi_add (mpdi_ptr a, mpdi_srcptr b, mpdi_srcptr c)
/* relies on the fact that each operand is OK, */
/* ie its left endpoint is <= its right one.   */
/* This should always hold.                    */
{
  int inexact_left, inexact_right, inexact=0;

  if (MPDI_IS_ZERO (c)) {
    return (mpdi_set (a,b));
  }
  else if (MPDI_IS_ZERO (b)) {
    return (mpdi_set (a,c));
  }
  else {
    inexact_left = mpd_add (&(a->left), &(b->left), &(c->left),MPDI_RNDD);
    inexact_right = mpd_add (&(a->right), &(b->right), &(c->right),MPDI_RNDU);

    /* do not allow -0 as lower bound */
    if (mpd_zero_p (&(a->left)) && mpd_signbit (&(a->left))) {
      mpd_neg (&(a->left), &(a->left), MPDI_RNDU);
    }
    /* do not allow +0 as upper bound */
    if (mpd_zero_p (&(a->right)) && !mpd_signbit (&(a->right))) {
      mpd_neg (&(a->right), &(a->right), MPDI_RNDD);
    }

    if (MPDI_IS_NAN (a))
      MPDI_RET_NAN;
    if (inexact_left)
      inexact += 1;
    if (inexact_right)
      inexact += 2;

    return inexact;
  }
}
