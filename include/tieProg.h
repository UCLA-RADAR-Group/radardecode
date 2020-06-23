#ifndef 	INCtieProgh
#define 	INCtieProgh
#include	"mathCon.h"
#include	"tttProgs.h"
/*
 * %W%  %G%
 * include file for tieProg. holds the program specific formats to 
 * communicate with the tiedowns. The generic stuff is in tttProgs.h 
 * and is shared with ttProg
 * 18aug97 added TIE_pnum...
 * 14nov98,<pjp001> - added new msg formats to slave for fill buffer command.
 *put under sccs 18nov98
*/
/* 
 * max num microcontroller for each program
*/
#define TIE_MAX_NUM_DEV				3		
#define TIE_MAX_FAULT_NUM			30
/*	device addresses on the  485 networks  */

#define	TIE_SLVADR_TIE1  1
#define	TIE_SLVADR_TIE2  2
#define	TIE_SLVADR_TIE3  3

/*
 * position limits inches. min is min extenstion (up) max if all way down
 * note: these are used for the software. The software stops sending
 * command .2 inches inside these. These would normally be the 
 * prelimits. Look at my web page for the actual hardware limits.
*/
#if FALSE
modification history:
..till 08feb00 then changed limit switches
 #define TIE_POS_FLIM12_MIN	  1.2
 #define TIE_POS_FLIM12_MAX   21.79
.. till 18mar05 new jack installed flimsw now 23.28..
#define TIE_POS_FLIM12_MAX   22.29

 #define TIE_POS_FLIM8_MIN	  1.52
 #define TIE_POS_FLIM8_MAX  22.14

 td4 reset position 3apr00 when jack flew up..
 #define TIE_POS_FLIM4_MIN	  1.95
 #define TIE_POS_FLIM4_MAX    23.21

 .. td4 3apr00 till 14may04 when jack replaced
 #define TIE_POS_FLIM4_MIN	  1.93
 #define TIE_POS_FLIM4_MAX    22.87
#endif
#define TIE_POS_FLIM12_MIN	  1.43
#define TIE_POS_FLIM12_MAX   22.69

#define TIE_POS_FLIM4_MIN	  1.28
#define TIE_POS_FLIM4_MAX    23.24

#define TIE_POS_FLIM8_MIN	  1.19
#define TIE_POS_FLIM8_MAX    22.20
/*
 * software limit is .2 inches inside this
*/
#define TIE_POS_SWLIM_OFFSET   .2

/* measured by moving jack and measuring deltaEnc, delta inches*/

#define TIE_PENC_CNTS_PER_INCH        43663.36
#define TIE_INCHES_PER_PENC_CNT    	2.29024976e-5


/* notes: REVPS    - revolutions/second
          CNTPS    - counts/second
          INCHPS   - inches/second
		  
  (5000Mtr.Rpm/2048DAcnts) * (1PinionRev/90Mtr.Rev)*(1min/60sec) 
   where pinionRev = encoder pinion
*/
#define TIE_PENC_REVPS_PER_DACNT	   			4.5211227-4

/*	there are 4096 encoder counts/encoder revolution */

#define TIE_PENC_CNTPS_PER_DACNT      	1.851850752
#define TIE_DACNTS_PER_PENC_CNTPS         .54
 
/* da counts if penc changes by 1 count in 5 ms */

#define TIE_DACNTS_PER_PENC_CNTPER5MS    108.
#define TIE_PENC_CNTPER5MS_PER_DACNT       .009259

/* now give velocities in inches/sec	*/

/*  (1daCnt/(1.85185encCnt/Sec)  * (43663.36 encCnt/inch) */

#define TIE_DACNTS_PER_INCHPS          23578.2284
#define TIE_INCHPS_PER_DACNT          4.241203269e-5  

/* acceleraion if dacnt changes by 1 count in 5 millisecs*/

#define TIE_1DACNT_IN_5MS_PER_INCHPS2   117.8911629
#define TIE_INCHPS2_PER_1DACNT_IN_5MS   .0084824

/* pid coeff.. for reference only. used by micro..*/

#define TIE_PID_FF_Kp	108.
#define TIE_PID_LL_Kp	4.80
#define TIE_PID_LL_Ki	.1066

#if FALSE
#define TIE_INCHES_TO_POS_ENC_UNITS      (1./2.29024976e-5)
#define TIE_IN_PER_SEC_TO_DA_CNT  (1./4.241203269e-5)

#endif

/* these values measured by ricardo...*/

