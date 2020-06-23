#include    <datkLib.h>

/******************************************************************************/
/*  unpack_pfs_2c2b_f4                               */
/******************************************************************************/
void unpack_pfs_2c2b_f4 (unsigned char *buf, float *outbuf, int bufsize)
{
  /*
    unpacks 2-channel, 2-bit data from the portable fast sampler
    input array buf is of size bufsize bytes
    output array contains 4*bufsize bytes
    outbuf must have storage for at least 4*bufsize*sizeof(float)
  */

  /* order is board 1 channel A, board 1 channel B */
  /* with wiring of PFS, this corresponds to RCP-Q RCP-I */
  /* connect BBC sin and cos to I and Q, respectively, for positive freq */

  unsigned char value, val2n;
  char lookup[13] = {+3,+1,-1,-3,+1,0,0,0,-1,0,0,0,-3};
  int i;

  for (i = 0; i < bufsize; i += 4)
  {
      value = buf[i+1];
      val2n = value >> 4;
      *outbuf++ = lookup[val2n & 3];
      *outbuf++ = lookup[val2n & 0x0C];
      *outbuf++ = lookup[value & 3];
      *outbuf++ = lookup[value & 0x0C];

      value = buf[i+0];
      val2n = value >> 4;
      *outbuf++ = lookup[val2n & 3];
      *outbuf++ = lookup[val2n & 0x0C];
      *outbuf++ = lookup[value & 3];
      *outbuf++ = lookup[value & 0x0C];

      value = buf[i+3];
      val2n = value >> 4;
      *outbuf++ = lookup[val2n & 3];
      *outbuf++ = lookup[val2n & 0x0C];
      *outbuf++ = lookup[value & 3];
      *outbuf++ = lookup[value & 0x0C];

      value = buf[i+2];
      val2n = value >> 4;
      *outbuf++ = lookup[val2n & 3];
      *outbuf++ = lookup[val2n & 0x0C];
      *outbuf++ = lookup[value & 3];
      *outbuf++ = lookup[value & 0x0C];
  }

  return;
}
