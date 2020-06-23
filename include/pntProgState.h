/*
 *	include file for pntProg.h  
 *  This is the state of pntProg that can be run on vxWorks or sun os.
 * 
 *  the program state general outline:
 *--------------------------------
    st.t - from pntTcl interpreter.. but this has been removed
	st.x - from pntXform .. 
 *--------------------------------
	st.x.pl - pipelined requests that are computed 2 seconds in the 
		      future. When scramnet memory is loaded, it gets the 
	          pipelined data for the current second.
	     pl.tm   - times for 2 seconds in the future.
	     pl.curP - agc computed position for  2 seconds in the future
	     pl.req  - agc request. 
				   a.requested point (pos,off,rate,time) for time in future
				   b.reqState(trk,hold),master,pntCor,settleTm,trackTol
				   a. --> pl.curP when the time arrives.
				   b. --> gets applied immediately..
		 pl.curTur   - current turret request. position,pattern
	 	 pl.reqTur   - turret request for time in future.
		 pl.curTie   - current tiedown request. position,pattern
		 pl.reqTur   - tiedown request for time in future.
		 pl.model    - outdated.. holds encoder offsets if model correction
		           was selected as encoder.. hardly ever used.
*--------------------------------
 * 30nov98 - updated for tiedown changes..old file pntProgState.hold
 * 15sep99 - include tiedown auto tracking pattern
 * 16feb00 - progStat include 2 bits for td tracking mode
 * 21feb00 - <pjp016> in PNT_X_CUR_TUR.. switch 
    	int        reqState;  0-noReq,1-tracking ,2-holdpnt
        int        validPnt;  true--> pntXform looks at point
        int        movCode;   1-sin,2-pos,vel,3-scan
	    to : statWd:
			 tempF
			 fill 1
		and statWd will have the reqState,validPnt,movCode
 *3mar00  - <pjp018> include avgPlatHgt in x_cur_tie. was a filler location
 *14apr00 -  adde lrLastTempOk. lrLastHghtOk in PNT_X_STATWD
 *13jul01 -  added code for tertiary
 *13oct02 -  PNT_X_STATWD lrNoComCnt .. not talkin to distomats added..
 *            PNT_X_CUR_tie_STATWD distOk:6.. 1 each bit--> distomat ok.
 *09feb04 - added paralactic angle to pntProgState, axis,validPnt went
 *          int -> short size doesn't change...
 *17mar04 - <pjp032> added alfrProgRunning to status
 *18oct07 - <pjp038> added 2 doubles.. model corection for encoder az,za
 *10oct14 - moved some things to pntMisc. so they could be included in 
 *          12meter and 305 meter code
*/
#ifndef INCpntProgStateh
#define INCpntProgStateh
#if 0
   lib not yet converted..
#include "pntXformLib.h"
#endif   
#include "pntMisc.h"
#include <pntProgMsg.h>

/*	defines		*/

#define         PNTX_REQ_NOTRACK 0
#define         PNTX_REQ_TRACK   1
#define         PNTX_REQ_HOLD    2
#define         PNTX_REQ_EXIT    3
 
#define         MASTER_GREG 1
#define         MASTER_CH   2
/*
 * correction.. none, model, encoder only
*/
#define		    PNTX_COR_NONE	0
#define		    PNTX_COR_MODEL  1
#define		    PNTX_COR_ENC    2

#define         PNTX_ZACOR_IND_GR  0   
#define         PNTX_ZACOR_IND_CH  1   

/*	typedefs	*/
#if 0
.. moved to pntMisc.h

/* the fill values are to keep doubles/structures aligned on  8 byte
 * boundaries. this is to get around the different packing of structures
 * done by 68k and the sun.
*/

typedef struct {
    double      c1;     /* coordinate 1*/
    double      c2;     /* coordinate 2*/
    double      st;     /* start time .. seconds from midnight ast*/
    int         cs;     /* coordinate system for this coordinate*/
	int		   fill;
    } PNT_TUPLE;
/*
 * coordinate. Set of tupples that defines a point in pos,off,rate space
*/
typedef struct {
        PNT_TUPLE  pos;        /* position (8*int)*/
        PNT_TUPLE  off;        /* offset   (8*int)*/
        PNT_TUPLE  rate;       /* rate     (8*int)*/
        double     rateStDayNum;/* dayNum.frac ast for start time */
        double     rateDur;     /* duration rate active. solar secs*/
    }  PNT_COORD;			   /* 28*int*/
#endif

