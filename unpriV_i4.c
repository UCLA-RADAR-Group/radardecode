#include    <datkLib.h>
#include    <unpri.h>
#include    <byteswap.h>
/*****************************************************************************
*unpriV_i4 -  unpack vmeRi data to ints   
*
*DESCRIPTION
*Unpack vme ri data to ints.
*	
*	 numfifos = 1  
*	    iqSepReg != 0
*	        i--> outptr1
*              q--> outptr2 
*	    iqSepReg == 0
*              all data to outPtr1.
*	        order is i1,q1,i2,q2....
*	 numfifos = 2  
*	    iqSepReg != 0
*	        iF1--> outptr1
*              qF1--> outptr2 
*	        iF2--> outptr3
*              qF2--> outptr4 
*	    iqSepReg == 0
*              all fifo1 data to  outPtr1.
*              all fifo2 data to  outPtr2.
*	        order is i1f1,q1f1,i2f1,q2f1....  outptr1
*/
STATUS 	unpriV_i4(
	int     numwrds,	/* # of 32 bit input words*/
	int     numFifos,	/* 1 or 2*/
	int	bits,		/* packing*/
	int     iqSepReg,       /* false --> i,q in same reg*/
	char	*inPtr,		/* ptr to input */
	int  *outPtr1,	/* ptr to output 1 */
	int  *outPtr2,	/* ptr to output 2 */
	int  *outPtr3,	/* ptr to output 3 if 2 fifos*/
	int  *outPtr4)	/* ptr to output 4 if 2 fifos*/
{
/*   	- inptr holds 16 bit data from the vme ri
	- unpack the data into doubles  words
        - output order is determined by iqInterleave and numfifos outpus is:
 *	        order is i1f2,q1f2,i2f2,q2f2....  outptr1
history:
	25apr93. add iq interleave option and outbufs 1,2,3,4.
	21aug95. changed constants to int in lkup table
	10jun04. added linux compile option
	15may06 linux 2 fifos was not swapping the bytes (the swap
            command was there but the unpack macro used the unswapped ptr.
            eg: swi1=bswap_16(*inPtrI1);
            unpri_1(*inPtrI1,outPtrI1,outStep); instead of :
            unpri_1(swi1,outPtrI1,outStep);
            So all 2fifo ri data was wrong except for 
            8bit where you had two samples per baud since the output  was
            i2,i1,i4,i3,  and if i(n) eq i (n+1) then it was ok
*/
#if FALSE
static  int   lkup_1[2]={1.,-1.};
static  int   lkup_2[4] = {0.,1.,-2.,-1.};
static  int   lkup_4[16] = {0.,1.,2.,3.,4.,5.,6.,7.,-8.,-7.,-6.,-5.,-4.,-3.,
			      -2.,-1.};
#endif
static  int   lkup_1[2]={1,-1};
static  int   lkup_2[4] = {0,1,-2,-1};
static  int   lkup_4[16] = {0,1,2,3,4,5,6,7,-8,-7,-6,-5,-4,-3,
			      -2,-1};
	short   *inPtrI1,*inPtrQ1;
	short   *inPtrI2,*inPtrQ2;
    unsigned short swi1,swq1;
    unsigned short swi2,swq2;
/*  12 (16 bit) needs to used signed variable so we sign
    extend into  the 32bits
*/
    short swi1S,swq1S;
    short swi2S,swq2S;
	int   *outPtrI1,*outPtrQ1;
	int   *outPtrI2,*outPtrQ2;
	int  	instep;		/* number shorts between inputs 1 dig*/
	int  	outStep;	/* number double between outputs 1 dig*/
	int     i;
/*
 *	check that inputs were reasonable, if not, return ERROR (-1);
*/
	switch(numFifos){
	      case 1:
 	           if ((outPtr1==(int  *)NULL)) goto errout;
	           if (iqSepReg) {
 	              if (outPtr2==(int  *)NULL)goto errout;
		   }
	           break;
	      case 2:
 	             if ((outPtr1==(int  *)NULL) || 
 	                 (outPtr2==(int  *)NULL)) goto errout;
	             if (iqSepReg) {
 	                if ((outPtr3==(int  *)NULL) || 
 	                    (outPtr4==(int  *)NULL)) goto errout;
		     }
		     break;
	      default:
	             goto errout;
	             break;
	}
	switch(bits){
	      case 1:
	      case 2:
	      case 4:
	      case 8:
	      case 12:
		     break;
	      default:
	             goto errout;
	             break;
	}
	switch (numFifos) {
/*
 *	using 1 fifo..
*/
	  case 1:

	    inPtrQ1=(short *)inPtr;  
	    inPtrI1=(short *)(inPtr+2);  
	    instep=2;			   /* inputs separated by 2 shorts*/
	    if (iqSepReg) {
	       outPtrI1=outPtr1;
	       outPtrQ1=outPtr2;
	       outStep=1;		   /*2 bufs, i data sep by 1 double*/
	    }
	    else {
	       outPtrI1=outPtr1;
	       outPtrQ1=outPtr1+1; 	   /* iq to same outbuf*/
	       outStep=2;		   /*outdata 1 dig sep by 2 doubles*/
	    }
	    switch (bits) {
	      case 1:
	        for (i=0;i<numwrds;i++){
                swi1=bswap_16(*inPtrI1);
                swq1=bswap_16(*inPtrQ1);
                unpri_1(swi1,outPtrI1,outStep);
                unpri_1(swq1,outPtrQ1,outStep);
		  inPtrI1+=instep;
		  inPtrQ1+=instep;	
	        }
	        break;
	      case 2:
	        for (i=0;i<numwrds;i++){
          swi1=bswap_16(*inPtrI1);
          swq1=bswap_16(*inPtrQ1);
          unpri_2(swi1,outPtrI1,outStep);
          unpri_2(swq1,outPtrQ1,outStep);
		  inPtrI1+=instep;
		  inPtrQ1+=instep;	
	        }
	        break;
	      case 4:
	        for (i=0;i<numwrds;i++){
          swi1=bswap_16(*inPtrI1);
          swq1=bswap_16(*inPtrQ1);
          unpri_4(swi1,outPtrI1,outStep);
          unpri_4(swq1,outPtrQ1,outStep);
		  inPtrI1+=instep;
		  inPtrQ1+=instep;	
	        }
	        break;
	      case 8:
	        for (i=0;i<numwrds;i++){
          swi1=bswap_16(*inPtrI1);
          swq1=bswap_16(*inPtrQ1);
          unpri_8(swi1,outPtrI1,outStep);
          unpri_8(swq1,outPtrQ1,outStep);
		  inPtrI1+=instep;	
		  inPtrQ1+=instep;
	        }
	        break;
	      case 12:
	        for (i=0;i<numwrds;i++){
          swi1S=bswap_16(*inPtrI1);
          swq1S=bswap_16(*inPtrQ1);
          unpri_12(swi1S,outPtrI1,outStep);
          unpri_12(swq1S,outPtrQ1,outStep);
		  inPtrI1+=instep;
		  inPtrQ1+=instep;	
	        }
	        break;
	   }
	   break;
/*
 *	using two fifos
*/
 	   case 2:

            inPtrQ1=(short *)inPtr;
            inPtrI1=(short *)(inPtr+2);
            inPtrQ2=(short *)(inPtr+4);
            inPtrI2=(short *)(inPtr+6);
	    instep=4;			/* 4 shorts each input*/
	    if (iqSepReg) {
	       outPtrI1=outPtr1;
	       outPtrQ1=outPtr2;
	       outPtrI2=outPtr3;
	       outPtrQ2=outPtr4;
	       outStep=1;		   /*2 bufs, i data sep by 1 double*/
	    }
	    else {
	       outPtrI1=outPtr1;
	       outPtrQ1=outPtr1+1; 	   /* iq to same outbuf*/
               outPtrI2=outPtr2;
               outPtrQ2=outPtr2 + 1;
	       outStep=2;		   /*outdata 1 dig sep by 2 doubles*/
	    }
            switch (bits) {
              case 1:
                for (i=0;i<numwrds/2;i++){
                  swi1=bswap_16(*inPtrI1);
                  swq1=bswap_16(*inPtrQ1);
                  swi2=bswap_16(*inPtrI2);
                  swq2=bswap_16(*inPtrQ2);
				  unpri_1(swi1,outPtrI1,outStep);
                  unpri_1(swq1,outPtrQ1,outStep);
                  unpri_1(swi2,outPtrI2,outStep);
                  unpri_1(swq2,outPtrQ2,outStep);
                  inPtrI1+=instep;
                  inPtrQ1+=instep;
                  inPtrI2+=instep;
                  inPtrQ2+=instep;
                }
                break;
              case 2:
                for (i=0;i<numwrds/2;i++){
                  swi1=bswap_16(*inPtrI1);
                  swq1=bswap_16(*inPtrQ1);
                  swi2=bswap_16(*inPtrI2);
                  swq2=bswap_16(*inPtrQ2);
				  unpri_2(swi1,outPtrI1,outStep);
                  unpri_2(swq1,outPtrQ1,outStep);
                  unpri_2(swi2,outPtrI2,outStep);
                  unpri_2(swq2,outPtrQ2,outStep);
                  inPtrI1+=instep;
                  inPtrQ1+=instep;
                  inPtrI2+=instep;
                  inPtrQ2+=instep;
                }
                break;
              case 4:
                for (i=0;i<numwrds/2;i++){
                  swi1=bswap_16(*inPtrI1);
                  swq1=bswap_16(*inPtrQ1);
                  swi2=bswap_16(*inPtrI2);
                  swq2=bswap_16(*inPtrQ2);
				  unpri_4(swi1,outPtrI1,outStep);
                  unpri_4(swq1,outPtrQ1,outStep);
                  unpri_4(swi2,outPtrI2,outStep);
                  unpri_4(swq2,outPtrQ2,outStep);
                  inPtrI1+=instep;
                  inPtrQ1+=instep;
                  inPtrI2+=instep;
                  inPtrQ2+=instep;
                }
                break;
	      case 8:
	        for (i=0;i<numwrds/2;i++){
                  swi1=bswap_16(*inPtrI1);
                  swq1=bswap_16(*inPtrQ1);
                  swi2=bswap_16(*inPtrI2);
                  swq2=bswap_16(*inPtrQ2);
				  unpri_8(swi1,outPtrI1,outStep); 
                  unpri_8(swq1,outPtrQ1,outStep);
                  unpri_8(swi2,outPtrI2,outStep);
                  unpri_8(swq2,outPtrQ2,outStep);
		  inPtrI1+=instep;
		  inPtrQ1+=instep;
		  inPtrI2+=instep;
		  inPtrQ2+=instep;
	        }
	        break;
	      case 12:
	        for (i=0;i<numwrds/2;i++){
                  swi1S=bswap_16(*inPtrI1);
                  swq1S=bswap_16(*inPtrQ1);
                  swi2S=bswap_16(*inPtrI2);
                  swq2S=bswap_16(*inPtrQ2);
				  unpri_12(swi1S,outPtrI1,outStep); 
                  unpri_12(swq1S,outPtrQ1,outStep);
                  unpri_12(swi2S,outPtrI2,outStep);
                  unpri_12(swq2S,outPtrQ2,outStep);
		  inPtrI1+=instep;
		  inPtrQ1+=instep;	
		  inPtrI2+=instep;
		  inPtrQ2+=instep;	
	        }
	        break;
	  }
	  break;
	}
	return(OK);
errout: return(ERROR);
} 
