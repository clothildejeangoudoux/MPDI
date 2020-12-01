/* mpd_sizeinbase10 -- takes a mantissa (GMP number) and returns its size in base 10 */

#include "mpd-impl.h"

size_t mpd_sizeinbase10 (mpz_srcptr x) {
  size_t size =  mpz_sizeinbase(x,10);
  char str[size];

  mpz_get_str(str,10,x);
  size=strlen(str);

  if (mpz_cmp_si(x,0) < 0) {
    size -=1;
  }
  
  return size;
}
