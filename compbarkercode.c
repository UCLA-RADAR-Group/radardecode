/* 
 *      program to compute barker code
 *
 *      comppncode -a -c codelen -b bigvalue -s smallvalue
 *      
 *      -a ascii output. default is i*4 binary. 1 # per line
 *      -c codelen to generate
 *      -s smallval small value to output  def:0 
 *      -b bigvalue to output  def:1 
 *  currently only 13 length code
 *
 *history-
 * 20aug99 copied from comppncode
*/
#include        <stdio.h>
#include        <math.h>
#include        <unistd.h>
#define         TRUE    -1 
#define         FALSE    0
#define         STDOUT   1

/*
 *  functions
*/
void    processargs(int argc,char **argv,int *codenum,int *minval,
					int *maxval,int *asciiout);

/* revision control variable */
static char const rcsid[] = 
"$Id$";

int main(int argc,char **argv)
{
        int     codelen ;               /* codelen generate*/
        int     minval,maxval;          /* for the code we're generating*/
        int     asciiout;       
        int     i,j;      
        int     code[99];

        codelen=13;                   /* default code*/
        minval  = 0;maxval=1;   /* min/max val for code*/       
        asciiout=FALSE;

        processargs(argc,argv,&codelen,&minval,&maxval,&asciiout);
/*
        fprintf(stderr,"numreg: %d, len %d, numfdbk %d fdbak: %d %d %d %d\n",
               code_info.num_reg,code_info.len,code_info.num_fdback,
        code_info.fdback[0],code_info.fdback[1],code_info.fdback[2],
        code_info.fdback[3]);
*/
		switch (codelen)	{
			case 13 :
			/*   5. -2.  2. -1.  1. -1.  1.*/
				i=0;
				for (j=0;j<5;j++) code[i++]=maxval;
				for (j=0;j<2;j++) code[i++]=minval;
				for (j=0;j<2;j++) code[i++]=maxval;
				for (j=0;j<1;j++) code[i++]=minval;
				for (j=0;j<1;j++) code[i++]=maxval;
				for (j=0;j<1;j++) code[i++]=minval;
				for (j=0;j<1;j++) code[i++]=maxval;
				break;
			default:
				fprintf(stderr,"compbarkercode bad code length\n");
				exit(1);
		 }
      if (asciiout) {
         for (i=0;i< codelen;i++)
             printf("%6d\n",code[i]);
      }
      else {
         write(STDOUT,code,4*codelen);
      }
      exit(0);
}
/*****************************************************************************/
/*      process args                                                         */
/*****************************************************************************/
void    processargs
(
int     argc,
char    **argv,
int     *codelen,                               /* 7*/
int     *minval,
int  	*maxval,                        /* min/max for code*/
int     *asciiout)                              /* output in ascii*/
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
        char  *myoptions = "ac:s:b:";      /* options to search for. :--> needs
                                            an argument*/
         char *USAGE =
        "Usage: comppncode [-ascii] [-c codelen] [-s ismallval] [-b ibigval]";
 

        opterr = 0;                             /* turn off there message*/
/*
        loop over all the options in list
*/
        while ((c = getopt(argc,argv,myoptions)) != -1){
          switch (c) {
          case 'a':
                   *asciiout = TRUE;    
                   break;
          case 'c':
                   sscanf(optarg,"%d",codelen);  /* code to use*/
                   if (*codelen !=13) goto errout;
                   break;
          case 's':
                   sscanf(optarg,"%d",minval);   /* new min value*/
                   break;
          case 'b':
                   sscanf(optarg,"%d",maxval);    /* new max value*/
                   break;
          case '?':                     /*if c not in myoptions, getopt rets ?*/             goto errout;
             break;
          }
        }
        return;
/*
        here if illegal option or argument
*/
errout: fprintf(stderr,"%s\n",rcsid);
        fprintf(stderr,"%s\n",USAGE);
        exit(1);
} 
