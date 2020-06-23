/*hdrCor.h - include file for corProg portion of headers
*  %W%    %G%
*/
/*modification history:
----------------------
x.x 05sep96 added attn[2],pc[2],pwrRatio[2] to header
x.x 22aug98 version 1.0->1.1 changed free[2] to bitsToUse,free[1]
				    2.0      added bits to use to state
x.x 27nov98 got rid of dcd.h.. not needed this routine
x.x 22jun99 added variables for dcd.
x.x 18oct99 added rfFrqMhz. center freq this subband
				  fill2
x.x 06mar00 added ifndef on HDRAO_COR
*/
#ifndef INChdrCorh
#define INChdrCorh
#include	<stdio.h>
#include	"hdrLib.h"

/*
 *	cor config info for headers
*/
#define HDRAO_COR_ID	   "cor "
#define HDRAO_COR_CUR_VER      " 1.0"
#define HDRAO_COR_CUR_VER_NEW  " 2.0"

/* new to define here since this is compiled into a library*/

#define HDRAO_COR HDRAO_CORV2
#ifndef HDRAO_COR
#define HDRAO_COR HDRAO_CORV1
#endif
/*
 *	macros to access header locatoins
*/
/*
 *	pass in start of header, return ptr to start of riPortion of header
*/
#define CORHDR_GET(phdr)  ( \
	 (HDRAO_COR *) ( \
	      ((char*)(phdr)) + \
              HDR_S_GET_OFF(((HDRAO_STD *)(phdr))->sec.inp)\
	     ))

/*
 * version 1  before 15apr98
*/
typedef struct {
/*
 *	here's the dcd specific junk
 *	extra space at bottom makes multiple of 8 bytes and can be used
 *	for additions later on
*/
    char id[4];			/*	"cor " no null termination*;				[ 0]*/
	char ver[4];	    /*		"xx.x" version... 						[ 1]*/
	int	masterClkPeriod;/* master clock period in nanosecs				[ 2]*/
	int	dumpLen;        /* in master clock counts						[ 3]*/
	int dumpsPerInteg;  /*included in integration						[ 4]*/
	int	lagSbcIn;		/* lags per sbc before processing				[ 5]*/
	int lagSbcOut;		/* lags per sbc after processing				[ 6]*/
	int numSbcIn;		/* num sbc/board before processing				[ 7]*/
	int numSbcOut;   	/* num sbc/board after processing				[ 8]*/
	int	bwNum;	        /* 1=maxband (1/masterClkPeriod), 9=min band	[ 9]*/
						/*   each step smaller by an octave				    */
	int	lagConfig;		/* for correlator								[10]*/
		/* below  is in lagConfig										    */
    int levels;			/* 3,9											[11]*/
	int stokes;			/* true/false									[12]*/
	/* ... */
	int	doubleNyquist;	/* true/false									[13]*/
	int chipTestMode;	/*  true/false									[14]*/
	int blankingEnabled;/* true/false									[15]*/
	int startOn;		/* 0- imd 1 - 1sectick 10- 10sec tick 99- exttick[16]*/

	int dataFormat;	 	/* 1 raw acf's, 2 combined acfs, 3 spectra		[17]*/
	int	totCntsInc;		/* true/false included with data				[18]*/
	int	pwrCntInc;      /* true/false included with data 				[19]*/

	int	boardId;		/* board number 6,7,8,9							[20]*/
	int numBrdsUsed;	/*hc22 h54 number boards used					[21]*/
	/* below -1 --> not included..*/
	int	  attnDb[2];		/* correl attenuator values 0..15			[22]*/
	float pwrCnt[2];		/* power counter I,Q avged for integration	[24]*/
	float lag0PwrRatio[2];	/* hc27 h59 meas/optimum power for lvl setting[26]*/
	int	  bitsToUse;       /* 0..3 for digital filters*/
	int   free[1];		   /* current length 30*4=120 bytes				[28]*/
	}	HDRAO_CORV1;

/*
 * version 2 06mar00
*/
typedef struct {
/*
 *  here's the correlator specific junk
 *  extra space at bottom makes multiple of 8 bytes and can be used
 *  for additions later on
 *   Hxx integer offset start of Stdheader
 *   Cxx integer offset start of corheader
*/
    char id[4];         /*  "cor " no null termination*;                [0]*/
    char ver[4];        /*      "xx.x" version...                       [1]*/
 
    int masterClkPeriod;/* master clock period in nanosecs              [2]*/
    int dumpLen;        /* in master clock counts                       [3]*/
						/* dcd.. includes cohadds*/
    int dumpsPerInteg;  /* dumps in 1 rec. include all frequencies      [4]*/
						/* dcd..dumps/rec*/
    int lagSbcIn;       /* lags per sbc before processing               [5]*/
 
    int lagSbcOut;      /* lags per sbc after processing        [40]    [6]*/
    int numSbcIn;       /* num sbc/board before processing              [7]*/
 
    int numSbcOut;      /* num sbc/board after processing               [8]*/
    int bwNum;          /* 1=maxband (1/masterClkPeriod), 9=min band    [9]*/
                        /*   each step smaller by an octave                */
    int lagConfig;      /* for correlator                              [10]*/
    int state;          /* we used for this integration                [11]*/

	int	frqBufThisRec;  /* 1,2,3,4  binary							   [12]*/
	int	cycleLen;		/* for cals/freq                               [13]*/

	char calCyc[8];		/* y,n,...no null termination                  [14]*/
	char frqCyc[8];		/* ascii 1,2,3,4 for freq buf 1,2,3,4          [16]*/
 
    int boardId;        /* board number 6,7,8,9                        [18]*/
    int numBrdsUsed;    /*                                             [19]*/
 
    /* below -1 --> not included..*/
    int   attnDb[2];        /* correl attenuator values 0..15          [20]*/
    float pwrCnt[2];        /* power counter I,Q avged for integration [22]*/
    float lag0PwrRatio[2];  /* meas/optimum power for level setting[56][24]*/
    float calOff[2];        /* cal off pwr                             [26]*/
    float calOn[2];         /*                                         [28]*/
	int	  state2;			/* 2nd stat word                           [30]*/
    int   fill;             /* total length 32*4=128 bytes  8*16       [31]*/
	/*
	 * dcd info
	*/
	int 	baudLen;   		/* unit = .05 usecs                     [32]*/
	int  	codeLen;   		/* in bauds                             [33]*/
	int  	codeDelay;  	/* in bauds                             [34]*/
	int	 	cohAdd;    		/* coherently add cohAdd codes          [35]*/
	int		fill2[4];		/* unused 							    [36]*/
                               /* 40*4  = 160 bytes                        */
    }   HDRAO_CORV2;


void    hdrPrCor(FILE *fptr,void *phdr);
void    hdrCorToD(void *phdr,double *pd);
void    hdrDToCor(double *pd,void *phdr);
#endif /*INChdrDcdRih*/
