/* mpd_set_fr() -- convert a binary mpfr into a decimal mpd
   x is MPFR
   y is MPD
   such that :
   x = m*2^E -> y = n*10^F
*/

#include "mpd-impl.h"

int  mpd_set_fr (mpd_ptr y, mpfr_srcptr x, mpd_rnd_t rnd_mode){
  int i1, i2, j=0, cmp, cpt;
  mpd_exp_t F;
  mpfr_prec_t p, precX;
  mpd_prec_t k;
  mpfr_t fr1, fr2, r, rh, rl;
  mpz_t nh, nl, n;

  /* Test x for singular values */
  /* NaN */
  if (MPFR_IS_NAN(x)) {
    MPD_CLASS(y) = MPD_CLASS_NAN;
    MPD_RET_NAN;
  }

  /* Infinity */
  cmp = mpfr_cmp_si(x,0);
  if (MPFR_IS_INF(x)) {
    if (cmp < 0) {
      MPD_SET_NEG_INF(y);
    } else {
      MPD_SET_POS_INF(y);
    }
    MPD_RET(0); /* infinity is exact */
  }

  /* Zero */
  if (MPFR_IS_ZERO(x)) {
    if (cmp < 0) {
      MPD_SET_NEG_ZERO(y);
    } else {
      MPD_SET_POS_ZERO(y);
    }
    MPD_RET(0); /* zero is exact */
  }
    
  
  /* x is not a singular */

  /* p : binary precision used to compute a k decimal precision MPD */
  /* p = k*log2(10)+4 as k=precX*log10(2), then p=precX+4 -> depends on the rounding mode*/

  precX = (mpfr_prec_t) 66;
  mpfr_init2(fr2,precX);
  
  precX=mpfr_get_prec(x);
  k = MPD_PREC(y); 
  p=mpd_precinbase2(k);
  p+=4;

  mpfr_init2(fr1,precX);

  mpz_init(nh);
  mpz_init(nl);
  mpz_init(n);
  mpfr_init2(r,p);
  mpfr_init2(rl,p);
  mpfr_init2(rh,p);
   
  /* /\* Determination of F such that y=n*10^F*\/     */
  /* /\* t66 = RNDD(log10(|x|)) *\/ */
  mpfr_abs(fr1,x,MPFR_RNDN);
  mpfr_log10(fr2,fr1,MPFR_RNDD);

  /* F = FLOOR(t66 - (k - 1)) exact operation */
  /* Computation of k such that k=precX*log10(2) */
  mpfr_sub_si(fr2,fr2,k-1,MPFR_RNDD);
  F = mpfr_get_si(fr2,MPFR_RNDD);

  /* Initialisations before the Ziv loop */
  mpfr_set_ui(fr1,10,rnd_mode);

 step2:
  /* printf("prec %ld, precx %ld\n",p,precX); */
  /* Increase the precision for each Ziv's loop tour */
  mpfr_set_prec(r,p); /* Set the new precision and reset the number */
  mpfr_set_prec(rl,p);
  mpfr_set_prec(rh,p);
  mpfr_set_prec(fr2,p);

  /* steps 2 and 3 */
  i1 = mpfr_pow_si(fr2,fr1,(long int) -F,rnd_mode);
  i2 = mpfr_mul(r,fr2,x,rnd_mode);
  mpfr_set(rh,r,rnd_mode);
  mpfr_set(rl,r,rnd_mode);

  cpt=0;
  if(IS_INEXACT(INEX(i1,i2))){
    /* Compure rh et rl with 3 next_after and next_below */
    while(cpt<3){
      mpfr_nextabove(rh);
      mpfr_nextbelow(rl);
      cpt++;
    }
  }

  /* Step 6 */
  j = mpfr_get_z(nh,rh,rnd_mode);
  mpfr_get_z(nl,rl,rnd_mode);

  /* Step 7 */
  if(mpz_cmp(nh,nl)==0){
    mpz_set(n,nh);
    goto step9;
  }

  /* Step 8 */
  p = 1.5*p;
  goto step2;
  
  /* Step 9 */
 step9:

  // Ici passer en opérations en GMP
  mpz_ui_pow_ui(nl,10,k);
  cmp = mpz_cmp(n,nl);
  
  if (cmp > 0) {
    mpfr_printf("should not happend\n");
    /* Ici on est mort ! */
    MPD_RET_NAN;
  }

  mpd_round(nl,n,MPD_PREC(y),rnd_mode);

  /* Set the mantissa and exponent */
  if (cmp == 0) {
    mpz_tdiv_q_ui(MPD_MANT(y),n,10);
    MPD_SET_EXP(y,F+1);
  } else {
    mpz_set(MPD_MANT(y),n);
    MPD_SET_EXP(y,F);
  }

  cmp = mpz_cmp_ui(n,0);
  /* set the class */
  if (cmp > 0){
    MPD_CLASS(y) = MPD_CLASS_POS_NUMBER;
  } else if (cmp < 0) {
    MPD_CLASS(y) = MPD_CLASS_NEG_NUMBER;
  } else { /* only case left : cmp == 0 */
    MPD_CLASS(y) = MPD_CLASS_POS_ZERO;
  }
  
  /* Free local variables and return */
  mpfr_clear(fr1);
  mpfr_clear(fr2);
  mpfr_clear(r);
  mpfr_clear(rh);
  mpfr_clear(rl);
  mpz_clear(nh);
  mpz_clear(nl);
  mpz_clear(n);
  
  MPD_RET(j);
}
