/* 
 *	include file for dcd 
 *12sep95 - added digFilter includes
 *19sep95 - changed lagConfigs. 7,8--> 6,7, 56--> 5 added 8
 *04oct95 - updated digital filter masks..
 *09oct95 - dig filter output
 *04nov95 - added ioctl's that are specific to dcdRDrv only.
 *10dec95 - commented out ioctl for dcdrdchips, rd1sbc.. use rddma now..
 *          also commented out structures for readchips..
 *29aug96 - changed dcd_clks_per_used from 25 to 40
 *03sep96 - added dcd_read_single struct and ioctl READSNG to do single
 * 		   words reads.
 *19apr97 - DCDR_SETUPREAD removed lagsChip,chipToRead from DCDR_SETUPREAD
 *		    was there in case lagConfig < 0 but i had only used that
 *		    for debugging.
 *		  - DCDR_READ - numWords now an array.
 *		  - added ioctls 
 *	      - DCDRIOCSETUP
 *	      - DCDRIOCDFSETUP
 *21apr97 - DCDR_SETUPREAD1  added for setup to single board. 
 *		    DCDR_SETUPREAD now an array of DCDR_SETUPREAD1.
 *22apr97 - DCDR_PROCSETUP changed to an array of int ptrs 
 *06apr98 - added waitIntegCycle to config bits, and setup_structure
 *        - added ioctl to send a software continue cmd. used if 
 *			waitIntegCycle.
 *20aug98 -<pjp001>changes for programmable bit selection in filter boards
 *			testPattern-->relBitShift
 *          DF_MAX_BIT_SHIFT 3
 *08jun99 -added ioctl dcdRDrv to load pncode
 *        
*/
#ifndef INCdcdh
#define INCdcdh
#include	<stdio.h>
#include	"ipic.h"
#include    "cor.h"

/*	start duplicating some defs for correlator */

#if FALSE
#define COR_MAX_BOARDS    4
#define COR_CLKS_PER_USEC 50
#endif

#define DCD1DEVNAME	"/dcd1"
#define DCDRDEVNAME	"/dcdR"
#define DCD_CLKS_PER_USEC 40
#define DCD_MAX_SBC       8
#define DCD_MAX_LAGS_SBC  2048
#define DCD_MAX_LAGS      8192 
#define DCD_MAX_BOARDS    4
#define DCD_MIN_CPU       6
#define DCD_MAX_CPU       9
#define DCD_ADJPWR_TOLOOP_DEF 4
#define DCD_DEAD_TIME_DUMP_CYCLES 32
/* ... set to 1000192 so its divisible by all the shift lengths (256 max) */
#define DCD_ADJPWR_INTEGLEN_DEF 1000192
/* 30 bits 2**30 - 1 */
#define DCD_MAX_INTEG_LEN_CLKS 1073741823
/*
 *	interrupts 0- data ready, 1- 1sec tick
*/
#define	DCD_INT0_NUM	0xff
#define	DCD_INT1_NUM	0xfe
#define DCD_INT_DATA_READY  0
#define DCD_INT_TICK        1
/* 
 *	dcd particular ioctl's
*/
#define DCDIOCWAITINT	        0x5
#define DCDIOCSTATUS            0x6 
#define DCDIOCDEBUG             0xa 
#define DCDIOCENAINT            0xb 
#define DCDIOCDISINT            0xc 

