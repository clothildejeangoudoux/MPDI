/* mpfr_swap (U, V) -- Swap U and V.  */

#include "mpd-impl.h"

/* Using memcpy is a few slower than swapping by hand. */

void mpd_swap (mpd_ptr u, mpd_ptr v) {
  mpd_prec_t p1, p2;
  mpd_class_t c1, c2;
  mpd_exp_t e1, e2;
  mpz_t m1, m2;

  p1 = MPD_PREC(u);
  p2 = MPD_PREC(v);
  MPD_PREC(v) = p1;
  MPD_PREC(u) = p2;

  c1 = MPD_CLASS(u);
  c2 = MPD_CLASS(v);
  MPD_CLASS(v) = c1;
  MPD_CLASS(u) = c2;

  e1 = MPD_EXP(u);
  e2 = MPD_EXP(v);
  MPD_EXP(v) = e1;
  MPD_EXP(u) = e2;

  mpz_init_set(m1,MPD_MANT(u));
  mpz_init_set(m2,MPD_MANT(v));
  mpz_set(MPD_MANT(u),m2);
  mpz_set(MPD_MANT(v),m1);
}
