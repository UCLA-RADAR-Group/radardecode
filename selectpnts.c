#include        <stdio.h>
#include        <fcntl.h>
#include        <malloc.h>
#include <unistd.h>
#include <tarLib.h>
#include <philLib.h> 
#include	<errno.h>
 

#define STDOUT 1
#define  min(a,b)   ( (a) < (b) ? (a) : (b) )
#define  BUFSIZE        4096
#define  movebytes(numbytes,inp,out) \
         { int i; for(i=0;i<numbytes;i++) out[i] = inp[i];}

void    processargs(int argc,char **argv,int *bytes_per_pnt,int *first_pnt,
				int *pnts_in_grp,int *pnts_in_ipp);

/* revision control variable */
static char const rcsid[] = 
"$Id$";

int main(int argc,char **argv)
{
/*
 *      select points from the input stream, write to output stream 
 *      
 *       selectpnts -f firstpt -b bytesperpnt -g ptsingrp -s sizeofskip 
 *
 *      -b  bytes in point. default = 4
 *      -f  first point to start with (def = 1)
 *      -g  points in group. output g continuous points (def 1)
 *      -s  points to skip (points in ipp).
*/
        int     bytes_per_pnt;          /* bytes one point*/
        int     first_pnt;                      /*start here*/
        int     pnts_in_grp;                    /* to move together*/
        int     bytes_in_grp;                   
        int     pnts_in_ipp;                    /* rep spacing*/
        int     bytes_in_ipp;   
        
        int     bytes_inp_req;                  /* we want to read*/ 
        int     bytes_inp;                      /* actually read*/      
        int     ipp_inp_req;                    /* how many ipps we want*/
        int     ipp_out_req;                    /* before output.*/  
        int     bytes_out;
        int     bytes_out_req;
        int     inp_per_out;                    /* reads for each write*/
/*
 *      buffers
*/
        char    *inp_buf;                       /* input buffer*/
        char    *out_buf;                       /* output*/
        char    *iptr,*optr;                    /* input,output ptrs*/

        int     bytes_to_skip;  
        int     inrec; 
		int		fdOut;

/*
 *      setup the defaults
*/
		fdOut=1;
        bytes_per_pnt = 4;                      /* 4 bytes/point*/
        first_pnt = 1;                          /* counting starts at 1*/
        pnts_in_grp=1;                          /* move 1 point*/
        pnts_in_ipp=1;                          /* 1 will move inp to out*/
		optr=NULL;
/*
 *      get the parameters
*/
        processargs(argc,argv,&bytes_per_pnt,&first_pnt,&pnts_in_grp,
                    &pnts_in_ipp);
/*
 *      compute bytes, bufsizes. make them about BUFSIZE long
*/
        bytes_in_grp = pnts_in_grp * bytes_per_pnt;     
        bytes_in_ipp = pnts_in_ipp * bytes_per_pnt;

        ipp_inp_req  = BUFSIZE / bytes_in_ipp;          
        ipp_inp_req  = (ipp_inp_req == 0)? 1 : ipp_inp_req;/* at least 1*/
        bytes_inp_req= ipp_inp_req * bytes_in_ipp;

/*
 *      make output req a multiple of the ipps for input
*/
        ipp_out_req =  BUFSIZE / bytes_in_grp;          /* till output*/
        ipp_out_req =  ipp_out_req == 0 ? 1 : ipp_out_req;
        ipp_out_req =  ((ipp_out_req + ipp_inp_req - 1) / ipp_inp_req) *
                       ipp_inp_req;
        inp_per_out =  ipp_out_req/ipp_inp_req; 
        bytes_out_req = ipp_out_req * bytes_in_grp;
/*
 *      allocate buffers
*/
        inp_buf = (char *)calloc((unsigned)bytes_inp_req,sizeof(char));
        if (inp_buf == NULL){
            perror("selectpnts: Allocating input buffer");
			goto errout;
        }
        out_buf = (char *)calloc((unsigned)bytes_out_req,sizeof(char));
        if (out_buf == NULL){
            perror("selectpnts: Allocating output buffer");
			goto errout;
        }
/* 
 *      discard beginning points that they don't want
*/
        bytes_to_skip =(first_pnt - 1)*bytes_per_pnt;   
        while (bytes_to_skip > 0){
             bytes_inp = min(BUFSIZE,bytes_to_skip);
             bytes_inp = read_pipe(inp_buf,bytes_inp);
             if (bytes_inp == 0) goto done;                /* hit eof*/
             bytes_to_skip-=bytes_inp;
        }
/*
 *      loop till done
*/
        for (;;){                               /* till hit eof*/
/*
 *         loop till we fill up an output buffer
*/
            for (optr=out_buf,inrec=0;inrec< inp_per_out;inrec++){      
/*
 *              input a buffer
*/
                bytes_inp = read_pipe(inp_buf,bytes_inp_req);
                if (bytes_inp == 0) goto done;  /* hit eof*/
                if (bytes_inp < 0) {
				   fprintf(stderr,
				   "selectpnts: inp error. bytes req:%d ,read:%d..error:%x\n",
						bytes_inp,bytes_inp_req,errno);
				   goto errout;
                }
                for (iptr=inp_buf;iptr<inp_buf+bytes_inp;iptr+=bytes_in_ipp){
                    movebytes(bytes_in_grp,iptr,optr);
                    optr+=bytes_in_grp;
                }
            }
/*
 *          now output the data
*/
            bytes_out_req = optr - out_buf;
			if (fdOut != STDOUT){
				fprintf(stderr,
				"selectpnts internal error. fdOut:%d, stdout:%d\n",
						fdOut,STDOUT);
				goto errout;
			}
            bytes_out = write(fdOut,out_buf,bytes_out_req);
            if (bytes_out_req != bytes_out){
               fprintf(stderr,
               "selectpnts: output error. bytes out %d\n",bytes_out);
               goto errout;
            }
        }
done:   if (optr > out_buf) {           /* partial record to output*/
            bytes_out_req = optr - out_buf;
            bytes_out = writen(STDOUT,out_buf,bytes_out_req);
            if (bytes_out_req != bytes_out){
               fprintf(stderr,
               "selectpnts: output error. bytes out %d\n",bytes_out);
               goto errout;
            } 
         }
        exit(0);
errout: fprintf(stderr,"\n");
 		fflush(stderr);
		exit(-1);
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
int     *first_pnt,
int     *pnts_in_grp,
int     *pnts_in_ipp)
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
        char  *myoptions = "f:b:g:s:";  /* options to search for. :--> needs
                                            an argument*/
        char *USAGE =
        "Usage: selectpnts -b byte/pnt -f firstpnt -g pntingrp -s skippnts";

        opterr = 0;                             /* turn off there message*/
/* 
        loop over all the options in list
*/
        while ((c = getopt(argc,argv,myoptions)) != -1){ 
          switch (c) {
          case 'b':
                   sscanf(optarg,"%d",bytes_per_pnt);
                   break;
          case 'f':
                   sscanf(optarg,"%d",first_pnt);
                   break;
          case 'g':
                   sscanf(optarg,"%d",pnts_in_grp);
                   break;
          case 's':
                   sscanf(optarg,"%d",pnts_in_ipp);
                   break;
          case '?':                     /*if c not in myoptions, getopt rets ?*/
             goto errout;
             break;
          }
        }

        if (*pnts_in_grp > *pnts_in_ipp){
           fprintf(stderr,"Points in group %d must be <= points to skip %d\n",
                *pnts_in_grp,*pnts_in_ipp);
           goto errout;
        }
        return;
/*
        here if illegal option or argument
*/
errout: fprintf(stderr,"%s\n",rcsid);
        fprintf(stderr,"%s\n",USAGE);
        exit(1);
}
