/* mpd_sqrt() -- sqrt of a decimal MPD */

#include "mpd-impl.h"

int mpd_sqrt(mpd_ptr r, mpd_srcptr u, mpd_rnd_t rnd) {

  int i, j1, j2, cpt=0;
  mpfr_t fr, fr_src, fr_dest, nh, nl, rh, rl;
  mpd_prec_t k;
  mpfr_prec_t p;

  /* Special cases */

  /* NaN */
  if (MPD_IS_NAN(u)) {
    MPD_SET_NAN(r);
    MPD_RET_NAN;
  }

  /* Zero */
  if (MPD_IS_ZERO(u)) {
    MPD_SET_POS_ZERO(r);
    MPD_RET(0); /* 0 is exact */
  }

  /* Infinity */
  if (MPD_IS_INF(u)) {
    if (MPD_IS_NEG(u)) {
      /* sqrt(-Inf) = NaN */
      MPD_SET_NAN(r);
      MPD_RET_NAN;
    }
    MPD_SET_POS_INF(r);
    MPD_RET(0); /* sqrt(+Inf) is exact */
  }

  /* u is negative */
  if (MPD_IS_NEG(u)) {
    MPD_SET_NAN(r);
    MPD_RET_NAN;
  }

  /* Set the class to a positive number */
  MPD_CLASS(r) = MPD_CLASS_POS_NUMBER; /* No need, redifined in mpd_set_fr */
  
  /* Precisions */
  k = MPD_PREC(r);
  p=mpd_precinbase2(k);
  
  /* Conversion into a MPFR */
  mpfr_init2(fr_src,p);
  mpfr_init2(fr_dest,p);
  mpd_get_fr(fr_src,u,rnd);

  /* Ziv loop */
  mpfr_init2(fr,p);
  mpfr_init2(nh,p);
  mpfr_init2(nl,p);
  mpfr_init2(rh,p);
  mpfr_init2(rl,p);
  
  startloop:
  /* Increase the precision for each Ziv's loop tour */
  mpfr_set_prec(fr,p);
  mpfr_set_prec(rl,p);
  mpfr_set_prec(rh,p);

  i = mpfr_sqrt(fr,fr_src,rnd);

  mpfr_set(rh,fr,rnd);
  mpfr_set(rl,fr,rnd);

  if(IS_INEXACT(i)) {
    while (cpt<3) {
      mpfr_nextabove(rh);
      mpfr_nextbelow(rl);
      cpt++;
    }
  }

   /* nh and nl are two MPFR with the precision of fr */
  j1 = mpfr_set(nh,rh,rnd);
  mpfr_set(nl,rl,rnd);
  
  /* we reached the precision needed, set fr */
  if(mpfr_cmp(nh,nl)==0){
    mpfr_set(fr_dest,nh,rnd);
    goto endloop;
  }

  p = 1.5*p;
  goto startloop;

 endloop:

  /* Convert back to MPD */
  j2 = mpd_set_fr(r,fr_dest,rnd);

  mpfr_clear(fr);
  mpfr_clear(fr_src);
  mpfr_clear(fr_dest);
  mpfr_clear(nh);
  mpfr_clear(nl);
  mpfr_clear(rh);
  mpfr_clear(rl);
  
  MPD_RET(INEX(j1,j2));
}
