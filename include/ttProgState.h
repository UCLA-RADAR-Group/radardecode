#ifndef     INCttProgStateh
#define     INCttProgStateh
#include	"ttProg.h"
#include	"tttProgs.h"


/*  fixed msg info comes back every msg */
 
typedef struct {
    int             timeMs;     /* milliseconds from midnite*/
    int             position;
    unsigned short  devStat;    /* device status*/
    short           dataValue;  /* data value.. signed and unsigned.*/
    int             bytesInp;   /* bytes input for msg*/
    } TT_INP_MSG_FIXED;
 
typedef struct {
     	TT_PRGSLV_STATWD statWd;
#if FALSE
        int statWd;             /* our status word this slave*/
        int mode;               /* device is in*/
#endif
        int 			slewDest;/* slew destination encoder units*/
		int				ioTry;	 /* send/rcv attempts*/
		int				ioFail;  /* snd/rcv fail*/
        TT_INP_MSG_FIXED inpMsg; /* last msg input, fixed part*/
        TT_INP_MSG_FIXED tickMsg;/* inp message at last tick*/
        /*
         * the parts of the msg that may change optional data
        */
        TTT_CLOCK_TIME getTime;  /* meas:ms,tm1..ao sec midnite*/
        TTT_CLOCK_TIME getClock; /* meas:sec, tm1..ao secmid tm2:ms tm micro*/
        /* this is from the get status dump */
        TTT_DATA_VALUE   data;       /* data values read in*/
        /* from get log */
        TTT_FAULT_LOG    fltLog[TTT_MAX_FAULT_LOG];/* from get log*/
      }TT_STATE_SLV;

typedef struct {
    int             secMLastTick;       /* seconds midnite last tick*/
    int             statWd;             /* status word*/
	int			    syncTry[2];			/* times we tried to sync/master*/
	int			    syncFail[2];		/* times we failed to sync*/
    TTT_ST_PT_INFO   ptI;                /* state of program track queue*/

    TT_STATE_SLV    slv[4];             /* tur,ter1,ter2,ter3*/
    } TT_STATE;

#endif
