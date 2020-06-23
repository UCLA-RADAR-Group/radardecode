#include        <stdio.h>
#include        <stdlib.h>
#include        <fcntl.h>
#ifdef __APPLE__
#include        <malloc/malloc.h>
#else
#include        <malloc.h>
#endif
#include <unistd.h>
#include <philLib.h> 
 

#define STDOUT 1
#define  min(a,b)   ( (a) < (b) ? (a) : (b) )
#define  BUFSIZE        4096
#define  movebytes(numbytes,inp,out) \
         { int i; for(i=0;i<numbytes;i++) out[i] = inp[i];}

void    processargs(int argc,char **argv,int *bytes_per_pnt,int *pnts_in_ipp,
                                        int     *pnts_to_rotate);

 int main(int argc,char **argv)
{
/*
 *      Rotate points within ipp.
 *      
 *       rotate  -b bytesperpnt -i ptsinipp -r pointstorotate
 *
 *      -b  bytes in point. default = 4
 *      -i  points in group. length of ipp in points. (def 1)
 *      -r  points to rotate positive is to the right
*/
        int     bytes_per_pnt;          /* bytes one point*/
        int     pnts_in_ipp;                    /* rep spacing*/
        int     bytes_in_ipp;   
        
        int     bytes_inp_req;                  /* we want to read*/ 
        int     bytes_inp;                      /* actually read*/      
        int     bytes_inp_used;                 /* multiple of ipp*/
        int     ipp_inp_req;                    /* how many ipps we want*/
        int     bytes_out;
        int     bytes_out_req;
        int     pnts_to_rotate;
        int     rto1stpos;
        int     rto1stlen;
        int     rfrom1stlen;
        int     rto1stposb,rto1stlenb,rfrom1stlenb;
        int     byteoff1;       
        int     ipps_inp;                       /* we actually input*/
/*
 *      buffers
*/
        char    *inp_buf;                       /* input buffer*/
        char    *out_buf;                       /* output*/
        char    *iptr,*iptr1,*optr;             /* input,output ptrs*/


/*
 *      setup the defaults
*/
        bytes_per_pnt = 4;                      /* 4 bytes/point*/
        pnts_to_rotate=1;
        pnts_in_ipp=1024;
/*
 *      get the parameters
*/
        processargs(argc,argv,&bytes_per_pnt,&pnts_in_ipp,&pnts_to_rotate);
/*
 *      compute bytes, bufsizes. make them about BUFSIZE long
*/
        bytes_in_ipp = pnts_in_ipp * bytes_per_pnt;

        ipp_inp_req  = BUFSIZE / bytes_in_ipp;          
        ipp_inp_req  = (ipp_inp_req == 0)? 1 : ipp_inp_req;/* at least 1*/
        bytes_inp_req= ipp_inp_req * bytes_in_ipp;

/*
 *      compute where rotate values are   
*/
        rto1stpos= (pnts_in_ipp -(pnts_to_rotate-1)) % pnts_in_ipp;
        rto1stlen= (pnts_in_ipp -(rto1stpos - 1));/*continguous pnts*/ 
        rfrom1stlen= pnts_in_ipp - rto1stlen;
        rto1stposb = bytes_per_pnt * rto1stpos;
        rto1stlenb = bytes_per_pnt * rto1stlen;
        rfrom1stlenb=bytes_per_pnt * rfrom1stlen;
        byteoff1= rto1stposb - bytes_per_pnt;   /* since array starts at 0*/
/*
 *      allocate buffers input/output same size
*/
        inp_buf = (char *)calloc((unsigned)bytes_inp_req,sizeof(char));
        if (inp_buf == NULL){
            perror("rotate: Allocating input buffer");
            exit(-1);
        }
        out_buf = (char *)calloc((unsigned)bytes_inp_req,sizeof(char));
        if (out_buf == NULL){
            perror("rotate: Allocating output buffer");
            exit(-1);
        }
/*
 *      loop till done
*/
        for (;;){                               /* till hit eof*/
/*
 *              input a buffer
*/
                bytes_inp = read_pipe(inp_buf,bytes_inp_req);
                if (bytes_inp == 0) goto done;  /* hit eof*/
                if (bytes_inp < 0) {
                   perror("rotate: inputing data");
                   exit(-1);
                }
                ipps_inp=bytes_inp/bytes_in_ipp; /* throw out fract at end*/
                bytes_inp_used=ipps_inp*bytes_in_ipp;
                
                for (iptr=inp_buf,optr=out_buf;iptr<inp_buf+bytes_inp_used;
                     iptr+=bytes_in_ipp){
                    iptr1=iptr+(byteoff1);
                    movebytes(rto1stlenb,iptr1,optr);
                    optr+=rto1stlenb;
                    movebytes(rfrom1stlenb,iptr,optr);
                    optr+=rfrom1stlenb;
                }
/*
 *          now output the data
*/
            if ((bytes_out_req = optr - out_buf) > 0) {
               bytes_out = write(STDOUT,out_buf,bytes_out_req);
               if (bytes_out_req != bytes_out){
                  fprintf(stderr,
                  "rotate: output error. bytes out %d\n",bytes_out);
                  exit(-1);
               }
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
int     *pnts_in_ipp,
int     *pnts_to_rotate)
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
        char  *myoptions = "b:i:r:";    /* options to search for. :--> needs
                                            an argument*/
        char *USAGE =
        "Usage: rotate -b byte/pnt -i pntinipp -r pntstorotate";

        opterr = 0;                             /* turn off there message*/
/* 
        loop over all the options in list
*/
        while ((c = getopt(argc,argv,myoptions)) != -1){ 
          switch (c) {
          case 'b':
                   sscanf(optarg,"%d",bytes_per_pnt);
                   break;
          case 'i':
                   sscanf(optarg,"%d",pnts_in_ipp);
                   break;
          case 'r':
                   sscanf(optarg,"%d",pnts_to_rotate);
                   break;
          case '?':                     /*if c not in myoptions, getopt rets ?*/
             goto errout;
             break;
          }
        }

        if (*pnts_to_rotate >= *pnts_in_ipp){
           fprintf(stderr,"Points to rotate %d must be < points in ipp %d\n",
                *pnts_to_rotate,*pnts_in_ipp);
           goto errout;
        }
        return;
/*
        here if illegal option or argument
*/
errout: fprintf(stderr,"%s\n",USAGE);
        exit(1);
}
