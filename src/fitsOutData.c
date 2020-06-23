#include	<stdio.h>
#include	<unistd.h>
#include	<utilLib.h>
#include	<netinet/in.h>
/*
 *	output fits data 
 *	if ok, return 0
 *	if error return -1
*/
/*
 * MCN 20080103 added htonl in SCALEIT macro.
 * pjp 20080614 htonl only works for longs.. need to split SCALEIT
 *              int SCALEITi SCALITs to work for ints and shorts.. 
 */

/* 
 *	macro to scale the data
*/
#define SCALEITi(before,after) after=htonl((int)((before - bzero) * dscale))
#define SCALEITs(before,after) after=htons((short)((before - bzero) * dscale))
/*
 *	macro to output a full record
*/
#define OUTPUTIT(j)  \
              bytesout=(usefptr) ? fwrite((char *)outbuf,1,2880,fptr) \
                                   :write(fd,(char *)outbuf,2880);\
                if (bytesout != 2880) {\
                  perror("error outputing data");\
                  return(ERROR);\
                }\
		j=0
/*
 *	macro to handle last partial rec if any 
*/
#define LASTREC(j,pobuf)\
        if (j != 0) {\
            for (;j<wordsPerRec;j++)pobuf[j]=0;\
	    OUTPUTIT(j);\
        }
/*
 *	macro to due all process for 1 set of data types
*/
#define PROCESSs(pbuf,pobuf)  \
            for (j=0,i=0;i<numwords;i++){\
	       SCALEITs(pbuf[i],pobuf[j++]);\
               if ( j >= wordsPerRec) {   /* filled a rec??*/\
	          OUTPUTIT(j);\
	       }\
             }\
	     LASTREC(j,pobuf);

#define PROCESSi(pbuf,pobuf)  \
            for (j=0,i=0;i<numwords;i++){\
	       SCALEITi(pbuf[i],pobuf[j++]);\
               if ( j >= wordsPerRec) {   /* filled a rec??*/\
	          OUTPUTIT(j);\
	       }\
             }\
	     LASTREC(j,pobuf);


int	fitsOutData(
		int usefptr,	/* if true use fptr, else use fd*/
		FILE *fptr,	/* if non NULL output to file ptr*/
		int fd,		/* file descriptor*/
		char *datatype, /* "i","s","d","f", int, short, double,float*/
	 	char *outtype,  /* "i","s", integer,short*/
		int numwords,   /* of the data type*/
		double bscale,	/* to scale*/
		double bzero,
		char *buf)	/* the data*/
{
	 char     outbuf[2880]; /* + 1 for null!!*/
	 int    *poutI,*pbufI;
	 short  *poutS,*pbufS;
	 float  *pbufF;
	 double *pbufD;
	 double dscale;		/* 1./bscale*/
	
	 int 	bytesout;
	 int    wordsPerRec;
	 int	outInt;		/* output is integer*/
	 int    i,j;

	outInt= ((outtype[0]=='i') || (outtype[0]=='I'));
	wordsPerRec= (outInt)?(2880/4):(2880/2);
	
	if (bscale == 0.) {
	   fprintf(stderr,"fitsOutData:bscale == 0.\n");
	   return(ERROR);
	}
	dscale=1./bscale;
/*
 *      now decide on the type of input/output and then process
*/
	switch (datatype[0]) {
/*
 *	short input
*/
	  case 'S':
          case 's':
	    pbufS=(short *)buf;
	    if (outInt) {
	       poutI=(int *)outbuf;
               PROCESSi(pbufS,poutI);
	    }
	    else {
	       poutS=(short *)outbuf;
               PROCESSs(pbufS,poutS);
	    }
	    break;
/*
 *	int   input
*/
	  case 'I':
          case 'i':
	    pbufI=(int *)buf;
	    if (outInt) {
	       poutI=(int *)outbuf;
               PROCESSi(pbufI,poutI);
	    }
	    else {
	       poutS=(short *)outbuf;
               PROCESSs(pbufI,poutS);
	    }
	    break;
/*
 *	float input
*/
	  case 'F':
          case 'f':
	    pbufF=(float *)buf;
	    if (outInt) {
	       poutI=(int *)outbuf;
               PROCESSi(pbufF,poutI);
	    }
	    else {
	       poutS=(short *)outbuf;
               PROCESSs(pbufF,poutS);
	    }
	    break;
/*
 *	double input
*/
	  case 'D':
          case 'd':
	    pbufD=(double *)buf;
	    if (outInt) {
	       poutI=(int *)outbuf;
               PROCESSi(pbufD,poutI);
	    }
	    else {
	       poutS=(short *)outbuf;
               PROCESSs(pbufD,poutS);
	    }
	    break;
          default:
	      fprintf(stderr,"fitsOutData:Illegal data type:%s\n",datatype);
	      return(ERROR);
	}
	return(OK);
}
