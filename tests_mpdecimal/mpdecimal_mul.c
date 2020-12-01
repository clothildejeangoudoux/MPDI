#include <mpdecimal.h>
#include "mpdecimal-test.h"

/* checks that a+b gives the expected result c */
void check_mul(const char *a, const char *b,
	       const char *c, unsigned int prec, int newround, mpd_cpt_t *cpt, int print) {
  
  mpd_t *A, *B, *C, *res;
  mpd_context_t ctx;
  char *rstring;

  mpd_init(&ctx, prec);
  ctx.traps = 0;
  mpd_qsetround(&ctx,newround);
  
  cpt->all+=1;
  
  A = mpd_new(&ctx);
  B = mpd_new(&ctx);
  C = mpd_new(&ctx);
  res = mpd_new(&ctx);
  mpd_set_string(A, a, &ctx);
  mpd_set_string(B, b, &ctx);
  mpd_set_string(C, c, &ctx);

  mpd_mul(res,A,B,&ctx);
  
  if (print == 1) {
    printf(ANSI_COLOR_CYAN"TEST %d :\t"ANSI_COLOR_RESET,cpt->all);
    rstring = mpd_to_sci(A, 1);
    printf("%s\t+\t",rstring);
    rstring = mpd_to_sci(B, 1);
    printf("%s \t=\t",rstring);
    rstring = mpd_to_sci(C, 1);
    printf("%s\n",rstring);
  }
  
  if (mpd_cmp(res,C,&ctx)!=0) {
    /* mpd_snprint_flags(status_str, MPD_MAX_FLAG_STRING, ctx.status); */
    /* printf("%s  %s\n", rstring, status_str); */
    rstring = mpd_to_sci(C, 1);
    printf(ANSI_COLOR_RED"FAIL %d :\t"ANSI_COLOR_RESET"Expecting the result \t %s\n",cpt->all,rstring);
    rstring = mpd_to_sci(res, 1);
    printf("\t\tand getting the result \t %s\n",rstring); /* TODO: mpd_str_out function */
    cpt->fail+=1;
  }

  mpd_del(A);
  mpd_del(B);
  mpd_del(C);
  mpd_del(res);
}


void mpdecimal_mul(int print){

  mpd_cpt_t *cpt;
  cpt=(mpd_cpt_t *) malloc(sizeof(mpd_cpt_t));
  (cpt) -> all = 0;
  (cpt) -> fail = 0;

  check_mul("6.9314718055994530941514e-1", "0.0", "0.0", 16, MPD_ROUND_DOWN, cpt, print); /* 1 */
  check_mul("0.0", "6.9314718055994530941514e-1", "0.0", 16, MPD_ROUND_DOWN, cpt, print); /* 2 */
  check_mul("-4.165000000e4", "-0.00004801920768307322868063274915", "1.9999999999999999745483540020975", 16, MPD_ROUND_HALF_UP, cpt, print); /* 3 */
  check_mul("2.71331408349172961467e-08", "-6.72658901114033715233e-165", "-1.8251348697787779159324997772673e-172", 16, MPD_ROUND_DOWN, cpt, print); /* 4 */ 
  check_mul("2.71331408349172961467e-08", "-6.72658901114033715233e-165", "-1.8251348697787781872639081264402e-172", 16, MPD_ROUND_UP,cpt, print); /* 5 */ 
  check_mul("0.31869277231188065", "0.88642843322303122",  "2.8249833483992453642e-1", 16, MPD_ROUND_DOWN, cpt, print); /* 6 */ 
  check_mul("8.47622108205396074254e-01","3.24039313247872939883e-01", "2.74662885836590790664861009631765946072282e-1", 28, MPD_ROUND_CEILING, cpt, print); /* 7 */ 
  check_mul("8.47622108205396074254e-01","3.24039313247872939883e-01","2.74662885836590790664861009631765946072282e-1", 28, MPD_ROUND_UP, cpt, print); /* 8 */ 
  check_mul("2.63978122803639081440e-01", "6.8378615379333496093e-1", "1.805045852774850156391110530560234881392e-1", 31, MPD_ROUND_HALF_UP, cpt, print); /* 9 */ 
  check_mul("1.0", "0.11835170935876249132", "0.11835170935876249132", 36, MPD_ROUND_HALF_UP, cpt, print); /* 10 */ 
  check_mul("67108865.0", "134217729.0", "900719945606758500e-2", 16, MPD_ROUND_HALF_UP, cpt, print); /* 11 */ 
  check_mul("1.37399642157394197284e-01", "2.28877275604219221350e-01","3.1447655765978979359872885588741196e-2", 32, MPD_ROUND_HALF_UP, cpt, print); /* 12 */ 
  check_mul("4.03160720978664954828e-01", "5.854828e-1"/*"5.85483042917246621073e-01"*/, "2.360436677686074980145709584e-1", 32, MPD_ROUND_DOWN, cpt, print); /* 13 */ 
  check_mul("3.90798504668055102229e-14", "9.85394674650308388664e-04","3.85090765361205181537965724071304784732056e-17", 12, MPD_ROUND_HALF_UP, cpt, print); /* 14 */ 
  check_mul("4.58687081072827851358e-01", "2.20543551472118792844e-01", "1.01369844917094955150118e-1", 2, MPD_ROUND_HALF_UP, cpt, print); /* 15 */ 

  printf(ANSI_COLOR_YELLOW"ALL:\t"ANSI_COLOR_RESET"%d\n",cpt->all);
  printf(ANSI_COLOR_RED"FAIL:\t%d\n"ANSI_COLOR_RESET,cpt->fail);
}
