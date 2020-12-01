/* mul.c -- Multiply two intervals.  */

#include "mpdi-impl.h"

int mpdi_mul (mpdi_ptr a, mpdi_srcptr b, mpdi_srcptr c) {
  mpd_t t1;
  mpd_t t2;
  int inexact_left, inexact_right;
  int inexact = 0;

  /* Handling the NaN cases */
  if ( MPDI_IS_NAN (b) || MPDI_IS_NAN (c) )
    {
      MPDI_SET_NAN(a);
      MPDI_RET_NAN;
    }

  /* Handling the case where one operand is 0, in order */
  /* to avoid problems with 0 * an indinite interval    */
  if (MPDI_IS_ZERO (b)) {
    return (mpdi_set (a, b));
  }
  if (MPDI_IS_ZERO (c)) {
    return (mpdi_set (a, c));
  }

  if (mpd_sgn (&(b->left)) >= 0) {
    if (mpd_sgn (&(c->left)) >=0) {
      /* b nonnegative and c nonnegative */
      inexact_left = mpd_mul (&(a->left), &(b->left), &(c->left), MPDI_RNDD);
      inexact_right = mpd_mul (&(a->right), &(b->right), &(c->right), MPDI_RNDU);
    }
    else {
      mpd_init2 (t1, mpd_get_prec (&(a->left)));
      if (mpd_sgn (&(c->right)) <= 0) {
	/* b nonnegative and c non-positive */
        inexact_left = mpd_mul (t1, &(b->right), &(c->left), MPDI_RNDD);
        inexact_right = mpd_mul (&(a->right), &(b->left), &(c->right), MPDI_RNDU);
      }
      else {
	/* b nonnegative and c overlapping 0 */
	inexact_left = mpd_mul (t1, &(b->right), &(c->left), MPD_RNDD);
	inexact_right = mpd_mul (&(a->right), &(b->right), &(c->right), MPD_RNDU);
      }
      mpd_set (&(a->left), t1, MPDI_RNDD); /* exact */
      mpd_clear (t1);
    }
  }
  else {
    if (mpd_sgn (&(b->right)) <= 0) {
      /* b non-positive */
      mpd_init2 (t1, mpd_get_prec (&(a->left)));
      if (mpd_sgn (&(c->left)) >= 0) {
        /* b non-positive and c nonnegative */
        inexact_left = mpd_mul (t1, &(b->left), &(c->right), MPDI_RNDD);
        inexact_right = mpd_mul (&(a->right), &(b->right), &(c->left), MPDI_RNDU);
      }
      else {
        if (mpd_sgn (&(c->right)) <= 0) {
	  /* b non-positive and c non-positive */
          inexact_left = mpd_mul (t1, &(b->right), &(c->right), MPDI_RNDD);
          inexact_right = mpd_mul (&(a->right), &(b->left), &(c->left), MPDI_RNDU);
        }
        else {
	  /* b non-positive and c overlapping 0 */
	  inexact_left = mpd_mul (t1, &(b->left), &(c->right), MPDI_RNDD);
	  inexact_right = mpd_mul (&(a->right), &(b->left), &(c->left), MPDI_RNDU);
        }
      }
      mpd_set (&(a->left), t1, MPDI_RNDD); /* exact */
      mpd_clear (t1);
    }
    else {
      /* b contains 0 */
      if (mpd_sgn (&(c->left)) >= 0) {
	/* b overlapping 0 and c nonnegative  */
        mpd_init2 (t1, mpd_get_prec (&(a->left)));

	inexact_left = mpd_mul (t1, &(b->left), &(c->right), MPDI_RNDD);
	inexact_right = mpd_mul (&(a->right), &(b->right), &(c->right), MPDI_RNDU);

        mpd_set (&(a->left), t1, MPDI_RNDD);
        mpd_clear (t1);
      }
      else {
	if (mpd_sgn (&(c->right)) <= 0) {
	  /* b overlapping 0 and c non-positive */
          mpd_init2 (t1, mpd_get_prec (&(a->left)));

	  inexact_left = mpd_mul (t1, &(b->right), &(c->left), MPDI_RNDD);
	  inexact_right = mpd_mul (&(a->right), &(b->left), &(c->left), MPDI_RNDU);

          mpd_set (&(a->left), t1, MPDI_RNDD);
          mpd_clear (t1);
	}
	else {
	  /* b overlapping 0 and c overlapping 0
	     Beware the case where the result is one of the operands! */
          int inexact_tmp;

	  mpd_init2 (t1, mpd_get_prec (&(a->left)));
	  mpd_init2 (t2, mpd_get_prec (&(a->left)));
	  inexact_tmp = mpd_mul (t1, &(b->left), &(c->right), MPDI_RNDD);
	  inexact_left = mpd_mul (t2, &(b->right), &(c->left), MPDI_RNDD);
	  if (mpd_cmp (t1, t2) < 0) {
	    mpd_swap (t2, t1); /* same precision */
            inexact_left = inexact_tmp;
	  }

          mpd_set_prec (t1, mpd_get_prec (&(a->right)));
	  inexact_tmp = mpd_mul (t1, &(b->left), &(c->left), MPDI_RNDU);
	  inexact_right = mpd_mul (&(a->right), &(b->right), &(c->right), MPDI_RNDU);
	  if (mpd_cmp (t1, &(a->right)) > 0) {
            mpd_set (&(a->right), t1, MPDI_RNDU); /* exact */
	    inexact_right = inexact_tmp;
	  }
	  mpd_set (&(a->left), t2, MPDI_RNDD); /* exact */
	  mpd_clear (t1);
	  mpd_clear (t2);
	}
      }
    }
  }

  /* no need to check to sign of an endpoint equal to 0, it should be OK */
  if (inexact_left)
    inexact += 1;
  if (inexact_right)
    inexact += 2;

  return inexact;
}
