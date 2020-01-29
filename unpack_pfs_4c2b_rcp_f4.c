#include    <datkLib.h>
/******************************************************************************/
/*unpack_pfs_4c2b_rcp      */
/******************************************************************************/
void unpack_pfs_4c2b_rcp_f4 (unsigned char *buf, float *rcp, int bufsize)
{
  /*
    unpacks 4-channel, 2-bit data from the portable fast sampler
    input array buf is of size bufsize bytes
    output arrays rcp contains 2*bufsize*sizeof(float) bytes
    rcp must each have storage for at least 2*bufsize*sizeof(float)
  */

  /* order is RCP-I, RCP-Q and LCP-I, LCP-Q */
  /* i.e. board 1 channel A, board 1 channel B */
  /* and  board 2 channel A, board 2 channel B */
  /* tested */

  unsigned char value;
  char lookup[13] = {3,1,-1,-3,1,0,0,0,-1,0,0,0,-3};
  int i;

  for (i = 0; i < bufsize; i += 4)
  {
      value = buf[i+1];
      *rcp++ = lookup[value & 3];
      *rcp++ = lookup[value & 0x0C];

      value = buf[i+0];
      *rcp++ = lookup[value & 3];
      *rcp++ = lookup[value & 0x0C];

      value = buf[i+3];
      *rcp++ = lookup[value & 3];
      *rcp++ = lookup[value & 0x0C];

      value = buf[i+2];
      *rcp++ = lookup[value & 3];
      *rcp++ = lookup[value & 0x0C];
  }

  return;
}
