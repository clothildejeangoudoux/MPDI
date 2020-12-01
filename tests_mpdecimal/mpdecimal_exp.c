#include <mpdecimal.h>
#include "mpdecimal-test.h"

/* checks that a+b gives the expected result c */
void check_exp(const char *a,
	       const char *c, int newround, mpd_cpt_t *cpt, int print) {
  
  mpd_t *A, *C, *res;
  mpd_context_t ctx;
  char *rstring;
  unsigned int prec=16;

  mpd_init(&ctx, prec);
  ctx.traps = 0;
  mpd_qsetround(&ctx,newround);
  
  cpt->all+=1;
  
  A = mpd_new(&ctx);
  C = mpd_new(&ctx);
  res = mpd_new(&ctx);
  mpd_set_string(A, a, &ctx);
  mpd_set_string(C, c, &ctx);

  mpd_exp(res,A,&ctx);
  
  if (print == 1) {
    printf(ANSI_COLOR_CYAN"TEST %d :\t"ANSI_COLOR_RESET,cpt->all);
    rstring = mpd_to_sci(A, 1);
    printf("%s\t+\t",rstring);
    rstring = mpd_to_sci(C, 1);
    printf("%s\n",rstring);
  }
  
  if (mpd_cmp(res,C,&ctx)!=0) {
    /* mpd_snprint_flags(status_str, MPD_MAX_FLAG_STRING, ctx.status); */
    /* printf("%s  %s\n", rstring, status_str); */
    rstring = mpd_to_sci(C, 1);
    printf(ANSI_COLOR_RED"FAIL %d :\t"ANSI_COLOR_RESET"Expecting the sum \t %s\n",cpt->all,rstring);
    rstring = mpd_to_sci(res, 1);
    printf("\t\tand getting the result \t %s\n",rstring); /* TODO: mpd_str_out function */
    cpt->fail+=1;
  }

  mpd_del(A);
  mpd_del(C);
  mpd_del(res);
}


void mpdecimal_exp(int print){

  mpd_cpt_t *cpt;
  cpt=(mpd_cpt_t *) malloc(sizeof(mpd_cpt_t));
  (cpt) -> all = 0;
  (cpt) -> fail = 0;

  check_exp("4.44089209850062517562e-16", "1.000000000000000444089209",MPD_ROUND_HALF_UP,cpt, print); /* 1 */
  check_exp("6.39488462184069720009e-14", "1.000000000000063948846218409",MPD_ROUND_HALF_UP,cpt, print); /* 2 */
  check_exp("1.84741111297455401935e-12", "1.0000000000018474111129762604",MPD_ROUND_HALF_UP,cpt, print); /* 3 */
  check_exp("1.76177628026265550074e-10", "1.000000000176177628041784828383391977524226820",MPD_ROUND_HALF_UP,cpt, print); /* 4 */
  check_exp("1.76177628026265550074e-10", "1.000000000176177628041784828383",MPD_ROUND_HALF_UP,cpt, print); /* 5 */
  check_exp("7.54175277499595900852e-10", "1.0000000007541752777839860755192",MPD_ROUND_HALF_UP,cpt, print); /* 6 */
  /* bug found by Vincent Lefe`vre on December 8, 1999 */
  check_exp("-5.42410311287441459172e+02", "2.71765848688457211176779296286172460544e-236",MPD_ROUND_HALF_UP,cpt, print); /* 7 */
  /* further cases communicated by Vincent Lefe`vre on January 27, 2000 */
  check_exp("-1.32920285897904911589e-10", "0.9999999998670797141109289896121989", MPD_ROUND_HALF_UP, cpt, print); /* 8 */
  check_exp("-1.44037948245738330735e-10", "0.9999999998559621072757", MPD_ROUND_HALF_UP, cpt, print); /* 9 */
  check_exp("-1.66795910430705305937e-10", "0.9999999998332040895832", MPD_ROUND_DOWN, cpt, print); /* 10 */
  check_exp("-1.64310953745426656203e-10", "0.9999999998356890462680723885566", MPD_ROUND_HALF_UP, cpt, print); /* 11 */
  check_exp("-1.38323574826034659172e-10", "0.9999999998616764251835", MPD_ROUND_DOWN, cpt, print); /* 12 */
  check_exp("-1.23621668465115401498e-10", "0.9999999998763783315425", MPD_ROUND_DOWN, cpt, print); /* 13 */
  
  printf(ANSI_COLOR_YELLOW"ALL:\t"ANSI_COLOR_RESET"%d\n",cpt->all);
  printf(ANSI_COLOR_RED"FAIL:\t%d\n"ANSI_COLOR_RESET,cpt->fail);
}

 
