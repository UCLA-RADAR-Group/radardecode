#include    <datkLib.h>
/******************************************************************************/
/*  unpack_pdev_4c4b_lcp                           */
/******************************************************************************/
void unpack_pdev_4c4b_lcp_f4 (unsigned char *buf, float *lcp, int bufsize)
{
  /*
    unpacks 4-channel (2pol), 4-bit data from the portable fast sampler
    outputs the lcp pol only
    input array buf is of size bufsize bytes
    output arrays  lcp contaings (bufsize*sizeof(float) bytes
    lcp must each have storage for at least bufsize*sizeof(char)
  */

  /* output order is:
     realPOlA  imgPOlA   
  /* I'm asumming that polA (left rack) is lcp)..need to check*/

  unsigned char value;
  char lookup[16] = {1,3,5,7,9,11,13,15,-15,-13,-11,-9,-7,-5,-3,-1};
// char lookup[16] = {+15,+13,+11,+9,+7,+5,+3,+1,-1,-3,-5,-7,-9,-11,-13,-15};
  int i;

  // assume lcp is polA and comes first.. i+=2 skips polB
  for (i = 0; i < bufsize; i += 2)
  {
      value = buf[i];
      *lcp++ = lookup[value>>4];
      *lcp++ = lookup[value & 15];
  }

  return;
}

