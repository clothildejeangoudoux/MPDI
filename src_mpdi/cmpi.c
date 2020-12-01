/* cmp.c -- Default comparison functions. */

#include "mpdi-impl.h"

/* Warning: there is no canonical order =>      */
/* interval comparison is not clearly defined   */

/* Customizable comparison functions */
/* Since the mpdi_cmp_* are based on mpdi_cmp, only mpdi_cmp needs to be modidied */

int (*mpdi_cmp)    (mpdi_srcptr, mpdi_srcptr)         = mpdi_cmp_default;
/*
int (*mpdi_cmp_d)  (mpdi_srcptr, const double)        = mpdi_cmp_d_default;
int (*mpdi_cmp_ui) (mpdi_srcptr, const unsigned long) = mpdi_cmp_ui_default;
int (*mpdi_cmp_si) (mpdi_srcptr, const long)          = mpdi_cmp_si_default;
int (*mpdi_cmp_z)  (mpdi_srcptr, mpz_srcptr)          = mpdi_cmp_z_default;
int (*mpdi_cmp_q)  (mpdi_srcptr, mpq_srcptr)          = mpdi_cmp_q_default;
int (*mpdi_cmp_d) (mpdi_srcptr, mpd_srcptr)         = mpdi_cmp_d_default;
*/

/* Default comparison functions */
/* They return 1 if one (at least) of their operands is invalid (contains NaN) */

int
mpdi_cmp_default (mpdi_srcptr a, mpdi_srcptr b)
{
  if ( MPDI_IS_NAN (a) || MPDI_IS_NAN (b) )
    return 1;
  return ( (mpd_cmp (&(a->right), &(b->left)) < 0) ? -1
	   :(mpd_cmp (&(b->right), &(a->left)) < 0) );
}

/*
int
mpdi_cmp_d_default (mpdi_srcptr a, const double b)
{
  int res = 0;
  mpdi_t tmp;

  mpdi_init2 (tmp, mpdi_get_prec (a));
  mpdi_set_d (tmp, b);
  res = mpdi_cmp (a, tmp);
  MPDI_CLEAR (tmp);

  return (res);
}

int
mpdi_cmp_ui_default (mpdi_srcptr a, const unsigned long b)
{
  int res = 0;
  mpdi_t tmp;

  mpdi_init2 (tmp, mpdi_get_prec (a));
  mpdi_set_ui (tmp, b);
  res = mpdi_cmp (a, tmp);
  MPDI_CLEAR (tmp);

  return (res);
}

int
mpdi_cmp_si_default (mpdi_srcptr a, const long b)
{
  int res = 0;
  mpdi_t tmp;

  mpdi_init2 (tmp, mpdi_get_prec (a));
  mpdi_set_si (tmp, b);
  res = mpdi_cmp (a, tmp);
  MPDI_CLEAR (tmp);

  return (res);
}

int
mpdi_cmp_z_default (mpdi_srcptr a, mpz_srcptr b)
{
  int res = 0;
  mpdi_t tmp;

  mpdi_init2 (tmp, mpdi_get_prec (a));
  mpdi_set_z (tmp, b);
  res = mpdi_cmp (a, tmp);
  MPDI_CLEAR (tmp);

  return (res);
}

int
mpdi_cmp_q_default (mpdi_srcptr a, mpq_srcptr b)
{
  int res = 0;
  mpdi_t tmp;

  mpdi_init2 (tmp, mpdi_get_prec (a));
  mpdi_set_q (tmp, b);
  res = mpdi_cmp (a, tmp);
  MPDI_CLEAR (tmp);

  return (res);
}

int
mpdi_cmp_d_default (mpdi_srcptr a, mpd_srcptr b)
{
  int res = 0;
  mpdi_t tmp;

  mpdi_init2 (tmp, mpdi_get_prec (a));
  mpdi_set_d (tmp, b);
  res = mpdi_cmp (a, tmp);
  MPDI_CLEAR (tmp);

  return (res);
}
*/
