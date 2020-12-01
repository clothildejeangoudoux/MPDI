#include "mpd.h"
#include "mpdi.h"
#include "mpd-test.h"
#include "mpfi.h"
#include <stdint.h>
#include <time.h>


int main (int argc, char **argv) {

  mpfr_t fr;
  mpfr_init2(fr,25);

  mpd_t d;
  mpd_init2(d,4);

  mpfr_set_str(fr,"127.999995",10,MPFR_RNDN);
  double f=mpfr_get_d(fr,MPFR_RNDN);
  
  mpfr_printf("%.6RNf\n",fr);
  mpd_set_fr(d,fr,MPD_RNDN);
  gmp_printf("%Zd 10 ^ %d \t %lf\n",MPD_MANT(d),MPD_EXP(d),f);
  
  mpfr_clear(fr);
  mpd_clear(d);
  
  
  /* printf("TEST ADD\n"); */
  /* test_add(); */
  
  /* printf("TEST MUL\n"); */
  /* test_mul(); */
  
  /* printf("TEST DIV\n"); */
  /* test_div(); */
  
  /* printf("TEST SQRT\n"); */
  /* test_sqrt(); */
  
  /* printf("TEST EXP\n"); */
  /* test_exp(); */
  
  /* printf("TEST LOG\n"); */
  /* test_log(); */
  
  return 0;
}

  /* mpd_t aD, bD; */
  /* mpfr_t aF, bF; */
  /* double a=0.5; */

  /* mpd_init2(aD, 2); */
  /* mpd_init2(bD, 2); */
  /* mpfr_init2(aF, 2); */
  /* mpfr_init2(bF, 2); */

  /* mpd_set_d(aD, a, MPD_RNDN); */
  /* mpfr_set_d(aF, a, MPFR_RNDN); */
  /* //mpfr_set_str(frstart,"0.0000000002364536723",10,MPFR_RNDN); */

  /* printf("Début test\n\n"); */
  /* printf("a = %lf \n",a); */
  /* mpfr_printf("aF = %.10RNf %.10Ra\n",aF,aF); */
  /* gmp_printf("aD = %Zd x 10 ^ %ld\n\n",MPD_MANT(aD), MPD_EXP(aD)); */

  /* mpd_exp(bD,aD,MPD_RNDN); */
  /* mpfr_exp(bF,aF,MPFR_RNDN); */

  /* mpfr_printf("bF = %.11RNf %.10Ra\n",bF,bF); */
  /* gmp_printf("bD = %Zd x 10 ^ %ld\n\n",MPD_MANT(bD), MPD_EXP(bD)); */

  
  /* mpd_clear(aD); */
  /* mpd_clear(bD); */
  /* mpfr_clear(aF); */
  /* mpfr_clear(bF); */

  
  /* FILE *f1 = fopen("mpd_exp_timing.dat", "w"); */
  /* FILE *f2 = fopen("mpdi_exp_timing.dat", "w"); */
  /* FILE *f3 = fopen("mpfr_exp_timing.dat", "w"); */
  /* FILE *f16 = fopen("mpfi_exp_timing.dat", "w"); */
  /* FILE *f4 = fopen("mpd_log_timing.dat", "w"); */
  /* FILE *f5 = fopen("mpdi_log_timing.dat", "w"); */
  /* FILE *f6 = fopen("mpfr_log_timing.dat", "w"); */
  /* FILE *f17 = fopen("mpfi_log_timing.dat", "w"); */
  /* FILE *f7 = fopen("mpd_exp_prec_timing.dat", "w"); */
  /* FILE *f8 = fopen("mpdi_exp_prec_timing.dat", "w"); */
  /* FILE *f9 = fopen("mpfr_exp_prec_timing.dat", "w"); */
  /* FILE *f18 = fopen("mpfi_exp_prec_timing.dat", "w"); */
  /* FILE *f10 = fopen("mpd_log_prec_timing1.dat", "w"); */
  /* FILE *f11 = fopen("mpdi_log_prec_timing1.dat", "w"); */
  /* FILE *f12 = fopen("mpfr_log_prec_timing1.dat", "w"); */
  /* FILE *f19 = fopen("mpfi_log_prec_timing1.dat", "w"); */
  /* FILE *f13 = fopen("mpd_log_prec_timing2.dat", "w"); */
  /* FILE *f14 = fopen("mpdi_log_prec_timing2.dat", "w"); */
  /* FILE *f15 = fopen("mpfr_log_prec_timing2.dat", "w"); */
  /* FILE *f20 = fopen("mpfi_log_prec_timing2.dat", "w"); */
  
  
  /* if (f1 == NULL) */
  /*   { */
  /*     printf("Error opening file!\n"); */
  /*     exit(1); */
  /*   } */
  /* if (f2 == NULL) */
  /*   { */
  /*     printf("Error opening file!\n"); */
  /*     exit(1); */
  /*   } */
  /* if (f3 == NULL) */
  /*   { */
  /*     printf("Error opening file!\n"); */
  /*     exit(1); */
  /*   } */

  /* if (f4 == NULL) */
  /*   { */
  /*     printf("Error opening file!\n"); */
  /*     exit(1); */
  /*   } */
  /* if (f5 == NULL) */
  /*   { */
  /*     printf("Error opening file!\n"); */
  /*     exit(1); */
  /*   } */
  /* if (f6 == NULL) */
  /*   { */
  /*     printf("Error opening file!\n"); */
  /*     exit(1); */
  /*   } */

  /* if (f7 == NULL) */
  /*   { */
  /*     printf("Error opening file!\n"); */
  /*     exit(1); */
  /*   } */
  /* if (f8 == NULL) */
  /*   { */
  /*     printf("Error opening file!\n"); */
  /*     exit(1); */
  /*   } */
  /* if (f9 == NULL) */
  /*   { */
  /*     printf("Error opening file!\n"); */
  /*     exit(1); */
  /*   } */

  /* if (f10 == NULL) */
  /*   { */
  /*     printf("Error opening file!\n"); */
  /*     exit(1); */
  /*   } */
  /* if (f11 == NULL) */
  /*   { */
  /*     printf("Error opening file!\n"); */
  /*     exit(1); */
  /*   } */
  /* if (f12 == NULL) */
  /*   { */
  /*     printf("Error opening file!\n"); */
  /*     exit(1); */
  /*   } */

  /* if (f13 == NULL) */
  /*   { */
  /*     printf("Error opening file!\n"); */
  /*     exit(1); */
  /*   } */
  /* if (f14 == NULL) */
  /*   { */
  /*     printf("Error opening file!\n"); */
  /*     exit(1); */
  /*   } */
  /* if (f15 == NULL) */
  /*   { */
  /*     printf("Error opening file!\n"); */
  /*     exit(1); */
  /*   } */
  /* if (f16 == NULL) { */
  /*   printf("Error opening file!\n"); */
  /*   exit(1); */
  /* } */
  /* if (f17 == NULL) { */
  /*   printf("Error opening file!\n"); */
  /*   exit(1); */
  /* } */
  /* if (f18 == NULL) { */
  /*   printf("Error opening file!\n"); */
  /*   exit(1); */
  /* } */
  /* if (f19 == NULL){ */
  /*   printf("Error opening file!\n"); */
  /*   exit(1); */
  /* } */
  /* if (f20 == NULL) { */
  /*   printf("Error opening file!\n"); */
  /*   exit(1); */
  /* } */
  
  
  /* /\* */
  /* printf("Check MPD_EXP\n"); */
  /* exp_check_worst_cases(); */
  
  /* printf("Check MPD_LOG\n"); */
  /* log_check_worst_cases(); *\/ */
  
  /* mpd_t start, step, point, res; */
  /* mpfr_t frstart, frend, frstep, frpoint, frres; */
  /* mpz_t zstart, zstep,zpoint; */
  /* int i = 1; */
  /* clock_t begin, end; */
  /* double time_spent; */
  /* mpdi_t distart, distep, dipoint, dires; */
  /* mpfi_t fistart, fistep, fipoint, fires; */
  
  /* printf("Timing EXP\n"); */

  /* mpd_init2(point,26); */
  /* mpfr_init2(frpoint,87); */
  /* mpdi_init2(dipoint,26); */
  /* mpd_init2(step,26); */
  /* mpfr_init2(frstep,87); */
  /* mpz_init(zstep); */
  /* mpdi_init2(distep,26); */
  /* mpfr_init2(frend,87); */
  /* mpd_init2(start,26); */
  /* mpfr_init2(frstart,87); */
  /* mpz_init(zstart); */
  /* mpdi_init2(distart,26); */
  /* mpfi_init2(fistart,87); */
  /* mpfi_init2(fipoint,87); */
  /* mpfi_init2(fistep,87); */

  /* mpfr_set_str(frend,"456.653728934",10,MPFR_RNDN); */
  
  /* mpz_set_str(zstart,"-325653728934",10); */
  /* mpd_set_z(start,zstart,MPD_RNDN); */
  /* mpd_set_exp(start,-9); */
  /* mpfr_set_str(frstart,"-325.653728934",10,MPFR_RNDN); */
  /* mpdi_set_dec(distart,start); */
  /* mpfi_set_str(fistart,"-325.653728934",10); */
  
  /* mpz_set_str(zstep,"6593847230",10); */
  /* mpd_set_z(step,zstep,MPD_RNDN); */
  /* mpd_set_exp(step,-10); */
  /* mpfr_set_str(frstep,"0.6593847230",10,MPFR_RNDN); */
  /* mpdi_set_dec(distep,step); */
  /* mpfi_set_str(fistep,"0.6593847230",10); */
  
  /* while (i) { */

  /*   mpd_init2(res,26); */
  /*   mpfr_init2(frres,87); */
  /*   mpdi_init2(dires,26); */
  /*   mpfi_init2(fires,87); */
    
  /*   mpd_set(point,start,MPD_RNDN); */
  /*   mpfr_set(frpoint,frstart,MPFR_RNDN); */
  /*   mpdi_set(dipoint,distart); */
  /*   mpfi_set(fipoint,fistart); */
    
  /*   begin = clock(); */
  /*   mpfr_exp(frres,frpoint,MPFR_RNDN); */
  /*   end = clock(); */
  /*   time_spent = (double)(end - begin) / CLOCKS_PER_SEC; */
  /*   fprintf(f3, "%lf %lf \n",mpfr_get_d(frpoint,MPFR_RNDN),time_spent); */

  /*   begin = clock(); */
  /*   mpd_exp(res,point,MPD_RNDN); */
  /*   end = clock(); */
  /*   time_spent = (double)(end - begin) / CLOCKS_PER_SEC; */
  /*   fprintf(f1, "%lf %lf \n",mpfr_get_d(frpoint,MPFR_RNDN),time_spent); */

  /*   begin = clock(); */
  /*   mpdi_exp(dires,dipoint); */
  /*   end = clock(); */
  /*   time_spent = (double)(end - begin) / CLOCKS_PER_SEC; */
  /*   fprintf(f2, "%lf %lf \n",mpfr_get_d(frpoint,MPFR_RNDN),time_spent); */

  /*   begin = clock(); */
  /*   mpfi_exp(fires,fipoint); */
  /*   end = clock(); */
  /*   time_spent = (double)(end - begin) / CLOCKS_PER_SEC; */
  /*   fprintf(f16, "%lf %lf \n",mpfr_get_d(frpoint,MPFR_RNDN),time_spent); */

  /*   mpfi_add(fistart,fipoint,fistep); */
  /*   mpd_add(start,point,step,MPD_RNDN); */
  /*   mpfr_add(frstart,frpoint,frstep,MPFR_RNDN); */
  /*   mpdi_add(distart,dipoint,distep); */
    
  /*   if (mpfr_cmp(frpoint,frend)>=0) */
  /*     i = 0; */

  /*   mpd_clear(res); */
  /*   mpfr_clear(frres); */
  /*   mpdi_clear(dires); */
  /*   mpfi_clear(fires); */
  /* } */
  
  /* mpd_clear(start); */
  /* mpd_clear(step); */
  /* mpd_clear(point); */
  /* mpfr_clear(frstart); */
  /* mpfr_clear(frend); */
  /* mpfr_clear(frstep); */
  /* mpfr_clear(frpoint); */
  /* mpz_clear(zstart); */
  /* mpz_clear(zstep); */
  /* mpdi_clear(distart); */
  /* mpdi_clear(distep); */
  /* mpdi_clear(dipoint); */
  /* mpfi_clear(fistart); */
  /* mpfi_clear(fistep); */
  /* mpfi_clear(fipoint); */
  

  /* printf("Timing EXP prec\n"); */
  /* mpd_prec_t k = 5, p; */

  /* mpd_init2(point,30); */
  /* mpfr_init2(frpoint,100); */
  /* mpdi_init2(dipoint,30); */
  /* mpz_init(zpoint); */
  /* mpfi_init2(fipoint,100); */
  
  /* mpz_set_str(zpoint,"1209734870928230983409880723",10); */
  /* mpd_set_z(point,zpoint,MPD_RNDN); */
  /* mpd_set_exp(point,-27); */
  /* mpfr_set_str(frpoint,"1.209734870928230983409880723",10,MPFR_RNDN); */
  /* mpdi_set_dec(dipoint,point); */
  /* mpfi_set_str(fipoint,"1.209734870928230983409880723",10); */
  
  /* while (k<50) { */
  /*   p=mpd_precinbase2(k); */
    
  /*   mpd_init2(res,k); */
  /*   mpfr_init2(frres,p); */
  /*   mpdi_init2(dires,k); */
  /*   mpfi_init2(fires,p); */

  /*   begin = clock(); */
  /*   mpfr_exp(frres,frpoint,MPFR_RNDN); */
  /*   end = clock(); */
  /*   time_spent = (double)(end - begin) / CLOCKS_PER_SEC; */
  /*   fprintf(f9,"%d %lf \n",k,time_spent); */

  /*   begin = clock(); */
  /*   mpd_exp(res,point,MPD_RNDN); */
  /*   end = clock(); */
  /*   time_spent = (double)(end - begin) / CLOCKS_PER_SEC; */
  /*   fprintf(f7,"%d %lf \n",k,time_spent); */

  /*   begin = clock(); */
  /*   mpdi_exp(dires,dipoint); */
  /*   end = clock(); */
  /*   time_spent = (double)(end - begin) / CLOCKS_PER_SEC; */
  /*   fprintf(f8,"%d %lf \n",k,time_spent); */

  /*   begin = clock(); */
  /*   mpfi_exp(fires,fipoint); */
  /*   end = clock(); */
  /*   time_spent = (double)(end - begin) / CLOCKS_PER_SEC; */
  /*   fprintf(f18,"%d %lf \n",k,time_spent); */
    
  /*   k++; */
  /*   mpd_clear(res); */
  /*   mpfr_clear(frres); */
  /*   mpdi_clear(dires); */
  /*   mpfi_clear(fires); */
  /* } */
  
  /* mpd_clear(point); */
  /* mpfr_clear(frpoint); */
  /* mpz_clear(zpoint); */
  /* mpdi_clear(dipoint); */
  /* mpfi_clear(fipoint); */
  
  /* printf("Timing LOG\n"); */

  /* mpd_init2(point,26); */
  /* mpfr_init2(frpoint,87); */
  /* mpdi_init2(dipoint,26); */
  /* mpd_init2(step,26); */
  /* mpfr_init2(frstep,87); */
  /* mpz_init(zstep); */
  /* mpdi_init2(distep,26); */
  /* mpfr_init2(frend,87); */
  /* mpd_init2(start,26); */
  /* mpfr_init2(frstart,87); */
  /* mpz_init(zstart); */
  /* mpdi_init2(distart,26); */
  /* mpfi_init2(fistart,87); */
  /* mpfi_init2(fipoint,87); */
  /* mpfi_init2(fistep,87); */

  /* mpfr_set_str(frend,"509.320974390",10,MPFR_RNDN); */
  
  /* mpz_set_str(zstart,"2364536723",10); */
  /* mpd_set_z(start,zstart,MPD_RNDN); */
  /* mpd_set_exp(start,-20); */
  /* mpfr_set_str(frstart,"0.0000000002364536723",10,MPFR_RNDN); */
  /* mpdi_set_dec(distart,start); */
  /* mpfi_set_str(fistart,"0.0000000002364536723",10); */
  
  /* mpz_set_str(zstep,"6593847230",10); */
  /* mpd_set_z(step,zstep,MPD_RNDN); */
  /* mpd_set_exp(step,-11); */
  /* mpfr_set_str(frstep,"0.06593847230",10,MPFR_RNDN); */
  /* mpdi_set_dec(distep,step); */
  /* mpfi_set_str(fistep,"0.06593847230",10); */
  
  /* i=1; */
  /* while (i) { */
  /*   mpd_init2(res,26); */
  /*   mpfr_init2(frres,87); */
  /*   mpdi_init2(dires,26); */
  /*   mpfi_init2(fires,87); */
    
  /*   mpd_set(point,start,MPD_RNDN); */
  /*   mpfr_set(frpoint,frstart,MPFR_RNDN); */
  /*   mpdi_set(dipoint,distart); */
  /*   mpfi_set(fipoint,fistart); */
    
  /*   begin = clock(); */
  /*   mpfr_log(frres,frpoint,MPFR_RNDN); */
  /*   end = clock(); */
  /*   time_spent = (double)(end - begin) / CLOCKS_PER_SEC; */
  /*   fprintf(f6, "%lf %lf \n",mpfr_get_d(frpoint,MPFR_RNDN),time_spent); */
   
  /*   begin = clock(); */
  /*   mpd_log(res,point,MPD_RNDN); */
  /*   end = clock(); */
  /*   time_spent = (double)(end - begin) / CLOCKS_PER_SEC; */
  /*   fprintf(f4, "%lf %lf \n",mpfr_get_d(frpoint,MPFR_RNDN),time_spent); */

  /*   begin = clock(); */
  /*   mpdi_log(dires,dipoint); */
  /*   end = clock(); */
  /*   time_spent = (double)(end - begin) / CLOCKS_PER_SEC; */
  /*   fprintf(f5, "%lf %lf \n",mpfr_get_d(frpoint,MPFR_RNDN),time_spent); */
    
  /*   begin = clock(); */
  /*   mpfi_log(fires,fipoint); */
  /*   end = clock(); */
  /*   time_spent = (double)(end - begin) / CLOCKS_PER_SEC; */
  /*   fprintf(f17, "%lf %lf \n",mpfr_get_d(frpoint,MPFR_RNDN),time_spent); */

  /*   mpfi_add(fistart,fipoint,fistep); */
  /*   mpd_add(start,point,step,MPD_RNDN); */
  /*   mpfr_add(frstart,frpoint,frstep,MPFR_RNDN); */
  /*   mpdi_add(distart,dipoint,distep); */
    
  /*   if (mpfr_cmp(frpoint,frend)>=0) */
  /*     i = 0; */

  /*   mpd_clear(res); */
  /*   mpfr_clear(frres); */
  /*   mpdi_clear(dires); */
  /*   mpfi_clear(fires); */
  /* } */

  /* mpd_clear(start); */
  /* mpd_clear(step); */
  /* mpd_clear(point); */
  /* mpfr_clear(frstart); */
  /* mpfr_clear(frend); */
  /* mpfr_clear(frstep); */
  /* mpfr_clear(frpoint); */
  /* mpz_clear(zstart); */
  /* mpz_clear(zstep); */
  /* mpdi_clear(distart); */
  /* mpdi_clear(distep); */
  /* mpdi_clear(dipoint); */
  /* mpfi_clear(fistart); */
  /* mpfi_clear(fistep); */
  /* mpfi_clear(fipoint); */
    
  /* printf("Timing LOG prec near 1\n"); */

  /* k=4; */
  
  /* mpd_init2(point,30); */
  /* mpfr_init2(frpoint,100); */
  /* mpdi_init2(dipoint,30); */
  /* mpz_init(zpoint); */
  /* mpfi_init2(fipoint,100); */
  
  /* mpz_set_str(zpoint,"86209734870928230983409880723",10); */
  /* mpd_set_z(point,zpoint,MPD_RNDN); */
  /* mpd_set_exp(point,-29); */
  /* mpfr_set_str(frpoint,"0.8209734870928230983409880723",10,MPFR_RNDN); */
  /* mpdi_set_dec(dipoint,point); */
  /* mpfi_set_str(fipoint,"0.8209734870928230983409880723",10); */
  
  /* while (k<50) { */
  /*   p=mpd_precinbase2(k); */
    
  /*   mpd_init2(res,k); */
  /*   mpfr_init2(frres,p); */
  /*   mpdi_init2(dires,k); */
  /*   mpfi_init2(fires,p); */
    
  /*   begin = clock(); */
  /*   mpfr_log(frres,frpoint,MPFR_RNDN); */
  /*   end = clock(); */
  /*   time_spent = (double)(end - begin) / CLOCKS_PER_SEC; */
  /*   fprintf(f12,"%d %lf \n",k,time_spent); */

  /*   begin = clock(); */
  /*   mpd_log(res,point,MPD_RNDN); */
  /*   end = clock(); */
  /*   time_spent = (double)(end - begin) / CLOCKS_PER_SEC; */
  /*   fprintf(f10, "%d %lf \n",k,time_spent); */

  /*   begin = clock(); */
  /*   mpdi_log(dires,dipoint); */
  /*   end = clock(); */
  /*   time_spent = (double)(end - begin) / CLOCKS_PER_SEC; */
  /*   fprintf(f11, "%d %lf \n",k,time_spent); */

  /*   begin = clock(); */
  /*   mpfi_log(fires,fipoint); */
  /*   end = clock(); */
  /*   time_spent = (double)(end - begin) / CLOCKS_PER_SEC; */
  /*   fprintf(f19, "%d %lf \n",k,time_spent); */

  /*   k++; */

  /*   mpd_clear(res); */
  /*   mpfr_clear(frres); */
  /*   mpdi_clear(dires); */
  /*   mpfi_clear(fires); */
  /* } */
  
  /* mpd_clear(point); */
  /* mpfr_clear(frpoint); */
  /* mpz_clear(zpoint); */
  /* mpdi_clear(dipoint); */
  /* mpfi_clear(fipoint); */

  /* printf("Timing LOG prec afar from 1\n"); */

  /* k=4; */
  
  /* mpd_init2(point,30); */
  /* mpfr_init2(frpoint,100); */
  /* mpdi_init2(dipoint,30); */
  /* mpz_init(zpoint); */
  /* mpfi_init2(fipoint,100); */
  
  /* mpz_set_str(zpoint,"1886209734870928230983409880723",10); */
  /* mpd_set_z(point,zpoint,MPD_RNDN); */
  /* mpd_set_exp(point,-29); */
  /* mpfr_set_str(frpoint,"18.8209734870928230983409880723",10,MPFR_RNDN); */
  /* mpdi_set_dec(dipoint,point); */
  /* mpfi_set_str(fipoint,"18.8209734870928230983409880723",10); */
  
  /* while (k<50) { */
  /*   p=mpd_precinbase2(k); */
    
  /*   mpd_init2(res,k); */
  /*   mpfr_init2(frres,p); */
  /*   mpdi_init2(dires,k); */
  /*   mpfi_init2(fires,p); */
    
  /*   begin = clock(); */
  /*   mpfr_log(frres,frpoint,MPFR_RNDN); */
  /*   end = clock(); */
  /*   time_spent = (double)(end - begin) / CLOCKS_PER_SEC; */
  /*   fprintf(f15, "%d %lf \n",k,time_spent); */

  /*   begin = clock(); */
  /*   mpd_log(res,point,MPD_RNDN); */
  /*   end = clock(); */
  /*   time_spent = (double)(end - begin) / CLOCKS_PER_SEC; */
  /*   fprintf(f13, "%d %lf \n",k,time_spent); */

  /*   begin = clock(); */
  /*   mpdi_log(dires,dipoint); */
  /*   end = clock(); */
  /*   time_spent = (double)(end - begin) / CLOCKS_PER_SEC; */
  /*   fprintf(f14,"%d %lf \n",k,time_spent); */

  /*   begin = clock(); */
  /*   mpfi_log(fires,fipoint); */
  /*   end = clock(); */
  /*   time_spent = (double)(end - begin) / CLOCKS_PER_SEC; */
  /*   fprintf(f20,"%d %lf \n",k,time_spent); */

  /*   k++; */

  /*   mpd_clear(res); */
  /*   mpfr_clear(frres); */
  /*   mpdi_clear(dires); */
  /*   mpfi_clear(fires); */
  /* } */
  
  /* mpd_clear(point); */
  /* mpfr_clear(frpoint); */
  /* mpz_clear(zpoint); */
  /* mpdi_clear(dipoint); */
  /* mpfi_clear(fipoint); */
  
  /* fclose(f1); */
  /* fclose(f2); */
  /* fclose(f3); */
  /* fclose(f4); */
  /* fclose(f5); */
  /* fclose(f6); */
  /* fclose(f7); */
  /* fclose(f8); */
  /* fclose(f9); */
  /* fclose(f10); */
  /* fclose(f11); */
  /* fclose(f12); */
  /* fclose(f13); */
  /* fclose(f14); */
  /* fclose(f15); */
  /* fclose(f16); */
  /* fclose(f17); */
  /* fclose(f18); */
  /* fclose(f19); */
  /* fclose(f20); */
  
  
  /* double time_spent, moy1, moy2,moy3; */
