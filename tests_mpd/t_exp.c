#include "mpd-test.h"

/* checks that a+b gives the expected result c */
void check_exp(const char *a, unsigned int prec_a,
	       const char *c, unsigned int prec_c, mpd_rnd_t rnd_mode, mpd_cpt_t *cpt, int print) {
  
  mpd_t A, C, res;

  cpt->all+=1;
  
  mpd_init2(A,prec_a);
  mpd_init2(C,prec_c);
  mpd_init2(res,prec_c);

  mpd_set_str(A,a,rnd_mode);
  mpd_set_str(C,c,rnd_mode);
  if (print==1) {
    printf(ANSI_COLOR_CYAN"TEST EXP %d :\t"ANSI_COLOR_RESET,cpt->all);
    gmp_printf(" exp ( %Zd x 10 ^ %d ) \t=\t",MPD_MANT(A),MPD_EXP(A));
    gmp_printf("%Zd x 10 ^ %d\n",MPD_MANT(C),MPD_EXP(C));
  }
  
  mpd_exp(res,A,rnd_mode);
  
  if (mpd_cmp(res,C)!=0) {
    printf(ANSI_COLOR_RED"FAIL %d :\t"ANSI_COLOR_RESET"Expecting the result \t",cpt->all);
    gmp_printf(" %Zd x 10 ^ %d\n",MPD_MANT(C),MPD_EXP(C)); 
    gmp_printf("\t\tand getting the result \t %Zd x 10 ^ %d\n",MPD_MANT(res),MPD_EXP(res)); /* TODO: mpd_str_out function */
    cpt->fail+=1;
  }

  mpd_clear(A);
  mpd_clear(C);
  mpd_clear(res);
}

#define check3_exp(x, r, z, c, print) check_exp(x, 16, r, 16, z, c, print)

