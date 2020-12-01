#include "mpd-test.h"

/* checks that a+b gives the expected result c */
void check_add(const char *a, unsigned int prec_a, const char *b, unsigned int prec_b,
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

  if (print == 1) {
    printf(ANSI_COLOR_CYAN"TEST %d :\t"ANSI_COLOR_RESET,cpt->all);
    gmp_printf("  %Zd x 10 ^ %d \t+\t",MPD_MANT(A),MPD_EXP(A));
    gmp_printf("%Zd x 10 ^ %d \t=\t",MPD_MANT(B),MPD_EXP(B)); 
    gmp_printf("%Zd x 10 ^ %d\n",MPD_MANT(C),MPD_EXP(C));
  }
  
  mpd_add(res,A,B,rnd_mode);
  
  if (mpd_cmp(res,C)!=0) {
    printf(ANSI_COLOR_RED"FAIL %d :\t"ANSI_COLOR_RESET"Expecting the sum \t",cpt->all);
    gmp_printf(" %Zd x 10 ^ %d\n",MPD_MANT(C),MPD_EXP(C)); 
    gmp_printf("\t\tand getting the result \t %Zd x 10 ^ %d\n",MPD_MANT(res),MPD_EXP(res)); /* TODO: mpd_str_out function */
    cpt->fail+=1;
  }

  mpd_clear(A);
  mpd_clear(B);
  mpd_clear(C);
  mpd_clear(res);
}

#define check53_add(x, y, r, z, c, print) check_add(x, 16, y, 16, r, 16, z, c, print)

void t_add(int print){

  mpd_cpt_t *cpt;
  cpt=(mpd_cpt_t *) malloc(sizeof(mpd_cpt_t));
  (cpt) -> all = 0;
  (cpt) -> fail = 0;
  
  check_add("293607738.0", 20, "1.9967571564050541e-5", 16, "2.936077380000200e8",16,MPD_RNDU, cpt, print); /* 1 */
  check_add("880524.0", 20, "-2.0769715792901673e-5", 16, "8.8052399997923028e5",16,MPD_RNDN,cpt, print); /* 2 */
  check_add("1196426492.0", 20, "-1.4218093058435347e-3", 16, "1.1964264919985781e9",16,MPD_RNDN,cpt, print); /* 3 */
  check_add("982013018.0", 20, "-8.941829477291838e-7", 16, "9.8201301799999905e8",16,MPD_RNDN,cpt, print); /* 4 */
  check_add("1092583421.0", 20, "1.0880649218158844e9", 16, "2.1806483428158844e9",16,MPD_RNDN,cpt, print); /* 5 */
  check_add("1.8476886419022969e-6", 16, "961494401.0", 20, "9.614944010000018476886419022969e8",16,MPD_RNDN,cpt, print); /* 6 */
  /* check_add("1.8476886419022969e-6", 16, "961494401.0", 20, "9.6149440100000179e8",16,MPD_RNDN,cpt, print); /\* 6  bis*\/ */
  check_add("-2.3222118418069868e5", 16, "1229318102.0", 20, "1.2290858808158193e9",16,MPD_RNDN,cpt, print); /* 7 */
  check_add("-3.0399171300395734e-6", 16, "874924868.0", 20, "8.749248679999970e8",16,MPD_RNDN,cpt, print); /* 8 */
  check_add("9.064246624706179e1", 16, "663787413.0", 20, "6.6378750364246624706179e8",16,MPD_RNDN,cpt, print); /* 9 */
  check_add("-1.0954322421551264e2", 16, "281806592.0", 20, "2.8180648245677578448736e8",16,MPD_RNDD,cpt, print); /* 10 */
  check_add("5.9836930386056659e-8", 16, "1016217213.0", 20,"1.0162172130000001e9",16,MPD_RNDN,cpt, print); /* 11 */
  check_add("-1.2772161928500301e-7", 16, "1237734238.0", 20,"1.2377342379999998e9",16,MPD_RNDN,cpt, print); /* 12 */
  check_add("-4.567291988483277e8", 16, "1262857194.0", 20, "8.061279951516723e8",16,MPD_RNDN,cpt, print); /* 13 */
  check53_add("4.7719471752925262e7", "196089880.0", "2.4380935175292528e8",MPD_RNDN,cpt, print); /* 14 */
  check_add("4.7719471752925262e7", 16, "196089880.0", 20,"2.4380935175292528e8",16,MPD_RNDN,cpt, print); /* 15 */
  check_add("-1.716113812768534e-140", 16, "1271212614.0", 20,"1.2712126139999998e9",16,MPD_RNDZ,cpt, print); /* 16 */
  check_add("-1.2927455200185474e-50", 16, "1675676122.0", 20,"1.6756761219999998e9", 16,MPD_RNDD,cpt, print); /* 17 */

  check53_add("1.22191250737771397120e+20", "948002822.0", "122191250738719408128.0",MPD_RNDN,cpt, print); /* 18 */
  check53_add("9966027674114492.0", "1780341389094537.0", "11746369063209028.0",MPD_RNDN,cpt, print); /* 19 */
  check53_add("2.99280481918991653800e+272", "5.34637717585790933424e+271", "3.527442536775707471424e272",MPD_RNDN,cpt, print); /* 20 */
  check53_add("6.14384195492641560499e-02", "-6.14384195401037683237e-02", "91604e-16",MPD_RNDU,cpt, print); /* 21 */
  check53_add("1.16809465359248765399e+196", "7.92883212101990665259e+196", "9.0969267746123943065e196",MPD_RNDU,cpt, print); /* 22 */
  check53_add("3.14553393112021279444e-67", "3.14553401015952024126e-67", "6.2910679412797336946e-67",MPD_RNDU,cpt, print); /* 23 */
  check53_add("5.43885304644369509058e+185","-1.87427265794105342763e-57", "5.4388530464436950905e185",MPD_RNDN,cpt, print); /* 24 */
  check53_add("5.43885304644369509058e+185","-1.87427265794105342763e-57", "5.4388530464436944867e185",MPD_RNDZ,cpt, print); /* 25 */
  check53_add("5.43885304644369509058e+185","-1.87427265794105342763e-57", "5.4388530464436950905e185",MPD_RNDU,cpt, print); /* 26 */
  check53_add("5.43885304644369509058e+185","-1.87427265794105342763e-57", "5.4388530464436944867e185",MPD_RNDD,cpt, print); /* 27 */
  
  
  printf(ANSI_COLOR_YELLOW"ALL:\t"ANSI_COLOR_RESET"%d\n",cpt->all);
  printf(ANSI_COLOR_RED"FAIL:\t%d\n"ANSI_COLOR_RESET,cpt->fail);
}