/*   int i; */
/*   mpz_t ztemp1, ztemp2, ztemp3; */
/*   mpd_t res_d, a_d, b_d; */
/*   mpfr_t res_fr, a_fr, b_fr; */
/*   mpdi_t res_di, a_di, b_di; */
/*   mpfi_t res_fi, a_fi, b_fi; */
/*   clock_t begin, end; */

/*   mpz_init(ztemp1); */
/*   mpz_init(ztemp2); */
/*   mpz_init(ztemp3); */
/*   mpd_init2(res_d,26); */
/*   mpd_init2(a_d,26); */
/*   mpd_init2(b_d,26); */
/*   mpfr_init2(res_fr,87); */
/*   mpfr_init2(a_fr,87); */
/*   mpfr_init2(b_fr,87); */
/*   mpdi_init2(res_di,26); */
/*   mpdi_init2(a_di,26); */
/*   mpdi_init2(b_di,26); */
/*   mpfi_init2(res_fi,87); */
/*   mpfi_init2(a_fi,87); */
/*   mpfi_init2(b_fi,87); */
  
/*   mpz_set_str(ztemp1,"236453672304957",10); */
/*   mpd_set_z(a_d,ztemp1,MPD_RNDN); */
/*   mpd_set_exp(a_d,-17); */
/*   mpfr_set_str(a_fr,"0.0236453672304957",10,MPFR_RNDN); */
/*   mpdi_set_dec(a_di,a_d); */
/*   mpfi_set_str(a_fi,"0.0236453672304957",10); */
  
