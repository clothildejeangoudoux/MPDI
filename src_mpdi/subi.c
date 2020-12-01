/* sub.c -- Subtract two intervals.  */

#include "mpdi-impl.h"

int mpdi_sub (mpdi_ptr a, mpdi_srcptr b, mpdi_srcptr c) {
  mpd_t tmp;
  int inexact_left, inexact_right, inexact = 0;

  if (MPDI_IS_ZERO (c)) {
    return mpdi_set (a, b);
  }
  else if (MPDI_IS_ZERO (b)) {
    return mpdi_neg (a, c);
  }
  else {
    mpd_init2 (tmp, mpd_get_prec (&(a->left)));
    inexact_left = mpd_sub (tmp, &(b->left), &(c->right), MPDI_RNDD);
    inexact_right = mpd_sub (&(a->right), &(b->right), &(c->left), MPDI_RNDU);
    mpd_set (&(a->left), tmp, MPDI_RNDD); /* exact */
    mpd_clear (tmp);

    /* do not allow -0 as lower bound */
    if (mpd_zero_p (&(a->left)) && mpd_signbit (&(a->left))) {
      mpd_neg (&(a->left), &(a->left), MPDI_RNDU);
    }
    /* do not allow +0 as upper bound */
    if (mpd_zero_p (&(a->right)) && !mpd_signbit (&(a->right))) {
      mpd_neg (&(a->right), &(a->right), MPDI_RNDD);
    }
    if ( MPDI_IS_NAN (a) ){
      MPDI_RET_NAN;
    }
    if (inexact_left)
      inexact += 1;
    if (inexact_right)
      inexact += 2;

    return inexact;
  }
}
