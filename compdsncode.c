/* 
 *      program to compute pn shiftregister codes:
 *
 *      comppncode -a -c codelen -b bigvalue -s smallvalue
 *      
 *      -a ascii output. default is i*4 binary. 1 # per line
 *      -c codelen to generate
 *      -s smallval small value to output  def:0 
 *      -b bigvalue to output  def:1 
 *
 *      note that the array indices are used 1 to MAXCODES. 
 *      we dimension the array to be MAXCODES+1 and ignore shiftreg[0] 
 *history-
 * fix code length 15,511 .. feed back position was wrong
 * jlm adapted for DSN codes, added code 2^17-1
*/
#include        <stdio.h>
#include        <math.h>
#include        <unistd.h>
#define         MAXCODES 17
#define         MAXLENCODE 131071
#define         TRUE    -1 
#define         FALSE    0
#define         STDOUT   1

struct  codeinfo {
        int     num_reg;                /* registers for this code*/
        int     len;                    /* length of code*/ 
        int     num_fdback;             /* number feed backs this code*/
        int     fdback[4];              /* feed backs for this code*/
        } code_info;  

/*
 *  functions
*/
int 	shiftit(int num_reg,int num_fdback,int fb1,int fb2,int fb3,int fb4,
			int *shiftreg);
void  	initarray(struct codeinfo *code_info,int codenum);
void    processargs(int argc,char **argv,int *codenum,int *minval,
					int *maxval,int *asciiout);

/* revision control variable */
static char const rcsid[] = 
"$Id$";

