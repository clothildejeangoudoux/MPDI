/* mpd_exp() -- exponential of a decimal MPD number */

#include "mpd-impl.h"

int mpd_exp(mpd_ptr y, mpd_srcptr x, mpd_rnd_t rnd) {

  long int i, j, cpt=0, cp=0;
  mpfr_t fr, fr_src, rh, rl, nh, nl;
  mpd_prec_t k;
  mpfr_prec_t p;
  
  /* Singular values */
  /* NaN */
  if (MPD_IS_NAN(x)) {
    MPD_SET_NAN(y);
    MPD_RET_NAN;
  }

  /* Infinity */
  if (MPD_IS_INF(x)) {
    if (MPD_IS_POS(x)) {
      MPD_SET_POS_INF(y);
    } else {
      MPD_SET_POS_ZERO(y);
    }
    MPD_RET(0);
  }
  
  /* Zero */
  if (MPD_IS_ZERO(x)) {
    mpd_set_ui(y,1,rnd);
    MPD_RET(0); /* only exact result for exp */
  }

  /* Set the class to a positive number */
  MPD_CLASS(y) = MPD_CLASS_POS_NUMBER;

   /* Precisions */
  k = MPD_PREC(y);
  p=mpd_precinbase2(k);
  
  /* Conversion into a MPFR */
  mpfr_init2(fr_src,p);
  mpd_get_fr(fr_src,x,rnd);

  /* Ziv loop */
  mpfr_init2(fr,p);
  mpfr_init2(nh,p);
  mpfr_init2(nl,p);
  mpfr_init2(rh,p);
  mpfr_init2(rl,p);

 startloop:
  cp++;
  /* Increase the precision for each Ziv's loop tour */
  mpfr_set_prec(fr,p);
  mpfr_set_prec(rl,p);
  mpfr_set_prec(rh,p);

  i = mpfr_exp(fr,fr_src,rnd);

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
  mpfr_set(nh,rh,rnd);
  mpfr_set(nl,rl,rnd);

  if (mpfr_zero_p(nh) != 0) {
    MPD_SET_ZERO(y);
    MPD_RET(-1);
  }

  if (mpfr_zero_p(nl) != 0) {
    MPD_SET_ZERO(y);
    MPD_RET(-1);
  }
  
  /* we reached the precision needed, set fr */
  if(mpfr_equal_p(nh,nl)){
    j = mpd_set_fr(y,fr,rnd);
    goto endloop;
  }

  p = 1.5*p;
  goto startloop;

 endloop:
  
  mpfr_clear(fr);
  mpfr_clear(fr_src);
  mpfr_clear(rh);
  mpfr_clear(rl);
  mpfr_clear(nh);
  mpfr_clear(nl);
  
  MPD_RET(j);
}




 /*  mpfr_get_z(nh,rh,rnd); */
 /*  size = mpd_sizeinbase10(nh); */

 /*  i = k-size; */
 /*  if (i > 0) { */
 /*    mpz_ui_pow_ui(nh,10,k-size); */
 /*    mpfr_mul_z(rh,rh,nh,rnd); */
 /*    mpfr_mul_z(rl,rl,nh,rnd); */
 /*    mpfr_get_z(nh,rh,rnd); */
 /*    mpfr_get_z(nl,rl,rnd); */
 /*  } */

 /*  /\* we reached the precision needed, set fr *\/ */
 /*  if(mpz_cmp(nh,nl)==0){ */
 /*    j = mpd_set_fr(y,fr,rnd); */
 /*    goto endloop; */
 /*  } */

 /*  p = 2*p; */
 /*  goto startloop; */

 /* endloop: */


/* /\* mpd_exp() -- exponential of a decimal MPD number *\/ */

/* #include "mpd-impl.h" */

/* int mpd_exp(mpd_ptr y, mpd_srcptr x, mpd_rnd_t rnd) { */

/*   int i, j1, j2, cpt; */
/*   mpfr_t fr, fr_src, rh, rl; */
/*   mpd_t nh, nl, test; */
/*   mpd_prec_t k; */
/*   mpfr_prec_t p; */
  
