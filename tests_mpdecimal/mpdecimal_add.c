#include <mpdecimal.h>
#include "mpdecimal-test.h"

/* checks that a+b gives the expected result c */
void check_add(const char *a, const char *b,
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

  mpd_add(res,A,B,&ctx);

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
    printf(ANSI_COLOR_RED"FAIL %d :\t"ANSI_COLOR_RESET"Expecting the sum \t %s\n",cpt->all,rstring);
    rstring = mpd_to_sci(res, 1);
    printf("\t\tand getting the result \t %s\n",rstring); /* TODO: mpd_str_out function */
    cpt->fail+=1;
  }

  mpd_del(A);
  mpd_del(B);
  mpd_del(C);
  mpd_del(res);
}


void mpdecimal_add(int print){

  mpd_cpt_t *cpt;
  cpt=(mpd_cpt_t *) malloc(sizeof(mpd_cpt_t));
  (cpt) -> all = 0;
  (cpt) -> fail = 0;
  
  check_add("293607738.0", "1.9967571564050541e-5", "2.936077380000200e8",16, MPD_ROUND_CEILING, cpt, print); /* 1 */
  check_add("880524.0", "-2.0769715792901673e-5", "8.8052399997923028e5",16, MPD_ROUND_HALF_UP, cpt, print); /* 2 */
  check_add("1196426492.0", "-1.4218093058435347e-3", "1.1964264919985781e9",16,MPD_ROUND_HALF_UP, cpt, print); /* 3 */
  check_add("982013018.0", "-8.941829477291838e-7", "9.8201301799999905e8",16, MPD_ROUND_HALF_UP, cpt, print); /* 4 */
  check_add("1092583421.0", "1.0880649218158844e9", "2.1806483428158844e9",16, MPD_ROUND_HALF_UP, cpt, print); /* 5 */
  check_add("1.8476886419022969e-6", "961494401.0", "9.614944010000018476886419022969e8",16, MPD_ROUND_HALF_UP, cpt, print); /* 6 */
  check_add("1.8476886419022969e-6", "961494401.0", "9.6149440100000179e8",16, MPD_ROUND_HALF_UP, cpt, print); /* 6, print bis */
  check_add("-2.3222118418069868e5", "1229318102.0", "1.2290858808158193e9",16, MPD_ROUND_HALF_UP, cpt, print); /* 7 */
  check_add("-3.0399171300395734e-6", "874924868.0", "8.749248679999970e8",16, MPD_ROUND_HALF_UP, cpt, print); /* 8 */
  check_add("9.064246624706179e1", "663787413.0", "6.6378750364246624706179e8",16, MPD_ROUND_HALF_UP, cpt, print); /* 9 */
  check_add("-1.0954322421551264e2", "281806592.0", "2.8180648245677578448736e8",16, MPD_ROUND_HALF_UP, cpt, print); /* 10 */
  check_add("5.9836930386056659e-8", "1016217213.0", "1.0162172130000001e9",16, MPD_ROUND_HALF_UP, cpt, print); /* 11 */
  check_add("-1.2772161928500301e-7", "1237734238.0", "1.2377342379999998e9",16, MPD_ROUND_HALF_UP, cpt, print); /* 12 */
  check_add("-4.567291988483277e8", "1262857194.0","8.061279951516723e8",16, MPD_ROUND_HALF_UP, cpt, print); /* 13 */
  check_add("4.7719471752925262e7", "196089880.0", "2.4380935175292528e8", 16, MPD_ROUND_HALF_UP, cpt, print); /* 14 */
  check_add("4.7719471752925262e7", "196089880.0","2.4380935175292528e8",16, MPD_ROUND_HALF_UP, cpt, print); /* 15 */
  check_add("-1.716113812768534e-140", "1271212614.0","1.2712126139999998e9",16, MPD_ROUND_DOWN, cpt, print); /* 16 */
  check_add("-1.2927455200185474e-50", "1675676122.0","1.6756761219999998e9", 16, MPD_ROUND_FLOOR, cpt, print); /* 17 */

  check_add("1.22191250737771397120e+20", "948002822.0", "122191250738719408128.0", 16, MPD_ROUND_HALF_UP, cpt, print); /* 18 */
  check_add("9966027674114492.0", "1780341389094537.0", "11746369063209028.0",16, MPD_ROUND_HALF_UP, cpt, print); /* 19 */
  check_add("2.99280481918991653800e+272", "5.34637717585790933424e+271", "3.527442536775707471424e272", 16, MPD_ROUND_HALF_UP, cpt, print); /* 20 */
  check_add("6.14384195492641560499e-02", "-6.14384195401037683237e-02", "91604e-16", 16, MPD_ROUND_CEILING, cpt, print); /* 21 */
  check_add("1.16809465359248765399e+196", "7.92883212101990665259e+196", "9.0969267746123943065e196", 16, MPD_ROUND_CEILING, cpt, print); /* 22 */
  check_add("3.14553393112021279444e-67", "3.14553401015952024126e-67", "6.2910679412797336946e-67", 16, MPD_ROUND_CEILING, cpt, print); /* 23 */
  check_add("5.43885304644369509058e+185","-1.87427265794105342763e-57", "5.4388530464436950905e185", 16, MPD_ROUND_HALF_UP, cpt, print); /* 24 */
  check_add("5.43885304644369509058e+185","-1.87427265794105342763e-57", "5.4388530464436944867e185", 16, MPD_ROUND_DOWN, cpt, print); /* 25 */
  check_add("5.43885304644369509058e+185","-1.87427265794105342763e-57", "5.4388530464436950905e185", 16, MPD_ROUND_CEILING, cpt, print); /* 26 */
  check_add("5.43885304644369509058e+185","-1.87427265794105342763e-57", "5.4388530464436944867e185", 16, MPD_ROUND_FLOOR, cpt, print); /* 27 */
  
  printf(ANSI_COLOR_YELLOW"ALL:\t"ANSI_COLOR_RESET"%d\n",cpt->all);
  printf(ANSI_COLOR_RED"FAIL:\t%d\n"ANSI_COLOR_RESET,cpt->fail);
}
