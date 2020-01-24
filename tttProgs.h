#ifndef 	INCtttProgsh
#define 	INCtttProgsh
#include	"mathCon.h"
/*
 * include file for ttProg.h, tieProg. holds the generic  msg formats to 
 * communicate with the turret and tertiary and tiedowns.
 * The device specifiec info is stored in tieProg.h and ttProg.h. Thie
 * file is include by those 2
*/

/* max index for analog/digital data returned from turret
 * number of entries  == maxindex + 1 since the index counts from 1.
*/
#define TTT_MAX_DATA_IND	  21

/* when cycling through data index only go to 11 to get last analog value.
 * To get the discrete values, do a getstatus
*/

#define TTT_MAX_ANAVAL_IND 11
#define TTT_MAX_FAULT_LOG   7

/*
 * generic commands from vme to slave microprocessor.
*/
#define TTT_SLV_CMD_NOP		    0x0
#define TTT_SLV_CMD_RESET		0x1
#define TTT_SLV_CMD_PT_DATA     0x2
#define TTT_SLV_CMD_STOP        0x3
#define TTT_SLV_CMD_PT          0x4
#define TTT_SLV_CMD_SLEW        0x5
#define TTT_SLV_CMD_REQ_STAT    0x6
#define TTT_SLV_CMD_REQ_PARM    0x7
#define TTT_SLV_CMD_SET_PARM    0x8
#define TTT_SLV_CMD_FLUSH_BUF   0xa
#define TTT_SLV_CMD_BRAKES_ON   0xb
#define TTT_SLV_CMD_BRAKES_OFF  0xc
#define TTT_SLV_CMD_SET_TIME    0xd
#define TTT_SLV_CMD_REQ_TIME    0xe
#define TTT_SLV_CMD_PWR_ON      0xf
#define TTT_SLV_CMD_PWR_OFF    0x10
#define TTT_SLV_CMD_REQ_LOG    0x11
#define TTT_SLV_CMD_SET_CLOCK  0x12
#define TTT_SLV_CMD_REQ_CLOCK  0x13
#define TTT_SLV_CMD_PURGE_LOG  0x14
#define TTT_SLV_CMD_GET_FREEPOS 0x15
/*
 * motor  drive status
*/	
#define	TTT_DRIVE_DISABLED     0 
#define	TTT_DRIVE_ENABLED      1
#define	TTT_DRIVE_POWERED      2
#define	TTT_DRIVE_FAULT        3
/*
 * indices into get status
*/
#define TTT_GSIND_GEN_P24	       0 
#define TTT_GSIND_GEN_N24	       1 
#define TTT_GSIND_GEN_B24	       2 
#define TTT_GSIND_GEN_ENCMON       3 
#define TTT_GSIND_GEN_V_FB         4 
#define TTT_GSIND_GEN_M_I_MON      5 
#define TTT_GSIND_GEN_M_S_MON      6 
#define TTT_GSIND_GEN_ACCEL        9 
#define TTT_GSIND_GEN_RATE_PCU    10 
#define TTT_GSIND_GEN_VEL_CMD     11 
#define TTT_GSIND_GEN_DI_LS       12 
#define TTT_GSIND_GEN_DI_UIO1     13 
#define TTT_GSIND_GEN_DI_UIO2     14 
#define TTT_GSIND_GEN_DO_LS_UIO1  16 
#define TTT_GSIND_GEN_DO_UIO2_3   17 
#define TTT_GSIND_GEN_DRVSTAT_M   18 
#define TTT_GSIND_GEN_SAFETY      20 
#define TTT_GSIND_GEN_FAULTS      21 

/*
 * analog return value conversions levels to engineering units
*/
#define TTT_ANA_CNV_P24_V	.008 
#define TTT_ANA_CNV_N24_V	.016
#define TTT_ANA_CNV_B24_V	.008
#define TTT_ANA_CNV_ENC_V	.0025
#define TTT_ANA_CNV_V_FB_DS .01472
#define TTT_ANA_CNV_MOTCUR_A   .00305
#define TTT_ANA_CNV_MOTSPD_DS  .01797
/*
 * typedefs to send message to slave 
*/
typedef struct	{
	int		timeMs;		/* millisecs from midnite*/
	int		pos[5];		/* 5 positions*/
	} TTT_MSG_TO_SLV_PTDATA; 


typedef  struct  {
		unsigned short   val;		/* value*/
		char	         num;		/* parameter number*/
	} TTT_MSG_TO_SLV_SETPARM;	

typedef	union	{
	  TTT_MSG_TO_SLV_PTDATA    ptData;	/* program track positions for buffer*/
	  int 			          slewPos;  /* to slew to*/
	  char			          reqParm;	/* parameter number to request*/		
	  char					  dataByte; /* for generic uses*/
	  int                     dataInt; /* for generic uses*/
	  TTT_MSG_TO_SLV_SETPARM   setParm;/*set parameter*/
	  int			          setTime;/* set the time(ms) or clock(sec)*/ 
	  } TTT_MSG_TO_SLV_DATA;

/*
 * generic turret/tertiary message to slave
*/
typedef struct {
	char                cmd;
	char			retDataInd;   /* for data value to return*/
	TTT_MSG_TO_SLV_DATA data;	
	int				dataBytes;	/* of data this msg(not including cmd)*/
	int			    devToUse;   /* 1-tur,2-ter1,4-ter2,8-ter3..or together*/
								/*   1-tie1, 2-tie2,4-tie3 */
   } TTT_MSG_TO_SLV; 
/*
 * hold ptrs to labels for a status word
*/
typedef struct {
    char    *pon;       /* on label*/
    char    *poff;      /* off label*/
	int		grpNum;		/* not 0 --> decode it*/
    } TTT_LABELS;
/*
 * timing interval info
*/
typedef struct {
    double  lastIntvl;
    double  minIntvl;
    double  maxIntvl;
    } TTT_TIME_INTVL;
/*
 * 	typedefs used in the program state definition
*/

/* program track buffer status */
 
typedef struct {
    int     errCntBuf;  /* getting,putting buf*/
    int     errCntMsg;  /* getting,putting msgs*/
    int     lastErrBuf; /* remember the error*/
    int     lastErrMsg; /* remember the last error*/
    int     numSkipped; /* number skipped since time has passed*/
    int     lastSkipped;/* last off queue was skipped or not*/
    } TTT_ST_PT_INFO;
typedef struct {
        int      timeMs[TTT_MAX_DATA_IND+1];    /* value measured*/
        short    val[TTT_MAX_DATA_IND+1];           /* analog value*/
    }TTT_DATA_VALUE;
 
typedef struct {
        int     meas;           /* measured time*/
        int     compTm1;        /* compare time1*/
        int     compTm2;        /* compare time2*/
    }TTT_CLOCK_TIME;
 
typedef struct {
        int             timeSt;        /* time stamp*/
        unsigned short  count;         /* count*/
        unsigned short  id;            /* fault id.*/
     } TTT_FAULT_LOG;
#endif