/******************************************************************************
*	pntXform state
******************************************************************************/
/*
 * time info as computed by pntXform
*/
typedef struct {
        double  secMidD;    /* seconds from midnight double..*/
        double  astFrac;    /* fraction of day ast*/
        double  ut1Frac;    /* fraction of day ut1t*/
        double  lmstRd;     /* local mean sidereal time in radians*/
        double  lastRd;     /* local apparent sidereal time in radians*/
        int     dayNum;     /* dayNumber 1..366 ast*/
        int     year;       /* 4 digit ast*/
        int     mjd;        /* modified julian day for ut1Frac*/
		int		fill;
    } PNT_X_TIME;			/* 14 * int*/
/*
 * current point we are tracking
*/
typedef struct {
        PNT_COORD   pnt;    /* coordinate req (28*int)*/
        double      raDecTrueV[3];
        double      aberV[3];/* aberation vector*/
        double      raDecAppV[3];/*apparent ra/dec */
        double      haAppRd;     /*hour angle apparent*/
        double      azRd;        /* enc az radians (after exit compOffsets)*/
        double      zaRd;        /* feed za radians */
								/* warning.. xxOffCum only valid if
								   offset & rate are same coord sys*/
        double      c1OffCum;    /* we've applied to the 1st coord*/
        double      c2OffCum;
        double      lastAzRd;   /* for computing wrap*/
		double		corAzRd;	/* total correction azimuth*/
		double		corZaRd;	/* total correction zenith angle*/
        double      modelCorAzRd;  /* model correction az*/
        double      modelCorZaRd;  /* model correction za*/
        double      modelLocAzDeg;/* where we evaluated*/
        double      modelLocZaDeg;
		double		raJ;		 /* ra J2000 back converted from az,za*/
		double		decJ;		 /* dec J2000 back converted from az,za*/
		double		geoVelProj;  /* geocentric vel observer projected onto
									raJ,decJ. units:v/c*/
		double      helioVelProj;/* helio centric vel observer projected. v/c*/
        short       validPnt;/* false on startup, and after a stop*/
        short       axis;       /* to control 1-az,2-gr,4-ch*/
		float		parallacticRd; /* parallactic angle in radians*/
#if FALSE
        int         validPnt;/* false on startup, and after a stop*/
        int         axis;       /* to control 1-az,2-gr,4-ch*/
		float		paralacticRd; /* paralactic angle in radians*/
		int         filler;	      /* filler*/	
#endif
    } PNT_X_CUR_PNT;  /*(52*int)*/
/*
 * pntXform request info
*/
typedef struct {
        int        wrapReq;    /* 0-compute,1-[0,360),2-[360.,720]*/
        int        reqState;   /* 0-none,1-track,2-hold,3-exit*/
        int        pendPValid;/* true--> pntXform looks at point*/
        int        master;    /* to use 1 gr, 2 ch */
		int		   pntCor;    /* pointing correction. 0-none,1-model,2-enc*/
		short settleTmSec; 	  /* settle time in seconds <pjp001>*/
		short      fill; 	  
		double     trackTol;  /* tolerance for tracking.. radians*/
        PNT_COORD  pendP;      /* 28*int pending point */
    }   PNT_X_REQ;			   /* 36*int*/
/*
 * pntXform requests for turret, map onto  pnt_coord_tur
*/
typedef struct {
		float   c[4];       /* coordinate info*/
		} PNT_COORD_TT;
/* 	sin motion 	*/
typedef struct {
    float       posStRd;        /* start posiition in radians*/
    float       ampRd;          /* amplitude in radians*/
    float       frqW;           /* frequency radians/sec*/
    float       phaseRd;        /* phase offset radians*/
    } PNT_X_TUR_SIN;

/* position and constant velocity*/
 
typedef struct {
    float       posStRd;        /* start posiition in radians*/
    float       velRdSec;       /* radians per second*/
    int         filler[2];      /* how long we've being doing it*/
    } PNT_X_TUR_PV;

/*  scan between two points with constant time*/

typedef struct {
    float       pos1Rd;     /* start posiition in radians*/
    float       pos2Rd;     /* end position in radians*/
    float       timeMovSec; /* time to move between two points*/
    int         filler;
    } PNT_X_TUR_SCAN;
	
typedef struct {
    unsigned int    reqState:2; /* 0-noReq,1-tracking ,2-holdpnt*/
    unsigned int    validPnt:1; /* true--> pntXform looks at point*/
    unsigned int     movCode:3; /* 1-sin,2-pos,vel,3-scan,4-tietrk*/
    unsigned int        fill:26;
    }PNT_X_TUR_STATWD;

typedef struct {
        PNT_X_TUR_STATWD statWd;
		int		   fill;	
		double     startTm;    /* seconds from midnite*/
        PNT_COORD_TT pnt;      /* pending point */
    }   PNT_X_REQ_TUR; 		   /* int*/