/*   mpz_set_str(ztemp2,"29347392345",10); */
/*   mpd_set_z(b_d,ztemp2,MPD_RNDN); */
/*   mpd_set_exp(b_d,-12); */
/*   mpfr_set_str(b_fr,"0.29347392345",10,MPFR_RNDN); */
/*   mpdi_set_dec(b_di,b_d); */
/*   mpfi_set_str(b_fi,"0.29347392345",10); */
  
/*   begin = clock(); */
/*   mpz_mul(ztemp3,ztemp1,ztemp2); */
/*   end = clock(); */
/*   time_spent = (double)(end - begin) / CLOCKS_PER_SEC; */
/*   /\* fprintf(f18,"%d %lf \n",k,time_spent); *\/ */
/*   gmp_printf("MPZ MUL res %Zd \t timing %lf\n",ztemp3,time_spent); */
  
/*   moy1=moy2=moy3=0; */
/*   for (i=0;i<20;i++){ */
/*     begin = clock(); */
/*     mpd_mul(res_d,a_d,b_d,MPD_RNDN); */
/*     end = clock(); */
/*     time_spent = (double)(end - begin) / CLOCKS_PER_SEC; */
/*     moy1+=time_spent; */
/*     gmp_printf("MPD MUL \t %Zd x 10 ^ %ld x %Zd x 10 ^ %ld \t = %Zd x 10 ^ %ld \t\t %lf\n",MPD_MANT(a_d), MPD_EXP(a_d),MPD_MANT(a_d), MPD_EXP(b_d),MPD_MANT(res_d), MPD_EXP(res_d),time_spent); */
/*     begin = clock(); */
/*     mpd_mul_loop(res_d,a_d,b_d,MPD_RNDN); */
/*     end = clock(); */
/*     time_spent = (double)(end - begin) / CLOCKS_PER_SEC; */
/*     gmp_printf("MPD MUL LOOP \t %Zd x 10 ^ %ld x %Zd x 10 ^ %ld \t = %Zd x 10 ^ %ld \t\t %lf\n",MPD_MANT(a_d), MPD_EXP(a_d),MPD_MANT(a_d), MPD_EXP(b_d),MPD_MANT(res_d), MPD_EXP(res_d),time_spent); */
/*     moy2+=time_spent; */
/*     begin = clock(); */
/*     mpfr_mul(res_fr,a_fr,b_fr,MPFR_RNDN); */
/*     end = clock(); */
/*     time_spent = (double)(end - begin) / CLOCKS_PER_SEC; */
/*     moy3+=time_spent; */
/*     mpfr_printf("MPFR MUL \t %.17RNf x %.17RNf \t %.17RNf \t\t",a_fr,b_fr,res_fr); */
/*     gmp_printf(" timing %lf\n\n",time_spent); */
    
