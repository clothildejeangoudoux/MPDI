/* mpd_sizeinbase10 --  round the gmp mantissa x into the result r at precision p */

#include "mpd-impl.h"

int mpd_round (mpz_ptr r, mpz_srcptr x, mpd_prec_t p, mpd_rnd_t rnd_mode) {

  long int i, j, c, l;
  size_t size =  mpd_sizeinbase10(x);
  mpz_t n, m;
  
  if (size <= p) {
    mpz_set(r,x);
    MPD_RET(0);
  } else {
    mpz_init(n);
    mpz_init(m);
    
    if (rnd_mode == MPD_RNDZ) {
      mpz_ui_pow_ui(n,10,size-p);
      mpz_tdiv_q(m,x,n);
      l=-1;
    } else if (rnd_mode == MPD_RNDU) {
      mpz_ui_pow_ui(n,10,size-p);
      mpz_cdiv_q(m,x,n);
      l=1;
    } else if (rnd_mode == MPD_RNDD) {
      mpz_ui_pow_ui(n,10,size-p);
      mpz_fdiv_q(m,x,n);
      l=1;
    } else if (rnd_mode == MPD_RNDA) {
      mpz_ui_pow_ui(n,10,size-p);
      c = mpz_cmp_ui(x,0);
      if (c > 0) {
	mpz_cdiv_q(m,x,n);
      } else {
	mpz_fdiv_q(m,x,n);
      }
      l=1;
    } else { /* MPD_RNDN */
      mpz_ui_pow_ui(n,10,size-p-1);
      mpz_fdiv_q(m,x,n);
      mpz_fdiv_qr_ui(m,n,m,10);
      l=1;
      if (mpz_cmp_ui(n,5)>=0) {
	mpz_ui_pow_ui(n,10,size-p);      
	mpz_cdiv_q(m,x,n);
      } else if (mpz_cmp_ui(n,4)<0){
	mpz_ui_pow_ui(n,10,size-p);      
	mpz_fdiv_q(m,x,n);
      } else {
	i = 2;
	j = 0;
	l = size-p-i;
	while ((j == 0) && (l >= 0)) {
	  mpz_ui_pow_ui(n,10,size-p-i);
	  mpz_fdiv_q(m,x,n);
	  mpz_fdiv_qr_ui(m,n,m,10);
	  if(mpz_cmp_ui(n,5)>=0) {
	    j = 1;
	  } else if (mpz_cmp_ui(n,4)<0) {
	    j = -1;
	  }
	  i+=1;
	}
	if (j == 1) {
	  mpz_ui_pow_ui(n,10,size-p);      
	  mpz_cdiv_q(m,x,n);
	} else {
	  mpz_ui_pow_ui(n,10,size-p);      
	  mpz_fdiv_q(m,x,n);
	}
      }	  
    }
    mpz_set(r,m);
    mpz_clear(n);
    mpz_clear(m);
    MPD_RET(l);
  }
}


/*   memset(str,0,size); */
/*   mpz_get_str(str,10,x); */
  
/*   p2 = mpd_precinbase2(size); */
/*   mpfr_init2(fr,p2+1); */
/*   mpd_init2(out,p); */
  
/*   inex1 = mpfr_set_str(fr,str,10,rnd_mode); */
/*   printf("ICI\n"); */
/*   inex2 = mpd_set_fr(out,fr,rnd_mode); */
/*   printf("ICI OK\n"); */
/*   mpz_set(r,MPD_MANT(out)); */
  
/*   mpfr_clear(fr); */
/*   mpd_clear(out); */
/*   MPD_RET(INEX(inex1,inex2)); */
/* } */

/* /\* Propagate a carry from the end of a GMP number *\/ */
/* void propagate_carry(char *str_out, char *str_in) { */
/*   size_t size=strlen(str_in); */
/*   int i = size, j, last = 9; */
/*   char c, s[1]=" "; */

