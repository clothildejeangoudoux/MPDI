/* mpd_set_ui() -- copy an unsigned int into a mpd*/

#include "mpd-impl.h"

int  mpd_set_ui (mpd_ptr x, const unsigned long ui, mpd_rnd_t rnd){
  int inex;
  mpz_t X;

  /* Singular value zero */
  if (ui == 0) {
    MPD_SET_ZERO(x);
    MPD_RET(0);
  }

  /* positive number */
  MPD_CLASS(x) = MPD_CLASS_POS_NUMBER;

  mpz_init_set_ui(X,ui);
  inex = mpd_set_z(x,X,rnd);

  mpz_clear(X);
  MPD_RET(inex);
}


