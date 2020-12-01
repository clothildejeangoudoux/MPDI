/* mpd_cmp() -- compare two decimal mpd numbers */

#include "mpd-impl.h"

int mpd_cmp (mpd_srcptr a, mpd_srcptr b) {

  mpd_t aa, bb;
  size_t sizeA, sizeB;
  int c;
   
  /* Singular values */
  /* NaN */
  if (MPD_IS_NAN(a) || MPD_IS_NAN(b)) {
    mpd_set_invalidflag();
    printf("LA 1\n");
    return 0; /* return 0 for NaN */
  }
  
  /* Infinity */
  if (MPD_IS_INF(a)) {
    if (MPD_IS_INF(b)) {
      if (MPD_SIGN(b) == MPD_SIGN(a)) {
	/* A and B are infinity with the same sign */
	return 0;
      } else {
	return MPD_SIGN(a);
      }
    }
  } else if (MPD_IS_INF(b)) {
    return -MPD_SIGN(b);
  }

  /* Zero */
  if (MPD_IS_ZERO(a)) {
    if (MPD_IS_ZERO(b)) {
      return 0;
    } else {
      return -MPD_SIGN(b);
    }
  } else if (MPD_IS_ZERO(b)) {
    return MPD_SIGN(a);
  }

  /* a and b are real numbers */
  if (MPD_SIGN(a) != MPD_SIGN(b)) {
    return MPD_SIGN(a);
  }

  /* now sign are equal */
  
  /* Compare with equal exponents */
  if (MPD_EXP(a) == MPD_EXP(b)) {
    return mpz_cmp(MPD_MANT(a),MPD_MANT(b));
  }

  /* Compare without scaling */
  sizeA = mpd_sizeinbase10(MPD_MANT(a));
  sizeB = mpd_sizeinbase10(MPD_MANT(b));
  
  /* Compare the size of the mantissa */
  if (sizeA == sizeB) {
    return MPD_EXP(a) > MPD_EXP(b) ? 1 : -1;
  }
  
  /* Scale the two MPD to perform comparison */
  mpd_init2(aa,MPD_PREC(a));
  mpd_init2(bb,MPD_PREC(b));

  mpd_scale(aa,bb,a,b);

  /* Now aa and bb have the same exponent, compare the mantissas */
  c = mpz_cmp(MPD_MANT(aa),MPD_MANT(bb));

  mpd_clear(aa);
  mpd_clear(bb);

  return c;
}
