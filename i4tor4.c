#define STDIN 0
#define STDOUT 1
#include <stdio.h>
#include <stdlib.h>
#include	<unistd.h>

void    processargs(int argc,char **argv,int *quiet);

int main(int argc,char **argv)
{
/*      filter to convert from integer*4 to real*4
        input taken from standard input
        output sent to standard out
        - this routine handy if you want to use read unformatted
          within analyz (since can only read real*8 data unformatted)
        
        i4tor4 -q
*/
        int  inbuf[1000];
        float outbuf[1000];
        int  bytesin;
        int  bytesout;
        int  wordsin;   
        int  totalnumbers;      
        int i;
        int quiet;


        processargs(argc,argv,&quiet);
        totalnumbers=0; 
        for (;;){
                if ((bytesin=read(STDIN,(char *)inbuf,4000))<=0) break;         
                wordsin=bytesin/4;
                totalnumbers+=wordsin;
                for (i=0;i<wordsin;i++)         
                   outbuf[i]=inbuf[i];
                bytesout=write(STDOUT,(char *)outbuf,wordsin*4);
        }
        if (!quiet)
        fprintf(stderr,"%d numbers converted integer*4 to real*4\n",
                totalnumbers);  
        exit(0);
        /*NOTREACHED*/
}
/******************************************************************************/
/*    process args                                                            */
/******************************************************************************/
void    processargs(int argc,char **argv,int *quiet) 
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
        extern int opterr;              /* if 0, getopt won't output err mesg*/
        void to_lowercase();

        int c;                          /* Option letter returned by getopt*/
        char  *myoptions = "q"; /* options to search for. :--> needs
                                            an argument*/
char *USAGE = "Usage: i4tor4 -q";

        opterr = 0;                             /* turn off there message*/
        *quiet = 0;
/* 
        loop over all the options in list
*/
        while ((c = getopt(argc,argv,myoptions)) != -1){ 
          switch (c) {
          case 'q':
                   *quiet = 1;          /* they want it quiet*/
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
