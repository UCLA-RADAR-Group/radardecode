/* 
 *	include file for correlator
 * 12apr98 - created.
 * 22aug98 - <pjp001>added bitsToUse to state.. moved around the power
 *						        removed TESTPATTERN
 * 04jun99 - <pjp002> corsetup;. added decode info. had to recompile
 *                    dcdRDrv, corLProg...
 *				     - added status bit is_a_cor 1--> correlator
 * 10jun99 -  - added FMT_PACK to status. moved rdtotcnts to other location.
 *			  - updated fmt_mask.
 *		      - renames dcdstat to st2
 *		      - added options to stat2: pack8,16,32.
*/
#ifndef INCcorh
#define INCcorh

/*	start duplicating some defs for correlator */

#define COR_MAX_BOARDS      4
#define COR_CLKS_PER_USEC  50
#define COR_MAX_CYCLE_LEN   8
#define COR_MAX_NUM_FREQ    4

/*	some numeric codes used to pass in info to corProg	*/

#define COR_START_IMD_SW    0
#define COR_START_IMD_HW    -1
#define COR_START_1SECTICK  1
#define COR_START_10SECTICK 10

#define COR_DATA_RAWACF     1
#define COR_DATA_PROCACF    2
#define COR_DATA_SPEC       3
#define COR_DATA_PACK       4



#define	COR_ST_DOUBLENYQUIST	    0x00000001
#define	COR_ST_CHIPTESTMODE         0x00000002
#define	COR_ST_BLANKENABLED         0x00000004
#define	COR_ST_PWRCNTINC            0x00000008

/*      relbit shift 0..3 , Sgn 1--> neg, 0-->pos*/
/* note. corget does >>4, <<4 to relbit shift so dont move it in status*/
#define	COR_ST_RELBITSHIFT          0x00000030
#define	COR_ST_RELBITSHIFTSGN       0x00000040

#define	COR_ST_FMT_MASK             0x00000f00 
#define	COR_ST_FMT_RAWACF           0x00000100
#define	COR_ST_FMT_CMBACF           0x00000200 
#define	COR_ST_FMT_SPECTRA          0x00000400
#define	COR_ST_FMT_PACK             0x00000800


/*	these values must be the same for all boards	*/

#define COR_ST_START_MASK           0x0000f000
#define COR_ST_START_IMD_SW         0x00001000
#define COR_ST_START_IMD_HW         0x00002000
#define COR_ST_START_TICK1          0x00004000
#define COR_ST_START_TICK10         0x00008000

/* 	dump delay  .. bits are:
 *   if (stat & dmpdel_mask ==0) then
 *       continuous mode no wait
 *   else if (trg_int) then
 *		 wait for command then start after requested delay
 *   else (trg_tick){
 *       wait for external tick then start after delay
 *   }
*/
#define	COR_ST_DMPDEL_MASK          0x00030000
#define	COR_ST_DMPDEL_TRG_INT       0x00010000
#define	COR_ST_DMPDEL_TRG_TICK      0x00020000

#define COR_ST_ADJPWR_MASK          0x000c0000
#define COR_ST_ADJPWR_STSCAN        0X00040000 
#define COR_ST_ADJPWR_STREC         0X00080000

#define COR_ST_SPECTRA_FLIPPED      0x00100000
#define COR_ST_IS_A_COR             0x00200000
#define	COR_ST_TOTCNTSINC           0x00400000

/* derived from other values*/

#define COR_STC_MASK   		        0xff000000
#define COR_STC_CAL_MASK            0X03000000 
#define COR_STC_CAL_OFF             0X01000000 
#define COR_STC_CAL_ON              0X02000000
#define COR_STC_COMPLEX		        0x08000000
#define COR_STC_9LEVEL 		        0x10000000
#define COR_STC_STOKES 		        0x20000000
#define COR_STC_PWRCNTI 	        0x40000000
#define COR_STC_PWRCNTQ 	        0x80000000

/*
 * stat 2
*/
#define COR_ST2_PACKSHIFT_MASK      0x0000001f
#define COR_ST2_PACK_MASK           0x000000e0 
#define COR_ST2_PACK_8              0x00000020 
#define COR_ST2_PACK_16             0x00000040
#define COR_ST2_PACK_32             0x00000080
#define COR_ST2_2SMP_PER_BAUD       0x00000100 




typedef struct {
	int		bwNum;		  /* 1->9 max to min bw*/
	int		dumpIntegLen; /* dump integration len in master clock cycles*/

	int		lagConfig;	  /* 1-->9*/
	unsigned int st;		      /* single bit things*/

	int		lagsPerSbcInp;/* lags per sbc on input from correlator*/
	int		stepsPerCycle;/* include cal/freq changes*/

	char    calCycle[COR_MAX_CYCLE_LEN];/* 0-low,1-hi binary*/
	char    frqCycle[COR_MAX_CYCLE_LEN];/* freqnum 0..3 binary*/

	int	    cyclesPerRec; /* compute spectra once a rec*/
	int		integWaitDelayUsecs;  /* if doing integ cycle restarting*/
/* 
 * decoder junk
*/
	unsigned int st2;		    /* 2nd status word*/
	float		baudLen;		/* in usecs*/ 

	int	        codeLen;		/* in bauds*/
	int	        codeDelay;		/* in bauds*/

	int	        smpPerBaud;		/* in bauds*/
	int		    cohAdd;			/* codes added to get dumpIntegLen*/
	/*
	 * computed...
	*/
	int		numFrqBufs;		/* from frqCycle*/
	int		lagsPerSbcOut;

	int		numSbcInp;
	int		numSbcOut;

	int		dumpsPerRec;	/*this sets cycl/rec then we round*/
	                        /*if a decoder, this is the cohadd codes/rec*/
	int		fill1;

	int     numWDInpCor;	/* 32 bit words input from correlator brd*/
	int     numBDAfterProc;	/* number bytes data after processing/packing*/
	} COR_SETUP;

/*
 * hdr sent from corProg to corLProg->corLProc->corProg to pass
 * pwr info back and forth during datataking.
*/
typedef struct {
	int   attnDb[2];
    float pwrCnt[2];        /* power counter I,Q avged for integration */
    float lag0PwrRatio[2];  /* meas/optimum power for level setting    */
    float calOff[2];        /* cal off pwr                             */
    float calOn[2];         /*                                         */
	int   frqBufThisRec;	/* binary. 1,2,3,4...*/
	int	  filler;
	} COR_IOHDR;


#endif	/* INCdcdh*/
