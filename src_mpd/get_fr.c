/* mpd_get_fr() -- get mpfr from mpd decimal */

#include "mpd-impl.h"

int mpd_get_fr(mpfr_ptr fr, mpd_srcptr x, mpd_rnd_t rnd_mode) {

  int i1, i2, i3, j, cpt=0;
  mpd_prec_t k;
  mpfr_prec_t p;
  mpfr_t r, rh, rl, nh, nl, tmant, texp, dix;
  
  /* Singular values */
  /* NaN */
  if (MPD_IS_NAN(x)) {
    MPFR_SET_NAN(fr);
    MPFR_RET_NAN;
  }

  /* Infinity */
  if (MPD_IS_INF(x)) {
    MPFR_SET_INF(fr);
    MPFR_SET_SIGN(fr,MPD_SIGN(x));
    MPD_RET(0);
  }

  if (MPD_IS_ZERO(x)) {
    MPFR_SET_SIGN(fr,MPD_SIGN(x));
    MPFR_SET_ZERO(fr);
    MPD_RET(0);
  }

  /* Computation of the binary precision required */
  k = MPD_PREC(x);
  p=mpd_precinbase2(k);
 
  /* Conversion into a binary mpfr */
  mpfr_init2(tmant,p);
  mpfr_init2(texp,p);
  mpfr_init2(nh,mpfr_get_prec(fr));
  mpfr_init2(nl,mpfr_get_prec(fr));
  mpfr_init_set_ui(dix,10,rnd_mode);
  mpfr_init2(r,p); 
  mpfr_init2(rl,p);
  mpfr_init2(rh,p);
  
 startloop:
  /* Increase the precision for each Ziv's loop tour */
  mpfr_set_prec(r,p); /* Set the new precision and reset the number */
  mpfr_set_prec(rl,p);
  mpfr_set_prec(rh,p);
  mpfr_set_prec(tmant,p);
  mpfr_set_prec(texp,p);
  
  i1 = mpfr_set_z(tmant,MPD_MANT(x),rnd_mode); /* no rounding */
  i2 = mpfr_pow_si(texp,dix,MPD_EXP(x),rnd_mode);
  i3 = mpfr_mul(r,tmant,texp,rnd_mode);

  mpfr_set(rh,r,rnd_mode);
  mpfr_set(rl,r,rnd_mode);

  if(IS_INEXACT(INEX3(i1,i2,i3))) {
    while (cpt<3) {
      mpfr_nextabove(rh);
      mpfr_nextbelow(rl);
      cpt++;
    }
  }

  /* nh and nl are two MPFR with the precision of fr */
  j=mpfr_set(nh,rh,rnd_mode);
  mpfr_set(nl,rl,rnd_mode);
  
  /* we reached the precision needed, set fr */
  if(mpfr_cmp(nh,nl)==0){
    mpfr_set(fr,nh,rnd_mode);
    goto endloop;
  }

  p = 1.5*p;
  goto startloop;

 endloop:
  
  /* Clear temp values */
  mpfr_clear(dix);
  mpfr_clear(tmant);
  mpfr_clear(texp);
  mpfr_clear(r);
  mpfr_clear(rh);
  mpfr_clear(rl);
  mpfr_clear(nh);
  mpfr_clear(nl);
  
  MPD_RET(j);
}