#define DCDIOCLDSHIFTENALEN     0x10
#define DCDIOCLDCODELEN         0x11
#define DCDIOCLDCODESTADR       0x13
#define DCDIOCLDRAM             0x14
#define DCDIOCLDINTEGLEN        0x15
#define DCDIOCLDCORRPROD        0x16
#define DCDIOCLDCONFIGWRD       0x17
#define DCDIOCSNDCMD            0x18
#define DCDIOCRDSHIFTENALEN     0x19
#define DCDIOCRDCODELEN         0x1a
#define DCDIOCRDCODESTADR       0x1b
#define DCDIOCRDRAMCURADR       0x1c
#define DCDIOCRDINTEGLEN        0x1d
#define DCDIOCRDRAM             0x1e
#define DCDIOCRDUMPCNTR         0x1f
/*
#define DCDIOCRD1SBC            0x20
*/
#define DCDIOCRDSNG             0x20
#define DCDIOCRDCORRPROD        0x21
#define DCDIOCSETUP             0x22
#define DCDIOCGETSETUP          0x23
/*
#define DCDIOCRDCHIPS           0x24
#define DCDIOCRDCHIPSSINGLE     0x25
*/
#define DCDIOCDFSETUP           0x26 
#define DCDIOCDIGWRITE          0x27 
#define DCDIOCDBGTOGGLE         0x28 
#define DCDIOCRDSETUP           0x29 
#define DCDIOCRDDMA             0x2a 
#define DCDIOCSETATTN           0x2b 
#define DCDIOCGETATTN           0x2c 
#define DCDIOCCONTINUE          0x2d
#define DCDIOCLAST              0x2d
/*
 * IOCTLS for dcdRDrv must be > that DCDIOCLAST but less than 
 * GCSR cmds (0x100 gcsrLib.h). These are additional ioctls that are only
 * used in communicating info between the main cpu and the mv162fx computers.
*/
#define DCDRIOCTAKEDATA		0x50
#define DCDRIOCSETUPREAD 	0x51 
#define DCDRIOCSTOPTAKEDATA 	0x52
#define DCDRIOCREADDATA         0x53
#define DCDRIOCFLUSH            0x54
#define DCDRIOCSTAT             0x55
#define DCDRIOCRESET            0x56
#define DCDRIOCSETUPPROC        0x57
#define DCDRIOCADJPWR           0x58
#define DCDRIOCGETPWR           0x59
#define DCDRIOCSETUP            0x5a
#define DCDRIOCDFSETUP          0x5b
#define DCDRIOCSETUPCOR         0x5c
#define DCDRIOCWAITDUMP         0x5d
/*
 * iosel addresses useds:
 * the dcd uses ioSelAB, (or CD)  to address registers.
 * There is a mask for each register that masks the allowable data bits.
*/
#define	DCD_ADR_SHIFT_ENA_LEN  0X00
#define	DCD_ADR_CODE_LEN       0X01
#define	DCD_ADR_CODE_START_ADR 0X02
#define	DCD_ADR_INTEG_LEN      0X04 
#define	DCD_ADR_LD_CODE_DATA   0X03
#define	DCD_ADR_RD_CUR_RAM_ADR 0X03
#define	DCD_ADR_RD_CODE_DATA   0X05
#define	DCD_ADR_LD_CORR_PROD   0X05
#define	DCD_ADR_RD_CORR_PROD   0X06
#define	DCD_ADR_LD_CONFIG      0X06
#define	DCD_ADR_LD_CMD_WRD     0X07
#if FALSE
#define DCD_ADR_RD_DMP_CNTR    0x07
#endif
#define	DCD_ADR_STATUS         0X08
#define	DCD_ADR_RD_CHIP_DATA   0X09
#define DCD_ADR_ENA_CHIP       0x10
#define DCD_ADR_DISA_CHIPS     0X18
#define DCD_ADR_DMA	       0x20	
/*
 *	data masks for each address
*/
#define	DCD_MSK_SHIFT_ENA_LEN  0X0000ffff
#define	DCD_MSK_CODE_LEN       0X0000ffff
#define	DCD_MSK_CODE_START_ADR 0X0000ffff
#define	DCD_MSK_CODE_CUR_ADR   0X0000ffff
#define	DCD_MSK_CODE_DATA      0X0000000f
#define DCD_MSK_INTEG_LEN      0X3fffffff

