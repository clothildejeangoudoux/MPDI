/* clear.c -- Free the memory space allocated for an interval. */

#include "mpdi-impl.h"

void
mpdi_clear (mpdi_ptr a)
{
  /* There is no test to check that the two endpoints are different
     and thus are not cleared twice. They should be different if only
     mpdi functions have been used...  */
  mpd_clear (&(a->right));
  mpd_clear (&(a->left));
}
