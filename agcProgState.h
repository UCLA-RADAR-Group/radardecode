/*
 *  include file for agcProgState struct. This can be included by
 *  solaris or sun progams. It is used by agcProg and the 
 *  reflective memory
*/
#ifndef INCagcProgStateh
#define INCagcProgStateh
/*
*history..
*04aug96 - added doing tick processing variable.
*        - added log of time for tick processing
*16sep96 - added cmdRsp data info
*08apr97 - put in a few fillers so that the doubles end up on 
*		   multiples of 8 boundary..
*		 - vtx_oparm don't use in progstate since it is not word aligned
*		   vertex put a short between 2 ints. On vxWorks it's ok, but sun 
*		   puts in a filler.  
*23jun99 - added spdmon block for overspeed in place of the fill1[4].
*28aug00 - added preproc dlogging..filename,  and structure def.
*19nov07 -  <pjp030>AGC_STAT_POS_ERRS. got rid of yVtx,yAoReq,yAoCon
            Put them and ovrspd in a debug block to pass info to
            scramnet
*/

/*		includes	*/

#include	"phlibExtras.h"
#include	"vtxLib.h"
/*
 *   connection state values
*/
#define AGC_CON_NOTCONNECTED    0
#define AGC_CON_SELECT_LISTEN   1
#define AGC_CON_ACCEPTING       2
#define AGC_CON_CONNECTED       3
/*
 * bits determining what agcPrDbg outputs
*/
#define AGC_PRDBG_STD       1
#define AGC_PRDBG_CBLK      2
#define AGC_PRDBG_FBLK      4
#define AGC_PRDBG_LOCPROG   8
#define AGC_PRDBG_ALL      -1


#define	 AGC_NUM_AXIS 3

#define AGC_DLOG_PT_NAME  "/share/obs1/pnt/pt/dlogPt"
#define AGC_DLOG_POS_NAME "/share/obs1/pnt/pos/dlogPos"
#define AGC_DLOG_CBLK_NAME "/share/obs1/pnt/cblk/dlogCblk"
#define AGC_DLOG_FBLK_NAME "/share/obs1/pnt/fblk/dlogFblk"
#define AGC_DLOG_PREPROC_NAME "/share/obs1/pnt/pos/dlogPreProc"
/*	typedefs	*/

/**************************************************************************
 *	state of pointing program.. 
 *******************************
 *	- There are usually two typedefs for each kind of state:
*/
/*
 *	state of our connection with the vertex cpu
*/
typedef struct {
		int		stat;	 /*0 no connect,1 listen loop,2 accept,3 connected*/
		int	    numTryCon;/* we've tried to connect*/
		int	    numCon;  /* times we've connected*/
		int	    listenLoopCnt;/* times we looped on listen(10sec each)*/
		}	AGC_STATE_VTX_CON;
/*
 *	state of i/o to vertex cpu.
*/
typedef struct {
		int		    needSync;		/* i/o failed we need to resync*/
		int		    syncTry;		/* times we tried to sync*/
		int		    syncOk;		    /* times we successfully synced*/
		int			readTry;		/* read from vtx attempts*/
		int			readOk;
		int			writeTry;
		int			writeOk;
		int		    fill;
	    AGC_STATE_VTX_CON con;		/* connect info*/
		}	AGC_STATE_VTX_IO;
/*
 *  store position/time value. we do it for each axis separately
 *  since we can send a command to change 1 axis at 1 time and
 *  another axis at a different time.
*/
typedef struct {
		int		axis;	  /*1,2,4 orred together controlled*/
		int  	timeMs;	  /* millisecs from midnite*/
		int     posTTD[3];/* az,gr,ch position 1/10000 degrees*/
		} AGC_PT_VTX;
/*
 *  vertex has a fifo for program tracking. we need to remember the
 *  requested positions so that we can compute the position errors.
 *  The queue is allocated at startup. It holds the requested position
 *  and the constrained position (after checking for limits).
*/
typedef struct {
	    AGC_PT_VTX req;		/* requested position*/
	    AGC_PT_VTX con;		/* constrained position*/
		} AGC_STAT_PT_QENT;

/*
 *	the position errors. this is ours - theirs.
 *  do it for requested and constrained positions. also record the
 *  time and time differences
*/
typedef struct {
		AGC_STAT_PT_QENT aoPrevSec;
		AGC_STAT_PT_QENT aoCurSec;
		AGC_PT_VTX       vtxPrevSec;
/*      vtxCurSec is always the position/time at last 1 sec tick
        (tmSecMidite) 
*/
		AGC_PT_VTX		 vtxCurSec;
	    int		tmSecMidnite;	/* for the interpolated pos errors*/
	    int	    axis;   /* 1,2,4 orred together.. from request*/			
/*
 *     posDifRd Uses the requested value from our program track queue
 *     and the current position. If we are taken out of program track mode
 *     then the computation uses the last value from the program track
 *     queue that we sent... So outside of program track mode the 
 *     diff will not reflect the Requested-actual position.
*/
		double  reqPosDifRd[3]; 
		double  conPosDifRd[3]; 
		} AGC_STAT_POS_ERRS;
