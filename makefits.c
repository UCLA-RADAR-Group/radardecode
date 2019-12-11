#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	"utilLib.h"
#define STDOUT 1
#define TRUE 1
#define FALSE 0
// #define ERROR -1
#define  min(a,b) ( (a) < (b) ? (a) : (b) )
#define  max(a,b) ( (a) > (b) ? (a) : (b) )

void    processargs(int argc,char **argv,int *prows,int *pcols,int *pflip);
int main(int argc,char **argv)
{
/*
 *	makefits -r rows -c cols -f <  >
 *	 
 *	make a fits file out of a real*4 array
 *	
 *	-r number of rows in input map
 *	-c number of cols in input map
 *      -f flip top to bottom 
 *history:
 *14jan93... changed to use fits subroutines
*/
	int     numRows,numCols;
	int	flip;
	float   *flipbuf;
	float	*inbuf;	
	float   *inptr,*flipptr,*bptr;
	float   maxval,minval;
	int	bytesinp,bytesinpreq,wordsinp;
	int     wordsinptot;
	int	i,j;
	float	*prow,*pcol;
	int	irow,rowsinp;
	double  bscale,bzero,dscale;
	double  dmaxval,dminval;

	flip=FALSE;
	flipbuf=NULL;
	minval=1e15;
	maxval=-minval;
        processargs(argc,argv,&numRows,&numCols,&flip);
	if ((inbuf=(float *)malloc(sizeof(float)*numRows*numCols)) ==
		(float *)NULL){
	     perror("Allocating buffer");
	     exit(-1);
	}
	if (flip) {
	   if ((flipbuf=(float *)malloc(sizeof(float)*numCols*numRows)) ==
		(float *)NULL){
	     perror("Allocating flip buffer");
	     exit(-1);
	   }
	}
	bytesinpreq=numCols*sizeof(float);
/*
 *	input the array
*/
	wordsinptot=0;
	fprintf(stderr,"STarting read.. bytesreq: %d\n",bytesinpreq);
	for (irow=0,prow=inbuf;irow<numRows;prow+=numCols,irow++){
	    bytesinp=read_pipe((char *)prow,bytesinpreq);
	    if (bytesinp < 0) {
	        perror("inputing data");
	        exit(-1);
	    }
	    if (bytesinp == 0) goto done;
/*
 *	if first row, set max,min to first value
*/
	    if (irow==0) {
	       maxval=minval=prow[0];
	    }
	    wordsinp=bytesinp/sizeof(float);
	    wordsinptot+=wordsinp;
/*
	    if ((irow %1) == 0 ) fprintf(stderr,"Reading row %d\n",irow);
*/
/*
 *	check for max min thru this row of data
*/
	    for (pcol=prow;pcol < prow + wordsinp;pcol++) {
	        maxval=max(maxval,*pcol);
	        minval=min(minval,*pcol);
	    }
	}
done:   dmaxval=maxval;
	dminval=minval;
	if (fitsCmpScl("i",dmaxval,dminval,&bscale,&bzero) == ERROR) 
	        exit(-1);
	dscale=1./bscale;		/* multiply insted of divide*/
	rowsinp=wordsinptot/numCols; /* throw out any partial last row*/
	wordsinptot=rowsinp*numCols;
	fprintf(stderr,"dscale: %e\n",dscale);
	fprintf(stderr,"wordsinp:%d max:%e min:%e bzero:%e bscale:%e\n",
		wordsinptot,dmaxval,dminval,bzero,bscale);
/*
 *	output header
*/
	if (fitsOutHdr(FALSE,(FILE *)NULL,STDOUT,"i",2,numCols,numRows,0,
	    bscale,bzero) == ERROR) exit(-1);
/*
 * 	see if we need to flip the buffer
*/
	if (flip) {
	   for (i = 0;i< numRows;i++) {
	      inptr= inbuf + i*numCols;
	      flipptr=flipbuf + (numCols*(numRows - 1 - i));
	      for (j=0;j<numCols;j++) *flipptr++ = *inptr++;
	   }
	}
	bptr=(flip) ? flipbuf:inbuf;
	 
/*
 *	now loop scaling and outputing  the data
*/
	if (fitsOutData(FALSE,(FILE *)NULL,STDOUT,"f","i",wordsinptot,
	    bscale,bzero,(char*)bptr) == ERROR)
		 exit(ERROR);
	exit(0);
}
/*****************************************************************************/
/*      processargs                                                           */
/******************************************************************************/
void    processargs(int argc,char **argv,int *rows,int *cols,int *flip)
{
/*
        function to process a programs input command line.
        This is a template that can be customized for individual programs
        To use it you should:

        - pass in the parameters that may be changed.
        - edit the case statement below to correspond to what you want.
        - stdio.h must be added for this routine to work
 
        Don't forget the ** on the arguments coming in (since you want to
        pass back data.
*/
        int getopt();                   /* c lib function returns next opt*/
        extern char *optarg;            /* if arg with option, this pts to it*/
        extern int opterr;              /* if 0, getopt won't output err mesg*/
 
        int c;                          /* Option letter returned by getopt*/
        char  *myoptions = "c:r:f";    /* options to search for. :--> needs
                                            an argument*/
        char *USAGE = "Usage: makefits  -f -r numrows -c numcols";
 
        opterr = 0;                             /* turn off there message*/
	*rows=*cols=0;
/*
        loop over all the options in list

*/
        while ((c = getopt(argc,argv,myoptions)) != -1){
          switch (c) {
          case 'c':
                   sscanf(optarg,"%d",cols);    /* rows*/
                   break;
          case 'r':
                   sscanf(optarg,"%d",rows);    /* rows*/
                   break;
          case 'f':
                   *flip=TRUE;
                   break;
          case '?':                     /*if c not in myoptions, getopt rets ?*/             goto errout;
             break;
          }
        }
        if (( *cols < 1) || ( *rows < 1)) {
            goto errout;
        }
        return;
/*
        here if illegal option or argument
*/
errout: fprintf(stderr,"%s\n",USAGE);
        exit(1);
}