/*     mpd_set(a_d,b_d,MPD_RNDN); */
/*     mpfr_set(a_fr,b_fr,MPFR_RNDN); */
/*     mpd_add(b_d,res_d,a_d,MPD_RNDN); */
/*     mpfr_add(b_fr,res_fr,a_fr,MPFR_RNDN); */
/*   } */
/*   printf("\nMoyenne timing : MUL %lf, MUL LOOP %lf, MUL MPFR %lf\n",moy1/20,moy2/20,moy3/20); */
/*   //  fprintf(f18,"%lf\n",time_spent/20); */

  
/*   /\* mpz_set_str(ztemp1,"236453672304957",10); *\/ */
/*   /\* mpd_set_z(a_d,ztemp1,MPD_RNDN); *\/ */
/*   /\* mpd_set_exp(a_d,-17); *\/ */
/*   /\* mpfr_set_str(a_fr,"0.0236453672304957",10,MPFR_RNDN); *\/ */
/*   /\* mpdi_set_dec(a_di,a_d); *\/ */
/*   /\* mpfi_set_str(a_fi,"0.0236453672304957",10); *\/ */
/*   /\* moy1=moy2; *\/ */
/*   /\* for (i=0;i<6;i++){ *\/ */
/*   /\*   begin = clock(); *\/ */
/*   /\*   mpd_exp(res_d,a_d,MPD_RNDN); *\/ */
/*   /\*   end = clock(); *\/ */
/*   /\*   time_spent = (double)(end - begin) / CLOCKS_PER_SEC; *\/ */
/*   /\*   moy1+=time_spent; *\/ */
/*   /\*   gmp_printf("MPD EXP \t exp (%Zd x 10 ^ %ld) \t = %Zd x 10 ^ %ld \t\t %lf\n",MPD_MANT(a_d), MPD_EXP(a_d),MPD_MANT(res_d), MPD_EXP(res_d),time_spent); *\/ */