/*
 *	status errors from cblk,fblk decoded to error numbers
 *  beware: VTX_ERR_LIST contains a ptr to an malloced array to hold errnums.
 *          for scramnet memory, this ptr is garbage... there is no malloced
 *			list.
*/
typedef struct {
	 	int		totErrs;		/* we've currently got*/
		int	    timeMs;			/* last error check*/
		VTX_ERR_LIST_SCRM gen;		/* generic errors 3 int long*/ 
		VTX_ERR_LIST_SCRM az;		/* azimuth errors*/
		VTX_ERR_LIST_SCRM gr;		/* gregorian errors*/
		VTX_ERR_LIST_SCRM ch;		/* carriage house errors*/
		} AGC_STAT_ERRS;
typedef struct {
    int            encCorTTD[3];    /* az,gr,ch TTD*/
    int            tmoffsetPTMs;  /*time offset prog track millisecs*/
    short          tmoutNoHostSec;/* no request from host.. secs*/
	short		   filler;		  /* for sun alignment*/
    } AO_OPARM;
/*
 *	state 
*/
typedef	struct {
		int				     statWd;  /* bit description*/
		int				     fastCblk;/* 1-fastCblk,2-fastFblk if nothing else*/
  	    int			         secMLastTick;/* sec from mid last tick 0..86399*/
		int				     tickProcessing;/* true --> doing tick processing*/
	    AGC_STATE_VTX_IO     vtxIo;	      /* vertex i/o info*/
		int				     seqNum;	  /* sequence number fo messages*/
		int				     ctrlReq[AGC_NUM_AXIS];/*1 thru 4 who drives axis*/
		int				     ctrlCur[AGC_NUM_AXIS];/*1 thru 4 who drives axis*/
		/* if true, za is for greg, we then balance with the ch */
		int				     masterMode;/* 1 greg compute ch
										   2 ch  compute gr,
										   3 greg user sets ch
										   4 ch   user sets gr*/
		/*
		 * mode related state
		*/
		int		modeReq[AGC_NUM_AXIS];/* cur mode each axis
										0 stop,1 rate,2 pos,3 stow, 
										4 stow,5 aux
				 					   */
		int		modeCur[AGC_NUM_AXIS];/* cur mode each axis*/
		int     auxReq[AGC_NUM_AXIS];/* aux for az/gr/ch*/
		int     auxCur[AGC_NUM_AXIS];
		/*
		 * 	positions requested
	    */		
		double	    	 mRateDataReq[AGC_NUM_AXIS];/* rd/sec request*/
		double 			 mPosDataReq[AGC_NUM_AXIS]; /* rd's request*/
		AGC_STAT_POS_ERRS posErr;	/* record last position errors*/
        int              dbg[22];  /* <pjp030> use for snding dbinfo to scram*/

		/* double word aligned until here */
		AGC_PT_VTX       lastOnQCon;/* last cnstrn pos on q. time<0 --> nopos*/
		AGC_STAT_PT_QENT lastOffQ;  /* last we took off*/
		int			     lastOffQSkipped;
		int			     ptDiffSecs;  /* last program track*/
		int			     offQSkipped; /* time had passed.. total.*/ 
		int			     onQSkipped;  /* time had passed..total*/ 

		AO_OPARM 	     oparmReq;	/* operating parameters requested */
		AO_OPARM 	  	 oparmCur;	/* operating parameters current */
		VTX_RSP_CBLK     cblkMCur;  /* current critical block msg*/
		VTX_RSP_FBLK     fblkMCur;   /* current full block msg*/
		VTX_RSP_MSG_DATA cmdRspDat;	/* from last command send*/
		AGC_STAT_ERRS    errs;		/* hold errors..*/
		int				 filler;	/* make multiple of 8 bytes*/
		} AGC_STATE;
/*
 * structure defining data written to disc when logging tracking
 * info. written directly by agcProg
*/
typedef struct {
    int                 secMidnite;/* current tick */
    AGC_STAT_PT_QENT    aoCurSec;  /* cur pos req (if tracking)*/
    AGC_PT_VTX          vtxCurSec; /* cur pos from vertex */
    double              reqPosDifRd[3];/* requested position difference*/
    double              conPosDifRd[3];/* constrained position difference*/
    } AGC_TRACKING_LOG;

/* 
 * structure defining data written to disc when logging position 
 * info. written directly by agcProg
*/
typedef struct {
    int                 timeMs; /* from vertex cblock*/
    int                 posAz; /* azimuth position*/
    int                 posGr; /* greg position*/
    int                 posCh; /* ch position*/
    } AGC_POS_LOG;

typedef struct {
    int                 timeMs; /* from vertex cblock*/
	short				ptAxis;	/* program track axis*/
	short				preProcAxis;/* preProcAxis*/
    int                 posLim[3]; /* positions old*/
    int                 posPreProc[3]; /* preproc positions*/
    } AGC_PREPROC_LOG;
#endif
