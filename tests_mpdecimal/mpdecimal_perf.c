#include "mpdecimal-test.h"

#define EXP_MAX 400
#define MANT_MAX 500
#define TESTMAX 1000000

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


int empty_binary_operation(mpd_t *r, mpd_t *x, mpd_t *y, mpd_context_t *ctx) {
  return 1;
}

int empty_unary_operation(mpd_t *r, mpd_t *x, mpd_context_t *ctx) {
  return 1;
}

void __TIME_mpd_binary_operations(void(*f_mpd_test)(mpd_t *,const mpd_t *,const mpd_t *,mpd_context_t *),__mpd_binary_operation_testvector *testvector, int nb_tests, int nb_timing_runs, timeanalytics_t *t, mpd_context_t *ctx){
  int i, j;
  double fCT, timing;
  unsigned long long int before, after;
  
  /* Run the timing nb_timing_runs times to head the cache */
  for (j=0;j<nb_timing_runs;j++) {
    for (i=0;i<nb_tests;i++) {
      READ_TIME_COUNTER(&before);
      empty_binary_operation(testvector[i].r, testvector[i].x, testvector[i].y,ctx);
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
      empty_binary_operation(testvector[i].r, testvector[i].x, testvector[i].y,ctx);
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
      mpd_qsetprec(ctx, testvector[i].prec);
      mpd_qsetround(ctx, testvector[i].round);
      READ_TIME_COUNTER(&before);
      ((*f_mpd_test)(testvector[i].r, testvector[i].x, testvector[i].y,ctx));
      READ_TIME_COUNTER(&after);
      
      if ((after > before) && ((after - before) > fCT)) {
	timing = ((double) (after - before)) - fCT;
      } else {
	timing = (double) 0.0;
      }
    }
  }
  
  /* Get the timing needed to call a function */
  for (j=0;j<nb_timing_runs;j++) {
    for (i=0;i<nb_tests;i++) {
      mpd_qsetprec(ctx, testvector[i].prec);
      mpd_qsetround(ctx, testvector[i].round);
      READ_TIME_COUNTER(&before);
      ((*f_mpd_test)(testvector[i].r, testvector[i].x, testvector[i].y,ctx));
      READ_TIME_COUNTER(&after);
      
      if ((after > before) && ((after - before) > fCT)) {
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

void __TIME_mpd_unary_operations(void(*f_mpd_test)(mpd_t *,const mpd_t *,mpd_context_t *),__mpd_unary_operation_testvector *testvector, int nb_tests, int nb_timing_runs, timeanalytics_t *t, mpd_context_t *ctx){
  int i, j;
  double fCT, timing;
  unsigned long long int before, after;
  
  /* Run the timing nb_timing_runs times to head the cache */
  for (j=0;j<nb_timing_runs;j++) {
    for (i=0;i<nb_tests;i++) {
      READ_TIME_COUNTER(&before);
      empty_unary_operation(testvector[i].r, testvector[i].x,ctx);
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
      empty_unary_operation(testvector[i].r, testvector[i].x,ctx);
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
      mpd_qsetprec(ctx, testvector[i].prec);
      mpd_qsetround(ctx, testvector[i].round);
      READ_TIME_COUNTER(&before);
      ((*f_mpd_test)(testvector[i].r, testvector[i].x,ctx));
      READ_TIME_COUNTER(&after);
      
      if ((after > before) && ((after - before) > fCT)) {
	timing = ((double) (after - before)) - fCT;
      } else {
	timing = (double) 0.0;
      }
    }
  }

    /* char *rstring; */
    
  /* Get the timing needed to call a function */
  for (j=0;j<nb_timing_runs;j++) {
    for (i=0;i<nb_tests;i++) {
      mpd_qsetprec(ctx, testvector[i].prec);
      mpd_qsetround(ctx, testvector[i].round);
      READ_TIME_COUNTER(&before);
      /* rstring = mpd_to_sci(testvector[i].x, 1); */
      /* printf("EXP ( %s )\t = \t",rstring); */
      ((*f_mpd_test)(testvector[i].r, testvector[i].x,ctx));
      /* rstring = mpd_to_sci(testvector[i].r, 1); */
      /* printf("%s \n",rstring); */
      READ_TIME_COUNTER(&after);
      
      if ((after > before) && ((after - before) > fCT)) {
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

void __GEN_testvector_unary(__mpd_unary_operation_testvector *testvector_unary, int size, int prec, mpd_context_t *ctx){
  int i, newround;
  int64_t n;

  for (i=0 ; i< size ; i++) {
    mpd_qsetprec(ctx, prec);

    newround = rand() % 9;
    mpd_qsetround(ctx, newround);

    testvector_unary[i].prec=prec;
    testvector_unary[i].round=newround;

    n = (int64_t) ((rand() % TESTMAX) - TESTMAX/2);
    mpd_set_i64(testvector_unary[i].x,n,ctx);
  }

}

void __GEN_testvector_binary(__mpd_binary_operation_testvector *testvector_binary, int size, int prec, mpd_context_t *ctx){
  int i, newround;
  int64_t n;

  for (i=0 ; i< size ; i++) {
    mpd_qsetprec(ctx, prec);
    
    newround = rand() % 9;
    mpd_qsetround(ctx, newround);
    testvector_binary[i].prec=prec;
    testvector_binary[i].round=newround;
    
    n = (int64_t) ((rand() % TESTMAX) - TESTMAX/2);
    mpd_set_i64(testvector_binary[i].x,n,ctx);
    n = (int64_t) ((rand() % TESTMAX) - TESTMAX/2);
    mpd_set_i64(testvector_binary[i].y,n,ctx);
  }

}