/*   /\*   begin = clock(); *\/ */
/*   /\*   mpfr_exp(res_fr,a_fr,MPFR_RNDN); *\/ */
/*   /\*   end = clock(); *\/ */
/*   /\*   time_spent = (double)(end - begin) / CLOCKS_PER_SEC; *\/ */
/*   /\*   moy2+=time_spent; *\/ */
/*   /\*   mpfr_printf("MPFR MUL \t exp (%.17RNf) \t %.17RNf \t\t",a_fr,b_fr,res_fr); *\/ */
/*   /\*   gmp_printf(" timing %lf\n\n",time_spent); *\/ */
    
/*   /\*   mpd_sqrt(a_d,res_d,MPD_RNDN); *\/ */
/*   /\*   mpfr_sqrt(a_fr,res_fr,MPFR_RNDN); *\/ */
/*   /\* } *\/ */
/*   /\* printf("\nMoyenne timing : EXP %lf, EXP MPFR %lf\n",moy1/20,moy2/20); *\/ */
  

/*   begin = clock(); */
/*   mpd_mul_loop(res_d,a_d,b_d,MPD_RNDN); */
/*   end = clock(); */
/*   time_spent = (double)(end - begin) / CLOCKS_PER_SEC; */
/*   /\* fprintf(f18,"%d %lf \n",k,time_spent); *\/ */
/*   gmp_printf("MPD MUL LOOP res %Zd x 10 ^ %ld \t timing %lf\n",MPD_MANT(res_d), MPD_EXP(res_d),time_spent); */
    
