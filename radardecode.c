#include        <stdio.h>
#include        <fcntl.h>
#include        <malloc.h>
#include	 	<string.h>
#include		<riLib.h>
#include		<philLib.h>
#include		<unpack.h>
/*
 *      decode an input stream of radar data.                    
 *      
 *       radardecode -b bits -c codelen -l xformlen -n numcodes -q -t -o offset    
 *                   -s samples/baud -r   
 *
 *      -b  bits for packing
 *      -c  pn code length used in data
 *      -l   length of complex xform to do. (def = 32k).
 *      -n  number of codes to decode
 *      -q  run quietly
 *      -o  offset to add to input data
 *      -t print times
 *      -d debug... clip to +/- .5 input data must also set -o .5
 *		-s 2   .. samples per baud 1,2,3 ..etc
 *      -p  numpol polToUse:f
 *      -a  codeProgram to use
 *
 *      3aug99, -u     .. input data already unpacked as floats.
 *  			  in 16 bit word.. i,q
 * 			    replace by -m unpacked
 *      -r remove Dc 
 *      -m machine..unpacked,cbr,ri .. (for cbr should set numpol,poltouse
 *      below not implemented  yet...
 *      -f freqShift .. frequency bins to shift. positive is to higher freq.
 *                      1 bin = 1/(baud*xformlen)
 *
 *      The program will take input data as:
 *         1. ripacked data .. 1 pol only
 *		   2. unpacked 
 *       
 *for
 *      
 *      if x=data, c=code, and r= a range gate then we want the correlation
 *
 *      z(r) = sumi( x(i+r)*c(i)) summed for the code length
 *     
 *      The overlap save convolution algorithm pg 212 of fft and its
 *      applications  (brigham 1988) is used. You can use a convolution to 
 *      do a correlation as long as you conjugate the non-delayed function
 *      (code) in the frequency domain. Also remember that for correlations
 *      it is the last codelength-1 points that are no good (as opposed to
 *      convolutions where the 1st codelength-1 points are not complete.
 *
 *      the output is the decoded points (in the time domain).
 *      the first codelen-1 time points are not returned (since not meaningful)
 *
 *       the code is input from the file
 *       PNFILE_NAME "/home/aosun/u4/phil/skybolt/pncode.xxx"
 *       where xxx is the codelen. The code should be i*4 with +/- 1.  
 *       see program comppncode.c to generate file.
 *		 If samples/baud > 1, then each baud from the code is  duplicated
 *		 N times and the codelenused = codelen*samplesPerBaud.
 *      
 *       -o offset will be subtraced from the input data unless -r is selected
 *          in that case the mean will be removed on input
 *
 * history start:
 *   10/18/91.. bug in processargs.. offset was being read as %d instead of
 *              %f. --> offset was always zero.. for previous processing.
 *   10/17/91   <pjp001> added debug_clip. if -d clip to +/-.5 input data
 *              need to define the macro for the sun.
 *   9/8/91 ..  was computing number of codes completed... wrong.
 *              used (fftlen - codelen-1) wanted (fftlen -(codelen-1)
 *   6/20/91..  Found bug in getdata. was returning the number of floats,
 *              but program was expecting the number of complex points...
 *              . also changed initial read to exit if current number of
 *                bytes readin != to requested amount 
 *   6/5/91  .. conditional compiles to work on sun or sky.... took from
 *              sky version.
 *   12/23/90.. display_buf routine was wiping out the output? don't use it.
 *   12/21/90.. added -b bits.so we can unpack here.
 *   12/20/90.. ap routines added.
 *   11/28/90.. scaling different for sky fft. currently we * 1/lenfft
 *              we now need to multiply by lenfft**2
 *   3/6/98  .. <pjp002>. updated to input the data from the vme system.
 *				old version ran on sun but processed harris 3bytes/word data.
 *   5/26/98 .. get rid of skybold ifdefs...
 *              switch to c version of four1. note the crazy -1 to get the 
 *			    addressing of the arrays right.
 *  14may99  .. start adding code to do frequency shift while decoding
 *  24may99  .. add option for 2 samples per baud. we just make the
 *		   	    codelen twice as long and then compute..
 *  27may99  .. <pjp003>added option -z to remove dc on input points. 
 *			    do this and the offset add and the clip all in the
 *				get data routine.
 *  31may99  .. <pjp004> added -u unpacked option to input data that is
 *			    already in float i,q order
 *  03aug99  .. added -m cbr,ri,unpacked. 
 *			    -p numpol polToUse .. should be specified for cbr data
 *  05aug99  .. switched from four1 to fftwAo..
 *  need to update cbrunp and change test_main_decode to input
 *               -p option for cbr, and for cbr use just cbr not cbr1,2
 *				    and check for 2 pol selectpnts only on ri.
 *  20aug99  .. added -a option to specify a different program to 
 *				generate the code to decode. It should accept the following
 *              args.. prgname -c codelen -s small value -b bigvalue
 *  01nov99  .. fftwAo now had not inplace option.
 * history end:
*/
/*
 *              DEFINES
*/
#define SLOPBYTES 0 
#define OFFSETREAL 0

