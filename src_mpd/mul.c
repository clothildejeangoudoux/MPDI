/* mpd_mul() -- multiplication of two mpd */

#include "mpd-impl.h"

int mpd_mul (mpd_ptr x, mpd_srcptr a, mpd_srcptr b, mpd_rnd_t rnd_mode){
  mpd_exp_t temp_exp;
  mpd_prec_t temp_prec;
  int sign_product, inex;
  mpz_t temp_mant;

  /* Test x for singular values */
  /* NaN */
  if (MPD_IS_NAN(a) || MPD_IS_NAN(b)) {
    MPD_SET_NAN(x);
    MPD_RET_NAN;
  }
  
  sign_product = MPD_MULT_SIGN(a,b);

  /* Product with infinity */
  if (MPD_IS_INF(a)) {
    if (MPD_IS_INF(b) || MPD_NOTZERO(b)) {
      if(sign_product) {
	MPD_SET_POS_INF(x);
      } else {
	MPD_SET_NEG_INF(x);
      }
      MPD_RET(0); /* exact */
    } else {
      MPD_SET_NAN(x);
      MPD_RET_NAN;
    }
  } else if (MPD_IS_INF(b)) {
    if (MPD_NOTZERO(a)) {
     if(sign_product) {
       MPD_SET_POS_INF(x);
      } else {
       MPD_SET_NEG_INF(x);
      }
     MPD_RET(0); /* exact */
    } else {
      MPD_SET_NAN(x);
      MPD_RET_NAN;
    } 
  }

  if (MPD_IS_ZERO(a) || MPD_IS_ZERO(b)) {
    if (sign_product) {
      MPD_SET_POS_ZERO(x);
    } else {
      MPD_SET_NEG_ZERO(x);
    }
    MPD_RET(0); /* 0*0 is exact */
  }

  /* Begining of the product algorithm */
  if(sign_product){
    MPD_CLASS(x) = MPD_CLASS_POS_NUMBER;
  } else {
    MPD_CLASS(x) = MPD_CLASS_NEG_NUMBER;
  }
  
  temp_exp = MPD_EXP(a) + MPD_EXP(b);  /* Attention traiter les dépassements de capacité */
  /* Un truc du genre vérifier que exp est dans le range emin - emax sinon overflow/underflow */
  temp_prec = mpd_precinbase2(MPD_PREC(a) + MPD_PREC(b));
  mpz_init2(temp_mant,temp_prec);  
  mpz_mul(temp_mant,MPD_MANT(a),MPD_MANT(b));
   
  /* Prise en compte de la précision */
  inex = mpd_set_z(x,temp_mant,rnd_mode);
  MPD_EXP(x) += temp_exp;
 
  mpz_clear(temp_mant);
  
  MPD_RET(inex);
}
