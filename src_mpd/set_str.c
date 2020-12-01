/* mpd_set_str() -- set a number from a decimal string representation */
#include "mpd-impl.h"

int mpd_set_str (mpd_ptr x, const char *str, mpd_rnd_t rnd_mode){

  size_t t = strlen(str);
  char mant1[t], mant2[t], exp[t];
  unsigned int i,t_exp;
  int is_point=0, is_exp=0, n=0;
  int inex, valid, class;
  mpd_exp_t E;
  mpd_t y;
  
  /* Cannot get Nan of inf as input */

  /* initializations */
  memset(mant1, 0, sizeof(mant1));
  memset(mant2, 0, sizeof(mant2));
  memset(exp, 0, sizeof(exp));
  /* set z to prec t, may be too large */
  mpd_init2(y,t);
  
  /* String Parsing */
  for (i=0;i<t;i++) {
    /* if there is a decimal point */
    if (str[i] == '.') {
      is_point=i;
    }
    /* if there is an exponent e */
    if ((str[i] == 'e') || (str[i] == 'E')) {
      is_exp=i;
    }
  }

  /* String parsing */
  if(is_exp) {
    strncpy(exp,str+is_exp+1,t-is_exp+1);
    E=atol(exp);
      if(is_point) {
	strncpy(mant1,str,is_point);
	strncpy(mant2,str+is_point+1,is_exp-is_point-1);
	strcat(mant1,mant2);
	t_exp=strlen(mant2);
	E-=t_exp;
      } else {
	strncpy(mant1,str,is_exp);
      }
  } else {
    E=0;
    if(is_point) {
      strncpy(mant1,str,is_point);
      strncpy(mant2,str+is_point+1,t-is_point+1);
      strcat(mant1,mant2);
      t_exp=strlen(mant2);
      E-=t_exp;
    } else {
      strcpy(mant1,str);
    }
  }

  /* Set temporary MPD */
  MPD_SET_EXP(y,E);

  /* valid is 0 if the string is valid */
  valid = mpz_set_str(MPD_MANT(y),mant1,10); 

  /* Set the class of y */
  class=mpz_cmp_si(MPD_MANT(y),0);
  if(class == 0) {
    MPD_SET_ZERO(x);
  } else if (class == 1) {
    MPD_CLASS(y) = MPD_CLASS_POS_NUMBER;
  } else {
    MPD_CLASS(y) = MPD_CLASS_NEG_NUMBER;
    n=1;
  }

  if (valid==0) {
    /* Check the precision of x */
    if (MPD_PREC(x) >= (strlen(mant1)-n)) {
      /* No rounding, set y to x with GMP set function */
      MPD_SET(x,y);
      mpd_clear(y);
      MPD_RET(0);
    } else {
      /* prec(x) < prec(y)
	 Round y into x */
      inex = mpd_set(x,y,rnd_mode);
      
      mpd_clear(y);
      MPD_RET(inex);
    }
  } else {
    MPD_RET(valid);
  }


  MPD_RET(0);
}
