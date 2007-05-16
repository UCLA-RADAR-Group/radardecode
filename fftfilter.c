#include        <stdlib.h>
#include        <stdio.h>
#include        <fcntl.h>
#include        <malloc.h>
#include		<unistd.h>
#define STDOUT 1
#define TRUE 1
#define FALSE 0
#define  dmod(a,b)  ( (a) - (b)*(int)((a)/(b)))
#define  max(a,b)  ( (a) > (b) ? (a) : (b) )

void    processargs(int argc,char **argv,int *pnumpoints,char *xformdirection,
                int *pzerofill,int *pcpntsperfft,int *premoveDc,int *pnumskip);
extern int  read_pipe();
#if FALSE
extern void four1_();
#endif

extern void fftwAo(float *inDat,           /* to xform*/
            float *outDat,          /* NULL if inplace*/
            int lenxform,
            int direction,      /* sign of exponent*/
            int inplace ) ;       /* 1 inplace, 0 no inplace*/


char    xformdirection[2]="f";          /* f forward, r reverse*/
int main(int argc,char **argv)
{
/*
 *      compute complex fourier xform on input data.             
 *      
 *       fftfilter -d direction -n numchannels -z inpntsperxform -s numskip
 *
 *      -d  xform direction . f--> positive exp, r--> neg exp. def f
 *      -n   length of complex xform to do. (def = 1024).
 *      -z   zero fill if less data than requested
 *      -r   remove Dc before xforming
 *      -s skpPnts points to skip at start of data set.
 *  history:
 * 19may94 - switched to acc, added -r option to remove dc
 * 5aug99  - switched to fftwAo routine
 * 01nov99 - fftwAo allows for not inplace..
 * 14may06 - <pjp001> add -s numpnts .. number of points to skip at the 
 *           beginnning of the dataset. This is used by the radar processing
 *           (freq hop). /home/aosun/u2/black/src/fftfilter.c is a copy of 
 *			 this routine with the -s option added. After -s used here, you
 *           should be able to use this version or gregs interchangeably
*/

        int     numpoints;                      /* number of cmplx points*/
        int     xformdir;                       /* +/-1*/
/*
        char    datatype_inp[3]  = "r4";        
*/
        int     rec;    
        int     bytes_inp_req;      
        int     bytes_out_req;      
        int     bytes_buf;
        int     bytes_inp;
        int     bytes_out;
        float   *inp_buf;                       /* input buffer*/
        int     bytes_data_type;                /* 4 if real*4*/
        int     i;
        int     zerofill;
		int		numskip;						/* pnts to skip at start of
												   data set <pjp001>*/
		int		numskipB;						/* bytes to skip*/
        int     cpntsperfft;                    /* to read in before 0 fill*/
        int     fltpntsinp;                     /* number of floats inp*/
        int     removeDc;                       /* removeDc*/
        float   vI,vQ;                          /* i,q value for dc removal*/
        float   *pf;

/*
 *      setup the defaults
*/
        bytes_data_type = 4;                    /* real*4 */
        numpoints=1024;
		numskip=0;								/*<pjp001>*/	
        zerofill=FALSE;
        cpntsperfft=0;
        removeDc=FALSE;
/*
 *      get the parameters
*/
        processargs(argc,argv,&numpoints,xformdirection,&zerofill,
                    &cpntsperfft,&removeDc,&numskip);	 /*<pjp001*/
        xformdir = (xformdirection[0]=='f') ? 1 : -1;
        bytes_inp_req = (zerofill) ?cpntsperfft*bytes_data_type*2 :
                                    numpoints*bytes_data_type*2;
        bytes_out_req = numpoints*bytes_data_type*2; /* for each xform*/
/*
 *      for input buffer read in about 4k or at least 1 full sample
*/
        bytes_buf=max(bytes_inp_req,bytes_out_req);
        inp_buf = (float *)calloc((unsigned)bytes_buf,sizeof(char));
        if (inp_buf == NULL){
            perror("fft: Allocating input buffer");
            exit(-1);
        }
/*
 * 		optionally skip data at the beginning <pjp001> below
*/
		numskipB=numskip*bytes_data_type*2;	
		while (numskipB > 0) {
      		bytes_inp = read_pipe(inp_buf, (numskipB > bytes_buf) ?
            			bytes_buf : numskipB);
      		numskipB -= bytes_inp;
    	}
		
        for (rec=0;;rec++){
            bytes_inp = read_pipe(inp_buf,bytes_inp_req);
            if (bytes_inp == 0) goto done;      /* hit eof*/
            if (bytes_inp < 0) {
               perror("fft: inputing data");
               exit(-1);
            }
            if ((bytes_inp < bytes_inp_req) && (!zerofill)){
                 goto done;
            }
            if (zerofill) {
                fltpntsinp=bytes_inp / 4;
                for (i=fltpntsinp;i< 2*numpoints;i++) inp_buf[i]=0.;/*zero ext*/
            }
            if (removeDc) {
               vI=vQ=0.;
               for (pf=inp_buf;pf < (inp_buf + numpoints*2);){
                 vI+= *pf++;
                 vQ+= *pf++;
               }
               vI/=numpoints;
               vQ/=numpoints;
               for (pf=inp_buf;pf < (inp_buf+ numpoints*2);){
                 *pf++ -=vI;
                 *pf++ -=vQ;
               }
            }
            fftwAo(inp_buf,NULL,numpoints,xformdir,1);
#if FALSE
            four1_(inp_buf,&numpoints,&xformdir);
#endif
/*
 *      now write out the xform
*/
            bytes_out = write(STDOUT,(char *)inp_buf,bytes_out_req);
            if (bytes_out_req != bytes_out){
               fprintf(stderr,"fft: output error. bytes out %d\n",bytes_out);
               exit(-1);
            }
        }
done:   fprintf(stderr,"%d xforms done\n",rec);
        exit(0);
        /*NOTREACHED*/
}       
/******************************************************************************/
/*      processargs                                                           */
/******************************************************************************/
void    processargs
        ( 
         int            argc,
         char         **argv,
         int           *pnumpoints,
         char          *xformdirection,
         int           *pzerofill,
         int           *pcpntsperfft,
         int           *premoveDc,
		 int		   *pnumskip			/* <pjp001>*/
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
        char  *myoptions = "n:d:z:s:r"; /* options to search for. :--> needs
                                            an argument*/
        char *USAGE =
"Usage: fftfilter -n numpnts -d direction(f,r) -z pntinperfft -r (removeDc) -s numskip";

        opterr = 0;                             /* turn off there message*/
/* 
        loop over all the options in list
*/
        while ((c = getopt(argc,argv,myoptions)) != -1){ 
          switch (c) {
          case 'n':
                   sscanf(optarg,"%d",pnumpoints);

                   break;
          case 'd':
                   xformdirection[0]=optarg[0];
                   if (xformdirection[0] == 'F') xformdirection[0]='f';
                   if (xformdirection[0] == 'R') xformdirection[0]='r';
                   if ((xformdirection[0] !='f') && (xformdirection[0] != 'r'))
                       goto errout;
                   break;
          case 'z':
                   *pzerofill=TRUE;
                   sscanf(optarg,"%d",pcpntsperfft);
                   break;
         case 's':
                   sscanf(optarg,"%d",pnumskip);
                   break;
          case 'r':
                   *premoveDc=TRUE;
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
        exit(1);
}
