#include "mpd-test.h"
#include "mpd-impl.h"

#define EXP_MAX 400
#define MANT_MAX 500
#define TESTMAX 100000000
#define TESTMIN -99999999

/* An assembly macro to get the time counter */
/* time must be a pointer to an unsigned long long int */
#define READ_TIME_COUNTER(time)                              \
        __asm__ __volatile__(                                \
                "xorl %%eax,%%eax\n\t"                       \
                "cpuid\n\t"                                  \
                "rdtsc\n\t"                                  \
                "movl %%eax,(%0)\n\t"                        \
                "movl %%edx,4(%0)\n\t"                       \
                "xorl %%eax,%%eax\n\t"                       \
                "cpuid\n\t"                                  \
                : /* nothing */                              \
		: "S"((time))				     \
                : "eax", "ebx", "ecx", "edx", "memory")


int empty_binary_operation(mpd_t r, mpd_t x, mpd_t y, mpd_rnd_t rnd) {
  return 1;
}

int empty_unary_operation(mpd_t r, mpd_t x, mpd_rnd_t rnd) {
  return 1;
}

int MPFR_empty_binary_operation(mpfr_t r, mpfr_t x, mpfr_t y, mpfr_rnd_t rnd) {
  return 1;
}

int MPFR_empty_unary_operation(mpfr_t r, mpfr_t x, mpfr_rnd_t rnd) {
  return 1;
}

void __TIME_mpd_binary_operations(int(*f_mpd_test)(mpd_ptr,mpd_srcptr,mpd_srcptr,mpd_rnd_t),__mpd_binary_operation_testvector *testvector, int nb_tests, int nb_timing_runs, timeanalytics_t *t){
  int i, j;
  double fCT, timing;
  unsigned long long int before, after;
  
  /* Run the timing nb_timing_runs times to head the cache */
  for (j=0;j<nb_timing_runs;j++) {
    for (i=0;i<nb_tests;i++) {
      READ_TIME_COUNTER(&before);
      empty_binary_operation(testvector[i].r, testvector[i].x, testvector[i].y,testvector[i].rnd);
      READ_TIME_COUNTER(&after);
      
      if (after > before) {
	timing = (double) (after - before);
      } else {
	timing = (double) 0.0;
      }
    }
  }

  fCT = 0.0;
  /* Get the timing needed to call a function */
  for (j=0;j<nb_timing_runs;j++) {
    for (i=0;i<nb_tests;i++) {
      READ_TIME_COUNTER(&before);
      empty_binary_operation(testvector[i].r, testvector[i].x, testvector[i].y,testvector[i].rnd);
      READ_TIME_COUNTER(&after);
      
      if (after > before) {
	timing = (double) (after - before);
      } else {
	timing = (double) 0.0;
      }
      
      if (timing > t->tmax_empty){
	t->tmax_empty = timing;
      }

      fCT += timing;
    }
  }

  /* Get the average function call time */
  fCT /= ((double) (nb_tests * nb_timing_runs));

  /* Run the timing nb_timing_runs times to head the cache */
  for (j=0;j<nb_timing_runs;j++) {
    for (i=0;i<nb_tests;i++) {
      READ_TIME_COUNTER(&before);
      ((*f_mpd_test)(testvector[i].r, testvector[i].x, testvector[i].y,testvector[i].rnd));
      READ_TIME_COUNTER(&after);
      
      if ((after > before) && (after - before) > fCT) {
	timing = ((double) (after - before)) - fCT;
      } else {
	timing = (double) 0.0;
      }
    }
  }
  
  /* Get the timing needed to call a function */
  for (j=0;j<nb_timing_runs;j++) {
    for (i=0;i<nb_tests;i++) {
      READ_TIME_COUNTER(&before);
      ((*f_mpd_test)(testvector[i].r, testvector[i].x, testvector[i].y,testvector[i].rnd));
      READ_TIME_COUNTER(&after);
      
      if ((after > before) && (after - before) > fCT) {
	timing = ((double) (after - before)) - fCT;
      } else {
	timing = (double) 0.0;
      }
      t->tmoyen += timing;
      
      if (timing > t->tmax){
	t->tmax = timing;
      }
    }
  }
  t->tmoyen = t->tmoyen / (nb_timing_runs*nb_tests);
}

