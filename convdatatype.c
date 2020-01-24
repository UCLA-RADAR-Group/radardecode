#define STDIN 0
#define STDOUT 1
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <philLib.h>

void    processargs(int argc,char **argv,char *inpType,char *outType,int *inToOutCode,int *quiet);
// defaults to inpbuf,outbuf
#define MOVE_DATA(INPTYPE,OUTTYPE,NUM)  (\
 {INPTYPE *pin;OUTTYPE *pout;int i;\
  pin=(INPTYPE*)inBuf;pout=(OUTTYPE*)outBuf;\
  for (i=0;i<NUM;i++) pout[i]=(OUTTYPE)pin[i];\
 })
/*
 * give each type  a code number:
*/
#define vi1 1
#define vi2 2
#define vi4 3
#define vf4 4
#define vf8 5
/*
 *  code the  requested converstion  code=inpcode + outcode*10 
*/
#define i1_i2 (vi1+vi2*10)
#define i1_i4 (vi1+vi4*10)
#define i1_f4 (vi1+vf4*10)
#define i1_f8 (vi1+vf8*10)

#define i2_i4 (vi2+vi4*10)
#define i2_f4 (vi2+vf4*10)
#define i2_f8 (vi2+vf8*10)

#define i4_f4 (vi4+vf4*10)
#define i4_f8 (vi4+vf8*10)

#define f4_f8 (vf4+vf8*10)
#define f8_f4 (vf8+vf4*10)

// numbers in a block of 1 read..
#define	NUMBLK   4096
int main(int argc,char **argv)
{
/*	convdatatype -q -i inpformat -o outformat  < dataInp > dataOut
	filter to convert data formats int<->float<-> double
	-q  run quietly. if -q output msg at end: %d numbers converted 
	-i 'i1','i2','i4'
    -o 'i1','i2','i4,'f4','f8'
    
    allowable combinations:
		i1 -> i2,i4,f4,f8
        i2 -> i4,f4,f8
        i4 -> f4,f8
	    f4 -> f8
        f8 -> f4
	output sent to standard out

	-q to run quietly
*/
	char   inBuf[NUMBLK*8];
	char   outBuf[NUMBLK*8];
	int  bytesin;
	int  bytesout;
	int  wordsin; 	
	int  totalnumbers; 	
	int quiet;
	char inpType[3];
	char outType[3];
	int  dataSizeInp,dataSizeOut;		// data type size	
	int	   inToOutCode;

	strcpy(inpType,"i4");
	strcpy(outType,"f4");
	quiet=0;
    processargs(argc,argv,inpType,outType,&inToOutCode,&quiet);
	dataSizeInp=atoi(inpType+1);
	dataSizeOut=atoi(outType+1);
	totalnumbers=0;
	for (;;){
		if ((bytesin=read_pipe((char *)inBuf,NUMBLK*dataSizeInp))<=0) break; 	
                wordsin=bytesin/dataSizeInp;
		switch (inToOutCode) {
			case i1_i2:MOVE_DATA(char,short,wordsin);break;
			case i1_i4:MOVE_DATA(char,int,wordsin);break;
			case i1_f4:MOVE_DATA(char,float,wordsin);break;
			case i1_f8:MOVE_DATA(char,double,wordsin);break;
			case i2_i4:MOVE_DATA(short,int,wordsin);break;
			case i2_f4:MOVE_DATA(short,float,wordsin);break;
			case i2_f8:MOVE_DATA(short,double,wordsin);break;
			case i4_f4:MOVE_DATA(int,float,wordsin);break;
			case i4_f8:MOVE_DATA(int,double,wordsin);break;
			case f4_f8:MOVE_DATA(float,double,wordsin);break;
			case f8_f4:MOVE_DATA(double,float,wordsin);break;
		   default: fprintf(stderr,"Not allowed conversion:%s to %s\n",
				 inpType,outType);
				 exit(1);
		}
	    bytesout=write(STDOUT,(char *)outBuf,wordsin*dataSizeOut);
		totalnumbers+=wordsin;
	}
	if (!quiet) 
	fprintf(stderr,"%d numbers converted %s to %s\n",totalnumbers,inpType,outType);
	exit(0);
	/*NOTREACHED*/
}
/******************************************************************************/
/*    process args	 						      */
/******************************************************************************/
void    processargs(int argc,char **argv,char* inpType, char* outType,int *inToOutCode,int *quiet)
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
    int getopt();			/* c lib function returns next opt*/ 
	extern int opterr;      	/* if 0, getopt won't output err mesg*/
	void to_lowercase();

	int c;				/* Option letter returned by getopt*/
	int	 i1,i2;
	char  *myoptions = "qi:o:";	/* options to search for. :--> needs*/
	char  cbuf[3];

