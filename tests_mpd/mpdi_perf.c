#include "mpdi-test.h"
#include "mpdi-impl.h"

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


int MPDI_empty_binary_operation(mpdi_t r, mpdi_t x, mpdi_t y) {
  return 1;
}

int MPDI_empty_unary_operation(mpdi_t r, mpdi_t x) {
  return 1;
}

int MPFI_empty_binary_operation(mpfi_t r, mpfi_t x, mpfi_t y) {
  return 1;
}

int MPFI_empty_unary_operation(mpfi_t r, mpfi_t x) {
  return 1;
}

void __TIME_mpdi_binary_operations(int(*f_mpdi_test)(mpdi_ptr,mpdi_srcptr,mpdi_srcptr),__mpdi_binary_operation_testvector *testvector, int nb_tests, int nb_timing_runs, timeanalytics_t *t){
  int i, j;
  double fCT, timing;
  unsigned long long int before, after;
  
  /* Run the timing nb_timing_runs times to head the cache */
  for (j=0;j<nb_timing_runs;j++) {
    for (i=0;i<nb_tests;i++) {
      READ_TIME_COUNTER(&before);
      MPDI_empty_binary_operation(testvector[i].r, testvector[i].x, testvector[i].y);
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
      MPDI_empty_binary_operation(testvector[i].r, testvector[i].x, testvector[i].y);
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
      ((*f_mpdi_test)(testvector[i].r, testvector[i].x, testvector[i].y));
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
      ((*f_mpdi_test)(testvector[i].r, testvector[i].x, testvector[i].y));
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

void __TIME_mpfi_binary_operations(int(*f_mpfi_test)(mpfi_ptr,mpfi_srcptr,mpfi_srcptr),__mpfi_binary_operation_testvector *testvector, int nb_tests, int nb_timing_runs, timeanalytics_t *t){
  int i, j;
  double fCT, timing;
  unsigned long long int before, after;
  
  /* Run the timing nb_timing_runs times to head the cache */
  for (j=0;j<nb_timing_runs;j++) {
    for (i=0;i<nb_tests;i++) {
      READ_TIME_COUNTER(&before);
      MPFI_empty_binary_operation(testvector[i].r, testvector[i].x, testvector[i].y);
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
      MPFI_empty_binary_operation(testvector[i].r, testvector[i].x, testvector[i].y);
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
      ((*f_mpfi_test)(testvector[i].r, testvector[i].x, testvector[i].y));
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
      ((*f_mpfi_test)(testvector[i].r, testvector[i].x, testvector[i].y));
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

void __TIME_mpdi_unary_operations(int(*f_mpdi_test)(mpdi_ptr,mpdi_srcptr),__mpdi_unary_operation_testvector *testvector, int nb_tests, int nb_timing_runs, timeanalytics_t *t){
  int i, j;
  double fCT, timing;
  unsigned long long int before, after;
  
  /* Run the timing nb_timing_runs times to head the cache */
  for (j=0;j<nb_timing_runs;j++) {
    for (i=0;i<nb_tests;i++) {
      READ_TIME_COUNTER(&before);
      MPDI_empty_unary_operation(testvector[i].r, testvector[i].x);
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
      MPDI_empty_unary_operation(testvector[i].r, testvector[i].x);
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
      ((*f_mpdi_test)(testvector[i].r, testvector[i].x));
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
      ((*f_mpdi_test)(testvector[i].r, testvector[i].x));
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

void __TIME_mpfi_unary_operations(int(*f_mpfi_test)(mpfi_ptr,mpfi_srcptr),__mpfi_unary_operation_testvector *testvector, int nb_tests, int nb_timing_runs, timeanalytics_t *t){
  int i, j;
  double fCT, timing;
  unsigned long long int before, after;
  
  /* Run the timing nb_timing_runs times to head the cache */
  for (j=0;j<nb_timing_runs;j++) {
    for (i=0;i<nb_tests;i++) {
      READ_TIME_COUNTER(&before);
      MPFI_empty_unary_operation(testvector[i].r, testvector[i].x);
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
      MPFI_empty_unary_operation(testvector[i].r, testvector[i].x);
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
      ((*f_mpfi_test)(testvector[i].r, testvector[i].x));
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
      ((*f_mpfi_test)(testvector[i].r, testvector[i].x));
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

void __GENI_testvector_unary(__mpdi_unary_operation_testvector *testvector_unary, int size, mpd_prec_t prec){
  int i;
  int64_t n;

  for (i=0 ; i< size ; i++) { 
    mpdi_set_prec(testvector_unary[i].r,prec);
    mpdi_set_prec(testvector_unary[i].x,prec);

    n = (int64_t) ((rand() % TESTMAX) - TESTMAX/2);
    mpdi_set_si(testvector_unary[i].x,n);
  }
}

void __GEN_MPFI_testvector_unary(__mpfi_unary_operation_testvector *testvector_unary, int size, mpfr_prec_t prec){
  int i, p;
  int64_t n;

  p = mpd_precinbase2(prec);
  
  for (i=0 ; i< size ; i++) {
    mpfi_set_prec(testvector_unary[i].r,p);
    mpfi_set_prec(testvector_unary[i].x,p);

    n = (int64_t) ((rand() % TESTMAX) - TESTMAX/2);
    mpfi_set_si(testvector_unary[i].x,n);
  }
}

void __GENI_testvector_binary(__mpdi_binary_operation_testvector *testvector_binary, int size, mpd_prec_t prec){
  int i;
  int64_t n;
  
  for (i=0 ; i< size ; i++) {
    mpdi_set_prec(testvector_binary[i].r,prec);
    mpdi_set_prec(testvector_binary[i].x,prec);
    mpdi_set_prec(testvector_binary[i].y,prec);

    n = (int64_t) ((rand() % TESTMAX) - TESTMAX/2);
    mpdi_set_si(testvector_binary[i].x,n);
    n = (int64_t) ((rand() % TESTMAX) - TESTMAX/2);
    mpdi_set_si(testvector_binary[i].y,n);
  }
}

void __GEN_MPFI_testvector_binary(__mpfi_binary_operation_testvector *testvector_binary, int size, mpfr_prec_t prec){
  int i, p;
  int64_t n;

  p = mpd_precinbase2(prec);
  
  for (i=0 ; i< size ; i++) {
    mpfi_set_prec(testvector_binary[i].r,p);
    mpfi_set_prec(testvector_binary[i].x,p);
    mpfi_set_prec(testvector_binary[i].y,p);

    n = (int64_t) ((rand() % TESTMAX) - TESTMAX/2);
    mpfi_set_si(testvector_binary[i].x,n);
    n = (int64_t) ((rand() % TESTMAX) - TESTMAX/2);
    mpfi_set_si(testvector_binary[i].y,n);
  }
}

void __GENI_testvector_unary_double(__mpdi_unary_operation_testvector *testvector_unary, int size, mpd_prec_t prec){
  int i;
  double n, f;

  for (i=0 ; i< size ; i++) { 
    mpdi_set_prec(testvector_unary[i].r,prec);
    mpdi_set_prec(testvector_unary[i].x,prec);
 
    f = (double)rand() / RAND_MAX;
    n =  TESTMIN + f * (TESTMAX - TESTMIN);

    mpdi_set_d(testvector_unary[i].x,n);
  }
}

void __GEN_MPFI_testvector_unary_double(__mpfi_unary_operation_testvector *testvector_unary, int size, mpfr_prec_t prec){
  int i, p;
  double n, f;

  p = mpd_precinbase2(prec);
  
  for (i=0 ; i< size ; i++) {
    mpfi_set_prec(testvector_unary[i].r,p);
    mpfi_set_prec(testvector_unary[i].x,p);

    f = (double)rand() / RAND_MAX;
    n =  TESTMIN + f * (TESTMAX - TESTMIN);

    mpfi_set_d(testvector_unary[i].x,n);
  }
}

void __GENI_testvector_binary_double(__mpdi_binary_operation_testvector *testvector_binary, int size, mpd_prec_t prec){  
  int i;
  double n, f;
  
  for (i=0 ; i< size ; i++) {
    mpdi_set_prec(testvector_binary[i].r,prec);
    mpdi_set_prec(testvector_binary[i].x,prec);
    mpdi_set_prec(testvector_binary[i].y,prec);

    f = (double)rand() / RAND_MAX;
    n =  TESTMIN + f * (TESTMAX - TESTMIN);
    mpdi_set_d(testvector_binary[i].x,n);
    f = (double)rand() / RAND_MAX;
    n =  TESTMIN + f * (TESTMAX - TESTMIN);
    mpdi_set_d(testvector_binary[i].y,n);
  }
}

void __GEN_MPFI_testvector_binary_double(__mpfi_binary_operation_testvector *testvector_binary, int size, mpfr_prec_t prec){
  int i, p;
  double n, f;

  p = mpd_precinbase2(prec);
  
  for (i=0 ; i< size ; i++) {
    mpfi_set_prec(testvector_binary[i].r,p);
    mpfi_set_prec(testvector_binary[i].x,p);
    mpfi_set_prec(testvector_binary[i].y,p);

    f = (double)rand() / RAND_MAX;
    n =  TESTMIN + f * (TESTMAX - TESTMIN);
    mpfi_set_d(testvector_binary[i].x,n);
    f = (double)rand() / RAND_MAX;
    n =  TESTMIN + f * (TESTMAX - TESTMIN);
    mpfi_set_d(testvector_binary[i].y,n);
  }
}