void __TIME_mpfr_binary_operations(int(*f_mpfr_test)(mpfr_ptr,mpfr_srcptr,mpfr_srcptr,mpfr_rnd_t),__mpfr_binary_operation_testvector *testvector, int nb_tests, int nb_timing_runs, timeanalytics_t *t){
  int i, j;
  double fCT, timing;
  unsigned long long int before, after;
  
  /* Run the timing nb_timing_runs times to head the cache */
  for (j=0;j<nb_timing_runs;j++) {
    for (i=0;i<nb_tests;i++) {
      READ_TIME_COUNTER(&before);
      MPFR_empty_binary_operation(testvector[i].r, testvector[i].x, testvector[i].y,testvector[i].rnd);
      READ_TIME_COUNTER(&after);
      
      if (after > before) {
	timing = (double) (after - before);
      } else {
	timing = (double) 0.0;
      }
    }
  }

  fCT = 0.0;
  /* Get the timing needed to call a function */
  for (j=0;j<nb_timing_runs;j++) {
    for (i=0;i<nb_tests;i++) {
      READ_TIME_COUNTER(&before);
      MPFR_empty_binary_operation(testvector[i].r, testvector[i].x, testvector[i].y,testvector[i].rnd);
      READ_TIME_COUNTER(&after);
      
      if (after > before) {
	timing = (double) (after - before);
      } else {
	timing = (double) 0.0;
      }
      
      if (timing > t->tmax_empty){
	t->tmax_empty = timing;
      }

      fCT += timing;
    }
  }

  /* Get the average function call time */
  fCT /= ((double) (nb_tests * nb_timing_runs));

  /* Run the timing nb_timing_runs times to head the cache */
  for (j=0;j<nb_timing_runs;j++) {
    for (i=0;i<nb_tests;i++) {      
      READ_TIME_COUNTER(&before);
      ((*f_mpfr_test)(testvector[i].r, testvector[i].x, testvector[i].y,testvector[i].rnd));
      READ_TIME_COUNTER(&after);
      
      if ((after > before) && (after - before) > fCT) {
	timing = ((double) (after - before)) - fCT;
      } else {
	timing = (double) 0.0;
      }
    }
  }
  
  /* Get the timing needed to call a function */
  for (j=0;j<nb_timing_runs;j++) {
    for (i=0;i<nb_tests;i++) {
      READ_TIME_COUNTER(&before);
      ((*f_mpfr_test)(testvector[i].r, testvector[i].x, testvector[i].y,testvector[i].rnd));
      READ_TIME_COUNTER(&after);
      
      if ((after > before) && (after - before) > fCT) {
	timing = ((double) (after - before)) - fCT;
      } else {
	timing = (double) 0.0;
      }
      t->tmoyen += timing;
      
      if (timing > t->tmax){
	t->tmax = timing;
      }
    }
  }
  t->tmoyen = t->tmoyen / (nb_timing_runs*nb_tests);
}