int main(int argc,char **argv)
{
        int     codenum ;               /* code to generate*/
        int     minval,maxval;          /* for the code we're generating*/
        int     asciiout;       
        int     i;      
        int     shiftreg[MAXCODES+1];   
        int     code[MAXLENCODE];

        codenum = 10;                   /* default code*/
        minval  = 0;maxval=1;   /* min/max val for code*/       
        asciiout=FALSE;

        processargs(argc,argv,&codenum,&minval,&maxval,&asciiout);
/*
 *      initialize our array
*/      
        initarray(&code_info,codenum);

        fprintf(stderr,"numreg: %d, len %d, numfdbk %d fdbak: %d %d %d %d\n",
               code_info.num_reg,code_info.len,code_info.num_fdback,
        code_info.fdback[0],code_info.fdback[1],code_info.fdback[2],
        code_info.fdback[3]);

 
        for (i=1;i<=code_info.num_reg;i++){
          shiftreg[i]=FALSE; 
        }
      for (i=1;i<= code_info.len;i++){
        if (shiftit(code_info.num_reg,code_info.num_fdback,
                  code_info.fdback[0],code_info.fdback[1],code_info.fdback[2],
                  code_info.fdback[3],shiftreg)){
             code[i]=maxval;
        }
        else {   
             code[i]=minval;
        }
      }
      if (asciiout) {
         for (i=1;i<= code_info.len;i++)
             printf("%6d\n",code[i]);
      }
      else {
         write(STDOUT,&code[1],4*code_info.len);
      }
      exit(0);
}
/*****************************************************************************/
/*      shiftit                                                              */
/*****************************************************************************/
int shiftit
(
int     num_reg,                        /* total*/
int     num_fdback,                     /* feed back registers*/
int     fb1,
int		fb2,
int		fb3,
int		fb4,                /* feed back locations start at 1*/
int     *shiftreg)
{
/*
 *    shift then return position 1 as the value
*/
        int newvalue;
        int i;
        
		newvalue=0;
        if (num_fdback == 1) {
           newvalue = ~shiftreg[fb1];
        }
        else if (num_fdback == 2) {
           newvalue = ~(shiftreg[fb1] ^ shiftreg[fb2]);
        }
        else if (num_fdback == 4){
           newvalue = ~((shiftreg[fb1] ^ shiftreg[fb2]) ^
                        (shiftreg[fb3] ^ shiftreg[fb4]));
        } 
/*
 *      now shift the register
*/
      for (i=num_reg;i>1;i--){
        shiftreg[i]=shiftreg[i-1];
      }
      shiftreg[1]=newvalue;
      return(newvalue);
}
/*****************************************************************************/
/*      initarray                                                            */
/*****************************************************************************/
void  initarray
(
struct  codeinfo  *code_info,   
int     codenum)                        /* to use*/
{
/*
 *    initialize arrays for characteristics of each code
*/
        switch (codenum) {
        case 1:
               code_info->num_reg=1;
               code_info->len    =1;
               code_info->num_fdback=1;
               code_info->fdback[0]=1;
               break;
        case 2:
               code_info->num_reg=2;
               code_info->len    = pow(2.0,2.0) - 1. + .5;
               code_info->num_fdback=2;
               code_info->fdback[0]=1;
               code_info->fdback[1]=2;
               break;
        case 3:
               code_info->num_reg=3;
               code_info->len    = pow(2.0,3.0) - 1. + .5;
               code_info->num_fdback=2;
               code_info->fdback[0]=2;
               code_info->fdback[1]=3;
               break;
        case 4:
               code_info->num_reg=4;
               code_info->len    = pow(2.0,4.0) - 1. + .5;
               code_info->num_fdback=2;
               code_info->fdback[0]=3;
               code_info->fdback[1]=4;
               break;
        case 5:
               code_info->num_reg=5;
               code_info->len    = pow(2.0,5.0) - 1. + .5;
               code_info->num_fdback=2;
               code_info->fdback[0]=3;
               code_info->fdback[1]=5;
               break;
        case 6:
               code_info->num_reg=6;
               code_info->len    = pow(2.0,6.0) - 1. + .5;
               code_info->num_fdback=2;
               code_info->fdback[0]=5;
               code_info->fdback[1]=6;
               break;
        case 7:
               code_info->num_reg=7;
               code_info->len    = pow(2.0,7.0) - 1. + .5;
               code_info->num_fdback=2;
               code_info->fdback[0]=6;
               code_info->fdback[1]=7;
               break;
        case 8:
               code_info->num_reg=8;
               code_info->len    = pow(2.0,8.0) - 1. + .5;
               code_info->num_fdback=4;
               code_info->fdback[0]=2;
               code_info->fdback[1]=3;
               code_info->fdback[2]=7;
               code_info->fdback[3]=8;
               break;
        case 9:
               code_info->num_reg=9;
               code_info->len    = pow(2.0,9.0) - 1. + .5;
               code_info->num_fdback=2;
               code_info->fdback[0]=5;
               code_info->fdback[1]=9;
               break;
        case 10:
               code_info->num_reg=10;
               code_info->len    = pow(2.0,10.0) - 1. + .5;
               code_info->num_fdback=2;
               code_info->fdback[0]=7;
               code_info->fdback[1]=10;
               break;
        case 11:
               code_info->num_reg=11;
               code_info->len    = pow(2.0,11.0) - 1. + .5;
               code_info->num_fdback=2;
               code_info->fdback[0]=9;
               code_info->fdback[1]=11;
               break;
        case 12:
               code_info->num_reg=12;
               code_info->len    = pow(2.0,12.0) - 1. + .5;
               code_info->num_fdback=4;
               code_info->fdback[0]=5;
               code_info->fdback[1]=8;
               code_info->fdback[2]=9;
               code_info->fdback[3]=12;
               break;
        case 13:
               code_info->num_reg=13;
               code_info->len    = pow(2.0,13.0) - 1. + .5;
               code_info->num_fdback=4;
               code_info->fdback[0]=9;
               code_info->fdback[1]=10;
               code_info->fdback[2]=12;
               code_info->fdback[3]=13;
               break;
        case 14:
               code_info->num_reg=14;
               code_info->len    = pow(2.0,14.0) - 1. + .5;
               code_info->num_fdback=4;
               code_info->fdback[0]=2;
               code_info->fdback[1]=3;
               code_info->fdback[2]=13;
               code_info->fdback[3]=14;
               break;
        case 15:
               code_info->num_reg=15;
               code_info->len    = pow(2.0,15.0) - 1. + .5;
               code_info->num_fdback=2;
               code_info->fdback[0]=14;
               code_info->fdback[1]=15;
               break;
        case 16:
               code_info->num_reg=16;
               code_info->len    = pow(2.0,16.0) - 1. + .5;
               code_info->num_fdback=4;
               code_info->fdback[0]=11;
               code_info->fdback[1]=13;
               code_info->fdback[2]=14;
               code_info->fdback[3]=16;
               break;

        case 17:
               code_info->num_reg=17;
               code_info->len    = pow(2.0,17.0) - 1. + .5;
               code_info->num_fdback=2;
               code_info->fdback[0]=14;
               code_info->fdback[1]=17;
               break;

        }
        return;
}
/*****************************************************************************/
/*      process args                                                         */
/*****************************************************************************/
void    processargs
(
int     argc,
char    **argv,
int     *codenum,                               /* 1 thru 16 code to use*/
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
        int   codelen;                  /* input by user*/
 
        int c;                          /* Option letter returned by getopt*/
        char  *myoptions = "ac:s:b:";      /* options to search for. :--> needs
                                            an argument*/
         char *USAGE =
        "Usage: comppncode [-ascii] [-c inumreg] [-s ismallval] [-b ibigval]";
 
		double   logOf2;

        opterr = 0;                             /* turn off there message*/
		logOf2=log(2.);
/*
        loop over all the options in list
*/
        while ((c = getopt(argc,argv,myoptions)) != -1){
          switch (c) {
          case 'a':
                   *asciiout = TRUE;    
                   break;
          case 'c':
                   sscanf(optarg,"%d",&codelen);  /* code to use*/
                   *codenum =  (log((double)(codelen + 1)))/logOf2 + .5;
                   if ((*codenum < 1) || (*codenum > 17)) goto errout;
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