/*   /\* Singular values *\/ */
/*   /\* NaN *\/ */
/*   if (MPD_IS_NAN(x)) { */
/*     MPD_SET_NAN(y); */
/*     MPD_RET_NAN; */
/*   } */

/*   /\* Infinity *\/ */
/*   if (MPD_IS_INF(x)) { */
/*     if (MPD_IS_POS(x)) { */
/*       MPD_SET_POS_INF(y); */
/*     } else { */
/*       MPD_SET_POS_ZERO(y); */
/*     } */
/*     MPD_RET(0); */
/*   } */
  
/*   /\* Zero *\/ */
/*   if (MPD_IS_ZERO(x)) { */
/*     mpd_set_ui(y,1,rnd); */
/*     MPD_RET(0); /\* only exact result for exp *\/ */
/*   } */
  
/*   /\* Set the class to a positive number *\/ */
/*   MPD_CLASS(y) = MPD_CLASS_POS_NUMBER; */

/*    /\* Precisions *\/ */
/*   k = MPD_PREC(y); */
/*   p=mpd_precinbase2(k); */

/*   printf("DEBUT EXP\n"); */
  
/*   /\* Conversion into a MPFR *\/ */
/*   mpfr_init2(fr_src,p); */
/*   mpd_get_fr(fr_src,x,rnd); */

/*   /\* Ziv loop *\/ */
/*   mpfr_init2(fr,p); */
/*   mpd_init2(test,k); */
/*   mpd_init2(nh,k); */
/*   mpd_init2(nl,k); */
/*   mpfr_init2(rh,p); */
/*   mpfr_init2(rl,p); */
  
/*   startloop: */
/*   /\* Increase the precision for each Ziv's loop tour *\/ */
/*   mpfr_set_prec(fr,p); */
/*   mpfr_set_prec(rl,p); */
/*   mpfr_set_prec(rh,p); */
/*   gmp_printf("START LOOP prec %lu %lu\t %Zd * 10 ^ %lu\n",MPD_PREC(x), p ,MPD_MANT(x),MPD_EXP(x)); */
/*   i = mpfr_exp(fr,fr_src,rnd); */

/*   mpfr_set(rl,fr,rnd); */
/*   mpfr_set(rh,fr,rnd); */

/*   cpt=0; */
/*   if(IS_INEXACT(i)) { */
/*     while (cpt<3) { */
/*       mpfr_nextabove(rh); */
/*       mpfr_nextbelow(rl); */
/*       cpt++; */
/*     } */
/*   } */

/*   mpd_set_fr(test,fr,rnd); */
/*   gmp_printf("TEST :\t %Zd * 10 ^ %lu \t=",MPD_MANT(test),MPD_EXP(test)); */
/*   mpd_set_fr(test,rl,rnd); */
/*   gmp_printf(" [ %Zd * 10 ^ %lu ;",MPD_MANT(test),MPD_EXP(test)); */
/*   mpd_set_fr(test,rh,rnd); */
/*   gmp_printf(" %Zd * 10 ^ %lu ]\n ",MPD_MANT(test),MPD_EXP(test)); */

/*    /\* nh and nl are two MPFR with the precision of fr *\/ */
/*   j1 = mpd_set_fr(nh,rh,rnd); */
/*   mpd_set_fr(nl,rl,rnd); */

/*   /\* mpfr_printf("[%.10RNf ; %.10RNf]\n",nl,nh); *\/ */
  
/*   /\* we reached the precision needed, set fr *\/ */
/*   if(mpd_cmp(nh,nl) == 0){ */
/*     printf("SUCCESS \n\n"); */
/*     /\* Convert back to MPD *\/ */
/*     j2 = mpd_set(y,nl,rnd); */
/*     goto endloop; */
/*   } */

/*   p = 1.5*p; */
/*   goto startloop; */

/*  endloop: */

/*   mpfr_clear(fr); */
/*   mpfr_clear(fr_src); */
/*   mpd_clear(nh); */
/*   mpd_clear(nl); */
/*   mpfr_clear(rh); */
/*   mpfr_clear(rl); */
  
/*   MPD_RET(INEX(j1,j2)); */
/* } */
