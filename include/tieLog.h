#ifndef     INCtieLogh
#define     INCtieLogh
#include	"tieProgState.h"


/*  fixed msg info comes back every msg */
 
/*
 * 	info read from device at the tick
*/
typedef struct {
	int				timeMs;		/* time ms from device at tick*/
	int				position;	/* encoder counts position*/
	int				ldCell1;	/* load cell 1 raw counts*/
	int				ldCell2;	/* load cell 1 raw counts*/
	unsigned short  devStat;    /* returned in device msg*/
	short 			dataValid;  /* 0--> this data not valid*/
    TIE_GET_STATUS_DATA data;    /* returned from getstatus call*/
	} TIE_LOG_TICK;	
 
typedef struct {
		TIE_PRGSLV_STATWD   statWd;/* stat word.. bitfield left to right*/
#if FALSE
        int slewDest;           /* slew destination, encoder units*/
#endif
        int lastReqPos;         /* last req position*/
		int	ioTry;				/* send/rcv attempts*/
		int	ioFail;				/* snd/rcv fail*/
        TIE_LOG_TICK 	 tickI;/* info at tick*/
      }TIE_LOG_SLV;

typedef struct {
    int             secMLastTick;       /* seconds midnite last tick*/
    int             statWd;             /* status word*/
	int			    syncTry;			/* times we tried to sync/master*/
	int			    syncFail;		    /* times we failed to sync*/
	int			    vtxTmMs;			/* timestamp from vertex*/
	int				azPos;				/* ten thousandths of a deg*/
	int				grPos;				/* ten thousandths of a deg*/
	int				chPos;				/* ten thousandths of a deg*/
	int			    tempPl;				/* platform temperature*/
    TIE_LOG_SLV    slv[TIE_MAX_NUM_DEV];/* tie1,tie2,tie3*/
    } TIE_LOG;

#endif