void __TIME_mpd_unary_operations(int(*f_mpd_test)(mpd_ptr,mpd_srcptr,mpd_rnd_t),__mpd_unary_operation_testvector *testvector, int nb_tests, int nb_timing_runs, timeanalytics_t *t){
  int i, j;
  double fCT, timing;
  unsigned long long int before, after;
  
  /* Run the timing nb_timing_runs times to head the cache */
  for (j=0;j<nb_timing_runs;j++) {
    for (i=0;i<nb_tests;i++) {
      READ_TIME_COUNTER(&before);
      empty_unary_operation(testvector[i].r, testvector[i].x,testvector[i].rnd);
      READ_TIME_COUNTER(&after);
      
      if (after > before) {
	timing = (double) (after - before);
      } else {
	timing = (double) 0.0;
      }
    }
  }

  fCT = 0.0;
  /* Get the timing needed to call a function */
  for (j=0;j<nb_timing_runs;j++) {
    for (i=0;i<nb_tests;i++) {
      READ_TIME_COUNTER(&before);
      empty_unary_operation(testvector[i].r, testvector[i].x, testvector[i].rnd);
      READ_TIME_COUNTER(&after);
      
      if (after > before) {
	timing = (double) (after - before);
      } else {
	timing = (double) 0.0;
      }
      
      if (timing > t->tmax_empty){
	t->tmax_empty = timing;
      }

      fCT += timing;
    }
  }

  /* Get the average function call time */
  fCT /= ((double) (nb_tests * nb_timing_runs));
 
  /* Run the timing nb_timing_runs times to head the cache */
  for (j=0;j<nb_timing_runs;j++) {
    for (i=0;i<nb_tests;i++) {
      READ_TIME_COUNTER(&before);
      ((*f_mpd_test)(testvector[i].r, testvector[i].x, testvector[i].rnd));
      READ_TIME_COUNTER(&after);
      
      if ((after > before) && (after - before) > fCT) {
	timing = ((double) (after - before)) - fCT;
      } else {
	timing = (double) 0.0;
      }
    }
  }
 
  /* Get the timing needed to call a function */
  for (j=0;j<nb_timing_runs;j++) {
    for (i=0;i<nb_tests;i++) {
      READ_TIME_COUNTER(&before);
      ((*f_mpd_test)(testvector[i].r, testvector[i].x, testvector[i].rnd));
      READ_TIME_COUNTER(&after);
      
      if ((after > before) && (after - before) > fCT) {
	timing = ((double) (after - before)) - fCT;
      } else {
	timing = (double) 0.0;
      }
      t->tmoyen += timing;
      
      if (timing > t->tmax){
	t->tmax = timing;
      }
    }
  }
  t->tmoyen = t->tmoyen / (nb_timing_runs*nb_tests);
}

void __TIME_mpfr_unary_operations(int(*f_mpfr_test)(mpfr_ptr,mpfr_srcptr,mpfr_rnd_t),__mpfr_unary_operation_testvector *testvector, int nb_tests, int nb_timing_runs, timeanalytics_t *t){
  int i, j;
  double fCT, timing;
  unsigned long long int before, after;
  
  /* Run the timing nb_timing_runs times to head the cache */
  for (j=0;j<nb_timing_runs;j++) {
    for (i=0;i<nb_tests;i++) {
      READ_TIME_COUNTER(&before);
      MPFR_empty_unary_operation(testvector[i].r, testvector[i].x,testvector[i].rnd);
      READ_TIME_COUNTER(&after);
      
      if (after > before) {
	timing = (double) (after - before);
      } else {
	timing = (double) 0.0;
      }
    }
  }

  fCT = 0.0;
  /* Get the timing needed to call a function */
  for (j=0;j<nb_timing_runs;j++) {
    for (i=0;i<nb_tests;i++) {
      READ_TIME_COUNTER(&before);
      MPFR_empty_unary_operation(testvector[i].r, testvector[i].x, testvector[i].rnd);
      READ_TIME_COUNTER(&after);
      
      if (after > before) {
	timing = (double) (after - before);
      } else {
	timing = (double) 0.0;
      }
      
      if (timing > t->tmax_empty){
	t->tmax_empty = timing;
      }

      fCT += timing;
    }
  }

  /* Get the average function call time */
  fCT /= ((double) (nb_tests * nb_timing_runs));
  
  /* Run the timing nb_timing_runs times to head the cache */
  for (j=0;j<nb_timing_runs;j++) {
    for (i=0;i<nb_tests;i++) {
      READ_TIME_COUNTER(&before);
      ((*f_mpfr_test)(testvector[i].r, testvector[i].x, testvector[i].rnd));
      READ_TIME_COUNTER(&after);
      
      if ((after > before) && (after - before) > fCT) {
	timing = ((double) (after - before)) - fCT;
      } else {
	timing = (double) 0.0;
      }
    }
  }

  /* Get the timing needed to call a function */
  for (j=0;j<nb_timing_runs;j++) {
    for (i=0;i<nb_tests;i++) {
      READ_TIME_COUNTER(&before);
      ((*f_mpfr_test)(testvector[i].r, testvector[i].x, testvector[i].rnd));
      READ_TIME_COUNTER(&after);
      
      if ((after > before) && (after - before) > fCT) {
	timing = ((double) (after - before)) - fCT;
      } else {
	timing = (double) 0.0;
      }
      t->tmoyen += timing;
      
      if (timing > t->tmax){
	t->tmax = timing;
      }
    }
  }
  t->tmoyen = t->tmoyen / (nb_timing_runs*nb_tests);
}

