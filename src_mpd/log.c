/* mpd_log() -- natural logarithm of a decimal mpd */

#include "mpd-impl.h"

int mpd_log (mpd_ptr r, mpd_srcptr a, mpd_rnd_t rnd) {

  int i, j1, j2, cpt=0, l;
  mpfr_t fr, fr_src, fr_dest, nh, nl, rh, rl;
  mpd_prec_t k;
  mpfr_prec_t p;
  mpd_t un, y;

  /* special cases */
  /* NaN */
  if (MPD_IS_NAN(a)) {
    MPD_SET_NAN(r);
    MPD_RET_NAN;
  }

  /* Check for infinity before zero */
  if (MPD_IS_INF(a)) {
    if (MPD_IS_NEG(a)) {
      /* log(-Inf) = NaN */
      MPD_SET_NAN(r);
      MPD_RET_NAN;
    } else {
      /* log(+Inf) = +Inf */
      MPD_SET_POS_INF(r);
      MPD_RET(0); /* exact */
    }
  }
  
  /* Zero */
  if (MPD_IS_ZERO(a)) {
    /* log(0) is an exact -infinity */
    MPD_SET_NEG_INF(r);
    mpd_set_divbyzero(); /* exception raised */
    MPD_RET(0);
  }
  
  /* Negative number : the result is NaN */
  if (MPD_CLASS(a) == MPD_CLASS_NEG_NUMBER) {
    MPD_SET_NAN(r);
      MPD_RET_NAN;
  }
  
  /* If a is 1, the result is 0 */
  if (mpd_cmp_ui(a,1) == 0) {
    MPD_SET_POS_ZERO(r);
    MPD_RET(0); /* only numerical case where the result is exact */
  }
  
  /* Logarithm algorithm */

  /* The function as a singularity around 1, but is well behaved on the rest of it's range*/
  /* Special computation for numbers near 1 */

  if (mpd_cmp_ui(a,2) >= 0) {
    /* Away from 1 */
    l=0;
  } else {
    /* near 1 */
    l=1;
  }
    
    /* Set the class to a positive number */
  MPD_CLASS(r) = MPD_CLASS_POS_NUMBER; /* No need, redifined in mpd_set_fr */

  /* Precisions */
  k = MPD_PREC(r);
  p=mpd_precinbase2(k);

  /* Conversion into a MPFR */
  mpfr_init2(fr_src,p);
  mpfr_init2(fr_dest,p);

  if(l==1){
    /* near 1, compute y=a-1 */
    mpd_init(un);
    mpd_init2(y,MPD_PREC(a));
    mpd_set_ui(un,1,rnd);
    mpd_sub(y,a,un,rnd);
    mpd_get_fr(fr_src,y,rnd);
    mpd_clear(un);
    mpd_clear(y);
  } else {
    mpd_get_fr(fr_src,a,rnd);
  }

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
 
  if(l==1){
    /* near 1, use mpfr_log1p */
    i = mpfr_log1p(fr,fr_src,rnd);
  } else {
    i = mpfr_log(fr,fr_src,rnd);
  }
  
  mpfr_set(rh,fr,rnd);
  mpfr_set(rl,fr,rnd);

  cpt=0;
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