#define	DCD_MSK_CORR_PROD      0X0000000f
#define	DCD_MSK_CONFIG         0X0000001f
#define	DCD_MSK_CMD_WRD        0X0000000f
#define	DCD_MSK_STATUS         0X0000f07f
#define	DCD_MSK_CHIP_DATA      0Xffffffff
/*
 *  correlation product configurations
 *  note that CODE is the bottom 2 bits of the ram
 *  note that _POL sends same config as complex to correlator. 
 *       but processing programs hanle it differently.
*/
#define DCD_PROD_9X9_I	       0
#define DCD_PROD_9X9_Q	       1
#define DCD_PROD_9X3_IQ_CODE   2
#define DCD_PROD_3X3_RAM       3
#define DCD_PROD_3X3_CMPLX     4
#define DCD_PROD_3X3_IQ        5
#define DCD_PROD_3X3_INTLV_I   6
#define DCD_PROD_3X3_INTLV_Q   7
#define DCD_PROD_3X3_INTLV_IQ  8
#define DCD_PROD_9X9_IQ        9
#define DCD_PROD_3X3_POL      10
#define DCD_PROD_LAST         10
/*
 * 	configuration word bits
*/
#define DCD_CNFG_1SMP_PER_BAUD    0x0 
#define DCD_CNFG_2SMP_PER_BAUD    0x1
#define DCD_CNFG_DBLE_NYQUIST     0x2
#define DCD_CNFG_CHIP_TEST_MODE   0x4
#define DCD_CNFG_ENA_BLANKING     0x8
#define DCD_CNFG_INTEGCYCLE_WAIT  0x10
/*
 * 	command word bits
 *	note that SE is shift enable, INT is integration
*/
#define DCD_CMD_SE_STOP            0x1 
#define DCD_CMD_SE_START_TRIG      0x2 
#define DCD_CMD_SE_START_IMD       0x3 
#define DCD_CMD_INT_STOP           0x4 
#define DCD_CMD_INT_START_TRIG     0x8 
#define DCD_CMD_INT_START_IMD      0xc 
/*
 * status bits
*/
#define DCD_STAT_SHIFT_ENA        0x0001
#define DCD_STAT_INT_ENA          0x0002
#define DCD_STAT_2SMP_PER_BAUD    0x0004
#define DCD_STAT_DOUBLE_NYQUIST   0x0008
#define DCD_STAT_CHIP_TEST_MODE   0x0010
#define DCD_STAT_BLANKING_ENA     0x0020
#define DCD_STAT_INTEGCYCLE_WAIT  0x0040
#define DCD_STAT_DMP_CNT          0xf000
/*
 *	get dmp cnt from status
*/
#define DCD_DMP_CNT_FROM_STAT(istat) 	((istat & DCD_STAT_DMP_CNT )>>12)

#define  DCD_BWNUM_MAXBW		1
#define  DCD_BWNUM_MINBW		9
#define  DCD_ATTN_MIN_VAL_DB    0
#define  DCD_ATTN_MAX_VAL_DB   15
/*
 * digital filter bit mask is relative to 8 bits. 24BIT_MASK is used
 * to determine where the 8 bits sit in the 24bit digital i/o.
*/
#define	 DF_MSK_INTERPOLATE 	0x100000
#define	 DF_MSK_INTERLEAVE  	0x200000
#if FALSE
#define	 DF_MSK_TESTPATTERN 	0x800000 <pjp001> replace with RELBITSH
#endif
#define	 DF_MSK_RELBITSH    	0xc00000
#define	 DF_MSK_24BIT_DIO   	0xff0000
#define	 DF_MAX_BIT_SHIFT	           3
/*
 * masks for power counters via digital i/o board
*/
#define PC_MSK_BLANKING		0x004000
#define PC_BLANK_ON         0x004000
#define PC_BLANK_OFF        0x000000
#define PC_MSK_CHANGE_ATTN  0x0080ff
#define PC_NO_CHANGE_ATTN   0x008000
#define PC_RD_PC            0x008000
#define PC_CHANGE_ATTN      0x000000
#define PC_MSK_SELREAD  	0x00b000
#define PC_SELREAD_ILO     	0x000000
#define PC_SELREAD_IHI     	0x001000
#define PC_SELREAD_QLO     	0x002000
#define PC_SELREAD_QHI     	0x003000
#define PC_MSK_READ     	0x000fff

