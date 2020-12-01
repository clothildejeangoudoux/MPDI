/* mpd_div() -- division of two mpd */

#include "mpd-impl.h"

int mpd_div (mpd_ptr x, mpd_srcptr a, mpd_srcptr b,mpd_rnd_t rnd){

  int i, j1, j2, cpt=0, sign_quotient;
  mpfr_t fr, fr_srcA, fr_srcB, fr_dest, nh, nl, rh, rl;
  mpd_prec_t k;
  mpfr_prec_t p;
  
  /* Special cases */

  /* NaN */

  if (MPD_IS_NAN(a) || MPD_IS_NAN(b)) {
    MPD_SET_NAN(x);
    MPD_RET_NAN;
  }

  sign_quotient = MPD_MULT_SIGN(a,b);

  /* Quotient with infinity */
  if (MPD_IS_INF(a))
    {
      if (MPD_IS_INF(b))
	{
          MPD_SET_NAN(x);
	  MPD_RET_NAN;
	}
      else
	{
	  if(sign_quotient) {
	    MPD_SET_POS_INF(x);
	  } else {
	    MPD_SET_NEG_INF(x);
	  }
	  MPD_RET(0); /* exact */
	}
    }
  else if (MPD_IS_INF(b))
    {
      MPD_SET_ZERO(x);
      MPD_RET(0);
    }
  /* Zero cases */
  else if (MPD_IS_ZERO(b))
    {
      if (MPD_IS_ZERO(a)) {
	MPD_SET_NAN(x);
	MPD_RET_NAN;
      } else {
	/* Division by 0 */
	 if(sign_quotient) {
	    MPD_SET_POS_INF(x);
	  } else {
	    MPD_SET_NEG_INF(x);
	  }
	 mpd_set_divbyzero();
	MPD_RET(0);
      }
    }
  else if (MPD_IS_ZERO(a))
    {
      MPD_SET_ZERO(x);
      MPD_RET(0); /* 0 / b exact with b not NaN or Inf */
    }

  /* Decimal division algorithm */
  
  /* Precisions */
  k = MPD_PREC(x);
  p=mpd_precinbase2(k);
  
  /* Conversion into a MPFR */
  mpfr_init2(fr_srcA,p);
  mpfr_init2(fr_srcB,p);
  mpfr_init2(fr_dest,p);
  mpd_get_fr(fr_srcA,a,rnd);
  mpd_get_fr(fr_srcB,b,rnd);

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

  i = mpfr_div(fr,fr_srcA,fr_srcB,rnd);

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
  j2 = mpd_set_fr(x,fr_dest,rnd);

  mpfr_clear(fr);
  mpfr_clear(fr_srcA);
  mpfr_clear(fr_srcB);
  mpfr_clear(fr_dest);
  mpfr_clear(nh);
  mpfr_clear(nl);
  mpfr_clear(rh);
  mpfr_clear(rl);
  
  MPD_RET(INEX(j1,j2)); 
}