#define TIE_ANA_CNV_P24_V   .0069
#define TIE_ANA_CNV_N24_V   .0135
#define TIE_ANA_CNV_B24_V   .0068
#define TIE_ANA_CNV_ENC_V   .00135

/*   22aug97 .. this needs to be fixed ???*/
#define TIE_ANA_CNV_V_FB_DS .0069  
/* 	not correct values yet...*/
/*#define TIE_ANA_CNV_MOTCUR_A   .00305  */
/* 4feb99 page 2-9 kolmorgan bds4/psr manual
	20ampspeak/8volts * 2.5/2048 =.00305 
	still off. forced foldback current to be 10 amps geave .01788
*/
#define TIE_ANA_CNV_MOTCUR_A   .01788
/*
*	30aug99 dome motor on td 4. v=.0276 + .0066701*counts
*		and calibration page from kollmorgan give 5ampsrms/volt so
*		amps=.138 + .03335*counts
*       - velocity calibration:
*		  4.75V spdmon = 695 counts=5.80 cmd volts.
*          695/4.75=146.3  counts/volt 
*	       193.75 rpm/volt spdmon kollmorgan ..so  
*		   or 193.75/146.3=1.324 rpm/count
*/

#define TIE_ANA_CNV_MOTCUR_A_NEW   .03335
#define TIE_ANA_CNV_MOTSPD_RPM_NEW 1.324
#
#define TIE_ANA_CNV_MOTSPD_DS  18. 
#define TIE_ANA_CNV_MOTSPD_RPM 3. 
#


/* 
 * 28nov98 .0197--> .02
*/
#define TIE_LDCELL_CNTS_TO_KIPS     .02

/* riccardos memo 10jun97 */


/* 25aug98 switched to .02 kips/count all tiedowns*/

#define	TIE_LDC8_1_OFF 			   0.
#define	TIE_LDC8_1_GAIN			.02

#define	TIE_LDC8_2_OFF 			   0.
#define	TIE_LDC8_2_GAIN			.02

#define	TIE_LDC12_1_OFF  	       0.
#define	TIE_LDC12_1_GAIN        .02

#define	TIE_LDC12_2_OFF  	       0.
#define	TIE_LDC12_2_GAIN        .02

#define	TIE_LDC4_1_OFF  	       0.
#define	TIE_LDC4_1_GAIN  	    .02

#define	TIE_LDC4_2_OFF  	       0.
#define	TIE_LDC4_2_GAIN  	    .02

#define TIE_LDC12_2_ETOK(enc)	( (enc-TIE_LDC12_2_OFF)*TIE_LDC12_2_GAIN)
#define TIE_LDC4_2_ETOK(enc)	( (enc-TIE_LDC4_2_OFF )*TIE_LDC4_2_GAIN)
#define TIE_LDC8_2_ETOK(enc)	( (enc-TIE_LDC8_2_OFF )*TIE_LDC8_2_GAIN)

#define TIE_LDC12_1_ETOK(enc)	( (enc-TIE_LDC12_1_OFF)*TIE_LDC12_1_GAIN)
#define TIE_LDC4_1_ETOK(enc)	( (enc-TIE_LDC4_1_OFF )*TIE_LDC4_1_GAIN)
#define TIE_LDC8_1_ETOK(enc)	( (enc-TIE_LDC8_1_OFF )*TIE_LDC8_1_GAIN)

/*
 * some other constants
 * T8
 * raw encoder value all the way down.. 50369
 * raw encoder value all the way Up  ..
*/

