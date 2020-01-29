/* 
 *Initilize pncode struct for ao pncode
 *Syntax:
 *istat= comppncode(int codelen,int codetype,*pnpI->
 *ARGS:
 * codelen :  int  length of code to create  2^n-1 to n=1..17
 * codetype:  int  1 pnc from ao, 2 pnc for dsn 
 *RETURNS:
 * istat  :  int  returns:
 *                0 ok,
 *                -1 bad codelen
 *                -2 bad codetype code
 * pnpI-> *struct  returned with structure initialized for this codelen
 *                Note that use allocates before call.
 *
 *DESCRIPTION:
 *	Initialize pnpI->struct to compute codelen pncode
 *This is called by comppncode();
 *The user must allocate the structure before calling this routine.
 * 
*/
#include	    <stdlib.h>
#include        <math.h>
#include	    <utilLib.h>
#include		<string.h>
#include        <unistd.h>


int comppnc_init(int codelen,int codetype,PNCODE_INFO *pI)
{
        int     codenum ;               /* code to generate*/
		double   logOf2;

		logOf2  =  log(2.);
        codenum = (log((double)(codelen + 1)))/logOf2 + .5;
		memset(pI,0,sizeof(PNCODE_INFO));
//
//     pncode generated at AO
//
		if (codetype == CODETYPE_PNC_SITE_AO) {
/*
 *    initialize arrays for characteristics of each code
*/
        switch (codenum) {
        case 1:
               pI->num_reg=1;
               pI->len    =1;
               pI->num_fdback=1;
               pI->fdback[0]=1;
               break;
        case 2:
               pI->num_reg=2;
               pI->len    = pow(2.0,2.0) - 1. + .5;
               pI->num_fdback=2;
               pI->fdback[0]=1;
               pI->fdback[1]=2;
               break;
        case 3:
               pI->num_reg=3;
               pI->len    = pow(2.0,3.0) - 1. + .5;
               pI->num_fdback=2;
               pI->fdback[0]=2;
               pI->fdback[1]=3;
               break;
        case 4:
               pI->num_reg=4;
               pI->len    = pow(2.0,4.0) - 1. + .5;
               pI->num_fdback=2;
               pI->fdback[0]=3;
               pI->fdback[1]=4;
               break;
        case 5:
               pI->num_reg=5;
               pI->len    = pow(2.0,5.0) - 1. + .5;
               pI->num_fdback=2;
               pI->fdback[0]=3;
               pI->fdback[1]=5;
               break;
        case 6:
               pI->num_reg=6;
               pI->len    = pow(2.0,6.0) - 1. + .5;
               pI->num_fdback=2;
               pI->fdback[0]=5;
               pI->fdback[1]=6;
               break;
        case 7:
               pI->num_reg=7;
               pI->len    = pow(2.0,7.0) - 1. + .5;
               pI->num_fdback=2;
               pI->fdback[0]=6;
               pI->fdback[1]=7;
               break;
        case 8:
               pI->num_reg=8;
               pI->len    = pow(2.0,8.0) - 1. + .5;
               pI->num_fdback=4;
               pI->fdback[0]=4;
               pI->fdback[1]=5;
               pI->fdback[2]=6;
               pI->fdback[3]=8;
               break;
        case 9:
               pI->num_reg=9;
               pI->len    = pow(2.0,9.0) - 1. + .5;
               pI->num_fdback=2;
               pI->fdback[0]=5;
               pI->fdback[1]=9;
               break;
        case 10:
               pI->num_reg=10;
               pI->len    = pow(2.0,10.0) - 1. + .5;
               pI->num_fdback=2;
               pI->fdback[0]=7;
               pI->fdback[1]=10;
               break;
        case 11:
               pI->num_reg=11;
               pI->len    = pow(2.0,11.0) - 1. + .5;
               pI->num_fdback=2;
               pI->fdback[0]=9;
               pI->fdback[1]=11;
               break;
        case 12:
               pI->num_reg=12;
               pI->len    = pow(2.0,12.0) - 1. + .5;
               pI->num_fdback=4;
               pI->fdback[0]=6;
               pI->fdback[1]=8;
               pI->fdback[2]=11;
               pI->fdback[3]=12;
               break;
        case 13:
               pI->num_reg=13;
               pI->len    = pow(2.0,13.0) - 1. + .5;
               pI->num_fdback=4;
               pI->fdback[0]=10;
               pI->fdback[1]=9;
               pI->fdback[2]=12;
               pI->fdback[3]=13;
               break;
        case 14:
               pI->num_reg=14;
               pI->len    = pow(2.0,14.0) - 1. + .5;
               pI->num_fdback=4;
               pI->fdback[0]=2;
               pI->fdback[1]=3;
               pI->fdback[2]=13;
               pI->fdback[3]=14;
               break;
        case 15:
               pI->num_reg=15;
               pI->len    = pow(2.0,15.0) - 1. + .5;
               pI->num_fdback=2;
               pI->fdback[0]=14;
               pI->fdback[1]=15;
               break;
        case 16:
               pI->num_reg=16;
               pI->len    = pow(2.0,16.0) - 1. + .5;
               pI->num_fdback=4;
               pI->fdback[0]=11;
               pI->fdback[1]=13;
               pI->fdback[2]=14;
               pI->fdback[3]=16;
               break;
        case 17:
               pI->num_reg=17;
               pI->len    = pow(2.0,17.0) - 1. + .5;
               pI->num_fdback=2;
               pI->fdback[0]=14;
               pI->fdback[1]=17;
               break;
		default: return(-1);
			   break;
        }

//   dsn pn codes

	} else if  (codetype == CODETYPE_PNC_SITE_DSN) {
		
        switch (codenum) {
        case 1:
               pI->num_reg=1;
               pI->len    =1;
               pI->num_fdback=1;
               pI->fdback[0]=1;
               break;
        case 2:
               pI->num_reg=2;
               pI->len    = pow(2.0,2.0) - 1. + .5;
               pI->num_fdback=2;
               pI->fdback[0]=1;
               pI->fdback[1]=2;
               break;
        case 3:
               pI->num_reg=3;
               pI->len    = pow(2.0,3.0) - 1. + .5;
               pI->num_fdback=2;
               pI->fdback[0]=2;
               pI->fdback[1]=3;
               break;
        case 4:
               pI->num_reg=4;
               pI->len    = pow(2.0,4.0) - 1. + .5;
               pI->num_fdback=2;
               pI->fdback[0]=3;
               pI->fdback[1]=4;
               break;
        case 5:
               pI->num_reg=5;
               pI->len    = pow(2.0,5.0) - 1. + .5;
               pI->num_fdback=2;
               pI->fdback[0]=3;
               pI->fdback[1]=5;
               break;
        case 6:
               pI->num_reg=6;
               pI->len    = pow(2.0,6.0) - 1. + .5;
               pI->num_fdback=2;
               pI->fdback[0]=5;
               pI->fdback[1]=6;
               break;
        case 7:
               pI->num_reg=7;
               pI->len    = pow(2.0,7.0) - 1. + .5;
               pI->num_fdback=2;
               pI->fdback[0]=6;
               pI->fdback[1]=7;
               break;
        case 8:
               pI->num_reg=8;
               pI->len    = pow(2.0,8.0) - 1. + .5;
               pI->num_fdback=4;
               pI->fdback[0]=2;
               pI->fdback[1]=3;
               pI->fdback[2]=7;
               pI->fdback[3]=8;
               break;
		    case 9:
               pI->num_reg=9;
               pI->len    = pow(2.0,9.0) - 1. + .5;
               pI->num_fdback=2;
               pI->fdback[0]=5;
               pI->fdback[1]=9;
               break;
        case 10:
               pI->num_reg=10;
               pI->len    = pow(2.0,10.0) - 1. + .5;
               pI->num_fdback=2;
               pI->fdback[0]=7;
               pI->fdback[1]=10;
               break;
        case 11:
               pI->num_reg=11;
               pI->len    = pow(2.0,11.0) - 1. + .5;
               pI->num_fdback=2;
               pI->fdback[0]=9;
               pI->fdback[1]=11;
               break;
        case 12:
               pI->num_reg=12;
               pI->len    = pow(2.0,12.0) - 1. + .5;
               pI->num_fdback=4;
               pI->fdback[0]=5;
               pI->fdback[1]=8;
               pI->fdback[2]=9;
               pI->fdback[3]=12;
               break;
        case 13:
               pI->num_reg=13;
               pI->len    = pow(2.0,13.0) - 1. + .5;
               pI->num_fdback=4;
               pI->fdback[0]=8;
               pI->fdback[1]=10;
               pI->fdback[2]=12;
               pI->fdback[3]=13;
               break;
        case 14:
               pI->num_reg=14;
               pI->len    = pow(2.0,14.0) - 1. + .5;
               pI->num_fdback=4;
               pI->fdback[0]=2;
               pI->fdback[1]=3;
               pI->fdback[2]=13;
               pI->fdback[3]=14;
               break;
        case 15:
               pI->num_reg=15;
               pI->len    = pow(2.0,15.0) - 1. + .5;
               pI->num_fdback=2;
               pI->fdback[0]=14;
               pI->fdback[1]=15;
               break;
        case 16:
               pI->num_reg=16;
               pI->len    = pow(2.0,16.0) - 1. + .5;
               pI->num_fdback=4;
               pI->fdback[0]=9;
               pI->fdback[1]=13;
               pI->fdback[2]=14;
               pI->fdback[3]=16;
               break;
		default: return(-1);
	    }
	} else {
		return(-2);
	}
	return(0);
}
