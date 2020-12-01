#include "mpd-test.h"

/* checks that a+b gives the expected result c */
void check_mul(const char *a, unsigned int prec_a, const char *b, unsigned int prec_b,
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
    gmp_printf("  %Zd x 10 ^ %d \t*\t",MPD_MANT(A),MPD_EXP(A));
    gmp_printf("%Zd x 10 ^ %d \t=\t",MPD_MANT(B),MPD_EXP(B));
    gmp_printf("%Zd x 10 ^ %d\n",MPD_MANT(C),MPD_EXP(C));
  }
  
  mpd_mul(res,A,B,rnd_mode);
  
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

#define check53_mul(x, y, r, z, c, print) check_mul(x, 16, y, 16, r, 16, z, c, print)

void t_mul(int print){

  mpd_cpt_t *cpt;
  cpt=(mpd_cpt_t *) malloc(sizeof(mpd_cpt_t));
  (cpt) -> all = 0;
  (cpt) -> fail = 0;

  check53_mul("6.9314718055994530941514e-1", "0.0", "0.0", MPD_RNDZ, cpt, print); /* 1 */
  check53_mul("0.0", "6.9314718055994530941514e-1", "0.0", MPD_RNDZ, cpt, print); /* 2 */
  check53_mul("-4.165000000e4", "-0.00004801920768307322868063274915", "1.9999999999999999745483540020975", MPD_RNDN, cpt, print); /* 3 */
  check53_mul("2.71331408349172961467e-08", "-6.72658901114033715233e-165", "-1.8251348697787779159324997772673e-172", MPD_RNDZ, cpt, print); /* 4 */ 
  check53_mul("2.71331408349172961467e-08", "-6.72658901114033715233e-165", "-1.8251348697787781872639081264402e-172", MPD_RNDA,cpt, print); /* 5 */ 
  check53_mul("0.31869277231188065", "0.88642843322303122",  "2.8249833483992453642e-1", MPD_RNDZ, cpt, print); /* 6 */ 
  check_mul("8.47622108205396074254e-01", 28, "3.24039313247872939883e-01", 45, "2.74662885836590790664861009631765946072282e-1", 2, MPD_RNDU, cpt, print); /* 7 */ 
  check_mul("8.47622108205396074254e-01", 28, "3.24039313247872939883e-01", 45, "2.74662885836590790664861009631765946072282e-1", 2, MPD_RNDA, cpt, print); /* 8 */ 
  check_mul("2.63978122803639081440e-01", 34, "6.8378615379333496093e-1", 23, "1.805045852774850156391110530560234881392e-1", 31, MPD_RNDN, cpt, print); /* 9 */ 
  check_mul("1.0", 6, "0.11835170935876249132", 41, "0.11835170935876249132", 36, MPD_RNDU, cpt, print); /* 10 */ 
  check53_mul("67108865.0", "134217729.0", "900719945606758500e-2", MPD_RNDN, cpt, print); /* 11 */ 
  check_mul("1.37399642157394197284e-01", 49, "2.28877275604219221350e-01", 15, "3.1447655765978979359872885588741196e-2", 32, MPD_RNDN, cpt, print); /* 12 */ 
  check_mul("4.03160720978664954828e-01", 51, "5.854828e-1"/*"5.85483042917246621073e-01"*/, 22,  "2.360436677686074980145709584e-1", 32, MPD_RNDZ, cpt, print); /* 13 */ 
  check_mul("3.90798504668055102229e-14", 46, "9.85394674650308388664e-04", 22, "3.85090765361205181537965724071304784732056e-17", 12, MPD_RNDN, cpt, print); /* 14 */ 
  check_mul("4.58687081072827851358e-01", 49, "2.20543551472118792844e-01", 3,  "1.01369844917094955150118e-1", 2, MPD_RNDN, cpt, print); /* 15 */ 

  printf(ANSI_COLOR_YELLOW"ALL:\t"ANSI_COLOR_RESET"%d\n",cpt->all);
  printf(ANSI_COLOR_RED"FAIL:\t%d\n"ANSI_COLOR_RESET,cpt->fail);
}
