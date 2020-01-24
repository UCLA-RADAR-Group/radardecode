#ifndef     INCtieProgStateh 
#define     INCtieProgStateh
#include	"tieProg.h"

/*
 * modification history
 * 16feb00 <pjp005> slewDest -> lastReqPos
*/

#if FALSE
/*
 * slave status word
*/
#define TIE_PROGSTSLV_INUSE         0x80000000
#define TIE_PROGSTSLV_LASTIO_OK     0x40000000
#define TIE_PROGSTSLV_PT            0x20000000
#endif

#define TIE_DLOG_PT_NAME  "/share/obs2/tie/pt/dlogPt"


/*  fixed msg info comes back every msg */
 
typedef struct {
    int             timeMs;     /* milliseconds from midnite*/
    int             position;   /* in encoder counts*/
	int			    ldCell1;
	int			    ldCell2;
    unsigned short  devStat;    /* device status*/
    short           dataValue;  /* data value.. signed and unsigned.*/
	int			    bytesInp;	/* last msg*/
    int             fill[2];    /* round to  32 bytes*/
    } TIE_INP_MSG_FIXED;

/*  tie slave status word 32 bits as a bitfield */
 
typedef struct {
    unsigned int    inUse       :1;
    unsigned int    free1       :1; /* pjp006*/
    unsigned int    modeReq     :3;
    unsigned int    fdBackReq   :2;
    unsigned int    modeCur     :3; 	/* <pjp001> */
    unsigned int    lastIoROk   :1;    /*pjp006*/
    unsigned int    lastIoWOk   :1;
    unsigned int    fill        :20;
    } TIE_PRGSLV_STATWD;

/*  tie program status word 32 bits as a bitfield */
 
typedef struct {
	unsigned int	wrongMode   : 1;	/*1-->at least 1 micro not right mode*/
    unsigned int    fill        :25;
	unsigned int	procTick    : 1;	/* 1--> doing tick processing*/
	unsigned int	ptFutTime   : 1;	/* last pt req in the future*/
	unsigned int	ptLastSkipped: 1;	/* last pt req time had passed.d*/
	unsigned int	fill1       : 1;	/* not used*/
	unsigned int	syncMst1    : 1;	/* syncing master*/
	unsigned int	prgRunning  : 1;	/* tieProg is running*/
    } TIE_PROG_STATWD;

 
typedef struct {
		TIE_PRGSLV_STATWD 	statWd;
#if FALSE
        int statWd;             /* our status word this slave*/
        int mode;               /* device is in*/
		int	feedBack;			/* use avg, ldcell1,2,or encoder 0-->3*/
        int slewDest;           /* slew destination, encoder units*/
#endif
		int	lastReqPos;			/* enc units.. for this tick*/
		int	ioTry;				/* send/rcv attempts*/
		int	ioFail;				/* snd/rcv fail*/
        TIE_INP_MSG_FIXED inpMsg;/* last msg input, fixed part*/
        TIE_INP_MSG_FIXED tickMsg;/* inp message at last tick*/
        /*
         * the parts of the msg that may change optional data
        */
        TTT_CLOCK_TIME getTime;  /* meas:ms,tm1..ao sec midnite*/
        TTT_CLOCK_TIME getClock; /* meas:sec, tm1..ao secmid tm2:ms tm micro*/
        /* this is from the get status dump */
        TTT_DATA_VALUE   data;       /* data values read in*/
        /* from get log */
        TTT_FAULT_LOG    fltLog[TTT_MAX_FAULT_LOG];/* from get log*/
      }TIE_STATE_SLV;

typedef struct {
    int             secMLastTick;       /* seconds midnite last tick*/
	TIE_PROG_STATWD statWd;
	int			    syncTry;			/* times we tried to sync/master*/
	int			    syncFail;		    /* times we failed to sync*/
    TTT_ST_PT_INFO   ptI;               /* state of program track queue*/
    TIE_STATE_SLV    slv[TIE_MAX_NUM_DEV];/* tie1,tie2,tie3*/
    } TIE_STATE;
/*-------------------------------------------------------------------------
 * to access the 16 bit status words returned from little star
 * as a structure/bitfield, we need to define the structure and 
 * a union since bitfields on the sun want to be 32 bits long
*/
/* GeneralStatus, devStatus return from little star*/

