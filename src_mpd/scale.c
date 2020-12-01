/* mpd_scale() -- scale the two MPD a and b to perform comparison 
   Return an integer which is 
   0 if no scaling occurs
   if scaling occurs, return E such that the number is multiplied by 10^E*/

#include "mpd-impl.h"

int mpd_scale (mpd_ptr aa, mpd_ptr bb, mpd_srcptr a, mpd_srcptr b) {

  mpz_t p;
  mpd_exp_t e;
  size_t s;
  
  /* Singular values */
  /* NaN */
  if (MPD_IS_NAN(a) || MPD_IS_NAN(b)) {
    MPD_SET(aa,a);
    MPD_SET(bb,b);
    MPD_RET_NAN;
  }
  
  /* Infinity - no need to scale */
  if (MPD_IS_INF(a) || MPD_IS_INF(b)) {
    MPD_SET(aa,a);
    MPD_SET(bb,b);
    MPD_RET(0); 
  }
  
  /* Zero - no need to scale */
  if (MPD_IS_ZERO(a) || MPD_IS_ZERO(b)) {
    MPD_SET(aa,a);
    MPD_SET(bb,b);
    MPD_RET(0);
  }
  
  if (MPD_EXP(a) == MPD_EXP(b)) {
    /* No need to scale */
    MPD_SET(aa,a);
    MPD_SET(bb,b);
    MPD_RET(0);
  }
  
  mpz_init(p);
  
  if (MPD_EXP(a) > MPD_EXP(b)) {
    /* Scale a to b */
    MPD_SET(bb,b);
    MPD_CLASS(aa) = MPD_CLASS(a);
    e = MPD_EXP(a) - MPD_EXP(b);
    MPD_SET_EXP(aa,MPD_EXP(b));
    mpz_ui_pow_ui(p,10,e);
    mpz_mul(MPD_MANT(aa),MPD_MANT(a),p);
    s = mpz_sizeinbase(MPD_MANT(aa),10);
    
    if(MPD_PREC(a)>s) {
      MPD_PREC(aa) = MPD_PREC(a);
    } else {
      MPD_PREC(aa) = s;
    }
    
    mpz_clear(p);
    MPD_RET(e);
  } else { /* MPD_EXP(a) < MPD_EXP(b) */
    /* Scale b to a */
    MPD_SET(aa,a);
    MPD_CLASS(bb) = MPD_CLASS(b);
    e = MPD_EXP(b) - MPD_EXP(a);
    MPD_SET_EXP(bb,MPD_EXP(a));
    mpz_ui_pow_ui(p,10,e);
    mpz_mul(MPD_MANT(bb),MPD_MANT(b),p);
    s = mpz_sizeinbase(MPD_MANT(bb),10);
    
    if(MPD_PREC(b)>s) {
      MPD_PREC(bb) = MPD_PREC(b);
    } else {
      MPD_PREC(bb) = s;
    }
    
    mpz_clear(p);
    MPD_RET(e);
  }
}
