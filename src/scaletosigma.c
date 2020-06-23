#include        <stdio.h>
#include        <stdlib.h>
#include        <fcntl.h>
#include        <string.h>
#include        <math.h>
#include <unistd.h>
#include <philLib.h> 
 

/*
 *                         Filter to scale input map to units of sigma.
 *              will remove offset and the scale to sigma
 *
 *    call 
 *
 *    scaletosigma  -r rows -c cols -f firstpnt -l lastpnt -t logfile
 *
 *    -r number of rows in map
 *    -c number of cols in map
 *    -f first pnt in ipp(row) to use for sigma
 *    -l last pnt in ipp (row) to use for sigma
 *    -F first row to use .. count from 1 def 1
 *    -L last row to use .. count from 1  def numrows
 *    -t temp filename. if t option write
 *       avg  num
 *       sigma num
 *       to the first two lines of logfile. These are the offset and scaling
 *       that is used with the data.
 *
 *
 *  The data type for input is hardcoded to r4
 *
 * history: 
 *
*/
#define STDINP     0
#define STDOUT     1
#define PRGID      "scaletosigma"
#define TRUE       1
#define FALSE      0
#ifndef MAX
#define MAX(a,b)  ((a>b)?a:b)
#endif
#ifndef MIN
#define MIN(a,b)  ((a<b)?a:b)
#endif

void    processargs(int argc,char **argv,int *numrows,int *numcols,
				int *firstcol,int *lastcol,int *firstRow,int *lastRow,char **logfile);

int main(int argc,char **argv)
{
        int     numrows;        /* number of rows*/
        int     numcols;        /* number of cols*/
        int     firstcol,lastcol;       /* when computing sigma*/
		int	    firstRow,lastRow;	
        int     colsused;
        int     rowsused;
        int     wordsused;              /* for avg*/
        int     bytesperpnt;            /* bytes in a real*/
        float   *in_buf,*fptr;
        char    *logfile;               /* hold logfile name*/
        FILE    *pfile;                 /* for log file*/
        int     inbufbytes;     
        int     bytesout;               /* actually written*/
        int     numbytes;                               /* read in*/
        int     numwords;
        double  dsum;
        double  dsumsq;
        double  dtemp;
        double  davg;
        double  drms;
        double  dinvrms;
        int     i,j;

        numrows=32;                     /* default*/
        numcols=32;                     /* default*/
        firstcol=-1;
        lastcol =-1;
		firstRow= -1;
		lastRow=  -1;
        logfile=" ";                    /* init to a blank*/
        bytesperpnt=4;                  /* in case we change later on*/
/*
 *      get the parameters
*/
        processargs(argc,argv,&numrows,&numcols,&firstcol,&lastcol,&firstRow,&lastRow,&logfile);
/*
 *      allocate input buffer...
*/
	    if (firstRow < 0 ) firstRow=1;
	    if (firstcol < 0 ) firstcol=1;
	    if (lastRow < 0 )  lastRow=numrows;
	    if (lastcol < 0 )  lastcol=numcols;
        numwords=numrows*numcols;
        inbufbytes=bytesperpnt*numwords;
        if ((in_buf=(float *)malloc(inbufbytes)) == NULL){
             perror("scaletosigma: allocating input buffer");
             exit(1);
        }

        dsum = 0;
        dsumsq = 0.; 
        colsused = lastcol - firstcol + 1;
		rowsused = lastRow - firstRow + 1;
        wordsused=colsused*rowsused;
/*
 *      input the map 
*/
        numbytes=read_pipe((char *)in_buf,inbufbytes);
        if (numbytes != inbufbytes){
                   perror("scaletosigma:map too small");
                   exit(1);
        }
/*
 *      compute avg;rms
*/
        for (i=firstRow-1;i< lastRow;i++){
            fptr=in_buf + i*numcols + firstcol - 1;
            for (j=0;j<colsused;j++,fptr++){
                dtemp= *fptr;
                dsum+=dtemp;
                dsumsq = (dtemp*dtemp) + dsumsq;
            }
        }
        davg = dsum/((double)(wordsused));
        dtemp =  (dsumsq  - ((double)(wordsused)*davg*davg))/
                  ((double)(wordsused - 1));
        if (dtemp > 0.) {
           drms = sqrt(dtemp);
        }
        else {
           drms = 0.;
           fprintf(stderr,"rms computation sqrt <=0.");
           exit(1);
        }
        dinvrms=1./drms;
/*
 *      now remove mean and scale
*/
        for (i=0;i<numwords;i++){
            in_buf[i]= (in_buf[i] - davg) * dinvrms;
        }
        if ((bytesout=write(STDOUT,in_buf,inbufbytes)) != inbufbytes){
           perror("Scaletosigma. write error");
           exit(1);
        }
/*
 *      if they gave a filename, open it and output avg, and sigma on two
 *      lines.
*/
        if (logfile[0] != ' '){
           if ((pfile=fopen(logfile,"w")) == NULL){
               perror("Scaletosigma:opening logfile");
               exit(1);
           }
           fprintf(pfile,"avg %f\n",davg);
           fprintf(pfile,"sig %f\n",drms);
        }
        exit(0);
}
/******************************************************************************/
/*    process args                                                            */
/******************************************************************************/
void    processargs
(
int     argc,
char    **argv,
int     *numrows,
int     *numcols,
int     *firstcol,
int     *lastcol,
int     *firstRow,
int     *lastRow,
char    **logfile)
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
        void to_lowercase();

        int c;                          /* Option letter returned by getopt*/
        char  *myoptions = "r:c:f:l:t:F:L:"; /* options to search for. :--> needs
                                            an argument*/
char *USAGE =
"Usage: scaletosigma -r numrows -c numcols -f firstcol -l lastcol \n                    -F firstRow -L lastRow  -t tmpfile";

        opterr = 0;                             /* turn off there message*/
/* 
        loop over all the options in list
*/
        while ((c = getopt(argc,argv,myoptions)) != -1){ 
          switch (c) {
          case 'r':
                   sscanf(optarg,"%d",numrows);   
                   break;
          case 'c':
                   sscanf(optarg,"%d",numcols);   
                   break;
          case 'f':
                   sscanf(optarg,"%d",firstcol);   
                   break;
          case 'l':
                   sscanf(optarg,"%d",lastcol);   
                   break;
          case 'F':
                   sscanf(optarg,"%d",firstRow);   
                   break;
          case 'L':
                   sscanf(optarg,"%d",lastRow);   
                   break;
          case 't':
                   *logfile=optarg;
                   break;
          case '?':                     /*if c not in myoptions, getopt rets ?*/
             goto errout;
             break;
          }
        }
        return ;
/*
 *      here if error occured
*/
errout: ;
        fprintf(stderr,"%s\n",USAGE);
        exit(1);
}
