#include <mpdecimal.h>
#include "mpdecimal-test.h"

#include <stdint.h>
#include <time.h>

#define NB_TESTS 360
#define NB_ELEMENTS_TESTVECTOR 60
#define NB_TIMING_RUNS 200

void t_init (timeanalytics_t *t) {
  t->tmax = 0.0;
  t->tmax_empty = 0.0;
  t->tmoyen = 0.0;
}

int main (int argc, char **argv) {
  FILE *fadd = fopen("file_add_mpdecimal.dat", "w");
  FILE *fmul = fopen("file_mul_mpdecimal.dat", "w");
  FILE *fsub = fopen("file_sub_mpdecimal.dat", "w");
  FILE *fdiv = fopen("file_div_mpdecimal.dat", "w");
  FILE *fsqrt = fopen("file_sqrt_mpdecimal.dat", "w");
  FILE *fexp = fopen("file_exp_mpdecimal.dat", "w");
  FILE *flog = fopen("file_log_mpdecimal.dat", "w");
  
  
  if (fadd == NULL) {
    printf("Error opening file!\n");
    exit(1);
  }
  if (fsub == NULL) {
    printf("Error opening file!\n");
    exit(1);
  }
  if (fmul == NULL) {
    printf("Error opening file!\n");
    exit(1);
  }
  if (fdiv == NULL) {
    printf("Error opening file!\n");
    exit(1);
  }
  if (fsqrt == NULL) {
    printf("Error opening file!\n");
    exit(1);
  }
  if (fexp == NULL) {
    printf("Error opening file!\n");
    exit(1);
  }
  if (flog == NULL) {
    printf("Error opening file!\n");
    exit(1);
  }

  printf("TEST MPDECIMAL ADD\n");
  mpdecimal_add(1);

  printf("TEST MPDECIMAL MUL\n");
  mpdecimal_mul(1);

  printf("TEST MPDECIMAL EXP\n");
  mpdecimal_exp(1);

  int nb_loops = NB_TESTS / NB_ELEMENTS_TESTVECTOR, i;
  timeanalytics_t t;
  __mpd_unary_operation_testvector testvector_unary[NB_ELEMENTS_TESTVECTOR];
  __mpd_binary_operation_testvector testvector_binary[NB_ELEMENTS_TESTVECTOR];
  unsigned int prec=16;
  mpd_context_t ctx;
   
  memset(&t, 0, sizeof(t));  
  t_init (&t);

  mpd_init(&ctx, prec);
  ctx.traps = 0;  
  
  for (i=0 ; i < NB_ELEMENTS_TESTVECTOR ; i++) {
    testvector_unary[i].x = mpd_new(&ctx);
    testvector_unary[i].r = mpd_new(&ctx);
    testvector_binary[i].x = mpd_new(&ctx);
    testvector_binary[i].y = mpd_new(&ctx);
    testvector_binary[i].r = mpd_new(&ctx);

  }
  srand (time(NULL));

  printf("\n ------------------------------>  TIMINGS  <------------------------------\n\n");

  fprintf(fadd,"PREC mpdecimal mpdecimal\n");
  fprintf(fsub,"PREC mpdecimal mpdecimal\n");
  fprintf(fmul,"PREC mpdecimal mpdecimal\n");
  fprintf(fdiv,"PREC mpdecimal mpdecimal\n");
  fprintf(fsqrt,"PREC mpdecimal mpdecimal\n");
  fprintf(fexp,"PREC mpdecimal mpdecimal\n");
  fprintf(flog,"PREC mpdecimal mpdecimal\n");

  prec = 10;
  for (i=0 ; i<nb_loops ; i++) {
   
    /* printf("TEST %d\t\tPREC%u\n",i,prec); */
    /* Run nb_loops * NB_ELEMENTS_TESTVECTOR tests (less than NB_TESTS) */
    __GEN_testvector_binary(testvector_binary, NB_ELEMENTS_TESTVECTOR, prec, &ctx);
    __TIME_mpd_binary_operations(mpd_add,testvector_binary,NB_ELEMENTS_TESTVECTOR,NB_TIMING_RUNS,&t, &ctx);
    fprintf(fadd,"%d %lf %lf \n",prec,t.tmax,t.tmoyen);
    t_init (&t);
    __TIME_mpd_binary_operations(mpd_sub,testvector_binary,NB_ELEMENTS_TESTVECTOR,NB_TIMING_RUNS,&t, &ctx);
    fprintf(fsub,"%d %lf %lf \n",prec,t.tmax,t.tmoyen);
    t_init (&t);
    __TIME_mpd_binary_operations(mpd_mul,testvector_binary,NB_ELEMENTS_TESTVECTOR,NB_TIMING_RUNS,&t, &ctx);
    fprintf(fmul,"%d %lf %lf \n",prec,t.tmax,t.tmoyen);
    t_init (&t);
    __TIME_mpd_binary_operations(mpd_div,testvector_binary,NB_ELEMENTS_TESTVECTOR,NB_TIMING_RUNS,&t, &ctx);
    fprintf(fdiv,"%d %lf %lf \n",prec,t.tmax,t.tmoyen);
    t_init (&t);
    
    __GEN_testvector_unary(testvector_unary, NB_ELEMENTS_TESTVECTOR, prec, &ctx);
    __TIME_mpd_unary_operations(mpd_sqrt,testvector_unary,NB_ELEMENTS_TESTVECTOR,NB_TIMING_RUNS,&t, &ctx);
    fprintf(fsqrt,"%d %lf %lf \n",prec,t.tmax,t.tmoyen);
    t_init (&t);
    __TIME_mpd_unary_operations(mpd_exp,testvector_unary,NB_ELEMENTS_TESTVECTOR,NB_TIMING_RUNS,&t, &ctx);
    fprintf(fexp,"%d %lf %lf \n",prec,t.tmax,t.tmoyen);
    t_init (&t);
    __TIME_mpd_unary_operations(mpd_ln,testvector_unary,NB_ELEMENTS_TESTVECTOR,NB_TIMING_RUNS,&t, &ctx);
    fprintf(flog,"%d %lf %lf \n",prec,t.tmax,t.tmoyen);
    t_init (&t);
    prec+=35;
  }
  
  for (i=0 ; i < NB_ELEMENTS_TESTVECTOR ; i++) {
    mpd_del(testvector_unary[i].x);
    mpd_del(testvector_unary[i].r);
    mpd_del(testvector_binary[i].r);
    mpd_del(testvector_binary[i].x);
    mpd_del(testvector_binary[i].y);
  }

  fclose(fadd);
  fclose(fsub);
  fclose(fmul);
  fclose(fdiv);
  fclose(fsqrt);
  fclose(fexp);
  fclose(flog);

  return 0;
}
