#include "mpd-test.h"

/* checks that a+b gives the expected result c */
void check_div(const char *a, unsigned int prec_a, const char *b, unsigned int prec_b,
	       const char *c, unsigned int prec_c, mpd_rnd_t rnd_mode, mpd_cpt_t *cpt, int print) {
  
  mpd_t A, B, C, res;

  cpt->all+=1;
  
  mpd_init2(A,prec_a);
  mpd_init2(B,prec_b);
  mpd_init2(C,prec_c);
  mpd_init2(res,prec_c);

  mpd_set_str(A,a,rnd_mode);
  mpd_set_str(B,b,rnd_mode);
  mpd_set_str(C,c,rnd_mode);
  if (print==1) {
    printf(ANSI_COLOR_CYAN"TEST %d :\t"ANSI_COLOR_RESET,cpt->all);
    gmp_printf("  %Zd x 10 ^ %d \t/\t",MPD_MANT(A),MPD_EXP(A));
    gmp_printf("%Zd x 10 ^ %d \t=\t",MPD_MANT(B),MPD_EXP(B));
    gmp_printf("%Zd x 10 ^ %d\n",MPD_MANT(C),MPD_EXP(C));
  }
    
  mpd_div(res,A,B,rnd_mode);
  
  if (mpd_cmp(res,C)!=0) {
    printf(ANSI_COLOR_RED"FAIL %d :\t"ANSI_COLOR_RESET"Expecting the result \t",cpt->all);
    gmp_printf(" %Zd x 10 ^ %d\n",MPD_MANT(C),MPD_EXP(C)); 
    gmp_printf("\t\tand getting the result \t %Zd x 10 ^ %d\n",MPD_MANT(res),MPD_EXP(res)); /* TODO: mpd_str_out function */
    cpt->fail+=1;
  }

  mpd_clear(A);
  mpd_clear(B);
  mpd_clear(C);
  mpd_clear(res);
}

#define check53_div(x, y, r, z, c) check_div(x, 16, y, 16, r, 16, z, c)

void t_div(int print){

  mpd_cpt_t *cpt;
  cpt=(mpd_cpt_t *) malloc(sizeof(mpd_cpt_t));
  (cpt) -> all = 0;
  (cpt) -> fail = 0;

  printf(ANSI_COLOR_YELLOW"ALL:\t"ANSI_COLOR_RESET"%d\n",cpt->all);
  printf(ANSI_COLOR_RED"FAIL:\t%d\n"ANSI_COLOR_RESET,cpt->fail);
}