char *USAGE = "Usage: convdatatype -q -i{i1,i2,i4,f4,f8} -o{i2,i4,f4,f8}";

	opterr = 0;				/* turn off there message*/
	*quiet = 0;
/* 
	loop over all the options in list
*/
	while ((c = getopt(argc,argv,myoptions)) != -1){ 
	  switch (c) {
	  case 'q':
                   *quiet = 1; 	        /* they want it quiet*/
		   break;
	  case 'i':
			strncpy(cbuf,optarg,2);
			cbuf[3]=0;
			to_lowercase(cbuf);
			if ((!strcmp(cbuf,"i1")) || 
			 	(!strcmp(cbuf,"i2")) || 
			  	(!strcmp(cbuf,"i4")) || 
			 	(!strcmp(cbuf,"f4")) || 
			 	(!strcmp(cbuf,"f8")) ) {
				strcpy(inpType,cbuf);
			} else {
				goto errout;
			}
			break;
	  case 'o':
			strncpy(cbuf,optarg,2);
			cbuf[3]=0;
			to_lowercase(cbuf);
			if ( (!strcmp(cbuf,"i2")) || 
			  	(!strcmp(cbuf,"i4")) || 
			 	(!strcmp(cbuf,"f4")) || 
			 	(!strcmp(cbuf,"f8")) ) {
				strcpy(outType,cbuf);
			} else {
				goto errout;
			}
			break;
	  case '?':			/*if c not in myoptions, getopt rets ?*/
	     goto errout;
	     break;
	  }
	}
/*
 * now check that the combination is ok
*/
	if (
	    ( (!strcmp(inpType,"i2")) &&	// i2 disallow i1
	      ((!strcmp(outType,"i1")) ||
	       (!strcmp(outType,"i2")))
		) || 
	    ( 
		  (!strcmp(inpType,"i4"))  &&   // i4 disallow i1,i2
	      ( (!strcmp(outType,"i1")) ||
	        (!strcmp(outType,"i2")) ||
	        (!strcmp(outType,"i4"))
		  )
		) ||
	    ( 
		  (!strcmp(inpType,"f4"))  &&  // f4 only allow f8
	      ( strcmp(outType,"f8"))
		) ||
		(
	        (!strcmp(inpType,"f8")) &&// f8 only allow f4
	        ( strcmp(outType,"f4"))
		)
		) {
			fprintf(stderr,
"convdatatype: allowed conversions: i1:(i2,i4,f4,f8),i2:(i4,f4,f8),i4:(f4,f8),f4:f8,f8:f4");
			exit(1);
	}
	i1=(!strcmp(inpType,"i1")) ? vi1:
	   (!strcmp(inpType,"i2")) ? vi2:
	   (!strcmp(inpType,"i4")) ? vi4:
	   (!strcmp(inpType,"f4")) ? vf4:
	   (!strcmp(inpType,"f8")) ? vf8:-1;
	i2=(!strcmp(outType,"i1")) ? vi1:
	   (!strcmp(outType,"i2")) ? vi2:
	   (!strcmp(outType,"i4")) ? vi4:
	   (!strcmp(outType,"f4")) ? vf4:
	   (!strcmp(outType,"f8")) ? vf8:-1;
	*inToOutCode=i1 + 10*i2;
	return ;
/*
 * 	here if error occured
*/
errout: ;
        fprintf(stderr,"%s\n",USAGE);
	exit(1);
}