#define STDOUT 1
#define  K  1024 
#define  TRUE  1 
#define  FALSE 0
#define  MIN(a,b)  ((a)<(b))?(a):(b)
/*   prgname_pncode used by sun to generate codes,
*/
#define  PRGNAME_PNCODE "/home/margot/bin/comppncode" 
#define  prtime(loop,time,str) \
              fprintf(stderr,"loop:%d %f secs %s\n",loop,time,str)
/***************************************************************************
 *      here are the macros to do the computations
*****************************************************************************/
/*
 *      move npts cmplx numbers from from to to.
 *      from,to are pointers to reals.
*/
#define  cmplx_move(npts,from,to)    \
           { int i;\
             for(i=0;i<2*npts;){ \
                (to)[i]=(from)[i];i++;(to)[i]=(from)[i];i++;\
             } \
           }    
/*
 *      a * bcnj = b
 *      complex multiply a with conj of b, store back in b
 *      a,b are pointers to reals.
*/
#define  cmplx_mult_cnj(npts,a,b) \
        { float rtemp; \
          register float *pa,*pb; \
          for (pa=(a),pb=(b);(pa < ((a)+2*npts));pa+=2,pb+=2){ \
            rtemp  = pa[1] * pb[0]; \
            pb[0] =  pa[0] * pb[0] +  pa[1] * pb[1]; \
            pb[1] = rtemp           - pa[0] * pb[1]; \
          } \
        }
/*
 *      add a scalar to a floating point real vector.
 *      npts are the number of real points
*/
#define   scalar_add(npts,offs,buf) \
               { float *fptr; \
                 for (fptr=(buf);fptr < (buf)+(npts); *fptr++ +=offs); \
               } 
/*
 *      clip to +/- value
*/
#define clip_to_val(val,npts,buf)
/*
 * macros to unpack cbr data
*/
#define unpCbrCh1(val,pout,lkup) \
            (val)>>=4;\
            (pout)[1]=lkup[(val)&3];\
            (val)>>=2;\
            (pout)[0]=lkup[(val)&3];\
            (pout)+=2;

#define unpCbrCh2(val,pout,lkup) \
            (pout)[1]=lkup[(val)&3];\
            (val)>>=2;\
            (pout)[0]=lkup[(val)&3];\
            (pout)+=2;

/* setup for old box... first sample on the left */
			
#define unpCbrCh1chn(val,pout,lkup) \
            (pout)[3]=lkup[(val)&3];\
            (val)>>=2;\
            (pout)[2]=lkup[(val)&3];\
            (val)>>=2;\
            (pout)[1]=lkup[(val)&3];\
            (val)>>=2;\
            (pout)[0]=lkup[(val)&3];\
            (pout)+=4;
/*
 * 	codes for type of input.. used in bufinfo inputType
 * 1 ri data 1 pol
 * 2 unpacked floats
 * 3 cbr data
 * 4 pfs data
 * 5 bytes
*/

#define INPTYPE_RI	        1
#define INPTYPE_UNPACKED	2
#define INPTYPE_CBR     	3
#define INPTYPE_PFS     	4
#define INPTYPE_BYTES     	5


/*    typedefs 	*/

typedef struct {
	float	      *fft;	         /* allocated buffer used  for fft*/
	float		  *code;	     /* holds transformed pncode*/
	float   	  *save;         /* for overlap save */
    unsigned char *inpPacked;    /* inp buffer packed data*/
    float         *inpUnpacked;  /* inp data after unpackin <pjp003>*/
    int           lenInpPackedB; /* how long inpPacked is in bytes*/
    int           lenInpUnpackedF4; /* how long inpUnpacked is in words F4*/
    int           gdpoints_unused;  /* unpacked bytes unused*/
    float         *pinpUnpacked;  /* moves thru inpUnpacked <pjp003>*/
	int			  inputType;	  /* tells what kind of data the input is*/
	int			  numPol;		  /* 1,2*/
	int			  polToUse;		  /* 1 or 2 needed for cbr data*/
	} BUF_INFO;

/*
 *              FUNCTIONS
*/
int     allocate_buffers(BUF_INFO *pbufI,int fftlen,int points_to_save,int bits);
int     getdata(BUF_INFO *pbufI,int bits,float *buf,int points,
				float offset,int dbgClip,int removeDc);
int     input_code(int codelen,int samplesPerBaud,int lenfft,float *code_buf,
				   float scalefactor, char *codeProgName);
void    processargs(int argc,char **argv,int *codelen,int *lenfft,
				int *numcodes_req,int *quiet,float *offset,int *bits,
				int *timeout,int *samplesPerBaud,int *removeDc,int *inputType,
				float *pfreqShift,int *debug_clip,int *numpol,int *polToUse,
				char *codeProgName);

void unpcbr (int bytesInp,int numpol,int polToUse,unsigned char *packedBuf,
				 float *punpackedBuf);
void unppfs (int bytesInp,int bits,int numpol,int polToUse,unsigned char *packedBuf,
				 float *punpackedBuf);
