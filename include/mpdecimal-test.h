
#ifndef __MPDECIMAL_TEST_H__
#define __MPDECIMAL_TEST_H__

/* MPDECIMAL inlusion */
#ifndef __MPDECIMAL_H__
#include <mpdecimal.h>
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

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
  mpd_t *r;
  mpd_t *x;
  unsigned long int prec;
  int round;
} __mpd_unary_operation_testvector;

typedef struct {
  mpd_t *r;
  mpd_t *x;
  mpd_t *y;
  unsigned long int prec;
  int round;
} __mpd_binary_operation_testvector;

#ifdef __cplusplus
extern "C" {
#endif

  void mpdecimal_add(int);
  void mpdecimal_mul(int);
  void mpdecimal_exp(int);

  void __TIME_mpd_binary_operations(void(*)(mpd_t *,const mpd_t *,const mpd_t *,mpd_context_t *),__mpd_binary_operation_testvector *, int, int, timeanalytics_t *, mpd_context_t *);
  void __TIME_mpd_unary_operations(void(*)(mpd_t *,const mpd_t *,mpd_context_t *),__mpd_unary_operation_testvector *, int, int, timeanalytics_t *, mpd_context_t *);

  void __GEN_testvector_unary(__mpd_unary_operation_testvector *, int, int, mpd_context_t *);
  void __GEN_testvector_binary(__mpd_binary_operation_testvector *, int, int, mpd_context_t *);
  
#ifdef __cplusplus
}
#endif

  
#endif /* __MPDECIMAL_TEST_H__ */
