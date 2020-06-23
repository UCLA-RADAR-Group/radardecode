/* 
 *Routine  to compute pn shift register codes:
 *Syntax:
 *istat= comppncode(int codelen,int codetype,int smallval, int largval,
 *					int *pcode)
 *ARGS:
 * codelen :  int  length of code to create  2^n-1 to n=1..17
 * codetype:  int  1 - AO pncode, 2=dsn pnccode 
 * smallval: int  value for small value. normally 0 
 * largeval: int  value for large value. normally 1
 *RETURNS:
 * istat        :int   0  ok
 *                    -1 bad codelen
 *                    -2 bad codetype
 *pcode[codelen]:int  hold the code
 *
 *DESCRIPTION: 
 *	Compute pncode. up to 2^17-1  for ao, 2^16 for dsn
 *NOTES:
 *1. the array indices are used 1 to 17. we dimension the 
 *   array to be 18 and ignore shiftreg[0] 
 *2. calls comppnc_shiftit()
 *
 *HISTORY-
 * 28oct10: was indexing pcode 1..codelen. For function
 *          go 0..codelen-1 since users pass in pcode[codelen]
 * 27oct10: stole from program comppncode()
 * fix code length 15,511 .. feed back position was wrong
*/
#include	    <stdlib.h>
#include        <math.h>
#include		<string.h>
#include        <unistd.h>
#include	    <utilLib.h>

#define         MAXCODES 17
#define         MAXLENCODE 131071

int comppncode(int codelen,int codetype,int minval,int maxval,int *pcode)
{
        int     i,istat;      
        int     shiftreg[18];   
		PNCODE_INFO code_info;

		if ((codelen < 1) || (codelen > MAXLENCODE)) return(-1);
		if (( codetype != CODETYPE_PNC_SITE_AO) && 
			( codetype != CODETYPE_PNC_SITE_DSN)) return(-2);
//      even if codelen not, 2^n-1 compute
//      the closest n for codelen
		if ((istat=comppnc_init(codelen,codetype,&code_info)) !=0){
			 return(istat);
		}
/*
        fprintf(stderr,"numreg: %d, len %d, numfdbk %d fdbak: %d %d %d %d\n",
               code_info.num_reg,code_info.len,code_info.num_fdback,
        code_info.fdback[0],code_info.fdback[1],code_info.fdback[2],
        code_info.fdback[3]);
*/
 
        for (i=1;i<=code_info.num_reg;i++){
          shiftreg[i]=0; 
        }
        for (i=0;i<  code_info.len;i++){
         	if (comppnc_shiftit(code_info.num_reg,code_info.num_fdback,
                  code_info.fdback[0],code_info.fdback[1],code_info.fdback[2],
                  code_info.fdback[3],shiftreg)){
             pcode[i]=maxval;
        }
        else {   
             pcode[i]=minval;
        }
      }
      return(0);
}