typedef struct {
	unsigned int	trandDat:1 	;	
	unsigned int	rebooted:1 	;	/* little start has rebooted*/
	unsigned int	mode    :2  ;   /* stop,trk,slew,maint..0->3*/
	unsigned int    brkOff  :1  ;   /* 1 if brake off*/
	unsigned int    remCtrl :1  ;   /* 1 if in remote control*/
	unsigned int    drvEnab :1  ;   /* 1 if drive is enabled*/
	unsigned int    pwrOn   :1  ;   /* 1 if power is on*/
	unsigned int    fdBack  :2  ;   /* ldcAv,ldc1,ldc2,encoder*/
	unsigned int    trkFlt  :1  ;   /* tracking fault*/
	unsigned int    warning :1  ;   
	unsigned int    fill2   :1  ;   
	unsigned int    drv1Flt :1  ;   /* drive fault*/
	unsigned int    axisFlt :1  ;
	unsigned int    safetyO :1  ;   /* 1 if safety open*/
	} TIE_DEV_STATUS;

typedef union {
	TIE_DEV_STATUS  bf;		/* bit field access*/
	unsigned int	sh;		/* load the short here*/
	} TIE_DEV_STATUS_U;

/* MDrvState, MDriveStatus  from little star*/

typedef struct {
    unsigned int    fill1   :9  ;
    unsigned int foldBackFlt:1  ;   /* 1 if amp fold back*/
    unsigned int motOverTemp:1  ;   /* 1 if motor over temperature*/
    unsigned int drvOverTemp:1  ;   /* 1 if drive over temp*/
    unsigned int  outputFlt :1  ;   /* 1 if output fault*/
    unsigned int  fltContOpn:1  ;   /* 1 if fault contactor open*/
    unsigned int       state:2  ;   /* disable,enable,powered,fault*/
    } TIE_MOT_STATUS;

typedef union {
	TIE_MOT_STATUS  bf;		/* bit field access*/
	unsigned int	sh;		/* load the short here*/
	} TIE_MOT_STATUS_U;

/* safety,limit,axis status */

typedef struct {
    unsigned int safetyStat :4  ;
    unsigned int limitStat  :4  ;   /* 1 if amp fold back*/
    unsigned int fill       :4  ;   /* 1 if motor over temperature*/
    unsigned int axisStat   :4  ;   /* 1 if drive over temp*/
    } TIE_SAFLIMAXIS_STATUS;

typedef union {
	TIE_SAFLIMAXIS_STATUS  bf;		/* bit field access*/
	unsigned int	       sh;		/* load the short here*/
	} TIE_SAFLIMAXIS_STATUS_U;

/* fault status */

typedef struct {
    unsigned int fill1      :7  ;
    unsigned int brkFail    :1  ;   /* 1 if brake failure*/
    unsigned int fill2      :1  ;   
    unsigned int pwrSFail   :1  ;   /* 1 if power supply trouble*/
    unsigned int fill3      :1  ;  
    unsigned int drv1Fail   :1  ;   /* 1 if drive failure*/
    unsigned int overSpeed  :1  ;   /* 1 if drive over speed*/
    unsigned int cmdSpdErr  :1  ;   /* 1 if commanded/measured disagree*/
    unsigned int fill4      :1  ;  
    unsigned int safetyOpen :1  ;   /* 1 if safety is open*/
    } TIE_FAULT_STATUS;

typedef union {
	TIE_FAULT_STATUS  bf;		/* bit field access*/
	unsigned int      sh;		/* load the short here*/
	} TIE_FAULT_STATUS_U;

/* here they are all grouped together.. see routine tieLsStat()*/

typedef struct {
	TIE_DEV_STATUS_U	devStat;
	TIE_FAULT_STATUS_U	fltStat;
	TIE_MOT_STATUS_U	motStat;
	TIE_SAFLIMAXIS_STATUS_U	safLimAxis;
	} TIE_LS_STAT;


/*-------------------------------------------------------------------------
 * for program track log
*/

typedef struct {
	/*
	 * requested position
	*/
	int	timeMsCmd;
	int	cmdPos[3];
	/*
	 * position on last second
	*/
	int	timeMsMeas[3];
	int	measPos[3];	/* previous second*/
	} TIE_TRACKING_LOG;
#endif