void unpbytes (int bytesInp,unsigned char *packedBuf,float *punpackedBuf);
STATUS  unpriV_i4(int numwrds,int numFifos,int bits,int IQsepReg,char *inPtr,
				 int *outPtr1,int *outPtr2, int *outPtr3,int *outPtr4);

/*
void four1(float *dat,int lenxform,int direction);
*/

float   lkupCbrF[4] ={0.f,1.f,-2.f,-1.f}; /* value for cbr unpack*/
int     one = {1};
int     negone={-1};
int     two ={2};
int     bytes_per_cmplx_point = {8};
/*  
 *      globals for get data.. double buffering, etc
*/
char *rcp; /* char buffer for char unpacking of PFS data */

/* revision control variable */
static char const rcsid[] = 
"$Id$";

int main(int argc,char **argv) 
{ 

        int     codelen;                        /* code length requested*/
        int     codelenUsed;                    /* code length Req*smp/Baud*/
        int     lenfft;                         /* xformlen*/
        int     numcodes_req;                   /* they requested*/
        int     numffts_req;                    /* to decode the req codes*/
        int     dotime;                         /* they want times*/
        int     debug_clip;                     /* clip to +/- .5*/
        int     rec;    
        int     outrecs;                        /* actually done*/
        float   scalefactor;                    /* for 1/n in xform*/
        float   offset;                         /* for input data*/
        float   time1,tstart;
        float   tread,twrite,tfftf,tfftr,tcmplxmul,ttotal;
        float   tmovesavein;
		float   freqShift;						/* in freq bins*/
        int     points_inp_req;      
        int     bytes_out_req;      
        int     points_inp;
        int     bytes_out;
        int     points_to_save;                 /* for next dcd...cmplx*/
        int     xformdir;                       /* +/- 1 for exp(iwt)*/
        int     quiet;                          /* run quietly*/
        int     bits;                           /* for data*/
		int		samplesPerBaud;			/* 1,2,...*/
	    int	    removeDc; 	 /* true-->remove mean i,q after input 
									do this  xformlen at a time*/
		char	codeProgName[132];
/*
 *      buffers
 *      
 *      input:
 *      get_data
 *            inputs into inp_packed. 
 *            unpacks the entire buffer into inp_unpacked.
 *            moves inp_unpacked into float buffers when needed.
 *
 *       ffts:
 *       2 fft buffers are needed since not done in place.
 *
 *      read -->  bufI.inpPacked
 *      bufI.inpPacked--> unpack data --> bufI.inpUnpacked
 *      bufI.inpUnpacked --> bufI.fft   when needed
 *      bufI.fft  FFT --> bufI.fft
 *      bufI.fft * bufI.code --> bufI.fft
 *      bufI.fft FFT --> bufI.fft
 *      bufI.fft     --> output.
 *
 *      the pointers for fft_buf1  are:
 *    |-------------------- fftlen -------------------------------------|
 *    |(codelenUsed-1)   |                           |codelenUsed -1    |
 *    |-----------------------------------------------------------------| 
 *    ^***************^xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
 *    bufI.fft        fft_buf_newdata                    ^  
 * copy savebuf here| copy new data to here          |fftbuf_nextsave
 *                                                    copy here to savebuf
 *                                              
*/
        BUF_INFO bufI;						    /* holds allocated bufs*/
        float   *fft_buf_newdata;               /* after savebuf data*/
        float   *fft_buf_nextsave;              /* to save for next time*/
        int     codesdecoded;                   /* actually done*/

/*      do some inits to get rid of warning messages.*/
        ttotal=tcmplxmul=tfftr=tfftf=tread=twrite=tmovesavein=tstart=time1=0.;
        rec=0;
/*
 *      setup the defaults
*/
        numcodes_req= 100000000;                /* bignumber*/
        codelen = 2047;                         /* default codelen*/
        lenfft  = 16*K;
        offset=0.;                              /* for data*/
		outrecs=0;
        bits=12;
        dotime=FALSE;
        debug_clip=FALSE;
		freqShift=0.;
		samplesPerBaud=1;
		removeDc=FALSE;
		bufI.gdpoints_unused=0;		/* don't have any stored up yet*/
		bufI.inputType=INPTYPE_RI;	/* defaults to ri data*/
		bufI.numPol   =2;
		bufI.polToUse =1;
/*
 *      get the parameters
*/
        processargs(argc,argv,&codelen,&lenfft,&numcodes_req,&quiet,&offset,
                              &bits,&dotime,&samplesPerBaud,&removeDc,
							  &bufI.inputType,&freqShift,&debug_clip,
							  &bufI.numPol,&bufI.polToUse,codeProgName);

	    codelenUsed=codelen*samplesPerBaud;
        numffts_req = (((float)numcodes_req)*codelenUsed)/
				(lenfft-codelenUsed+1) + 1;
        points_to_save = codelenUsed - 1;           /* to save*/
        points_inp_req= (lenfft - points_to_save);
        bytes_out_req = points_inp_req*bytes_per_cmplx_point;
		if (dotime){
			if (timerstart()){perror("calling timerstart");}
		}
/*
 *     allocate buffers
*/
        if (!allocate_buffers(&bufI,lenfft,points_to_save,bits)) exit(-1);
        fft_buf_newdata = &(bufI.fft[points_to_save*2]);/* *2 since cmplx*/
        fft_buf_nextsave= &(bufI.fft[(lenfft-points_to_save)*2]);
/*
 *      input code, zero fill and transform,      
 *      we do 3 ffts of same direction. need to scale by two times the 
 *      xform scaling.
 *      Empirically i've found that the ap routine needs N**2 while the         
 *      four1 routine needs 1/N
*/
        scalefactor = 1./((float)lenfft);
        
        if (!input_code(codelen,samplesPerBaud,lenfft,bufI.code,scalefactor,codeProgName))
			exit(-1);   
/*
 *      read in 1st save buf points into save buf
*/
        points_inp = getdata(&bufI,bits,bufI.save,points_to_save,
				     offset,debug_clip,removeDc); /* <pjp003> */
        if (points_inp != points_to_save){
           if (points_inp == 0) goto done;      /* hit eof*/
           if (points_inp < 0) {
            perror("radardecode: inputing 1st save buf");
            exit(-1);
            }
            if (points_inp < points_to_save) {
             fprintf(stderr,"Not enough words 1st save buf. req:%d, read:%d\n",
               points_to_save,points_inp);
               exit(-1);
            }
        }
#if FALSE
		<pjp003>
        if (offset !=0.){
            scalar_add(points_inp*2,offset,bufI.save); /* *2 since real mult*/
            if (debug_clip){            /* <pjp001>   */
               clip_to_val(.5,points_inp*2,bufI.save);
            }
        }
#endif
/*
 *      now the main loop; +1 to finish last code
*/
        for (rec=0,outrecs=0;rec < numffts_req;rec++){
/*
 *      move save buf to front of fftbuf
*/
            if (dotime) tstart=timervalue();    

            if (dotime) time1=timervalue();     
            cmplx_move(points_to_save,bufI.save,bufI.fft);
            if (dotime) tmovesavein=time1-timervalue();
/*
 *      input data into fftbuf after the saved data
*/
            if (dotime) time1=timervalue();
            points_inp = getdata(&bufI,bits,fft_buf_newdata,points_inp_req,
				     offset,debug_clip,removeDc); /* <pjp003>*/
            if (dotime) tread=time1-timervalue();
            if (points_inp < 0) {
               perror("fft: inputing data");
               exit(-1);
            }
            if (points_inp < points_inp_req) goto done; /* ignore partial rec*/
#if FALSE
            if (offset !=0.){
               scalar_add(points_inp*2,offset,fft_buf_newdata);
               if (debug_clip){                 /* <pjp001>  */ 
                  clip_to_val(.5,points_inp*2,fft_buf_newdata);
               }
            }
#endif
/*
 *      now move end of fft buf to save buf for next time
*/
            cmplx_move(points_to_save,fft_buf_nextsave,bufI.save);
/*
 *      now go to the frequency domain 
*/
            xformdir=-1;
            if (dotime) time1=timervalue();     
			fftwAo(bufI.fft,NULL,lenfft,xformdir,1);
/* 
            four1(bufI.fft-1,lenfft,xformdir);
*/
            if (dotime) tfftf=time1-timervalue();
/*
 *      if x=data, h=code.. we want the correlation:
 *         z(r)= sum( x(r+i)*h(i))  where r is a range gate 
 *         use the convolution technique and remember to take the 
 *         conjugate of H* in the frequency domain.
 *
 *     X= fft(x,exp-)   
 *     H= fft(h,exp-)  
 *     Z= X*Hcnj   since we want a correlation instead of a convolution
 *     z= fft(Zcnj,exp-) with 1/N
 *     but 
 *     Zcnj = Xcnj*H    so compute H*Xcnj 
*/
/*
 *      multiply transformed code by the xformed data
*/
            if (dotime)time1=timervalue();      
            cmplx_mult_cnj(lenfft,bufI.code,bufI.fft); 
            if (dotime)tcmplxmul=time1-timervalue();
/*
 *      now do the inverse xform
*/
            if (dotime)time1=timervalue();      
			fftwAo(bufI.fft,NULL,lenfft,xformdir,1);
/*
            four1(bufI.fft-1,lenfft,xformdir);
*/
            if (dotime) tfftr=time1-timervalue();
/*
 *      write out the valid data points
*/
            if (dotime)time1=timervalue();
            bytes_out = fwrite((char *)bufI.fft,1,bytes_out_req,stdout);
            if (dotime)twrite=time1-timervalue();
            if (bytes_out_req != bytes_out){
               fprintf(stderr,
                "radardecode: output error. bytes out %d\n",bytes_out);
                 exit(-1);
            }
            outrecs++;                          /* count complete recs*/
/* 
 *      writeout times:
*/
            if (dotime) {
              ttotal=tstart-timervalue();
            }
            if (dotime){
              fprintf(stderr,"#%5d %7.4f sec total time.\n",rec,ttotal);
              fprintf(stderr,"       %7.4f     read,unpack.\n",tread); 
              fprintf(stderr,"       %7.4f     fft-->freq.\n",tfftf); 
              fprintf(stderr,"       %7.4f     X*C freq domain.\n",
                                                               tcmplxmul); 
              fprintf(stderr,"       %7.4f     fft-->time.\n",tfftr); 
              fprintf(stderr,"       %7.4f     write.\n",twrite);
            }
            if (( !dotime ) && (!quiet) && ((rec % 50) == 1)) {
               fprintf(stderr," %d ffts completed\r",rec);
            }
        }
done:
        codesdecoded=outrecs*(lenfft - (codelenUsed - 1))/(codelenUsed*1.);
        if (!quiet)  fprintf(stderr,"\n%d cycles decoded using %d ffts\n",
                     codesdecoded,outrecs);
        exit(0);
        /*NOTREACHED*/
}       
/******************************************************************************/
/*      allocate_buffers                      */
/******************************************************************************/
int     allocate_buffers
	(
	 BUF_INFO		*pbufI,
	 int     	    fftlen,
	 int            points_to_save,
	 int            bits
	)
{
        int samplesperword,wordsneeded;
/* 
 *      allocate buffers. return 1 if ok, 0 if error
*/

/*
 *     allocate fft buffer for data
*/
        pbufI->fft = (float *)calloc((unsigned)(fftlen*bytes_per_cmplx_point),
                                   sizeof(char));
        if (pbufI->fft == NULL){
            perror("radardecode: Allocating fft buffer");
            return(FALSE);
        }
/*
 *     allocate fft buffer for code 
*/
        pbufI->code = (float *)calloc((unsigned)(fftlen*bytes_per_cmplx_point),
                                   sizeof(char));
        if (pbufI->code == NULL){
            perror("radardecode: Allocating code buffer");
            return(FALSE);
        }
/*
 *      allocate save buffer for overlap
*/
        pbufI->save = (float *)calloc((unsigned)(
                           points_to_save*bytes_per_cmplx_point), sizeof(char));
        if (pbufI->save == NULL){
            perror("radardecode: Allocating save buffer");
            return(FALSE);
        }
/*
 *      allocate input buffer for packed data
*/
		switch (pbufI->inputType) {
			case INPTYPE_RI:
        		samplesperword=16/bits/pbufI->numPol;          /* i or q*/
			    break;
			case INPTYPE_CBR:
			    /*  kludge up so multiple of 4 bytes like ri data */
        		samplesperword=(pbufI->numPol == 2)?4:8;/*in 1 4 byte word*/
			    break;
			case INPTYPE_PFS:
			    /*  kludge up so multiple of 4 bytes like ri data */
        		samplesperword=16/bits/pbufI->numPol;/*in 1 4 byte word*/
			    break;
			case INPTYPE_BYTES:
        		samplesperword=2;/*in 1 4 byte word*/
			    break;
			default:
        		samplesperword=1; 			/* unpacked data */
		}
        wordsneeded= (fftlen + samplesperword -1)/samplesperword; /*round up*/
/* 
 *      if two channels input, multiply by two here
*/
        pbufI->lenInpPackedB= wordsneeded*4;        /* 4 bytes/ word*/
       pbufI->inpPacked=(unsigned char *)(calloc((unsigned)pbufI->lenInpPackedB,
                         sizeof(char)));
        if (pbufI->inpPacked == NULL){
            perror("radardecode: Allocating input_packed buffer");
            return(FALSE);
        }
/*
 *      allocate input buffer for unpacked data
 *         if 2 channels used, maybe you could divide by 2
*/
        pbufI->lenInpUnpackedF4 =(samplesperword*2)*wordsneeded; /* *2 or i,q */
        pbufI->inpUnpacked=(float *)(calloc((unsigned)
					(pbufI->lenInpUnpackedF4*4),sizeof(char)));
        if (pbufI->inpUnpacked == NULL){
            perror("radardecode: Allocating input_unpacked buffer");
            return(FALSE);
        }

	/* jlm allocate buffer for PFS unpacked char data */
	if (pbufI->inputType == INPTYPE_PFS)
	  {
	    rcp = (char *) malloc(pbufI->lenInpUnpackedF4 * sizeof(char));
	    if (rcp == NULL){
	      perror("radardecode: Allocating PFS char buffer");
	      return(FALSE);
	    }
	  }

        return(TRUE);
}
/******************************************************************************/
/*      getdata                                                              */
/******************************************************************************/
int  getdata
	(
	 BUF_INFO	*pbufI,
	 int         bits,    
	 float      *buf,                          /*input data to here*/
	 int     points,                                 /* cmplx points to input*/
	 float   offset,
	 int     debug_clip,
	 int	 removeDc
	)
{
        int words_inp,bytes_inp;   
        int points_needed;                      /* still*/
        float *bufptr;                          /* move along in buf*/
        int points_to_move;                     /* still in unpack buffer*/
		double meanId,meanQd;				/* if remove Dc*/
		double meanIf,meanQf;				/* if remove Dc*/
		float *pf;
        
        points_needed = points;
        bufptr=buf;

        while (points_needed > 0) {
           points_to_move= MIN(pbufI->gdpoints_unused,points_needed);
           if (points_to_move > 0){
			  /* <pjp003  below */
              cmplx_move(points_to_move,pbufI->pinpUnpacked,bufptr);
#if FALSE
              float_arr(itemp,pbufI->pinpUnpacked,bufptr);
#endif
              pbufI->pinpUnpacked+=(points_to_move*2);     /* *2 since cmplx*/
              pbufI->gdpoints_unused-=points_to_move;          /* number left*/
              points_needed-=points_to_move;
              bufptr+=(points_to_move*2);               /* *2 since cmplx*/
           }
/*
 *       see if we need to read more data
*/
           if (points_needed > 0){                      /* try another read??*/ 
			  /* 
			   * if data not unpacked, do it..
			  */
			  if (pbufI->inputType != INPTYPE_UNPACKED) { 			/* pjp004*/
              	  bytes_inp=read_pipe((char*)pbufI->inpPacked,
						pbufI->lenInpPackedB);
				  if (bytes_inp <= 0) {           /* eof or error. stop now*/
                    return(bytes_inp);
                  }
				  /* ri data.  will FAIL with dual polarization RI data */
				  /* must eliminate one polarization in main_decode.sc */
				  if (pbufI->inputType == INPTYPE_RI) {
                     words_inp= bytes_inp/4;          /* make sure full words*/

                     unpriV_f4(words_inp,1,bits,FALSE,(char*)pbufI->inpPacked,
					     pbufI->inpUnpacked,NULL,NULL,NULL);
                     pbufI->gdpoints_unused= words_inp*(16/bits);
		     /* we'd really like something that can handle dual polarization like
		     unpriV_f4(words_inp,pbufI->numPol,pbufI->polToUse,bits,FALSE,(char*)pbufI->inpPacked,
			       pbufI->inpUnpacked,NULL,NULL,NULL);
                     pbufI->gdpoints_unused= bytes_inp*(4/pbufI->numPol/bits);
		     */
				  /* cbr data, always 2 bits */
				  } else if (pbufI->inputType == INPTYPE_CBR) {
					 unpcbr(bytes_inp,pbufI->numPol,pbufI->polToUse,
							pbufI->inpPacked,pbufI->inpUnpacked);
                     pbufI->gdpoints_unused= bytes_inp*(2/pbufI->numPol);
				  /* pfs data */
				  } else if (pbufI->inputType == INPTYPE_PFS) {
					 unppfs(bytes_inp,bits,pbufI->numPol,pbufI->polToUse,
							pbufI->inpPacked,pbufI->inpUnpacked);
                     pbufI->gdpoints_unused= bytes_inp*(4/pbufI->numPol/bits);
				  /* bytes */
				  } else if (pbufI->inputType == INPTYPE_BYTES) {
					 unpbytes(bytes_inp,pbufI->inpPacked,pbufI->inpUnpacked);
                     pbufI->gdpoints_unused= bytes_inp/2;
				  } else {
					fprintf(stderr,"inputType:%d unkown type.. getdata\n",
						pbufI->inputType);
					    exit(-1);
				  }
			  } else {
              	  bytes_inp=read_pipe((char*)pbufI->inpUnpacked,
					pbufI->lenInpUnpackedF4*sizeof(float));
              	  if (bytes_inp <= 0) {           /* eof or error. stop now*/
                    return(bytes_inp);
                  }
                  pbufI->gdpoints_unused= bytes_inp/8;
			  }
              pbufI->pinpUnpacked=pbufI->inpUnpacked;/* start at begining*/
/* 
 *        	  you could start another read here..
 *			  <pjp003> below .. in case large values, cmp mean in double...
*/
			  if (removeDc) {
				 meanQd=0.;meanId=0.;
				 for (pf=pbufI->inpUnpacked;pf< (pbufI->inpUnpacked+
					  pbufI->gdpoints_unused*2);){
					  meanId+=*pf++;
					  meanQd+=*pf++;
				 }
				 meanIf= meanId/(pbufI->gdpoints_unused);
				 meanQf= meanQd/(pbufI->gdpoints_unused);
#if FALSE				 
				 fprintf(stderr,"n:%d mnIQ:%8.3f %8.3f\n",
					pbufI->gdpoints_unused*2,meanI,meanQ);
				 fflush(stderr);
#endif
				 for (pf=pbufI->inpUnpacked;pf< (pbufI->inpUnpacked+
					  pbufI->gdpoints_unused*2);){
					  *pf++ -=meanIf;
					  *pf++ -=meanQf;
				 }
			  } 
			  else if (offset !=0.){
                 scalar_add(pbufI->gdpoints_unused*2,offset,pbufI->inpUnpacked);
                 if (debug_clip){                 /* <pjp001>  */ 
                   clip_to_val(.5,pbufI->gdpoints_unused*2,pbufI->inpUnpacked);
                 }
              }
           }
        }
        return((int)(bufptr-buf)/2);    /* how cmplx points we moved*/
}
/******************************************************************************/
/*      input_code                                                            */
/******************************************************************************/
int     input_code
	(
 	 int     codelen,                        /* len of code requested*/
	 int	 samplesPerBaud,			    /* sampled*/
	 int     lenfft,                        /* len of xform to use*/
	 float   *code_buf,                      /* put transformed code here*/
	 float   scalefactor,                     /* for 1/n of xforms*/
	 char *codeProgName			/* code program to use */
	)
	  
