#include	    <stdlib.h>
#include        <stdio.h>
#include        <fcntl.h>
#include        <malloc.h>
#include        <unistd.h>
#include        <philLib.h>
 
#define STDOUT 1
#define  min(a,b)   ( (a) < (b) ? (a) : (b) )
#define  max(a,b)   ( (a) > (b) ? (a) : (b) )

void    processargs(int argc,char **argv,int *bytes_per_pnt,int *pnts_in_inp,
					int  *pnts_in_out,int *pnozerfill);

int main(int argc,char **argv) 
{
/*
 *      
 *       zerofill -b bytesperpnt -i inppoints -o outputpnts -n
 *
 *      input inppoints at a time, output outputpnts.
 *      if outputpnts > inputpnts, pad with zeros.
 *
 *      -b  bytes in point. default = 4
 *      -i  points in input
 *      -o  points in output
 *      -n  no zero fill, throw away fractional buffer
 *history:
 * 13apr00 - added -n option
*/
        int     bytes_per_pnt;          /* bytes one point*/
        int     pnts_in_inp;                    /* rep spacing*/
        int     pnts_in_out;                    /* rep spacing*/
        int     floats_in_inp;
        int     floats_in_out;                  /* floats in output*/
		int		noZeroFill;
        
        int     bytes_in_buf;           /* to allocate*/
        int     bytes_inp_req;                  /* we want to read*/ 
        int     bytes_inp;                      /* actually read*/      
        int     bytes_out;
        int     bytes_out_req;
/*
 *      buffers
*/
        char    *buf;                           /* input buffer*/
        float   *fptr;

        int     i; 

/*
 *      setup the defaults
*/
        bytes_per_pnt = 4;                      /* 4 bytes/point*/
        pnts_in_inp=1;                          /* move 1 point*/
        pnts_in_out=1;                          /* 1 will move inp to out*/
/*
 *      get the parameters
*/
        processargs(argc,argv,&bytes_per_pnt,&pnts_in_inp, &pnts_in_out,
					&noZeroFill);
/*
 *      compute bytes, bufsizes. make them about BUFSIZE long
*/
        bytes_inp_req = pnts_in_inp * bytes_per_pnt;    
        bytes_out_req = pnts_in_out * bytes_per_pnt;
        bytes_in_buf=max(bytes_inp_req,bytes_out_req);
        floats_in_out=bytes_out_req/sizeof(float);
/*
 *      allocate buffers
*/
        buf = (char *)calloc((unsigned)bytes_in_buf,sizeof(char));
        if (buf == NULL){
            perror("zerofill: Allocating input buffer");
            exit(-1);
        }
        fptr=(float *)buf;
/*
 *      loop till done
*/
        for (;;){                               /* till hit eof*/
/*
 *              input a buffer
*/
            bytes_inp = read_pipe(buf,bytes_inp_req);
            if (bytes_inp == 0) goto done;      /* hit eof*/
            if (bytes_inp < 0) {
                   perror("zerofill: inputing data");
                   exit(-1);
            }
			if  ((bytes_inp < bytes_inp_req) && noZeroFill) goto done;
            floats_in_inp=bytes_inp/sizeof(float);
            for (i=floats_in_inp;i< floats_in_out;i++)fptr[i]=0.;
/*
 *          now output the data
*/
            bytes_out = write(STDOUT,buf,bytes_out_req);
            if (bytes_out_req != bytes_out){
               fprintf(stderr,
               "zerofill: output error. bytes out %d\n",bytes_out);
               exit(-1);
            }
        }
done:   exit(0);
        /*NOTREACHED*/
}       
/******************************************************************************/
/*      processargs                                                           */
/******************************************************************************/
void    processargs
(
int     argc,
char    **argv,
int     *bytes_per_pnt,
int     *pnts_in_inp,
int     *pnts_in_out,
int	    *pnoZeroFill)
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
        char  *myoptions = "b:i:o:n";    /* options to search for. :--> needs
                                            an argument*/
        char *USAGE =
        "Usage: zerofill -n{nozerofill} -b byte/pnt  -i pntinInp -o pntinOut";

        opterr = 0;                             /* turn off there message*/
		*pnoZeroFill=0;
/* 
        loop over all the options in list
*/
        while ((c = getopt(argc,argv,myoptions)) != -1){ 
          switch (c) {
          case 'n':
                   *pnoZeroFill=1;
                   break;
          case 'b':
                   sscanf(optarg,"%d",bytes_per_pnt);
                   break;
          case 'i':
                   sscanf(optarg,"%d",pnts_in_inp);
                   break;
          case 'o':
                   sscanf(optarg,"%d",pnts_in_out);
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
