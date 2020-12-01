
#ifndef __MPD_TEST_H__
#define __MPD_TEST_H__

#include "mpd.h"
#include "mpd-impl.h"

/* GMP inlusion */
#ifndef __GMP_H__
# include <gmp.h>
#endif

/* MPFR inlusion */
#ifndef __MPFR_H__
# include <mpfr.h>
#endif

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#include <stdint.h>
#include <time.h>

/* Definition of decimal class */
typedef struct {
  int all;
  int fail;
} mpd_cpt_t;

typedef struct {
  double tmax;
  double tmax_empty;
  double tmoyen;
} timeanalytics_t;

typedef struct {
  mpd_t r;
  mpd_t x;
  mpd_rnd_t rnd;
} __mpd_unary_operation_testvector;

typedef struct {
  mpd_t r;
  mpd_t x;
  mpd_t y;
  mpd_rnd_t rnd;
} __mpd_binary_operation_testvector;

typedef struct {
  mpfr_t r;
  mpfr_t x;
  mpfr_rnd_t rnd;
} __mpfr_unary_operation_testvector;

typedef struct {
  mpfr_t r;
  mpfr_t x;
  mpfr_t y;
  mpfr_rnd_t rnd;
} __mpfr_binary_operation_testvector;

#ifdef __cplusplus
extern "C" {
#endif

  void t_add();
  void t_mul();
  void t_div();
  void t_sqrt();
  void t_exp();
  void t_log();

  void __TIME_mpd_binary_operations(int(*)(mpd_ptr,mpd_srcptr,mpd_srcptr,mpd_rnd_t),__mpd_binary_operation_testvector *, int, int, timeanalytics_t *);
  void __TIME_mpd_unary_operations(int(*)(mpd_ptr,mpd_srcptr,mpd_rnd_t),__mpd_unary_operation_testvector *, int, int, timeanalytics_t *);

  void __GEN_testvector_unary(__mpd_unary_operation_testvector *, int, mpd_prec_t);
  void __GEN_testvector_binary(__mpd_binary_operation_testvector *, int, mpd_prec_t);

  void __TIME_mpfr_binary_operations(int(*)(mpfr_ptr,mpfr_srcptr,mpfr_srcptr,mpfr_rnd_t),__mpfr_binary_operation_testvector *, int, int, timeanalytics_t *);
  void __TIME_mpfr_unary_operations(int(*)(mpfr_ptr,mpfr_srcptr,mpfr_rnd_t),__mpfr_unary_operation_testvector *, int, int, timeanalytics_t *);

  void __GEN_MPFR_testvector_unary(__mpfr_unary_operation_testvector *, int, mpfr_prec_t);
  void __GEN_MPFR_testvector_binary(__mpfr_binary_operation_testvector *, int, mpfr_prec_t);

  void __GEN_testvector_unary_double(__mpd_unary_operation_testvector *, int, mpd_prec_t);
  void __GEN_MPFR_testvector_unary_double(__mpfr_unary_operation_testvector *, int, mpfr_prec_t);
  void __GEN_testvector_binary_double(__mpd_binary_operation_testvector *, int, mpd_prec_t);
  void __GEN_MPFR_testvector_binary_double(__mpfr_binary_operation_testvector *, int, mpfr_prec_t);
  
#ifdef __cplusplus
}
#endif

  
#endif /* __MPD_TEST_H__ */
