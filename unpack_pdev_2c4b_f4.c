#include    <datkLib.h>

/******************************************************************************/
/*  unpack_pdev_2c4b_f4                               */
/******************************************************************************/
void unpack_pdev_2c4b_f4 (unsigned char *buf, float *outbuf, int bufsize)
{
  /*
    unpacks 2-channel (1pol), 4-bit data from the pdev timedomain sampling
    input array buf is of size bufsize bytes
    output array outbuf contains 2*bufsize bytes*sizeof(float)
    output array must have been allocated for at least 2*bufsize*sizeof(float)
  */

  /* order is real, imaginary  */
  /* with wiring of pdev, this corresponds to RCP (need to check this)*/

  unsigned char value;
//  use same spacing as pfs
  char lookup[16] = {1,3,5,7,9,11,13,15,-15,-13,-11,-9,-7,-5,-3,-1};
//  char lookup[16] = {+15,+13,+11,+9,+7,+5,+3,+1,-1,-3,-5,-7,-9,-11,-13,-15};
  int i;

  for (i = 0; i < bufsize; i++)
    {
      value = buf[i];
      *outbuf++ = lookup[value >> 4];
      *outbuf++ = lookup[value & 15];
    }

  return;
}