#define PC_READ_I		0x01
#define PC_READ_Q		0x02
#define PC_READ_IQ		0x03
#define PC_READ_NONE 	 	0x00

/*	in sum arrays, i always returned before Q */
#define	PC_INDEX_I		0
#define	PC_INDEX_Q		1
/*
 * sinc filter board bits
*/
#define SF_CLOCK_DIV_MAX	6
#define SF_CLOCK_FREQ(DIV)  ( 40. / (1 << div))
#define SF_CLOCK_DIV(A)	    ( (A<<1) & 0xe )
#define SF_STROBE_ON(A)	    ( A |  0x080000)
#define SF_STROBE_OFF(A)    ( A &  0xf7ffff)
#define SF_SAMPLES_TO_ACCUM(A) (( A & 0xfff) << 4)
#define SF_BITS(A)	     (( A & 0x7) << 16)
#define SF_BANDWIDTH(A)	     ( (A)?1:0)
/*	
 *	wait interrupt structure
*/
typedef struct {
	int     intToUse;	/* 0 1sec tic, 1 data available*/
        int     late;           /* for interupt*/
        int     timeout;        /* for wait in ticks*/
        int     intcount;       /* interrupt*/
        int     statAtInt;      /* status at last interrupt*/
        }  DCD_INTINFO;
/*	
 *	load/read ram structure
*/
typedef struct {
	int     numWrds;	/* number of wrds to. 1 to 64k*/
	int     startAdr;	/* starting mem address. 0 to 64k-1*/
	int	revOrder;	/* load data in reverse order*/
        char    *buf;           /* data is or goes here (lowermost 4 bits)*/
        }  DCD_RAMINFO;
/*
 *	setup the decoder registers
*/
#if FALSE
 .. change setup to bit field ????

#define DCD_CNFG_1SMP_PER_BAUD    0x0 
#define DCD_CNFG_2SMP_PER_BAUD    0x1
#define DCD_CNFG_DBLE_NYQUIST     0x2
#define DCD_CNFG_CHIP_TEST_MODE   0x4
#define DCD_CNFG_ENA_BLANKING     0x8
#define DCD_CNFG_INTEGCYCLE_WAIT  0x10
int		suBits;	
#define DCD_SUBITS_2SMPPERBAUD  0x0001
#define DCD_SUBITS_DNYQUIST 	0x0002 
#define DCD_SUBITS_CHIPTESTMODE 0x0004
#define DCD_SUBITS_ENABLEBLANK  0x0008
#define DCD_SUBITS_INTEGCYCLEWAIT 0x0010

#define DCD_SUBITS_TESTPATTERN  0x1000 no longer used.. now RELBITSH 
#endif

typedef struct {
	int	isACor;		/* true-> df and bwNum
				   false-> sinx/x and bwDivisor*/
        int     bwDivisor;      /* shift rate. divide into master clock*/
	    int	    bwNum;		/* if a correlator*/
        int     codeLen;        /* code length*/
        int     codeStartAdr;   /* code start address (start at 0)*/
        int     dumpIntegLen;  /* in master clock cycles*/
        int     lagConfig;         /* 0 thru 4 */
        int     smpPerBaud;     /* 1 or 2*/
        int     doubleNyquist;  /* true/false*/
        int     chipTestMode;   /* true/false*/
#if FALSE
        int     testPattern;  <pjp001>  replace with relBitShift
#endif
        int     relBitShift;    /* -3..+3 relative bit shift requested dig flt*/
	    int	    enableBlanking; /* enable blanking*/
	    int	    integCycleWait; /* wait for go after each integ cycle*/
		int		filler;
        } DCD_SETUP; 