/*   begin = clock(); */
/*   mpfr_mul(res_fr,a_fr,b_fr,MPFR_RNDN); */
/*   end = clock(); */
/*   time_spent = (double)(end - begin) / CLOCKS_PER_SEC; */
/*   /\* fprintf(f18,"%d %lf \n",k,time_spent); *\/ */
/*   mpfr_printf("MPFR MUL res %.10RNf \t",res_fr); */
/*   gmp_printf(" timing %lf\n\n",time_spent); */

/*   begin = clock(); */
/*   mpz_add(ztemp3,ztemp1,ztemp2); */
/*   end = clock(); */
/*   time_spent = (double)(end - begin) / CLOCKS_PER_SEC; */
/*   /\* fprintf(f18,"%d %lf \n",k,time_spent); *\/ */
/*   gmp_printf("MPZ ADD res %Zd \t timing %lf\n",ztemp3,time_spent); */

/*   begin = clock(); */
/*   mpd_add(res_d,a_d,b_d,MPD_RNDN); */
/*   end = clock(); */
/*   time_spent = (double)(end - begin) / CLOCKS_PER_SEC; */
/*   /\* fprintf(f18,"%d %lf \n",k,time_spent); *\/ */
/*   gmp_printf("MPD ADD res %Zd x 10 ^ %ld \t timing %lf\n",MPD_MANT(res_d), MPD_EXP(res_d),time_spent); */

/*   begin = clock(); */
/*   mpd_add_loop(res_d,a_d,b_d,MPD_RNDN); */
/*   end = clock(); */
/*   time_spent = (double)(end - begin) / CLOCKS_PER_SEC; */
/*   /\* fprintf(f18,"%d %lf \n",k,time_spent); *\/ */
/*   gmp_printf("MPD ADD LOOP res %Zd x 10 ^ %ld \t timing %lf\n",MPD_MANT(res_d), MPD_EXP(res_d),time_spent); */
    
/*   begin = clock(); */
/*   mpfr_add(res_fr,a_fr,b_fr,MPFR_RNDN); */
/*   end = clock(); */
/*   time_spent = (double)(end - begin) / CLOCKS_PER_SEC; */
/*   /\* fprintf(f18,"%d %lf \n",k,time_spent); *\/ */
/*   mpfr_printf("MPFR ADD res %.18RNf \t",res_fr); */
/*   gmp_printf(" timing %lf\n",time_spent); */

/*   /\* printf("MPFR ADD OK\n"); *\/ */
  
/*   /\* begin = clock(); *\/ */
/*   /\* mpdi_add(res_di,a_di,b_di); *\/ */
/*   /\* end = clock(); *\/ */
/*   /\* time_spent = (double)(end - begin) / CLOCKS_PER_SEC; *\/ */
/*   /\* /\\* fprintf(f18,"%d %lf \n",k,time_spent); *\\/ *\/ */
/*   /\* //gmp_printf("MPDI ADD res [%Zd x 10 ^ %ld ; %Zd x 10 ^ %ld] \t timing %lf\n\n",MPD_MANT(res_di->left->_mpd_mant), MPD_EXP(res_di.left),MPD_MANT(res_di.right), MPD_EXP(res_di.right),time_spent); *\/ */
/*   /\* printf("MPDI ADD OK\n"); *\/ */
  
/*   /\* begin = clock(); *\/ */
/*   /\* mpfi_add(res_fi,a_fi,b_fi); *\/ */
/*   /\* end = clock(); *\/ */
/*   /\* time_spent = (double)(end - begin) / CLOCKS_PER_SEC; *\/ */
/*   /\* /\\* fprintf(f18,"%d %lf \n",k,time_spent); *\\/ *\/ */
/*   /\* mpfr_printf("MPFI ADD res [%.30RNf ; %.30RNf] \t timing %lf\n\n",res_fi->left,res_fi->right,time_spent); *\/ */
/*   /\* printf("MPFI ADD OK\n"); *\/ */

/*   float f=0.5, r; */
/*   mpfr_t fr,res; */
/*   mpd_t d, resd; */
/*   mpz_t te; */

