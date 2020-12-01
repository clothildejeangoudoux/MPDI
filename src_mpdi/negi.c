/* neg.c -- Return interval opposite.  */

#include "mpdi-impl.h"

int mpdi_neg (mpdi_ptr a, mpdi_srcptr b) {
  mpd_t tmp;
  int inexact_left, inexact_right, inexact=0;

  mpd_init2 (tmp, mpd_get_prec (&(a->right)));
  inexact_right = mpd_set (tmp, &(b->left), MPDI_RNDD);
  inexact_left = mpd_neg (&(a->left), &(b->right), MPDI_RNDD);
  mpd_neg (&(a->right), tmp, MPDI_RNDU); /* exact */
  mpd_clear (tmp);

  if (MPDI_IS_NAN (a))
    MPDI_RET_NAN;

  if (inexact_left)
    inexact += 1;
  if (inexact_right)
    inexact += 2;

  return inexact;
}