void t_exp(int print){

  mpd_cpt_t *cpt;
  cpt=(mpd_cpt_t *) malloc(sizeof(mpd_cpt_t));
  (cpt) -> all = 0;
  (cpt) -> fail = 0;

  check3_exp("4.44089209850062517562e-16", "1.000000000000000444089209",MPD_RNDN,cpt, print); /* 1 */
  check3_exp("6.39488462184069720009e-14", "1.000000000000063948846218409",MPD_RNDN,cpt, print); /* 2 */
  check3_exp("1.84741111297455401935e-12", "1.0000000000018474111129762604",MPD_RNDN,cpt, print); /* 3 */
  check3_exp("1.76177628026265550074e-10", "1.000000000176177628041784828383391977524226820",MPD_RNDN,cpt, print); /* 4 */
  check3_exp("1.76177628026265550074e-10", "1.000000000176177628041784828383",MPD_RNDN,cpt, print); /* 5 */
  check3_exp("7.54175277499595900852e-10", "1.0000000007541752777839860755192",MPD_RNDN,cpt, print); /* 6 */
  /* bug found by Vincent Lefe`vre on December 8, 1999 */
  check3_exp("-5.42410311287441459172e+02", "2.71765848688457211176779296286172460544e-236",MPD_RNDN,cpt, print); /* 7 */
  /* further cases communicated by Vincent Lefe`vre on January 27, 2000 */
  check3_exp("-1.32920285897904911589e-10", "0.9999999998670797141109289896121989", MPD_RNDN, cpt, print); /* 8 */
  check3_exp("-1.44037948245738330735e-10", "0.9999999998559621072757", MPD_RNDN, cpt, print); /* 9 */
  check3_exp("-1.66795910430705305937e-10", "0.9999999998332040895832", MPD_RNDZ, cpt, print); /* 10 */
  check3_exp("-1.64310953745426656203e-10", "0.9999999998356890462680723885566", MPD_RNDN, cpt, print); /* 11 */
  check3_exp("-1.38323574826034659172e-10", "0.9999999998616764251835", MPD_RNDZ, cpt, print); /* 12 */
  check3_exp("-1.23621668465115401498e-10", "0.9999999998763783315425", MPD_RNDZ, cpt, print); /* 13 */
  /* check3_exp("-60185e5", "0", MPD_RNDD, cpt,print); /\* 13 *\/ */
  /*  check3_exp("0.0", MPFR_RNDU, "1.0"); */
  /* check3_exp("-1e-170", MPFR_RNDU, "1.0"); */
  /* check3_exp("-1e-170", MPFR_RNDN, "1.0"); */
  /* check3_exp("-8.88024741073346941839e-17", MPFR_RNDU, "1.0"); */
  /* check3_exp("8.70772839244701057915e-01", MPFR_RNDN, "2.38875626491680437269"); */
  /* check3_exp("1.0", MPFR_RNDN, "2.71828182845904509080"); */
  /* check3_exp("-3.42135637628104173534e-07", MPFR_RNDZ, "0.999999657864420798958"); */
  /* /\* worst case for argument reduction, very near from 5*log(2), */
  /*    thanks to Jean-Michel Muller  *\/ */
  /* check3_exp("3.4657359027997265421", MPFR_RNDN, "32.0"); */
  /* check3_exp("3.4657359027997265421", MPFR_RNDU, "32.0"); */
  /* check3_exp("3.4657359027997265421", MPFR_RNDD, "31.999999999999996447"); */
  /* check3_exp("2.26523754332090625496e+01", MPFR_RNDD, "6.8833785261699581146e9"); */
  /* check3_exp("1.31478962104089092122e+01", MPFR_RNDZ, "5.12930793917860137299e+05"); */
  /* check3_exp("4.25637507920002378103e-01", MPFR_RNDU, "1.53056585656161181497e+00"); */
  /* check3_exp("6.26551618962329307459e-16", MPFR_RNDU, "1.00000000000000066613e+00"); */
  /* check3_exp("-3.35589513871216568383e-03",MPFR_RNDD, "9.96649729583626853291e-01"); */
  /* check3_exp("1.95151388850007272424e+01", MPFR_RNDU, "2.98756340674767792225e+08"); */
  /* check3_exp("2.45045953503350730784e+01", MPFR_RNDN, "4.38743344916128387451e+10"); */
  /* check3_exp("2.58165606081678085104e+01", MPFR_RNDD, "1.62925781879432281494e+11"); */
  /* check3_exp("-2.36539020084338638128e+01",MPFR_RNDZ, "5.33630792749924762447e-11"); */
  /* check3_exp("2.39211946135858077866e+01", MPFR_RNDU, "2.44817704330214385986e+10"); */
  /* check3_exp("-2.78190533055889162029e+01",MPFR_RNDZ, "8.2858803483596879512e-13"); */
  /* check3_exp("2.64028186174889789584e+01", MPFR_RNDD, "2.9281844652878973388e11"); */
  /* check3_exp("2.92086338843268329413e+01", MPFR_RNDZ, "4.8433797301907177734e12"); */
  /* check3_exp("-2.46355324071459982349e+01",MPFR_RNDZ, "1.9995129297760994791e-11"); */
  /* check3_exp("-2.23509444608605427618e+01",MPFR_RNDZ, "1.9638492867489702307e-10"); */
  /* check3_exp("-2.41175390197331687148e+01",MPFR_RNDD, "3.3564940885530624592e-11"); */
  /* check3_exp("2.46363885231578088053e+01", MPFR_RNDU, "5.0055014282693267822e10"); */
  /* check3_exp("111.1263531080090984914932050742208957672119140625", MPFR_RNDN, "1.8262572323517295459e48"); */
  /* check3_exp("-3.56196340354684821250e+02",MPFR_RNDN, "2.0225297096141478156e-155"); */
  /* check3_exp("6.59678273772710895173e+02", MPFR_RNDU, "3.1234469273830195529e286"); */
  /* check3_exp("5.13772529701934331570e+02", MPFR_RNDD, "1.3445427121297197752e223"); */
  /* check3_exp("3.57430211008718345056e+02", MPFR_RNDD, "1.6981197246857298443e155"); */
  /* check3_exp("3.82001814471465536371e+02", MPFR_RNDU, "7.9667300591087367805e165"); */
  /* check3_exp("5.92396038219384422518e+02", MPFR_RNDD, "1.880747529554661989e257"); */
  /* check3_exp("-5.02678550462488090034e+02",MPFR_RNDU, "4.8919201895446217839e-219"); */
  /* check3_exp("5.30015757134837031117e+02", MPFR_RNDD, "1.5237672861171573939e230"); */
  /* check3_exp("5.16239362447650933063e+02", MPFR_RNDZ, "1.5845518406744492105e224"); */
  /* check3_exp("6.00812634798592370977e-01", MPFR_RNDN, "1.823600119339019443"); */
  
  printf(ANSI_COLOR_YELLOW"ALL:\t"ANSI_COLOR_RESET"%d\n",cpt->all);
  printf(ANSI_COLOR_RED"FAIL:\t%d\n"ANSI_COLOR_RESET,cpt->fail);
}
