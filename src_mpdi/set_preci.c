/* set_prec.c -- Set the interval's precision.  */

#include "mpdi-impl.h"

/* The precision of the interval x is set to prec,  */
/* the previous value of x is lost.                 */
void mpdi_set_prec (mpdi_ptr x,mpd_prec_t prec) {
  mpd_set_prec (&(x->right),prec);
  mpd_set_prec (&(x->left),prec);
}