void __GEN_testvector_unary(__mpd_unary_operation_testvector *testvector_unary, int size, mpd_prec_t prec){
  /* int i; */
  /* unsigned long n; */
  /* long int exp; */
  /* gmp_randstate_t state; */
  /* mpz_t temp; */

  /* mpz_init(temp); */
  /* gmp_randinit_mt (state); */

  /* for (i=0 ; i< size ; i++) { */
  /*   mpd_set_prec(testvector_unary[i].r,prec); */
  /*   mpd_set_prec(testvector_unary[i].x,prec); */
  
  /*   testvector_unary[i].rnd = rand() % 5; */
  /*   n = (unsigned long) (rand() % MANT_MAX); */

  /*   exp = (long int) ((rand() % (2*EXP_MAX)) - EXP_MAX); */
  /*   mpz_urandomb (temp, state, n); */
  /*   mpd_set_z(testvector_unary[i].x,temp,testvector_unary[i].rnd); */
  /*   mpd_set_exp(testvector_unary[i].x,exp); */
  /* } */

  /* mpz_clear(temp); */
  /* gmp_randclear(state); */
  int i, newround;
  int64_t n;

  for (i=0 ; i< size ; i++) { 
    newround = rand() % 5;

    mpd_set_prec(testvector_unary[i].r,prec);
    mpd_set_prec(testvector_unary[i].x,prec);
 
    testvector_unary[i].rnd=newround;
    
    n = (int64_t) ((rand() % TESTMAX) - TESTMAX/2);
    mpd_set_si(testvector_unary[i].x,n,testvector_unary[i].rnd);
  }
}

void __GEN_MPFR_testvector_unary(__mpfr_unary_operation_testvector *testvector_unary, int size, mpfr_prec_t prec){
  int i, p;
  int64_t n;

  p = mpd_precinbase2(prec);
  
  for (i=0 ; i< size ; i++) {
    mpfr_set_prec(testvector_unary[i].r,p);
    mpfr_set_prec(testvector_unary[i].x,p);

    testvector_unary[i].rnd = rand() % 5;
    
    n = (int64_t) ((rand() % TESTMAX) - TESTMAX/2);
    mpfr_set_si(testvector_unary[i].x,n,testvector_unary[i].rnd);
  }
}

void __GEN_testvector_binary(__mpd_binary_operation_testvector *testvector_binary, int size, mpd_prec_t prec){
  /* int i; */
  /* unsigned long n; */
  /* long int exp; */
  /* gmp_randstate_t state; */
  /* mpz_t temp; */

  /* mpz_init(temp); */
  /* gmp_randinit_mt (state); */
  
  /* for (i=0 ; i< size ; i++) { */
  /*   mpd_set_prec(testvector_binary[i].r,prec); */
  /*   mpd_set_prec(testvector_binary[i].x,prec); */
  /*   mpd_set_prec(testvector_binary[i].y,prec); */

  /*   testvector_binary[i].rnd = rand() % 5; */
  /*   n = (unsigned long) (rand() % MANT_MAX); */
    
  /*   exp = (long int) ((rand() % (2*EXP_MAX)) - EXP_MAX);     */
  /*   mpz_urandomb (temp, state, 64); */
  /*   mpd_set_z(testvector_binary[i].x,temp,testvector_binary[i].rnd); */
  /*   mpd_set_exp(testvector_binary[i].x,exp); */

  /*   exp = (long int) ((rand() % (2*EXP_MAX)) - EXP_MAX);     */
  /*   mpz_urandomb (temp, state, 64); */
  /*   mpd_set_z(testvector_binary[i].y,temp,testvector_binary[i].rnd); */
  /*   mpd_set_exp(testvector_binary[i].x,exp); */
  /* } */
  /* mpz_clear(temp); */
  /* gmp_randclear(state); */
  
  int i;
  int64_t n;
  
  for (i=0 ; i< size ; i++) {
    mpd_set_prec(testvector_binary[i].r,prec);
    mpd_set_prec(testvector_binary[i].x,prec);
    mpd_set_prec(testvector_binary[i].y,prec);

    testvector_binary[i].rnd = rand() % 5;
    
    n = (int64_t) ((rand() % TESTMAX) - TESTMAX/2);
    mpd_set_si(testvector_binary[i].x,n,testvector_binary[i].rnd);
    n = (int64_t) ((rand() % TESTMAX) - TESTMAX/2);
    mpd_set_si(testvector_binary[i].y,n,testvector_binary[i].rnd);
  }
}

