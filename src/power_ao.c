#include        <stdio.h>
#include        <stdlib.h>
#include        <fcntl.h>
#include        <math.h>
#include    <unistd.h>
#include    <philLib.h>
/*
 *                         Filter to compute logarithm of input data
 *
 *    call 
 *
 *    power_ao compute power of input data. 
 *
 *  data input is r*4
 *
 *
*/
#define STDINP     0
#define STDOUT     1
#define ISAPIPE    1
#define PRGID      "power_ao"
#define TRUE       1
#define FALSE      0
#ifndef MAX 
#define MAX(a,b)  ((a>b)?a:b)
#endif
#ifndef MIN
#define MIN(a,b)  ((a<b)?a:b)
#endif

int main(int argc,char **argv)
{
        float    inbuf[4096];
        float    outbuf[4096];
        int      inpbufbytes;   
        int      wordsinput;
        int      numbytes;                              /* read in*/
        int     bytes_out;
        int     i,j,bytesout;

        inpbufbytes = 4096;
        for (;;){
/*
 *      input a record 
*/
                if (!(numbytes=read_pipe((char *)inbuf, inpbufbytes)))
                   goto done;  
                wordsinput = numbytes / 4;
                for (i=0,j=0;i< wordsinput;i+=2,j++){
                    outbuf[j]=inbuf[i]*inbuf[i] + inbuf[i+1]*inbuf[i+1];
                }
                bytesout= numbytes/2;
                bytes_out=write(STDOUT,(char *)outbuf,bytesout);
                if (bytes_out != bytesout){
                   fprintf(stderr,"power_ao: output bytes != input bytes\n");
                   exit(-1);
                }
        }
done:   exit(0);
        /*NOTREACHED*/
}    
