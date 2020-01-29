#include        <stdio.h>
#include		<stdlib.h>
#include        <fcntl.h>
#include        <malloc.h>
#include		<unistd.h>
#include		<fftw3.h>
#include	    <math.h>
#include		<philLib.h>
 
#define STDOUT 1
#define TRUE 1
#define FALSE 0
#define  dmod(a,b)  ( (a) - (b)*(int)((a)/(b)))
#define  max(a,b)  ( (a) > (b) ? (a) : (b) )


typedef struct {
	int		lenfft;			/* transform len .cmpl numbers*/
	int		numbins;		/* number of range bins */
	int		numBlksInp;	    /* number complete blocks we have input*/
	float   fractLastFft;	/* 0.. 1.. numpnts/lenfft*/
	char 	*pinpBuf;		/* point to input buf*/
	float	*inpBlk;		/* holds input data, fft output*/
	float	*fftBlk;		/* holds input data, fft output*/
	float	*avgBuf;		/* holds averaged power*/
	int		packed;		    /* 0-no, 1,2,4 bytes integer data*/
	int     cmplxFft;       /* if not 0 then output complex fft data. no power, no averaging, only 1fft*/
	int		bytesInpReq;		/* for input*/
	int		bytesInpBlk;	/* after unpacking*/
	int		bytesOutReq;	/* for output after power*/
    double  tmSmp;          /* time (secs) for 1 sample. only needed if -x usec*/
    double  xoff;           /* apply frequency offset xoff [Hz, assuming 1 s per cmplx sample] during FFT */
	} RDRFFTI;

void    processargs(int argc,char **argv,RDRFFTI *pinfo);
void    swap_freq(float *data, int len);
void    apply_linear_phase(float *data, double freq, double time, 
			double timeint, int nsamples);