{
        FILE    *pstr;                  /* hold stream ptr for pipe*/
        char    pncommand[80];          /* build command for pncode prog*/
        int     smallvalue,bigvalue;    /* for the code*/
        int     *inpbuf;                /* hold code from program (integer)*/
        int     i,j,k;
        int     inpwords;
        int     xformdir;               /* for fft*/
		int		codelenUsed;			/* codelen*samplesperbaud*/
/*
 *      allocate buffer for read (we get integer data from program
*/
	    codelenUsed=codelen*samplesPerBaud;
        inpbuf = (int *)calloc((unsigned)(codelen),sizeof(int));
        if (inpbuf == NULL){
            perror("radardecode: Allocating input pncode buffer:");
            return(FALSE);
        }
/*
 *      startup filter that will create the code
*/
        smallvalue = -1;                /* for code*/
        bigvalue   = 1;                 /* for code*/
        sprintf(pncommand,"%s -c %d -s %d -b %d",codeProgName,
             codelen,smallvalue,bigvalue);
         if( (pstr=popen(pncommand,"r")) == NULL){
      fprintf(stderr,"Can't start pncode generating program: %s\n",
                      codeProgName);
             free((char *)inpbuf);              /* free the space*/
             return(FALSE);
         }
        inpwords=fread((char *)inpbuf,sizeof(int),codelen,pstr);
        if (inpwords != codelen) {
           fprintf(stderr,"Couldn't readin entire pncode\n");
           perror("radardecode");
           free((char *)inpbuf);
           pclose(pstr);                        /* close the stream*/
           return(FALSE);
        }
/*
 *      now move integer numbers to real array, expand if 
 *      if samples/baud > 1 duplicate the values
 *      pad remainder with zeros.
*/
        for (i=0,j=0;i< 2*codelenUsed;i+=(2*samplesPerBaud),j++){
			 for (k=0;k< (samplesPerBaud*2);k+=2) {
                code_buf[i+k]= inpbuf[j];
                code_buf[i+k+1]= 0;             /* imaginary is zero*/
			 }
        }
        for (i=2*codelenUsed;i<(2*lenfft);i+=2){              /* zero to end*/
             code_buf[i]=0.;                    /* real*/
             code_buf[i+1]=0.;                  /* imag*/
        }
        xformdir=-1;
        fftwAo(code_buf,NULL,lenfft,xformdir,1);             /* do the xform*/
#if FALSE
        four1(code_buf-1,lenfft,xformdir);             /* do the xform*/
#endif
        for (i=0;i<lenfft*2;i++){               /* now scale the results*/
            code_buf[i]*=scalefactor;
        }
/*
 *      close pipe, free memory
*/
        if (pclose(pstr) == -1){
            fprintf(stderr,"Error closing pncomp stream\n");
        }
        free((char *)inpbuf);
        return(TRUE);
}
/******************************************************************************/
/*      processargs                                                           */
/******************************************************************************/
void    processargs
	(
	 int     argc,
	 char    **argv,
	 int     *codelen,
	 int     *lenfft,
	 int     *numcodes_req,
	 int     *quiet,                         /* run quietly*/
	 float   *offset,        
	 int     *bits,
	 int     *timeout,
	 int	*samplesPerBaud,
	 int	 *removeDc,
	 int	 *inputType,
	 float   *freqShift,
	 int     *debug_clip,
	 int	 *pnumPol,
	 int	 *ppolToUse, 
	 char    *codeProgName
	)
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
#define getval(a) if (--argc >0){\
                     a=*++argv;}\
                  else {\
                     goto errout;}

        char    *optarg;
        char c;                         /* Option letter returned by getopt*/

        char *USAGE =
