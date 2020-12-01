/* div.c -- Divide two intervals. */

#include "mpdi-impl.h"

int mpdi_div (mpdi_ptr a, mpdi_srcptr b, mpdi_srcptr c) {
  mpd_t tmp;
  int inexact_left = 0, inexact_right = 0, inexact = 0;

  if ( MPDI_IS_NAN (b) || MPDI_IS_NAN (c) ){
    MPDI_SET_NAN(a);
    MPDI_RET_NAN;
  }

  if (MPDI_HAS_ZERO_NONSTRICT (c)) {
    if ( MPDI_HAS_ZERO (c) || MPDI_HAS_ZERO (b) ) { /* a = ]-oo, +oo [ */
      mpd_set_inf (&(a->left), -1);
      mpd_set_inf (&(a->right), 1);
    }
    else if (MPDI_IS_NONNEG (c)) {  /* c >= 0 and its left endpoint is 0 */
      if (MPDI_IS_NONNEG (b)) {                    /* a = [ bl/cr, +oo [ */
        inexact_left = mpd_div (&(a->left), &(b->left), &(c->right), MPDI_RNDD);
        mpd_set_inf (&(a->right), 1);
      }
      else { /* b <= 0 */                         /* a = ] -oo, br/cr ] */
        inexact_right = mpd_div (&(a->right), &(b->right), &(c->right), MPDI_RNDU);
        mpd_set_inf (&(a->left), -1);
      }
    }
    else { /* c <= 0 and its right endpoint is 0 */
      if (MPDI_IS_NONNEG (b)) {                    /* a = ] -oo, bl/cl ] */
        inexact_right = mpd_div (&(a->right), &(b->left), &(c->left), MPDI_RNDU);
        mpd_set_inf (&(a->left), -1);
      }
      else { /* b <= 0 */                         /* a = [ br/cl, +oo [ */
        inexact_left = mpd_div (&(a->left), &(b->right), &(c->left), MPDI_RNDD);
        mpd_set_inf (&(a->right), 1);
      }
    }
  }
  else if (MPDI_IS_POS (c)) {
    if (MPDI_IS_NONNEG (b)) {                       /* a = [ bl/cr, br/cl ] */
      mpd_init2 (tmp, mpd_get_prec (&(a->left)));
      inexact_left  = mpd_div (tmp, &(b->left), &(c->right), MPDI_RNDD);
      inexact_right = mpd_div (&(a->right), &(b->right), &(c->left), MPDI_RNDU);
      mpd_set (&(a->left), tmp, MPDI_RNDD); /* exact */
      mpd_clear (tmp);
    }
    else if (MPDI_IS_NONPOS (b)) {                 /* a = [ bl/cl, br/cr ] */
      inexact_left  = mpd_div (&(a->left), &(b->left), &(c->left), MPDI_RNDD);
      inexact_right = mpd_div (&(a->right), &(b->right), &(c->right), MPDI_RNDU);
    }
    else { /* b contains 0 in its interior */     /* a = [ bl/cl, br/cl ] */
      mpd_init2 (tmp, mpd_get_prec (&(a->right)));
      inexact_right = mpd_div (tmp, &(b->right), &(c->left), MPDI_RNDU);
      inexact_left  = mpd_div (&(a->left), &(b->left), &(c->left), MPDI_RNDD);
      mpd_set (&(a->right), tmp, MPDI_RNDU); /* exact */
      mpd_clear (tmp);
    }
  }
  else { /* c < 0 */
    mpd_init2 (tmp, mpd_get_prec (&(a->left)));
    if (MPDI_IS_NONNEG (b)) {                       /* a = [ br/cr, bl/cl ] */
      inexact_left  = mpd_div (tmp, &(b->right), &(c->right), MPDI_RNDD);
      inexact_right = mpd_div (&(a->right), &(b->left), &(c->left), MPDI_RNDU);
    }
    else if (MPDI_IS_NONPOS (b)) {                 /* a = [ br/cl, bl/cr ] */
      inexact_left  = mpd_div (tmp, &(b->right), &(c->left), MPDI_RNDD);
      inexact_right = mpd_div (&(a->right), &(b->left), &(c->right), MPDI_RNDU);
    }
    else { /* b contains 0 in its interior */     /* a = [ br/cr, bl/cr ] */
      inexact_left  = mpd_div (tmp, &(b->right), &(c->right), MPDI_RNDD);
      inexact_right = mpd_div (&(a->right), &(b->left), &(c->right), MPDI_RNDU);
    }
    mpd_set (&(a->left), tmp, MPDI_RNDD); /* exact */
    mpd_clear (tmp);
  }

  if ( MPDI_IS_NAN (a) ){
    MPDI_RET_NAN;
  }

  if (inexact_left)
    inexact += 1;
  if (inexact_right)
    inexact += 2;

  /* do not allow -0 as lower bound */
  if (mpd_zero_p (&(a->left)) && mpd_signbit (&(a->left))) {
    mpd_neg (&(a->left), &(a->left), MPDI_RNDU);
  }
  /* do not allow +0 as upper bound */
  if (mpd_zero_p (&(a->right)) && !mpd_signbit (&(a->right))) {
    mpd_neg (&(a->right), &(a->right), MPDI_RNDD);
  }

  return inexact;
}