int main(int argc,char **argv)
{
/*
 *		transpose input data then compute fft. 
 *		compute the power and then average..
 *		if we have only a partially full fft at the end, throw it 
 *      away unless it is the only block, then we will zero fill it.
 *
 *       radarfft  -c -l lenfft -r numrangebins -p packing -x freqCorHz
 *
 *      -c  output complex fft data. only  one fft*numberRangebins will be output
 *          no power or incoherent averaging will be done. Mainly used to later compute stokes
 *          parameters. (def; output avged power spectra)
 *      -l  len fft (def=1024)
 *      -r  number of range bins in data (def=1000)
 *      -p  packedIntegerData:1,2,or 4 byte integer.(def=assume 4byte float inputs)
 *      -t  time sample (secs) def:1e-6. time for each sample (only required/used if -x used)
 *      -x  freqOffset (hz) to apply to input data. (need to verify that sign of rotation is correct).
 *  history:
 * after 28oct10 see svn log radarfft.c
 * 25may99 - stole from fftfilter
 * 20jun99 - added -p 1,2,4 bytes.. for 1,2,4 byte integer data
 *		     use for decoder input data
 *  5aug99 - converted to fftwAo
 *  1nov99 - fftwAo now has not inplace option.
*/
        int     xformdir;                       /* +/-1*/
		int		blk;
        int     bytes_inp;
		int	    rowLenFlt;					/* row lenght flts before transf*/
//		int	    rowLenPnt;					/* in complex points*/
//		int	    numRowsInp; 				/* in floats*/
		int		numFltPwr;			        /* number of floats power array*/
		float	*pc,*pinp,*pout,*pa;
		int		ih,iv,i;					/* horizontal, veritical in*/
		float	scale;
        int     bytes_out;
		RDRFFTI  info;
		int		firstTime;
		int		*pi;
		short	*psh;
		char    *pch;
		fftwf_plan fftwPlan;

/*
 *      get the parameters
*/
        processargs(argc,argv,&info);
        xformdir = 1; 		/* this is the sign of exponent. called a reverse xform*/
        fftwPlan=fftwf_plan_dft_1d(info.lenfft,
                (fftwf_complex*)info.fftBlk,
                (fftwf_complex*)info.fftBlk,xformdir,FFTW_MEASURE);

		rowLenFlt =info.numbins*2;
//		rowLenPnt =info.numbins; 	/* number complex points*/
//		numRowsInp=info.lenfft;
		numFltPwr =info.numbins*info.lenfft;
		firstTime = 1;

#if FALSE
		fprintf(stderr,
"rowLenflt:%d rowLenPnt:%d numRowsInp:%d numFltPwr:%d\n",
rowLenFlt,rowLenPnt,numRowsInp,numFltPwr);
		fprintf(stderr,
"lenfft:%d numbins:%d bytesInpBlk:%d bytesOutRes%d\n",
info.lenfft,info.numbins,info.bytesInpBlk,info.bytesOutReq);
	    fflush(stderr);
#endif
        for (blk=0;;blk++){
            bytes_inp = read_pipe(info.pinpBuf,info.bytesInpReq);
            if (bytes_inp == 0) goto done;      /* hit eof*/
            if (bytes_inp < 0) {
               perror("fft: inputing data");
               exit(-1);
            }
            if (bytes_inp < info.bytesInpReq) {
			    if (blk != 0) goto done;
				/*
				 * first block, not filled up, zero fill it as float,or int
				*/
				if (info.packed == 0) {		/* floats*/
					for (i=bytes_inp/4;i<(info.bytesInpReq/4);i++){
						info.inpBlk[i]=0.;
					}
				} else {
					for (i=bytes_inp;i<(info.bytesInpReq);i++){
						info.pinpBuf[i]=0;/* 0 as integer*/
					}
				}
            }
			if (info.packed) {
				switch (info.packed) {
					/*
					 * 32 bit int
				 	*/
					case 1:
						pi=(int*)info.pinpBuf;
						for (i=0;i<(info.bytesInpReq/sizeof(int));i++)
							info.inpBlk[i]=pi[i];
						break;
					/*
					 * 16 bit short
				 	*/
					case 2:
						psh=(short*)info.pinpBuf;
						for (i=0;i<(info.bytesInpReq/sizeof(short));i++)
							info.inpBlk[i]=psh[i];
						break;
					case 4:
					/*
					 *  8 bit short
				 	*/
						pch=(char*)info.pinpBuf;
						for (i=0;i<(info.bytesInpReq/sizeof(char));i++)
							info.inpBlk[i]=pch[i];
						break;
				}
			}
			/*
			 * transpose the matrix
			*/
			pout=info.fftBlk;
			for (ih=0;ih < info.numbins;ih++){ /* one for each col*/
			    pinp=info.inpBlk + ih*2;	   /* start of this column*/
				for (iv=0;iv<info.lenfft;iv++){ /* move down a col*/
					*pout++=pinp[0];
					*pout++=pinp[1];
					pinp +=rowLenFlt;
				}
			}
			/*
			* now loop doing the transforms
			*/
			for (i=0,pc=info.fftBlk;i<info.numbins;i++,pc+=info.lenfft*2){
             	if (info.xoff != 0.)
				 apply_linear_phase(pc, info.xoff, 0.0, info.tmSmp, info.lenfft);
             	fftwf_execute_dft(fftwPlan,(fftwf_complex*)pc,(fftwf_complex*)pc);
				/* swap frequencies */
                swap_freq(pc,info.lenfft);
			}
			// if complex fft ,just 1 blk,  no power or averaging.. just leave data in fft buf
			if (info.cmplxFft != 0) {
				blk=1;				// so output message at end is correct.
				break;
			}
			/*
		 	* add the values into average array
			*/
			if (firstTime) {
		    	for (pa=info.avgBuf,pc=info.fftBlk;
				  pa < (info.avgBuf+numFltPwr);pa++,pc+=2){
				  *pa= (*pc)*(*pc) + (*(pc+1)) * (*(pc+1));
			    }
				firstTime=0;
			}
			else {
			 	for (pa=info.avgBuf,pc=info.fftBlk;
				  pa < (info.avgBuf+numFltPwr);pa++,pc+=2){
			   	  *pa= *pa + (*pc)*(*pc) + (*(pc+1)) * (*(pc+1));
				}
			}
		}
		/*
		 * now scale to number of blocks
		*/
		if ((info.cmplxFft == 0 ) && (blk > 1)) {
			scale=1./blk;
			for (pa=info.avgBuf;pa< (info.avgBuf+numFltPwr);pa++){
				*pa= (*pa)*scale;
			}
		}
	/*
 	*      now write out the xform
	*/
done: 
	  if (info.cmplxFft) {
	  	bytes_out = write(STDOUT,(char *)info.fftBlk,info.bytesOutReq);
	  } else {
	  	bytes_out = write(STDOUT,(char *)info.avgBuf,info.bytesOutReq);
	  }
      if (info.bytesOutReq != bytes_out){
               fprintf(stderr,"radarfft: output error. bytes out %d\n",
			   bytes_out);
               exit(-1);
      }
	  if (info.cmplxFft) {
      	fprintf(stderr,"%d blocks of %d lenfft x %d bins xformed and output as complex values\n",
				blk,info.lenfft,info.numbins);
	  } else {
      	fprintf(stderr,"%d blocks of %d lenfft x %d bins xformed and added\n",
				blk,info.lenfft,info.numbins);
	  }
      exit(0);
        /*NOTREACHED*/
}       
/******************************************************************************/
/*  apply_linear_phase                            */
/******************************************************************************/
void apply_linear_phase(float *data, double freq, double time, double timeint, int nsamples)
/* data      data array */
/* freq      linear phase correction, Hz */
/* time      start time of phase correction */
/* timeint   sample period */
/* nsamples  number of complex samples in data array */
{
  /* apply a linear phase correction of freq Hz to the data using the
     sample time spacing timeint
  */
  int i,j;
  float  phase_r, phase_i;  /* real and imag phase components */
  float  data_r, data_i;    /* real and imag data components */
  double phase;         /* phase correction in radians */
  double freq_rad;      /* frequency in rad/sec */
  double t;

  t        = time;
  freq_rad = 2 * M_PI * freq;

  for (i=0, j=1; i<2*nsamples; i+=2, j+=2)
  {
    phase   = freq_rad * t;
    phase_r = (float)cos( phase );
    phase_i = (float)sin( phase );

    data_r = data[i];
    data_i = data[j];

    data[i] = data_r*phase_r - data_i*phase_i;
    data[j] = data_r*phase_i + data_i*phase_r;

    t += timeint;
  }
  return;
}
/******************************************************************************/
/*  swap_freq                                 */
/******************************************************************************/
void swap_freq(float *data, int len)
/* spectrum array from fft */
/* spectrum length, complex words */
{
  /* swaps the location of the + and - frequencies for a continuous
     spectrum, the data array is 2*len samples long
  */
  int i,j;
  float temp;

  for (i=0, j=len; i<len; i++, j++)
    {
      temp    = data[i];
      data[i] = data[j];
      data[j] = temp;
    }

  return;
}
/******************************************************************************/
/*      processargs                                                           */
/******************************************************************************/
void    processargs
        ( 
         int            argc,
         char         **argv,
         RDRFFTI      *pI 
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
        int getopt();                   /* c lib function returns next opt*/ 
        extern char *optarg;            /* if arg with option, this pts to it*/
        extern int opterr;              /* if 0, getopt won't output err mesg*/

        int c;                          /* Option letter returned by getopt*/
        char  *myoptions = "cl:r:p:x:t:";   /* options to search for. :--> needs
                                            an argument*/
        char *USAGE =
"Usage: radarfft  -c -l lenffts -r rangeBins -p packed(1-4) -x freq_offset\n\
                 -c            output complex fft. Only 1 fft, no power or incoherent avgs.\n\
                 -l lenffts    length of fft to use (def=1024).\n\
                 -r rangeBins  number of rangeBins in data (def=1000)\n\
                 -p intPacking type of packed integer data:1,2,4 (def:4byteFloat)\n\
                 -t timeSmp    time sample in secs (def=1e-6). Only needed for -x option\n\
                 -x freqOffHz  frequency correction (hz) to make to the data\n";

        opterr = 0;                             /* turn off there message*/
		pI->lenfft =1024;
		pI->numbins=1000;
		pI->numBlksInp=0;
		pI->packed    =0;
		pI->xoff      =0.;
		pI->cmplxFft  =0.;
		pI->tmSmp     =-1.;
/* 
        loop over all the options in list
*/
        while ((c = getopt(argc,argv,myoptions)) != -1){ 
          switch (c) {
          case 'c':
				   pI->cmplxFft  =1.;
				   break;
          case 'x':
                   sscanf(optarg,"%lf",&pI->xoff);
                   break;
          case 'l':
                   sscanf(optarg,"%d",&pI->lenfft);

                   break;
          case 'r':
                   sscanf(optarg,"%d",&pI->numbins);
                   break;
          case 't':
                   sscanf(optarg,"%lf",&pI->tmSmp);
                   break;
          case 'p':
                   sscanf(optarg,"%d",&pI->packed);
				   if ((pI->packed <0) || (pI->packed > 4)) goto errout;
                   break;
          case '?':                     /*if c not in myoptions, getopt rets ?*/
             goto errout;
             break;
          }
        }
/*
 * xoff requires user to specify time sample
*/
	if ((pI->xoff != 0.) && (pI->tmSmp < 0.)) {
        fprintf(stderr,"Err-->  -x xoff requires you also specify -t tmSmpSec\n");
	    goto errout;
	}
/*
 * compute size of bufs then allocate them
 * input  lenrange*lenfft*size(float)*2(since comples)
*/
		pI->bytesInpBlk=sizeof(float)*2*pI->lenfft*pI->numbins;
		pI->bytesOutReq=(pI->cmplxFft)? pI->bytesInpBlk: pI->bytesInpBlk/2; /* not cmplx /2 since avg i,q)*/
		if ((pI->inpBlk=(float*)malloc(pI->bytesInpBlk)) == NULL) {
			perror("radarfft.. mallocing inputblk buffer");
			goto errout;
		}
		if ((pI->fftBlk=(float*)malloc(pI->bytesInpBlk)) == NULL) {
			perror("radarfft.. mallocing fft buffer");
			goto errout;
		}
		if (pI->cmplxFft == 0) {
			if ((pI->avgBuf=(float*)malloc(pI->bytesOutReq)) == NULL) {
				perror("radarfft.. mallocing avgerage buffer");
				goto errout;
			}
		}
		pI->bytesInpReq=pI->bytesInpBlk;
	 	if (pI->packed == 0){
			pI->pinpBuf=(char*)pI->inpBlk;	/* use same buf*/
		} else {
		   pI->bytesInpReq=pI->bytesInpReq/pI->packed;
		   if ((pI->bytesInpReq*pI->packed)!=pI->bytesInpBlk){
				fprintf(stderr,
				"radarFFt: lenfft*rangebins not divisible by packing:%d\n",
						pI->packed);
				goto errout;
		   }
		   if ((pI->pinpBuf=(char*)malloc(pI->bytesInpReq))==NULL){ 
			perror("radarfft.. mallocing input buf");
			goto errout;
		   }
		}	

        return;
/*
        here if illegal option or argument
*/
errout: fprintf(stderr,"%s\n",USAGE);
        exit(1);
}
