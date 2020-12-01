/* init.c -- Initialize an interval. */

#include "mpdi-impl.h"

void
mpdi_init (mpdi_t x)
{
  mpd_init (&(x->left));
  mpd_init (&(x->right));
}

void
mpdi_init2 (mpdi_t x, mpd_prec_t p)
{
  mpd_init2 (&(x->left),p);
  mpd_init2 (&(x->right),p);
}
