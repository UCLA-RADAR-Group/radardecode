#define         MAXWORDS     1024 
#define  STDIN 0
#define  STDOUT 1

#include        <stdlib.h>
#include        <stdio.h>
#include        <string.h>
#include        <unistd.h>
#include        <datkLib.h>
#include        <philLib.h>



#define PRGNAME "unpriV"
#define IONLY  1
#define QONLY  2
#define IQ     3

#define OUTINT4   1
#define OUTINT2   2
#define OUTFLOAT  3
#define OUTDOUBLE 4


void    processargs(int argc,char **argv,int *pbits,int *poutputFormat,
                    int *pnumFifos,int *pfifoForOutput,int *poutType);

int main(int argc,char **argv)
{
/*      unpriV [
       		 -b number of bits packed to.
          	 -i  number input fifos (def 1);
             -f  fifo to output 1 or 2 (only needed in infifos == 2)    
             -d  data format 
            	 1 - output I only
            	 2 - output Q only 
            	 3 - output iq (i followed by q)
             -t type of  data: i4,i2,f4,d8. default is i4

        Filter to read ri data and unpack.Input is from stdin, output to stdout.
        default output data type is i*4 .
        default output data sequence is i,q,i,q,i,....

history:
21aug95 recompiled since unpriV_i*.c had lkup table entries changed from 
        double to int.
14may06 stole from unpriVtoi4 and added the other data types.	
        Can now replace riVunp

*/
        unsigned int  inbuf[MAXWORDS+1];                /* input buffer*/
#if FALSE
        int           outbuf[2*(MAXWORDS)*16+1];        /*i out or i/q out*/
        int           outbufT[2*(MAXWORDS)*16+1]; /*temp buf for unused fifo*/
#endif
        char          *outbuf;        	/*i out or i/q out*/
        char          *outbufT;  		/*temp buf for unused fifo*/
        int           bytesread;                        /* input this read*/
        int           wordsRead;                        /* input this read*/
        int           outbytes;                         /* to write out*/
        int           outputFormat;     /* 1 i, 2 Q, 3(def) i followed by q*/
        int           numFifosIn;       /* number fifos input*/
        int           fifoForOutput;    /* fifo for out if 2 fifos*/
        int           bits;                             /* for packing*/
        int           outfactor;                        
        char          *out1,*out2,*out3,*out4;
        int           iqSep;            /* on unpackin iqSep is true/false*/
        int           recout;
        int           bytesWritten;
		int			  outType;	
		int			  outTypeB;			/*bytes for output type 1 number*/	
        
        bits=12;                                /*default bits*/
        outputFormat=IQ;
		iqSep=FALSE;
        numFifosIn=1;
        fifoForOutput=1;
        bytesWritten=0;
		outType     = OUTINT4;
		outTypeB    = 4;
        processargs(argc,argv,&bits,&outputFormat,&numFifosIn,&fifoForOutput,
							&outType);
#if DEBUG
          fprintf(stderr,"bits:%d outFormat:%d numFifosIn:%d fifoForOut:%d\n",
                    bits,outputFormat,numFifosIn,fifoForOutput);
#endif
	    switch (outType) { 
 			case OUTINT4:   outTypeB=4;
					   break;
 			case OUTINT2:   outTypeB=2;
					   break;
 			case OUTFLOAT:  outTypeB=4;
					   break;
 			case OUTDOUBLE: outTypeB=8;
					   break;
		}
	    outbuf =malloc(2*(MAXWORDS)*outTypeB*16+1);
	    outbufT=malloc(2*(MAXWORDS)*outTypeB*16+1);
        outfactor=2*outTypeB*(16/bits); /* iq * bytes/datatype * packing */
        if (numFifosIn == 2) outfactor/=2; /* only output 1 fifo*/
        if (outputFormat != IQ) {          /* just i or q reduce by 2*/
           outfactor/=2;
        }
        out1=out2=out3=out4=outbufT;
        if ((numFifosIn == 1)|| ((numFifosIn==2)&&(fifoForOutput==1))) {
           /*
            *  use the 1st fifo whatever it is
           */
           switch (outputFormat) {
                  case IONLY:           /* i dig */
                      out1=outbuf;
                      iqSep=TRUE;
                      break;
                  case QONLY:           /* q dig */
                      out2=outbuf;
                      iqSep=TRUE;
                      break;
                  case IQ:              /* iq output */
                      out1=outbuf;
                      iqSep=FALSE;
                      break;
           }
        }
        else {
           /*
            * num fifos = 2 and they want the 2nd fifo
           */
           switch (outputFormat) {
                  case IONLY:           /* i dig */
                      out3=outbuf;
                      iqSep=TRUE;
                      break;
                  case QONLY:           /* q dig */
                      out4=outbuf;
                      iqSep=TRUE;
                      break;
                  case IQ:              /* iq output */
                      out2=outbuf;
                      iqSep=FALSE;
                      break;
           }
        }

        recout=0;
        while (( bytesread=read_pipe((char*)inbuf,MAXWORDS*4)) > 0 ) {
            recout++;
            if (numFifosIn == 1){
                if ((bytesread % 4) != 0){
                  fprintf(stderr,"%s:rec:%d bytesinp %d not divis by 4\n",
                        PRGNAME,recout,bytesread);
                  exit(-1);
                }
            }
            else {
                if ((bytesread % 8) != 0){
                  fprintf(stderr,"%s:rec:%d bytesinp %d not divis by 8\n",
                        PRGNAME,recout,bytesread);
                  exit(-1);
                }
            }
            wordsRead = (bytesread) / 4 ;/* get  words */
            outbytes= wordsRead * outfactor;
			switch (outType) {
				case OUTINT4:
            		unpriV_i4(wordsRead,numFifosIn,bits,iqSep,(char*)inbuf,
                       (int*)out1,(int*)out2,(int*)out3,(int*)out4); 
					break;
				case OUTINT2:
            		unpriV_i2(wordsRead,numFifosIn,bits,iqSep,(char*)inbuf,
                       (short*)out1,(short*)out2,(short*)out3,(short*)out4); 
					break;
				case OUTFLOAT:
            		unpriV_f4(wordsRead,numFifosIn,bits,iqSep,(char*)inbuf,
                       (float*)out1,(float*)out2,(float*)out3,(float*)out4); 
					break;
				case OUTDOUBLE:
            		unpriV_d8(wordsRead,numFifosIn,bits,iqSep,(char*)inbuf,
                    (double*)out1,(double*)out2,(double*)out3,(double*)out4); 
					break;
			}
            bytesWritten=write(STDOUT,(char *)outbuf,outbytes);/*output */
            if (bytesWritten != outbytes){
               fprintf(stderr,"%s:bytes outrequested:%d written :%d\n",
                       PRGNAME,outbytes,bytesWritten);
#ifndef VXWORKS
               if (bytesWritten < 0) perror(" ");
#endif
               exit(-1);
            }
        }
        if (bytesread < 0) {
           fprintf(stderr,"unpV_to_i4 read error status %d\n",bytesread);
           perror(" ");
           exit(-1);
        }
        
        exit(0);
        /*NOTREACHED*/
}
/*****************************************************************************
*   processargs             
*****************************************************************************/
void    processargs
        (
         int    argc,
         char   **argv,
         int    *pbits,
         int    *poutputFormat,
         int    *pnumFifos,
         int    *pfifoForOutput,
         int    *poutType)
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
        char  *myoptions = "t:b:i:f:d:";  /* options to search for. :--> needs
                                            an argument*/
        char *USAGE =