/*   mpd_init2(d,8); */
/*   mpd_init2(resd,8); */
/*   mpz_init(te); */
/*   mpz_set_ui(te,9); */
/*   mpd_set_z(d,te,MPD_RNDN); */
/*   mpd_set_exp(d,-1); */
/*   /\* mpd_set_d(d,f,MPD_RNDN); *\/ */
/*   mpfr_init2(fr,28); */
/*   mpfr_init2(res,28); */
/*   mpfr_set_str(fr,"0.9",10,MPFR_RNDN); */

/*   mpfr_printf("\nMPFR %.10RNf, float %f\n",fr,f); */
/*   gmp_printf("MPD %Zd x 10 ^ %ld\n",MPD_MANT(d), MPD_EXP(d)); */

/*   mpfr_log(res,fr,MPFR_RNDN); */
/*   mpd_log(resd,d,MPD_RNDN); */
/*   r=mpfr_get_d(res,MPFR_RNDN);   */
/*   mpfr_printf("\nMPFR %.9RNf %.9f\n",res,r); */
/*   gmp_printf("MPD %Zd x 10 ^ %ld\n",MPD_MANT(resd), MPD_EXP(resd)); */
/*   mpfr_clear(fr); */
/*   mpfr_clear(res); */

  
/*   mpz_clear(ztemp1); */
/*   mpz_clear(ztemp2); */
/*   mpz_clear(ztemp3); */
/*   mpd_clear(res_d); */
/*   mpd_clear(a_d); */
/*   mpd_clear(b_d); */
/*   mpfr_clear(res_fr); */
/*   mpfr_clear(a_fr); */
/*   mpfr_clear(b_fr); */
/*   mpdi_clear(res_di); */
/*   mpdi_clear(a_di); */
/*   mpdi_clear(b_di); */
/*   mpfi_clear(res_fi); */
/*   mpfi_clear(a_fi); */
/*   mpfi_clear(b_fi); */

/*   fclose(f1_d); */
/*   fclose(f2_d); */
/*   fclose(f3_d); */
/*   fclose(f4_d); */
/*   fclose(f1_b); */
/*   fclose(f2_b); */
/*   fclose(f3_b); */
/*   fclose(f4_b); */
  
