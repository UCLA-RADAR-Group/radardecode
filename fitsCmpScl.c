#include	<stdio.h>

#define MINSHORT -32768.
#define MAXSHORT  32767.
#define MININT   -2147483648.
#define MAXINT    2147483647.
#define ERROR -1
#define OK     0

int	fitsCmpScl(
		char *outdata,	/*"i","s".. int,short output data*/
		double dmaxval, /* in data set*/
		double dminval, /* in data set*/    
	        double *pbscale,/* return  bscale value*/
	        double *pbzero) /* return bzero value*/
{
/*
 *	compute bscale, bzero for fits header, scaling... 
 *
 *	return 0 success, -1 on error.
 *
 *	scaling to fits format is:
 *	
 *	ifits= (dold - bzero)/bscale;
 *	
 *	and we want to max dmax -> imax, dmin -> imin so..
 *	1. imax=(dmax-bzero)/bscale;
 *      2. imin=(dmin-bzero)/bscale;
 *      2. --> bzero=dmin - bscale*imin
 *      1.--> imax*bscale=dmax - dmin+bscale*imin
 *       ..  bscale*(imax-imin)=dmax-dmin
 *	 -> bscale= (dmax-dmin)/(imax-imin)
 *	 -> bzero = (dmin - bscale*imin);
*/

 	switch (outdata[0]) {
	  case 'i':
	  case 'I':
	     *pbscale=(dmaxval - dminval)/(MAXINT-MININT);
	     *pbzero=  dminval - MININT *  (*pbscale);
	     *pbscale= ((*pbscale) == 0.) ? 1.: (*pbscale); 
	      break;
	  case 's':
	  case 'S':
	     *pbscale=(dmaxval-dminval)/(MAXSHORT-MINSHORT);
	     *pbzero=  dminval - MINSHORT* (*pbscale);
	     *pbscale= ((*pbscale)==0.) ? 1.: (*pbscale); 
	      break;
	  default:
	      fprintf(stderr,
		"fitsCmpScl:illegal data type %c. legal values: i,s .\n",
	         outdata[0]);
	      return(ERROR);
	}
	return(OK);
}