"Usage:unpriVtoi4 [-b bits -i fifosIn -f fifoOut -d OutFormat(1-I,2-Q,3-IQ) -t i4,i2,f4,f8";

        opterr = 0;                             /* turn off there message*/
/* 
        loop over all the options in list
*/
        while ((c = getopt(argc,argv,myoptions)) != -1){ 
          switch (c) {
          case 'b':
                   sscanf(optarg,"%d",pbits);
                   break;
          case 'i':
                   sscanf(optarg,"%d",pnumFifos);
                   if ((*pnumFifos != 1) && (*pnumFifos != 2)){
                     fprintf(stderr,"%s: -i numFifosInp can be 1 or 2\n",
                                PRGNAME);
                     goto errout;
                   }
                   break;
          case 'f':
                   sscanf(optarg,"%d",pfifoForOutput);
                   if ((*pfifoForOutput != 1) && (*pfifoForOutput != 2)){
                     fprintf(stderr,"%s: -f fifoForOutput can be 1 or 2\n",
                                PRGNAME);
                     goto errout;
                   }
                   break;
          case 'd':
                   sscanf(optarg,"%d",poutputFormat);
                   if ((*poutputFormat < 1) || (*poutputFormat > 3)){
                     fprintf(stderr,
                        "%s: -d dataFormat 1= i pol, 2= q pol, 3= iq \n",
                                PRGNAME);
                     goto errout;
                   }
                   break;
           case 't':
                   if (strncmp(optarg,"i4",2)==0){
				   		*poutType=OUTINT4;
				   }
			       else if (strncmp(optarg,"i2",2)==0){
				         *poutType=OUTINT2;
				   }
			       else if (strncmp(optarg,"f4",2)==0){
				         *poutType=OUTFLOAT;
				   }
	               else if (strncmp(optarg,"d8",2)==0){
	                     *poutType=OUTDOUBLE;
                   }
                   else {
                          goto errout;
                   }
				   break;
          case '?':                     /*if c not in myoptions, getopt rets ?*/
             goto errout;
             break;
          }
        }
        return;
/*
        here if illegal option or argument
*/
errout: fprintf(stderr,"%s\n",USAGE);
        exit(-1);
}
