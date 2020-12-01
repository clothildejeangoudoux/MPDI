/* mpd_set_si() -- copy an unsigned int into a mpd*/

#include "mpd-impl.h"

int  mpd_set_si (mpd_ptr x, const long i,mpd_rnd_t rnd){

  int inex;
  mpz_t X;
  
  /* Set mpd class */
  if (i == 0) {
    MPD_SET_ZERO(x);
    MPD_RET(0);
  }
  
  if (i < 0) {
    MPD_CLASS(x) = MPD_CLASS_NEG_NUMBER;
  } else {
    MPD_CLASS(x) = MPD_CLASS_POS_NUMBER;
  }

  mpz_init_set_si(X,i);
  inex = mpd_set_z(x,X,rnd);

  mpz_clear(X);
  MPD_RET(inex);
}