/*   memset(str_out,'0',size); */
  
/*   for (i=size-1 ; i>=0 ; i--) { */
/*     c=str_in[i]; */
/*     s[0] = c; */
/*     j = atoi(s); */
/*     if (j != 9) { */
/*       if (last == 9) { */
/* 	j = j+1; */
/* 	str_out[i] = j+'0'; */
/*       } else { */
/* 	str_out[i] = str_in[i]; */
/*       } */
/*     } else if (last != 9) { */
/*       str_out[i] = str_in[i]; */
/*     } */
/*     if (last == 9) { */
/*       last = j; */
/*     } else { */
/*       last = 0; */
/*     } */
/*   } */

/*   if (last == 9) { */
/*     str_out[0] = '1'; */
/*   } */
/* } */

/* /\* Propagate a carry for a length p string str_after from the larger str_before string *\/ */
/* void backward_propagate_carry(char *str_before, char *str_after, mpd_prec_t p, size_t size) { */

/*   char c=' ', s[1]=" "; */
/*   int i; */
/*   size_t p_size=p; */
  
/*   c=str_before[p]; */
/*   s[0] = c; */
/*   i = atoi(s); */

/*   while ((p_size <= size) && (i >= 4)) { */
/*     if (i >= 5) { */
/*       c=str_after[p-1]; */
/*       s[0] = c; */
/*       i = atoi(s); */
/*       if (i < 9) { */
/* 	str_after[p-1] = i+1+'0'; */
/*       } else { */
/* 	memset(str_before,0,size); */
/* 	propagate_carry(str_before,str_after); */
/* 	memset(str_after,0,size); */
/* 	memcpy(str_after,str_before,p); */
/*       } */
/*       return; */
/*     } else { */
/*       p_size++; */
/*       c=str_before[p_size]; */
/*       s[0] = c; */
/*       i = atoi(s); */
/*     } */
/*   } */

/*   if(p_size == p) { */
/*     memset(str_before,0,size); */
/*     propagate_carry(str_before,str_after); */
/*   } */
/* } */
  
/* int mpd_round (mpz_ptr r, mpz_srcptr x, mpd_prec_t p, mpd_rnd_t rnd_mode) { */

/*   int inex = 0; */
/*   size_t size =  mpd_sizeinbase10(x); */

/*   if (size <= p) { */
/*     mpz_set(r,x); */
/*     MPD_RET(0); */
/*   } */
  
/*   char str_before[size+1], str_after[size+1], c_end=' ', s_end[1]=" ", str_final[p+2]; */
/*   int i_end; */
/*   mpd_prec_t p_final = p; */
  
/*   memset(str_before,0,size); */
/*   memset(str_after,0,size); */
/*   mpz_get_str(str_before,10,x); */
/*   size=strlen(str_before); */

/*   if (rnd_mode == MPD_RNDN) { /\* round to nearest, with ties to even *\/ */
/*     if (mpz_cmp_ui(x,0)<0) { /\* The number is negative *\/ */
/*       p_final = p+1; */
/*     } */
/*     /\* Truncate *\/ */
/*     memcpy(str_after,str_before,p); */
    
/*     /\* and sub 1 *\/ */
/*     c_end=str_before[p]; */
/*     s_end[0] = c_end; */
/*     i_end = atoi(s_end); */

/*     if (i_end >= 4) { */
/*       backward_propagate_carry(str_before,str_after,p,size); */
/*       inex = 1; */
/*     } else { */
/*       inex = -1; */
/*     } */
/*   } else if (rnd_mode == MPD_RNDZ) {  /\* round toward zero *\/ */
/*     /\* Same algorithm if positive or negative : truncate the number *\/ */
/*     if (mpz_cmp_ui(x,0)>0) { /\* The number is positive *\/ */
/*       inex = -1; */
/*     } else { */
/*       p_final = p+1; */
/*       inex = 1; */
/*     } */
/*     memcpy(str_after,str_before,p_final); */
/*   } else if (rnd_mode == MPD_RNDU) { /\* round toward +Inf *\/ */
/*     if (mpz_cmp_ui(x,0)>0) { /\* The number is positive *\/ */
/*       /\* Truncate *\/ */
/*       memcpy(str_after,str_before,p); */

