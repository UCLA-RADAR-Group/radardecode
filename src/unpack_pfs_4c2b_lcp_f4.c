#include    <datkLib.h>

/******************************************************************************/
/*unpack_pfs_4c2b_lcp      */
/******************************************************************************/
void unpack_pfs_4c2b_lcp_f4 (unsigned char *buf, float *lcp, int bufsize)
{
  /*
    unpacks 4-channel, 2-bit data from the portable fast sampler
    input array buf is of size bufsize bytes
    output array lcp each contains 2*bufsize*sizeof(float) bytes
    lcp must each have storage for at least 2*bufsize*sizeof(float)
  */

  unsigned char value;
  char lookup[13] = {3,1,-1,-3,1,0,0,0,-1,0,0,0,-3};
  int i;

  for (i = 0; i < bufsize; i += 4)
  {
      value = buf[i+1] >> 4;
      *lcp++ = lookup[value & 3];
      *lcp++ = lookup[value & 0x0C];

      value = buf[i+0] >> 4;
      *lcp++ = lookup[value & 3];
      *lcp++ = lookup[value & 0x0C];

      value = buf[i+3] >> 4;
      *lcp++ = lookup[value & 3];
      *lcp++ = lookup[value & 0x0C];

      value = buf[i+2] >> 4;
      *lcp++ = lookup[value & 3];
      *lcp++ = lookup[value & 0x0C];
  }

  return;
}
