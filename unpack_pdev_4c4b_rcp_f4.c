#include    <datkLib.h>

/******************************************************************************/
/*  unpack_pdev_4c4b_rcp               */
/******************************************************************************/
void unpack_pdev_4c4b_rcp_f4 (unsigned char *buf, float *rcp, int bufsize)
{
 /*
    unpacks 4-channel (2pol), 4-bit data from the pdev timedomain
    Outputs the rcp pol only
    input array buf is of size bufsize bytes
    output arrays  rcp contaings (bufsize*sizeof(float) bytes
    rcp must each have storage for at least bufsize*sizeof(char)
  */

  /* output order is: realPOlB  imgPOlB   */
  /* with wiring of pdev, this corresponds to need to check
     I'm assuming polB (2nd pol is rcp).
  */


  unsigned char value;
  char lookup[16] = {1,3,5,7,9,11,13,15,-15,-13,-11,-9,-7,-5,-3,-1};
//  char lookup[16] = {+15,+13,+11,+9,+7,+5,+3,+1,-1,-3,-5,-7,-9,-11,-13,-15};
  int i;

// assume rcp is polB and comes 2nd.. i+=2 skips polA
  for (i = 1; i < bufsize; i += 2)
  {
      value = buf[i];
      *rcp++ = lookup[value>>4];
      *rcp++ = lookup[value & 15];
  }

  return;
}

