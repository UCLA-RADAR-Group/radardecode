#include    <datkLib.h>
/******************************************************************************/
/*  unpack_pfs_2c8b                               */
/******************************************************************************/
void unpack_pfs_2c8b_f4 (unsigned char *buf, float *outbuf, int bufsize)
{
  /*
    unpacks 2-channel, 8-bit data from the portable fast sampler
    input array buf is of size bufsize bytes
    output array outbuf contains bufsize bytes*sizeof(float)
    output array must have been allocated for at least bufsize*sizeof(float)
  */

  /* order is board 1 channel A, board 1 channel B */
  /* with wiring of PFS, this corresponds to RCP-Q RCP-I */
  /* connect BBC sin and cos to I and Q, respectively, for positive freq */

  int i;

  for (i = 0; i < bufsize; i+=4)
  {
      *outbuf++ = (unsigned char) buf[i+0] - 128;
      *outbuf++ = (unsigned char) buf[i+1] - 128;
      *outbuf++ = (unsigned char) buf[i+2] - 128;
      *outbuf++ = (unsigned char) buf[i+3] - 128;
  }

  return;
}