"Usage: radardecode -b bits -c codelen -l lenfft -n numcodes -o offset -q -t -d \
 -s smp/Baud -r (removeDc) -m {ri cbr pfs floats bytes} \
 -a codeProgName (-f freqShiftBins notyet)";


        *quiet = 0;
/* 
        loop over all the options in list
*/
	    strcpy(codeProgName,PRGNAME_PNCODE);/* default progam */
        while ((--argc>0) && ((*++argv)[0] == '-')){ 
          c = argv[0][1];
          switch (c) {
          case 'a':
                   getval(optarg);
				   strncpy(codeProgName,optarg,131);
				   codeProgName[131]=0;
                   break;
          case 'b':
                   getval(optarg);
                   sscanf(optarg,"%d",bits);
                   break;
          case 'l':
                   getval(optarg);
                   sscanf(optarg,"%d",lenfft);
                   break;
          case 'c':
                   getval(optarg);
                   sscanf(optarg,"%d",codelen);
                   break;
          case 'd':
                   *debug_clip= TRUE;
                   break;
          case 'n':
                   getval(optarg);
                   sscanf(optarg,"%d",numcodes_req);
                   break;
          case 'o':
                   getval(optarg);
                   sscanf(optarg,"%f",offset);
                   break;
          case 's':
                   getval(optarg);
                   sscanf(optarg,"%d",samplesPerBaud);
                   break;
          case 'q':
                   *quiet = TRUE;
                   break;
          case 'r':
                   *removeDc = TRUE;
                   break;
          case 't':
                   *timeout = TRUE;
                   break;
          case 'f':
                   getval(optarg);
                   sscanf(optarg,"%f",freqShift);
                   break;
          case 'm':
                   getval(optarg);
				   if ( strncmp(optarg,"floats",6) == 0) {
						*inputType=INPTYPE_UNPACKED;
				   } else if ( strncmp(optarg,"ri",2) == 0) {
						*inputType=INPTYPE_RI;
				   } else if ( strncmp(optarg,"cbr",3) == 0) {
						*inputType=INPTYPE_CBR;
				   } else if ( strncmp(optarg,"pfs",3) == 0) {
						*inputType=INPTYPE_PFS;
				   } else if ( strncmp(optarg,"bytes",5) == 0) {
						*inputType=INPTYPE_BYTES;
				   } else {
					    goto errout;
				   }
                   break;
          case 'p':
                   getval(optarg);
                   sscanf(optarg,"%d",pnumPol);
				   if ((*pnumPol < 1 ) || (*pnumPol > 2) ) goto errout;
                   getval(optarg);
                   sscanf(optarg,"%d",ppolToUse);
				   if ((*ppolToUse < 1 ) || (*ppolToUse > 2) ) goto errout;
                   break;
          default:                      /*if c not in myoptions, getopt rets ?*/
             goto errout;
          }
        }
        if ((*lenfft) < (2 * (*codelen)*(*samplesPerBaud))) {
           fprintf(stderr,"length of fft %d must be > 2*codelenUsed: %d\n",
			*lenfft, 2*(*codelen)*(*samplesPerBaud));
           goto errout;
        }
        return;