/*
 *	lag config structure. tell what each lag config can do
 *      In,Out difference is:
 *	 for 9 level you may have 4*2048 to work with but
 *	                          1*2048 after combination
*/
typedef	struct	{
	int	numSbcIn;	/* available this config	*/
	int	numSbcOut;	/* after processing	*/
	int	lagSbcInMax;	/* max lags/sbc input*/
	int	lagSbcOutMax;	/* max lags/sbc out after processing*/
	int	level;		/* 3,9*/
	int	decode;		/* decoder config*/	
	int	pol;		/* polarazation config*/
	int	ram;		/* uses ram both inputs*/
	int	intlv;		/* interleaved data*/
	int	complex;	/* complex sampled*/
	} DCD_CFINFO;
/*
 * 	digital filter setup
*/
typedef	struct {
	int	bwNum; 		/* 1..9 min thru max*/
	int	lagConfig;	/* we are using*/
	int	useDnyquist;/* use double nyquist*/
#if FALSE
	int	useTestPattern; pjp001 replaced with 	bitsToUse; 
#endif
	int	bitsToUse;  /* going to 9..level 3->0 --> bits 12,11,10,9 ...*/
	} DF_SETUP;
/*
 *      struct for read setup. The totCnts variable must match the sum
 *	of the data in the arrays.
 *	When doing reads, this setup remains in effect until the next
 *	read setup request.
*/
typedef struct {
	int	numChipsTot;	/* in total to read*/
	int	numLagsTot;	/* all chips*/
	int	numTotCntsTot;  /* all chips*/
    int lagsToRead[8];  /* lags to read each chip*/
    int chipToRead[8]; /* chip number to read. 1..8*/
    int rdTotCnt[8];    /* true/ false for this chip*/
    } DCD_SETUP_READ;
/*
 *	struct to do dma read on dcd brd.
*/
typedef	struct	{
	int	numLagsTot;    /* must match setup value*/
	int	numTotCntsTot; /* must match setup value*/
	int	timeoutTicks;  /* for read*/
	int	*lagBuf;       /* lags data goes here*/
	int	*totCntBuf;    /* totCnt data goes here*/
	int	*ppcIdig;      /* not null, read i dig power cnter*/
	int	*ppcQdig;      /* not null, read Q dig power cnter*/
	} DCD_READ;
/* 
 * structure used to do single word reads.
*/
typedef struct {
	int	numChipsTot;    /* to read*/
	int	numTotCntsTot;  
	int	lagsToRead[8];	/* lags to read each chip*/
	int	chipsToRead[8];	/* chip number each chip .. # 1 to 8*/
	int	rdTotCnt[8];	/* true/false for each chip*/
	int *lagBuf;	    /* lag data goes here*/
	int *totCntBuf;	    /* totCnt data goes here*/
	int *ppcIdig;	    /* null --> don't read */
	int *ppcQdig;	    /* null --> don't read */
	} DCD_READ_SINGLE;
/*
 *	hold all info needed for single reads..
*/
typedef	struct	{
	int	startCmd;	/* available this config*/
	DCD_SETUP_READ rdSu;	/* read setup structure*/
	DCD_READ       rd;	/* for read*/
	int	dmpIntLenMclks; /* dmp integration length in master clocks*/
	int	numDumps; 	/* number of dumps to accum*/
	int	numSbcIn;	
	int	numSbcOut;	
	int	lagSbcIn;	
	int	lagSbcOut;	
	int	lagSbcInMax;	/* max we can have this config*/
	} DCD_READINFO;
/*
 *	power info 1 signal
*/
typedef	struct	{
	float	lag0Norm;	/* - bias/ bias*/
	float	ads;		/* alpha/sigma for 3 level or lag0Norm of 0 level*/
	float	pwrRatio;   /* measured/expected value*/
	float	pc;			/* power counter for this 0 lag*/
	} DCD_POWER_ONE;