typedef struct {
        PNT_X_TUR_STATWD statWd;
		int        timeStamp;/* ditto*/
		float	   pos;		 /* value sent to turret*/
		float	   vel;		 /* ditto */
        double     stDayNum; /* dayNum.frac ast for start time */
        PNT_COORD_TT pnt;    /* coordinate passed to use */
    }   PNT_X_CUR_TUR; 		
/*
 * tiedown info
*/
typedef struct {
    unsigned int    reqState:2; /* 0-noReq,1-tracking ,2-holdpnt*/
    unsigned int    validPnt:1; /* true--> pntXform looks at point*/
    unsigned int     movCode:3; /* 1-sin,2-pos,vel,3-scan,4-tietrk*/
    unsigned int        fill:26;
    } PNT_X_REQ_TIE_STATWD;

typedef struct {
        PNT_X_REQ_TIE_STATWD statWd;
        int        fill;
        double     startTm;    /* seconds from midnite*/
        PNT_TIE_PAT pnt;      /* pending point pattern request*/
    }   PNT_X_REQ_TIE;         /* int*/

typedef struct {
	unsigned int	reqState:2; /* 0-noReq,1-tracking ,2-holdpnt*/
    unsigned int    validPnt:1; /* true--> pntXform looks at point*/
    unsigned int     movCode:3; /* 1-sin,2-pos,vel,3-scan,4-tietrk*/
	unsigned int	atrkMode:3; /* 0-no,1-temp,2-pos,3-postemp*/
	unsigned int	atrkHghtUseTemp:1;/* trk hgt, no lr so used temp from last
										 valid height*/
	unsigned int	rampActive:1;  /* 1--> currently in a ramp*/
	unsigned int	reqPrfErrCor:1;/* add prfErr to model cor if in prf mode*/
	unsigned int        fill:20;
	} PNT_X_CUR_TIE_STATWD;

typedef struct {
	    PNT_X_CUR_TIE_STATWD statWd; /* <pjp016>*/
		float	   tempF;		/* last temp we used*/
		float      avgHgt;		/* avg Height feet from laser rangers*/
        int        timeStamp;   /* for below position*/
        float      pos[3];      /* 1st value sent to tiedown*/
        float      vel[3];      /* ditto */
        double     stDayNum; /* dayNum.frac ast for start time */
        PNT_TIE_PAT pnt;     /* pattern info passed to use */
    }   PNT_X_CUR_TIE;
/*
 * tertiary info
*/
typedef struct {
	unsigned int	reqState:2; /* 0-noReq,1-tracking ,2-holdpnt*/
    unsigned int    validPnt:1; /* true--> pntXform looks at point*/
    unsigned int      crdSys:4; /* 1-enc,2-inchOff,3-domeCenLine,4-focus*/
    unsigned int     movCode:4; /* 1-sin,2-pos,vel,3-scan*/
	unsigned int        fill:21;
	} PNT_X_REQ_TER_STATWD;

typedef struct {
	    PNT_X_REQ_TER_STATWD statWd;
        int        fill;
        double     startTm;    /* seconds from midnite*/
        PNT_TER_PAT pnt;      /* pending point pattern request*/
    }   PNT_X_REQ_TER;         /* int*/

typedef struct {
	unsigned int	reqState:2; /* 0-noReq,1-tracking ,2-holdpnt*/
    unsigned int    validPnt:1; /* true--> pntXform looks at point*/
    unsigned int      crdSys:4; /* 1-enc,2-inchOff,3-domeCenLine,4-focus*/
    unsigned int     movCode:4; /* 1-sin,2-pos,vel,3-scan*/
	unsigned int        fill:21;
	} PNT_X_CUR_TER_STATWD;


typedef struct {
	    PNT_X_CUR_TER_STATWD statWd; 
        int        timeStamp;   /* for below position*/
        float      pos[5];      /* 1st value sent to ter*/
        float      vel[5];      /* ditto */
#if FALSE 
		int	      fill[2];	    /* figure out what we need later*/ 
#endif
		double     stDayNum; /* dayNum.frac ast for start time */
        PNT_TER_PAT pnt;     /* pattern info passed to use */
    }   PNT_X_CUR_TER;

/*
 * model related variables
*/
typedef struct {
        double     encOffAzRd;    /* add to position great circle*/
        double     encOffZaRd[2]; /* 0==greg, 1=ch*/
    } PNT_X_MODEL;