void __GEN_MPFR_testvector_binary(__mpfr_binary_operation_testvector *testvector_binary, int size, mpfr_prec_t prec){
  int i, p;
  int64_t n;

  p = mpd_precinbase2(prec);
  
  for (i=0 ; i< size ; i++) {
    mpfr_set_prec(testvector_binary[i].r,p);
    mpfr_set_prec(testvector_binary[i].x,p);
    mpfr_set_prec(testvector_binary[i].y,p);

    testvector_binary[i].rnd = rand() % 5;
    
    n = (int64_t) ((rand() % TESTMAX) - TESTMAX/2);
    mpfr_set_si(testvector_binary[i].x,n,testvector_binary[i].rnd);
    n = (int64_t) ((rand() % TESTMAX) - TESTMAX/2);
    mpfr_set_si(testvector_binary[i].y,n,testvector_binary[i].rnd);
  }
}

void __GEN_testvector_unary_double(__mpd_unary_operation_testvector *testvector_unary, int size, mpd_prec_t prec){
  int i, newround;
  double n, f;

  for (i=0 ; i< size ; i++) { 
    newround = rand() % 5;

    mpd_set_prec(testvector_unary[i].r,prec);
    mpd_set_prec(testvector_unary[i].x,prec);
 
    testvector_unary[i].rnd=newround;

    f = (double)rand() / RAND_MAX;
    n =  TESTMIN + f * (TESTMAX - TESTMIN);

    mpd_set_d(testvector_unary[i].x,n,testvector_unary[i].rnd);
  }
}

void __GEN_MPFR_testvector_unary_double(__mpfr_unary_operation_testvector *testvector_unary, int size, mpfr_prec_t prec){
  int i, p;
  double n, f;

  p = mpd_precinbase2(prec);
  
  for (i=0 ; i< size ; i++) {
    mpfr_set_prec(testvector_unary[i].r,p);
    mpfr_set_prec(testvector_unary[i].x,p);

    testvector_unary[i].rnd = rand() % 5;

    f = (double)rand() / RAND_MAX;
    n =  TESTMIN + f * (TESTMAX - TESTMIN);

    mpfr_set_d(testvector_unary[i].x,n,testvector_unary[i].rnd);
  }
}

void __GEN_testvector_binary_double(__mpd_binary_operation_testvector *testvector_binary, int size, mpd_prec_t prec){  
  int i;
  double n, f;
  
  for (i=0 ; i< size ; i++) {
    mpd_set_prec(testvector_binary[i].r,prec);
    mpd_set_prec(testvector_binary[i].x,prec);
    mpd_set_prec(testvector_binary[i].y,prec);

    testvector_binary[i].rnd = rand() % 5;

    f = (double)rand() / RAND_MAX;
    n =  TESTMIN + f * (TESTMAX - TESTMIN);
    mpd_set_d(testvector_binary[i].x,n,testvector_binary[i].rnd);
    f = (double)rand() / RAND_MAX;
    n =  TESTMIN + f * (TESTMAX - TESTMIN);
    mpd_set_d(testvector_binary[i].y,n,testvector_binary[i].rnd);
  }
}

void __GEN_MPFR_testvector_binary_double(__mpfr_binary_operation_testvector *testvector_binary, int size, mpfr_prec_t prec){
  int i, p;
  double n, f;

  p = mpd_precinbase2(prec);
  
  for (i=0 ; i< size ; i++) {
    mpfr_set_prec(testvector_binary[i].r,p);
    mpfr_set_prec(testvector_binary[i].x,p);
    mpfr_set_prec(testvector_binary[i].y,p);

    testvector_binary[i].rnd = rand() % 5;

    f = (double)rand() / RAND_MAX;
    n =  TESTMIN + f * (TESTMAX - TESTMIN);
    mpfr_set_d(testvector_binary[i].x,n,testvector_binary[i].rnd);
    f = (double)rand() / RAND_MAX;
    n =  TESTMIN + f * (TESTMAX - TESTMIN);
    mpfr_set_d(testvector_binary[i].y,n,testvector_binary[i].rnd);
  }
}


