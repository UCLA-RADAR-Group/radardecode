#include    <datkLib.h>

/******************************************************************************/
/*  unpack_pfs_2c4b_f4                               */
/******************************************************************************/
void unpack_pfs_2c4b_f4 (unsigned char *buf, float *outbuf, int bufsize)
{
  /*
    unpacks 2-channel, 4-bit data from the portable fast sampler
    input array buf is of size bufsize bytes
    output array outbuf contains 2*bufsize bytes*sizeof(float)
    output array must have been allocated for at least 2*bufsize*sizeof(float)
  */

  /* order is board 1 channel A, board 1 channel B */
  /* with wiring of PFS, this corresponds to RCP-Q RCP-I */
  /* connect BBC sin and cos to I and Q, respectively, for positive freq */

  unsigned char value;
  char lookup[16] = {+15,+13,+11,+9,+7,+5,+3,+1,-1,-3,-5,-7,-9,-11,-13,-15};
  int i;

  for (i = 0; i < bufsize; i += 4)
    {
      value = buf[i+1];
      *outbuf++ = lookup[value & 15];
      *outbuf++ = lookup[value >> 4];

      value = buf[i+0];
      *outbuf++ = lookup[value & 15];
      *outbuf++ = lookup[value >> 4];

      value = buf[i+3];
      *outbuf++ = lookup[value & 15];
      *outbuf++ = lookup[value >> 4];

      value = buf[i+2];
      *outbuf++ = lookup[value & 15];
      *outbuf++ = lookup[value >> 4];
    }

  return;
}