/*       /\* and add 1 *\/ */
/*       c_end=str_after[p-1]; */
/*       s_end[0] = c_end; */
/*       i_end = atoi(s_end); */

/*       if (i_end == 9) { */
/* 	backward_propagate_carry(str_before,str_after,p,size); */
/*       	inex = 1; */
/*       } else { */
/* 	i_end += 1; */
/* 	s_end[0] = i_end + '0'; */
/* 	str_after[p-1] = s_end[0]; */
/*       } */
/*     } else { /\* The number is negative *\/ */
/*       /\* Truncate *\/ */
/*       p_final = p+1; */
/*       memcpy(str_after,str_before,p_final); */
/*     } */
/*     inex = 1; */
/*   } else if (rnd_mode == MPD_RNDD) { /\* round toward -Inf *\/ */
/*     if (mpz_cmp_ui(x,0)>0) { /\* The number is positive *\/ */
/*       /\* Truncate *\/ */
/*       memcpy(str_after,str_before,p); */
/*     } else { /\* The number is negative *\/ */
/*       /\* Truncate *\/ */
/*       p_final = p+1; */
/*       memcpy(str_after,str_before,p_final); */
/*       /\* and subtract 1 *\/ */
/*       c_end=str_after[p_final-1]; */
/*       s_end[0] = c_end; */
/*       i_end = atoi(s_end); */

/*       if (i_end == 9) { */
/*       	propagate_carry(str_after,str_before); */
/*       	inex = 1; */
/*       } else { */
/* 	i_end += 1; */
/* 	s_end[0] = i_end + '0'; */
/* 	str_after[p_final-1] = s_end[0]; */
/*       } */
/*     } */
/*     inex = -1; */
/*   } else if (rnd_mode == MPD_RNDA) { /\* round away from zero *\/ */
/*     if (mpz_cmp_ui(x,0)>0) { /\* The number is positive *\/ */
/*       /\* Truncate *\/ */
/*       memcpy(str_after,str_before,p); */
/*       /\* and add 1 *\/ */
/*       c_end=str_after[p-1]; */
/*       s_end[0] = c_end; */
/*       i_end = atoi(s_end); */

/*       if (i_end == 9) { */
/*       	propagate_carry(str_after,str_before); */
/*       	inex = 1; */
/*       } else { */
/* 	i_end += 1; */
/* 	s_end[0] = i_end + '0'; */
/* 	str_after[p-1] = s_end[0]; */
/*       } */
/*       inex = 1; */
/*     } else { /\* The number is negative *\/ */
/*       /\* Truncate *\/ */
/*       p_final = p+1; */
/*       memcpy(str_after,str_before,p_final); */
/*       /\* and subtract 1 *\/ */
/*       c_end=str_after[p_final-1]; */
/*       s_end[0] = c_end; */
/*       i_end = atoi(s_end); */
      
/*       if (i_end == 9) { */
/*       	propagate_carry(str_after,str_before); */
/*       	inex = 1; */
/*       } else { */
/* 	i_end += 1; */
/* 	s_end[0] = i_end + '0'; */
/* 	str_after[p_final-1] = s_end[0]; */
/*       } */
/*       inex = -1; */
/*     } */
/*   } */

/*   memset(str_final,0,p_final+1); */
/*   memcpy(str_final,str_after,p_final); */
/*   mpz_set_str(r,str_final,10); */

/*   gmp_printf("IN MPZ \t %Zd \n",x); */
/*   gmp_printf("OUT MPZ\t %Zd \n\n",r); */
/*   MPD_RET(inex); */
/* } */