/*
        here if illegal option or argument
*/
errout: fprintf(stderr,"%s\n",rcsid);
        fprintf(stderr,"%s\n",USAGE);
        exit(1);
        /*NOTREACHED*/
}
/*****************************************************************************
*unpcbr - unpack the cbr data                                           
*
* unpack the cbr data. assumes it's 2 bits. will return one channel only.
*/
void unpcbr (
	int		bytesInp,		/* in buffer to unpack*/
	int		numPol,
	int		polToUse,
	unsigned char *packedBuf, /* buffer to unpack*/
	float	*punpackedBuf
	)
{
	int i;
	if (numPol == 2) {
		if (polToUse == 1) {
			for (i=0;i<bytesInp;i++ ) {
				unpCbrCh1(packedBuf[i],punpackedBuf,lkupCbrF);
			}
		} else {
			for (i=0;i<bytesInp;i++ ) {
				unpCbrCh2(packedBuf[i],punpackedBuf,lkupCbrF);
			}
		}
	} else {
		for (i=0;i<bytesInp;i++ ) {
			unpCbrCh1chn(packedBuf[i],punpackedBuf,lkupCbrF);
		}
	}
	return;
}

/*****************************************************************************
*unppfs - unpack the pfs data                                           
*
* unpack the pfs data. 
*/
void unppfs (
	int		bytesInp,	/* in buffer to unpack*/
	int             bits,		/* quantization */
	int		numPol,
	int		polToUse,
	unsigned char  *packedBuf, /* buffer to unpack*/
	float	       *punpackedBuf
	)
{
  int j;
  int nsamples = bytesInp * 4 / bits / numPol;

  if (numPol == 1) 
    switch (bits)
      {
      case  2: unpack_pfs_2c2b(packedBuf, rcp, bytesInp); break;
      case  4: unpack_pfs_2c4b(packedBuf, rcp, bytesInp); break;
      case  8: unpack_pfs_2c8b(packedBuf, rcp, bytesInp); break;
      default: fprintf(stderr,"Unknown value for quantization mode\n"); 
	       exit(-1);
      }
  else
    if (polToUse == 1)
      {
	if (bits == 2)
	  unpack_pfs_4c2b_rcp(packedBuf, rcp, bytesInp); 
	else
	  unpack_pfs_4c4b_rcp(packedBuf, rcp, bytesInp); 
       }
    else
      {
	if (bits == 2)
	  unpack_pfs_4c2b_lcp(packedBuf, rcp, bytesInp); 
	else
	  unpack_pfs_4c4b_lcp(packedBuf, rcp, bytesInp); 
      }

  for (j = 0; j < 2*nsamples; j++)
      punpackedBuf[j]   = (float) rcp[j];

  return;
}
/*****************************************************************************
*unpbytes - unpack 8 bit quantities
*
* unpack bytes
*/
void unpbytes (
	int		bytesInp,	/* in buffer to unpack*/
	unsigned char *packedBuf, /* buffer to unpack*/
	float	*punpackedBuf
	)
{
  int i;
  for (i = 0; i < bytesInp; i++)
    punpackedBuf[i] = (float) packedBuf[i];

  return;
}

