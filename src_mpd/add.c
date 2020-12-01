/* mpd_add() -- addition of two mpd numbers */

#include "mpd-impl.h"

int mpd_add(mpd_ptr x, mpd_srcptr a, mpd_srcptr b, mpd_rnd_t rnd) {

  size_t sizeA, sizeB;
  mpd_exp_t diff_exp;
  mpd_prec_t temp_prec;
  mpd_t temp, aa, bb;
  int inex;
  
  /* Test x for singular values */
  /* NaN */
  if (MPD_IS_NAN(a) || MPD_IS_NAN(b)) {
    MPD_SET_NAN(x);
    MPD_RET_NAN;
  }

  /* Infinity cases */
  if (MPD_IS_INF(a)) {
    if (!MPD_IS_INF(b) || MPD_SIGN(a) == MPD_SIGN(b)) {
      if (MPD_SIGN(a)){
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
  if(MPD_IS_INF(b)){
    if (MPD_SIGN(b)){
      MPD_SET_POS_INF(x);
    } else {
      MPD_SET_NEG_INF(x);
    }
    MPD_RET(0); /* exact */
  }

  /* Zero cases */
  if(MPD_IS_ZERO(a)){
    if(MPD_IS_ZERO(b)){
      /* for round away, we take the same convention for 0 + 0
	 as for round to zero or to nearest: it always gives +0,
	 except (-0) + (-0) = -0. */
      if (rnd != MPD_RNDD) {
	if (MPD_IS_NEG(a) && MPD_IS_NEG(b)) {
	  MPD_SET_NEG_ZERO(x);
	} else {
	  MPD_SET_POS_ZERO(x);
	}
	if (MPD_IS_POS(a) && MPD_IS_POS(b)) {
	  MPD_SET_POS_ZERO(x);
	} else {
	  MPD_SET_NEG_ZERO(x);
	}
      }
      MPD_RET(0); /* 0 + 0 is exact */
    }
    inex = mpd_set(x,b,rnd);
    MPD_RET(inex);
  } else if (MPD_IS_ZERO(b)) {
    inex = mpd_set(x,a,rnd);
    MPD_RET(inex);
  }

  /* Addition algorithm */
  /* Pre-computation of useful values */
  sizeA = mpz_sizeinbase(MPD_MANT(a),10); /* The value is either exact or 1 too big */
  sizeB = mpz_sizeinbase(MPD_MANT(b),10);
  
  if (MPD_SIGN(a) == MPD_SIGN(b)) {
    /* same signs, it is an addition */
    /* If the exponents are equals */
    if (MPD_EXP(a) == MPD_EXP(b)) {
      /* Intermediary precision for the addition */
      temp_prec = (sizeA > sizeB ? sizeA : sizeB) +1; /* The value is either exact or 1 too big */
      if (temp_prec <= MPD_PREC(x)) {
	/* no rounding necessary */
	mpz_add(MPD_MANT(x),MPD_MANT(a),MPD_MANT(b));
	MPD_SET_EXP(x,MPD_EXP(a));
	if (mpz_cmp_ui(MPD_MANT(x),0) > 0) {
	  MPD_CLASS(x) = MPD_CLASS_POS_NUMBER;
	} else {
	  MPD_CLASS(x) = MPD_CLASS_NEG_NUMBER;
	} /* Cannot be zero */

	MPD_RET(0);
      } else {
	/* rounding may occur */
	mpd_init2(temp,temp_prec);
	mpz_add(MPD_MANT(temp),MPD_MANT(a),MPD_MANT(b));
	MPD_SET_EXP(temp,MPD_EXP(a));
	if (mpz_cmp_ui(MPD_MANT(temp),0) > 0) {
	  MPD_CLASS(temp) = MPD_CLASS_POS_NUMBER;
	} else {
	  MPD_CLASS(temp) = MPD_CLASS_NEG_NUMBER;
	} /* Cannot be zero */
	/* rounding */
	inex = mpd_set(x,temp,rnd);

	mpd_clear(temp);
	MPD_RET(inex);
      }
    } else {
      /* The exponents are differents */     
      /* Compare the size of the mantissa and tackle the absorbtion cases */
      if (sizeA == sizeB) {
	if (MPD_EXP(a) > MPD_EXP(b)) {
	  diff_exp = MPD_EXP(a) - MPD_EXP(b); /* alwayse positive */
	  if (diff_exp >= MPD_PREC(x)) {
	    inex = mpd_set(x,a,rnd);
	    MPD_RET(inex);
	  }
	} else {
	  diff_exp = MPD_EXP(b) - MPD_EXP(a); /* alwayse positive */
	  if (diff_exp >= MPD_PREC(x)) {
	    inex = mpd_set(x,b,rnd);
	    MPD_RET(inex);
	  }
	}
      }
    
      /* Perform the addition with scaled values */
      mpd_init2(aa,MPD_PREC(a));
      mpd_init2(bb,MPD_PREC(b));
      temp_prec = MPD_EXP(a) - MPD_EXP(b) > 0 ? MPD_EXP(a) - MPD_EXP(b) : MPD_EXP(b) - MPD_EXP(a);
      temp_prec += sizeA + sizeB;
      mpd_init2(temp,temp_prec);
      mpd_scale(aa,bb,a,b);
       
      /* Now aa and bb have the same exponent, compare the mantissas */
      mpz_add(MPD_MANT(temp),MPD_MANT(aa),MPD_MANT(bb));
      MPD_SET_EXP(temp,MPD_EXP(aa));
      
      if (mpz_cmp_ui(MPD_MANT(temp),0) > 0) {
	MPD_CLASS(temp) = MPD_CLASS_POS_NUMBER;
      } else {
	MPD_CLASS(temp) = MPD_CLASS_NEG_NUMBER;
      } /* Cannot be zero */
      
      /* rounding */
      inex = mpd_set(x,temp,rnd);

      mpd_clear(temp);
      mpd_clear(aa);
      mpd_clear(bb);

      MPD_RET(inex);      
    }    
  } else {    
    /* signs differ, it is a substration */
    if (MPD_IS_POS(a)) {
      mpd_init2(bb,MPD_PREC(b));
      mpd_neg(bb,b,rnd);
      inex = mpd_sub(x,a,bb,rnd);
      mpd_clear(bb);
      MPD_RET(inex);
    } else {
      mpd_init2(aa,MPD_PREC(a));
      mpd_neg(aa,a,rnd);
      inex = mpd_sub(x,b,aa,rnd);
      mpd_clear(aa);
      MPD_RET(inex);
    }
  }
}