/*
 * pntXform state
*/
typedef struct {
		unsigned int	pntProgRunning       :1;
		unsigned int	agcProgRunning       :1;
		unsigned int	agcProgTrkMode       :1;
		unsigned int	pntProgHasPnt        :1;

		unsigned int	pntProgReqTrk        :1; /* not holding pnt*/
		unsigned int	settling             :1;
		unsigned int	firstSettle          :1;/* waiting for first in tol*/
		unsigned int	onSrcAndTracking     :1;/* all of the above*/

		unsigned int	reqSrcInZaRange      :1;/* req Src pos within za limit*/
		unsigned int	newPntInPipeline     :1;/* waiting 2 secs to be active*/
		unsigned int    pntXAgcPrComOk       :1;/* pntx,agcProg talking ok*/

		unsigned int    lrLastHghtOk         :1;/* last height input ok*/
		unsigned int    lrLastTempOk         :1;/* last temp input ok*/
		unsigned int    prfErrIncluded       :1;/* add prf err to model
		                                           if tdprf active*/
		unsigned int	lrNoComCnt		     :4;/* if n > 0 then no com with
						  distomats for last n  trys (3 min per try)*/
		unsigned int	distOk			     :6;/* one for each distomat ok*/
		unsigned int    alfaProgRunning      :1;/* alfa prog running ok*/
		unsigned int	fill			     :7;
		} PNT_X_STATWD;
/*
 *	info that is supplied/computed 2 seconds in advance to fill the
 *  pipeline of pntXform->pntAgc->vertex..
*/
typedef struct {
        PNT_X_TIME      tm;        /* for this pipelined point(14*int)*/
        PNT_X_CUR_PNT   curP;   /* current point (64*int)*/
        PNT_X_MODEL     model;	/* (4*in)t*/
        PNT_X_REQ       req;    /* from pntTcl (36*int)*/
		/*  turret info */
        PNT_X_REQ_TUR   reqTur;   /* from pntTcl*/
        PNT_X_CUR_TUR   curTur;   /* current position*/
        PNT_X_REQ_TIE   reqTie;   /* from pntTcl*/
        PNT_X_CUR_TIE   curTie;   /* current position*/
        PNT_X_REQ_TER   reqTer;   /* from pntTcl*/
        PNT_X_CUR_TER   curTer;   /* current position*/
		} PNT_X_PL;
	
/*
 * pntXform state
*/
typedef struct {
		PNT_X_PL        pl;
        PNT_X_TIME      curTm;  /* last tick (14*int)*/
		/*--- end buffered data*/
		PNT_X_STATWD    statWd; /* (1*int)*/
		short		    settleTmCnt;
		char    	    tdToUse;/* 0->7 1-td12,2=td4,4-td8*/
		char    	    terToUse;/* 0->7 1-Ver,2-hor,4=tile*/
        double          modelCorEncAzZa[2]; /* units= Radians pjp038*/
        int           	agcStErrs;/* times we had an error*/
        int           	errAgcSemTakePntX;	/* agcState semaphore*/
        int           	errAgcSemTakePntT;
		int			  	errPntXSemTakePntX;	/* pntXReq semaphore*/
    }PNT_X_STATE; 		/* (42*int)*/
/*
 * current state structure
*/
typedef struct  {
        PNT_X_STATE      x;     /* for point xform*/
    } PNT_STATE;
/******************************************************************************
*	misc
******************************************************************************/
#if 0
.. moved to pntMisc.h
/*
 * hold labels/codes for coord sys
*/
typedef struct {
    int     code;           /* numeric value */
    char    *name;
    char    let;            /* letter to use*/
	char    fillCh[3];
	int		fill;
    } PNT_CS_INFO;
#endif
#if 0

/*
 * .. pntXformLib.a not yet converted
 * general info filled in by pntXform.
 * pretty much static
*/
typedef struct {
        PRECNUT_INFO    precI;
        OBS_POS_INFO    obsPos;
        UTC_INFO        utcI;
		EPV_INFO		epvI;	   /* info for ssbarycenter ephemeris*/
		double			aoSitePos[3];/* geocentric position ao..*/
        double          BToJM[36];  /* 1950 to j2000*/
        double          secsInFut;  /* to send tracking commands*/
    } PNT_GEN_INFO;
#endif
#if 0
.. moved to pntMisc.h
/*
 * timing related structs
 * moved from pntProg.h
*/
typedef struct {
    double  tmStart;    /*start of interval*/
    double  tmEnd;      /*end of interval*/
    double  lastIntvl;  /* measured*/
    double  minIntvl;   /* measured*/
    double  maxIntvl;   /* measured*/
    } PNT_TIME_INTVL;
#endif
#endif  /*INCpntProgStateh */