/*   return 0;  */
/* } */

  
  /*  double time_spent;
      clock_t begin, end;
  
  *//*
  int i;
  mpd_prec_t k=4;

  mpd_t in1,out1;
  mpdi_t in2, out2;
  mpfr_t fr1, fr2, fr3;

  double d=0.0001;
 
  
  mpfr_init_set_ui(fr2,9,MPFR_RNDN);
  mpfr_init_set_ui(fr3,10,MPFR_RNDN);
  mpfr_init2(fr1,80);
  mpfr_div(fr1,fr2,fr3,MPFR_RNDN);
  
  for (i=0;i<20;i++) {
    printf("Close 1 log - Boucle %d à la précision %d\n",i,k);
    mpd_init2(in1,k);
    mpd_init2(out1,k);
    mpdi_init2(in2,k);
    mpdi_init2(out2,k);
    mpd_set_fr(in1,fr1,MPD_RNDN);
    
    begin = clock();
    mpd_log(out1,in1,MPD_RNDN);
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    gmp_printf("k : %d, in1: %Zd, out1: %Zd\n",MPD_PREC(in1), MPD_MANT(in1),MPD_MANT(out1));
    fprintf(f1, "%lf %d \n",time_spent,k);
    
    mpdi_set_dec(in2,in1);
    begin = clock();
    mpdi_log(out2,in2);
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    fprintf(f4, "%lf %d \n",time_spent,k);
    
     mpd_clear(in1);
    mpd_clear(out1);
     mpdi_clear(in2);
    mpdi_clear(out2);
    k=k*2;
  }

  mpfr_set_prec(fr2,80);
  mpfr_pow_ui(fr2,fr3,10,MPFR_RNDN);
  k=4;
  for (i=0;i<20;i++) {
    printf("far 1 log - Boucle %d à la précision %d\n",i,k);
    mpd_init2(in1,k);
    mpd_init2(out1,k);
     mpdi_init2(in2,k);
    mpdi_init2(out2,k);

    mpd_set_fr(in1,fr2,MPD_RNDN);
    
     begin = clock();
    mpd_log(out1,in1,MPD_RNDN);
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    gmp_printf("k : %d, in1: %Zd, out1: %Zd\n",MPD_PREC(in1), MPD_MANT(in1),MPD_MANT(out1)); 
    fprintf(f2, "%lf %d \n",time_spent,k);

    mpdi_set_dec(in2,in1);
    begin = clock();
    mpdi_log(out2,in2);
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    fprintf(f5, "%lf %d \n",time_spent,k);

     mpd_clear(in1);
    mpd_clear(out1);
     mpdi_clear(in2);
    mpdi_clear(out2);
    k=k*2;
  }

  k=1000000;
  mpfr_set_prec(fr3,80); */
  /*
  for (i=0;i<30;i++) {
    printf("exp - Boucle %d à la précision %d\n",i,k);
    
    mpd_init2(in1,k);
    mpd_init2(out1,k);
    mpdi_init2(in2,k);
    mpdi_init2(out2,k);
    
    mpfr_set_prec(fr2,80);
    d=d*2;
    
    mpfr_set_d(fr2,d,MPFR_RNDN);
    mpd_set_fr(in1,fr2,MPD_RNDN);
    
    begin = clock();
    mpd_exp(out1,in1,MPD_RNDN);
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    gmp_printf("k : %d, in1: %Zd, out1: %Zd\n",MPD_PREC(in1), MPD_MANT(in1),MPD_MANT(out1)); 
    fprintf(f3, "%lf %d\n", time_spent, k);
    
    mpdi_set_dec(in2,in1);
    begin = clock();
    mpdi_exp(out2,in2);
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    fprintf(f6, "%lf %d\n",time_spent, k);
    
    mpd_clear(in1);
    mpd_clear(out1);
    mpdi_clear(in2);
    mpdi_clear(out2);
  } */
  
  /*mpd_t v, w, x,y,z,new, ff1, ff2, ff3, ff4;
  unsigned long a1, b1, c1;
  unsigned long a2, b2, c2, d2, e2;
  double f3,f2,f1,f4;
  mpd_rnd_t r=MPD_RNDN;
  mpfr_t fr1, fr2;
  int inex;
  
  mpd_init(x);
  mpd_init(y);
  mpd_init(z);
  mpd_init(v);
  mpd_init(w);
  mpd_init(new);
  mpd_init(ff1);
  mpd_init(ff2);
  mpd_init(ff3);
  mpd_init(ff4);

  a1 = 10;
  b1 = ULONG_MAX;
  c1 = 65637;
  mpd_set_ui(x,a1,r);
  gmp_printf("Number X %lu set to MPD %Zd*10^%d\n", a1, MPD_MANT(x),MPD_EXP(x));
  mpd_set_ui(y,b1,r);
  gmp_printf("Number Y %lu set to MPD %Zd*10^%d\n", b1, MPD_MANT(y),MPD_EXP(y));
  mpd_set_ui(z,c1,r);
  gmp_printf("Number Z %lu set to MPD %Zd*10^%d\n\n", c1, MPD_MANT(z),MPD_EXP(z));
  
  a2 = 20;
  b2 = LONG_MAX;
  c2 = 0;
  d2 = LONG_MIN;
  e2 = -15;
  mpd_set_si(x,a2,r);
  gmp_printf("Number X %lu set to MPD %Zd*10^%d\n", a2, MPD_MANT(x),MPD_EXP(x));
  mpd_set_si(y,b2,r);
  gmp_printf("Number Y %lu set to MPD %Zd*10^%d\n", b2, MPD_MANT(y),MPD_EXP(y));
  mpd_set_si(z,c2,r);
  gmp_printf("Number Z %lu set to MPD %Zd*10^%d\n", c2, MPD_MANT(z),MPD_EXP(z));
  mpd_set_si(v,d2,r);
  gmp_printf("Number X %ld set to MPD %Zd*10^%d\n", d2, MPD_MANT(v),MPD_EXP(v));
  mpd_set_si(w,e2,r);
  gmp_printf("Number Y %ld set to MPD %Zd*10^%d\n\n", e2, MPD_MANT(w),MPD_EXP(w));

  printf("--------------------------------- debug mpd_set_d --------------------------------\n\n");

   f1=2;
  f2= 12.125;
  f4=29380000.125;
   f3=0.3;
  mpd_set_d(new,f1,r);
  gmp_printf("Number %E set to MPD %Zd*10^%d\n", f1, MPD_MANT(new),MPD_EXP(new));
  
  mpd_set_d(y,f2,r);
  gmp_printf("Number %E set to MPD %Zd*10^%d\n", f2, MPD_MANT(y),MPD_EXP(y));
  
  mpd_set_d(z,f3,r);
  gmp_printf("Number %.56E set to MPD %Zd*10^%d\n", f3, MPD_MANT(z),MPD_EXP(z));

  mpd_set_d(v,f4,r);
  gmp_printf("Number %.25E et to MPD %Zd*10^%d\n\n", f4, MPD_MANT(v),MPD_EXP(v));
  
  printf("----------------------- mpd_set_fr ------------------------\n");
  mpd_clear(x);
  mpd_clear(y);
  mpd_init(x);
  mpd_init2(y,26);
  mpfr_init(fr1);
  mpfr_init2(fr2,(mpfr_prec_t) 86);
  
  mpfr_set_si(fr1,10,r);
   mpfr_div_ui(fr2,fr1,3,r);
    
  mpd_set_fr(x,fr1,r);
  mpfr_printf("fr1 : %.53RNf\nMPD : %Zd * 10 ^ %d, prec %d\n\n",fr1,MPD_MANT(x),MPD_EXP(x),MPD_PREC(x));
  mpd_set_fr(y,fr2,r);
  mpfr_printf("fr2 : %.30RNf\nMPD : %Zd * 10 ^ %d prec %d\n\n",fr2,MPD_MANT(y),MPD_EXP(y),MPD_PREC(y));

  printf("----------------------- mpd_get_fr ------------------------\n");
  mpfr_clear(fr1);
  mpfr_clear(fr2);
  mpfr_init(fr1);
  mpfr_init2(fr2,(mpfr_prec_t) 80);
  
  inex = mpd_get_fr(fr1,x,r);
  mpfr_printf("inex = %d ---- fr1 : %.53RNf\nMPD : %Zd * 10 ^ %d, prec %d\n\n",inex,fr1,MPD_MANT(x),MPD_EXP(x),MPD_PREC(x));
  inex = mpd_get_fr(fr2,y,r);
  mpfr_printf("inex = %d --- fr2 : %.30RNf\nMPD : %Zd * 10 ^ %d prec %d\n\n",inex,fr2,MPD_MANT(y),MPD_EXP(y),MPD_PREC(y));

  printf("----------------------- mpd_mul ------------------------\n");
  mpd_clear(x);
  mpd_clear(y);
  mpd_clear(z);
  mpd_init2(x,4);
  mpd_init2(y,4);
  mpd_init2(z,4);

  mpd_set_si(y,42,r);
  mpd_set_si(z,-345,r);
  mpd_mul(x,y,z,r);
  
  gmp_printf("%Zd * 10 ^ %d MULT %Zd * 10 ^ %d = %Zd * 10 ^ %d\n\n",MPD_MANT(y),MPD_EXP(y),MPD_MANT(z),MPD_EXP(z),MPD_MANT(x),MPD_EXP(x));

  printf("----------------------- mpd_exp ------------------------\n");
  mpd_clear(x);
  mpd_clear(y);
  mpd_clear(z);
  mpd_init(x);
  mpd_init(y);
  mpd_init(z);

  mpd_set_si(y,42,r);
  mpd_set_si(z,-345536,r);

  mpd_exp(z,y,r);
  
  gmp_printf("exp : %Zd * 10 ^ %d = %Zd * 10 ^ %d\n\n",MPD_MANT(y),MPD_EXP(y),MPD_MANT(z),MPD_EXP(z));

  printf("%d\n",test());

  mpfr_clear(fr1);
  mpfr_clear(fr2);
  
  mpd_clear(x);
  mpd_clear(y);
  mpd_clear(z);
  mpd_clear(v);
  mpd_clear(w);
  mpd_clear(new);
  mpd_clear(ff1);
  mpd_clear(ff2);
  mpd_clear(ff3);
  mpd_clear(ff4); */
