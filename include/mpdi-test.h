#ifndef __MPDI_TEST_H__
#define __MPDI_TEST_H__

#include "mpdi.h"
#include "mpdi-impl.h"
#include "mpd-test.h"

/* GMP inlusion */
#ifndef __GMP_H__
# include <gmp.h>
#endif

/* MPFR inlusion */
#ifndef __MPFR_H__
# include <mpfr.h>
#endif

/* MPFI inlusion */
#ifndef __MPFI_H__
# include <mpfi.h>
#endif

#include <stdint.h>
#include <time.h>

/* Definition of decimal class */
typedef struct {
  mpdi_t r;
  mpdi_t x;
} __mpdi_unary_operation_testvector;

typedef struct {
  mpdi_t r;
  mpdi_t x;
  mpdi_t y;
} __mpdi_binary_operation_testvector;

typedef struct {
  mpfi_t r;
  mpfi_t x;
} __mpfi_unary_operation_testvector;

typedef struct {
  mpfi_t r;
  mpfi_t x;
  mpfi_t y;
} __mpfi_binary_operation_testvector;

#ifdef __cplusplus
extern "C" {
#endif

  void t_addi();
  void t_muli();
  void t_divi();
  void t_sqrti();
  void t_expi();
  void t_logi();

  void __TIME_mpdi_binary_operations(int(*)(mpdi_ptr,mpdi_srcptr,mpdi_srcptr),__mpdi_binary_operation_testvector *, int, int, timeanalytics_t *);
  void __TIME_mpdi_unary_operations(int(*)(mpdi_ptr,mpdi_srcptr),__mpdi_unary_operation_testvector *, int, int, timeanalytics_t *);

  void __GENI_testvector_unary(__mpdi_unary_operation_testvector *, int, mpd_prec_t);
  void __GENI_testvector_binary(__mpdi_binary_operation_testvector *, int, mpd_prec_t);

  void __TIME_mpfi_binary_operations(int(*)(mpfi_ptr,mpfi_srcptr,mpfi_srcptr),__mpfi_binary_operation_testvector *, int, int, timeanalytics_t *);
  void __TIME_mpfi_unary_operations(int(*)(mpfi_ptr,mpfi_srcptr),__mpfi_unary_operation_testvector *, int, int, timeanalytics_t *);

  void __GEN_MPFI_testvector_unary(__mpfi_unary_operation_testvector *, int, mpfr_prec_t);
  void __GEN_MPFI_testvector_binary(__mpfi_binary_operation_testvector *, int, mpfr_prec_t);

  void __GENI_testvector_unary_double(__mpdi_unary_operation_testvector *, int, mpd_prec_t);
  void __GEN_MPFI_testvector_unary_double(__mpfi_unary_operation_testvector *, int, mpfr_prec_t);
  void __GENI_testvector_binary_double(__mpdi_binary_operation_testvector *, int, mpd_prec_t);
  void __GEN_MPFI_testvector_binary_double(__mpfi_binary_operation_testvector *, int, mpfr_prec_t);
  
#ifdef __cplusplus
}
#endif

  
#endif /* __MPDI_TEST_H__ */