typedef struct {
	int		numRet;		/* num get power measures returned 1,2*/
	int	    level3;		/* true/false*/
	DCD_POWER_ONE pwr[2];	/* can return max of 2*/
	}DCD_POWER;

typedef struct {
	DCD_POWER   pwrI;	
	int	 		attnDb[2];	/* current setting*/
	int			attnDbToAdd[2];/* after adjustment what's needed*/
	float	 pcLag0Ratio[2];	/* measured/expected  lag0/pc ratio */ 
	} DCD_ADJPWR; 
/********************** 
*	dcdR structures..
*/
/*
 * decode setups per board. Should be one for each board openned
*/
typedef struct {
	DCD_SETUP	suAr[COR_MAX_BOARDS];
	} DCDR_SETUP;
/*
 * corsetups per board. Should be one for each board openned
*/
typedef struct {
	COR_SETUP	suAr[COR_MAX_BOARDS];
	} DCDR_SETUPCOR;
/*
 * digital filter setups
*/
typedef struct {
	DF_SETUP	suAr[COR_MAX_BOARDS];
	} DCDR_DF_SETUP;
/*
 * 	setup for reads on dcdProgL
*/
typedef	struct	{
	int	lagConfig;	/* if lagConfig < 0 use lagsChip,chipsToRd*/
	int	numLagsSbcIn;	/* number of lags each input sbc*/
	int	rdTotCnt;	/* true/false*/
	int	pcCode;		/* 00 non 1 i,2 q, 3 iq*/
	} DCDR_SETUPREAD1;

typedef struct {
	DCDR_SETUPREAD1 suAr[COR_MAX_BOARDS];
	} DCDR_SETUPREAD;
/*
 *  start datataking on dcdProgL
*/
typedef	struct	{
	int	startCmd;	/* to send to decoder*/
	int	numDumps;	/* to run*/
	} DCDR_STARTDT; 
/*
 *	struct send to dcdProgL to do reads
*/
typedef	struct	{
	int	numBoards;	/* to read from (order is open order*/
	int	timeOutTicks;/* timeout in clock ticks*/
	int	numWords[10];	/* to read each decoder board*/
	int	*baList[10];   /* address to put data for each decoder board*/
	} DCDR_READ;
/*
 *	struct for stat readback from all dcd boards
*/
typedef	struct	{
	int	numBrdsInUse;	/* boards in use*/
	int	cpuNum[10];	/* cpuNum each board*/
	int	errNum[10];     /* last errno each board*/
	} DCDR_STAT;
/*
 *	struct to setup dcd processing program..
*/
typedef	struct	{
		int		passThru;	/* true --> no processing*/
		int     lagsPerSbc; /* to use*/
        int     packing;/* 8,16,32 bits to pack*/
        int     toShift;  /* right shift this many bytes to pack*/
        int     inBufsPerOBuf;/* how many inbufs before an outbuf*/
        int     integTimeClocks;/* for bias removal*/
	} DCDR_PROCPROG_SETUP1;
typedef	struct	{
	char                 *suAr[COR_MAX_BOARDS];
	} DCDR_PROCPROG_SETUP;
/*
 *	adjust power filled in on return from adjpower
*/
typedef	struct	{
		int			numBoards;     /* user fills in.order is open order*/
		int			integLenClocks;
		DCD_ADJPWR  adjPwr[10];/* max 10 cpus*/
	} DCDR_ADJPWR;
/* 
 *	get power filled in on return from getpower
*/
typedef	struct	{
		int			numBoards;     /* user fills in.order is open order*/
		int			integLenClocks;
		DCD_POWER   pwrI[10];/* max 10 cpus*/
	} DCDR_GETPWR;
/*
 *	wait for dump 
*/
typedef	struct	{
		int			timeOutTicks;     /* user fills in.order is open order*/
		int			dumpNum[10];
	} DCDR_WAITDUMP;
#endif	/* INCdcdh*/
