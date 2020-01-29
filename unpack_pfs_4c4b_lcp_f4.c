#include    <datkLib.h>
/******************************************************************************/
/*  unpack_pfs_4c4b_lcp                           */
/******************************************************************************/
void unpack_pfs_4c4b_lcp_f4 (unsigned char *buf, float *lcp, int bufsize)
{
  /*
    unpacks 4-channel, 4-bit data from the portable fast sampler
    input array buf is of size bufsize bytes
    output arrays  lcp contaings (bufsize*sizeof(float) bytes
    lcp must each have storage for at least bufsize*sizeof(char)
  */

  /* order is board 1 channel A, board 1 channel B */
  /*          board 2 channel A, board 2 channel B */
  /* with wiring of PFS, this corresponds to RCP-Q RCP-I LCP-Q LCP-I */

  unsigned char value;
  char lookup[16] = {+15,+13,+11,+9,+7,+5,+3,+1,-1,-3,-5,-7,-9,-11,-13,-15};
  int i;

  for (i = 0; i < bufsize; i += 4)
  {
      value = buf[i+1];
      *lcp++ = lookup[value & 15];
      value = value >> 4;
      *lcp++ = lookup[value & 15];

      value = buf[i+3];
      *lcp++ = lookup[value & 15];
      value = value >> 4;
      *lcp++ = lookup[value & 15];
  }

  return;
}

