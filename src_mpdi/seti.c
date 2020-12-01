/* set.c -- Assignments between intervals.  */

#include "mpdi-impl.h"

int mpdi_set (mpdi_ptr a, mpdi_srcptr b) {
  int inexact_left, inexact_right, inexact=0;
  inexact_left = mpd_set (&(a->left), &(b->left), MPDI_RNDD);
  inexact_right = mpd_set (&(a->right), &(b->right), MPDI_RNDU);

  if ( MPDI_IS_NAN (a) ){
    MPDI_SET_NAN(a);
    MPDI_RET_NAN;
  }
  
  if (inexact_left)
    inexact += 1;
  if (inexact_right)
    inexact += 2;

  return inexact;
}

int mpdi_set_dec (mpdi_ptr a, mpd_srcptr b) {
  int inexact_left, inexact_right, inexact=0;
  inexact_left = mpd_set (&(a->left), b, MPDI_RNDD);
  inexact_right = mpd_set (&(a->right), b, MPDI_RNDU);

  if ( MPDI_IS_NAN (a) ){
    MPDI_SET_NAN(a);
    MPDI_RET_NAN;
  }
  
  if (inexact_left)
    inexact += 1;
  if (inexact_right)
    inexact += 2;

  return inexact;
}

/* Combined initialization and assignment      */
/*
int mpdi_init_set (mpdi_ptr a, mpdi_srcptr b) {
  int inexact_left, inexact_right, inexact = 0;

  inexact_left = mpd_init_set (&(a->left), &(b->left), MPDI_RNDD);
  inexact_right = mpd_init_set (&(a->right), &(b->right), MPDI_RNDU);

  if ( MPDI_NAN_P (a) )
    MPD_RET_NAN;

  if (inexact_left)
    inexact += 1;
  if (inexact_right)
    inexact += 2;

  return inexact;
  }*/