/*
 * tiedown specific commands from vme to slave microprocessor.
*/
#define TIE_SLV_CMD_SET_FDBACK 0x16
#define TIE_SLV_CMD_MNT_MODE   0x17
/*
 * tiedown specific ptrs into get status block 
*/
#define TTT_GSIND_TIE_LDCELL1      7 
#define TTT_GSIND_TIE_LDCELL2      8 
/*
 * parameter numbers for tiedowns.. different than turret/tertiary
*/
#define PNT_TIE_PNUM_BRAKE_MINVEL     0
#define PNT_TIE_PNUM_MAXVEL           1
#define PNT_TIE_PNUM_ALARM_DUR        2
#define PNT_TIE_PNUM_MAXVEL_DIF       3
#define PNT_TIE_PNUM_MAXACC           4 
#define PNT_TIE_PNUM_MAXPOS           5 
#define PNT_TIE_PNUM_MINPOS           6
#define PNT_TIE_PNUM_STOPBAND         7
#define PNT_TIE_PNUM_FREE8            8
#define PNT_TIE_PNUM_FREE9            9
#define PNT_TIE_PNUM_FREE10          10
#define PNT_TIE_PNUM_FREE11          11
#define PNT_TIE_PNUM_L_KA            12
#define PNT_TIE_PNUM_L_KI            13
#define PNT_TIE_PNUM_L_KP            14
#define PNT_TIE_PNUM_L_KD            15
#define PNT_TIE_PNUM_L_KF            16
#define PNT_TIE_PNUM_RATE_FACTOR     17
#define PNT_TIE_PNUM_MAXPOS_STEP_C   18
#define PNT_TIE_PNUM_0_VEL_OFFSET    19
#define PNT_TIE_PNUM_NET_ADR         20
#define PNT_TIE_PNUM_BIG_STEP        21
#define PNT_TIE_PNUM_SW_VERSION      22 
#define PNT_TIE_PNUM_MAX_TENSION     23
#define PNT_TIE_PNUM_MIN_TENSION     24
#define PNT_TIE_PNUM_RESET_PARAMS    25
#define PNT_TIE_PNUM_ENC_OFFSET      26
#define PNT_TIE_PNUM_LAST            26
/* 
 * reply message from slave  TIE downs
*/ 
typedef struct { 
	int				timeMs;		/* milliseconds from midnite*/	
	int				position;   /* encoder*/
	int				ldCell1;    /* load cell1 value*/
	int				ldCell2;    /* load cell2 value*/
	unsigned short  devStat;	/* device status*/ 
	short           dataValue;	/* data value.. signed and unsigned.*/
	char			optData[256];/* optional data could by multi byte*/
} TIE_MSG_FROM_SLV;
/*
 * get status reply in optional data tiedowns
*/
typedef struct {
	unsigned	short	aI_ps24P;
	unsigned	short	aI_ps24N;
	unsigned	short	aI_psB24P;
	unsigned	short	aI_psEnc5P;
	        	short	aI_VelFB;
	unsigned	short	aI_mAmpCurMon;
	unsigned	short	aI_mAmpSpdMon;
	unsigned	short	aI_ldCell1;
	unsigned	short	aI_ldCell2;
	unsigned	short	aI_accel;		/* used for dbging Ki,Kp*/
	unsigned	short	aI_ratePotPcu;

	unsigned	short	aO_velCmd;

	unsigned    short   dI_LS;			/* little star */
	unsigned    short   dI_uio1;		/* universal i/o 1*/
	unsigned    short   dI_uio2;		/* universal i/o 2*/
	unsigned    short   fill1;			/* not in use ..used for dbg Ki,Kp*/ 

	unsigned    short   dO_LSuio1;		/* little star and uio 1*/
	unsigned    short   dO_uio2_fill;   /* universal i/o 2, filler*/

	unsigned    short   st_mDrv;        /* master drive*/
	unsigned    short   fill2;       	/* not used used fordbg Ki,Kp*/
	unsigned    short   st_safLimLockAxis;      /* slave drive*/
	unsigned    short   st_fault;      /* fault*/
	} TIE_GET_STATUS_DATA;

typedef struct {
	int	timeMsCmd;
	int	cmdPos[3];
	int	timeMsMeas[3];
	int	measPos[3];	/* previous second*/
	} TIE_LOG_PT;
/*
 * 14nov98 new message format:
 * <pjp001>
*/
/*
 * typedefs to send message to slave
*/
typedef struct  {
    int     timeMs;     /* millisecs from midnite*/
    int     pos;        /* position at timeMs.. encoder counts*/
    short   inc[10];	/* increment to get to next 100 ms. encoder counts*/
    } TIE_MSG_TO_SLV_PTDATA;
 
 
typedef union   {
      TIE_MSG_TO_SLV_PTDATA    ptData;  /* program track positions for buffer*/
      int                     slewPos;  /* to slew to*/
      char                    reqParm;  /* parameter number to request*/
      char                    dataByte; /* for generic uses*/
      int                     dataInt; /* for generic uses*/
      TTT_MSG_TO_SLV_SETPARM   setParm;/*set parameter*/
      int                     setTime;/* set the time(ms) or clock(sec)*/
      } TIE_MSG_TO_SLV_DATA;
 
/*
 * generic turret/tertiary message to slave
*/
typedef struct {
    char                cmd;
    char            retDataInd;   /* for data value to return*/
    TIE_MSG_TO_SLV_DATA data;
    int             dataBytes;  /* of data this msg(not including cmd)*/
    int             devToUse;   /* 1-tur,2-ter1,4-ter2,8-ter3..or together*/
                                /*   1-tie1, 2-tie2,4-tie3 */
   } TIE_MSG_TO_SLV;

#endif
