/* 
 *Routine  to compute barker code (len 13)
 *Syntax:
 *istat= compbarkercode(int codelen,int smallval, int largval,int *pcode)
 *ARGS:
 * codelen:  int  length of code to create. For now only 13
 * smallval: int  value for small value. normally 0 
 * largeval: int  value for large value. normally 1
 *RETURNS:
 * istat        :int   0  ok
 *                    -1 error (illegal codelen requested)
 *pcode[codelen]:int  hold the code
 *
 *DESCRIPTION:
 *	Compute barker code. 
 * For now only supports length=13
*/

int compbarkercode(int codelen,int minval,int maxval,int *pcode)
{
        int     i,j;      

		i=0;
		switch (codelen) {
			case 13: 
            /*   5. -2.  2. -1.  1. -1.  1.*/
                for (j=0;j<5;j++) pcode[i++]=maxval;
                for (j=0;j<2;j++) pcode[i++]=minval;
                for (j=0;j<2;j++) pcode[i++]=maxval;
                for (j=0;j<1;j++) pcode[i++]=minval;
                for (j=0;j<1;j++) pcode[i++]=maxval;
                for (j=0;j<1;j++) pcode[i++]=minval;
                for (j=0;j<1;j++) pcode[i++]=maxval;
				break;
			default:
				return(-1);
		}
      return(0);
}
