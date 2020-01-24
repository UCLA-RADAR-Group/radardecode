/* 
 *	include file defining cblk,fblk and message format
*/
#ifndef INCvtxLogh
#define INCvtxLogh
#include	"phlibExtras.h"
#include	<stdio.h>


typedef struct {
	int	hdrId;	/* "<TT>" in 4 bytes, no null termination*/
	short   msgLenB;/* length in bytes including header*/
	short   msgType;/* type of msg*/
	} VTX_MSGPRE_RSP;

/*
 ******************** critical data block response*******************
*/
/*
 *	critical data block data
*/
typedef struct {
	int	    timeMs;	/* time in millisecs*/
	int	    tmoffsetPTMs;/* time offset in millisecs*/
	short   freePTpos;	/* freeprogram track stack positions*/
	unsigned short   genStat;	/* general status*/
	unsigned short   modeAz;	/* mode azimuth*/
	unsigned short	statAz;	/* status azimuth*/
	unsigned short	modeGr;	/* mode gregorian*/
	unsigned short	statGr;	/* status gregorian*/
	unsigned short	modeCh;	/* mode carriage house*/
	unsigned short	statCh;	/* status carriage house*/
	short   velAz;	/* azimuth        velocity 10^-4 deg/sec*/
	short	velGr;	/* gregorian      velocity 10^-4 deg/sec*/
	short   velCh;	/* carriage house velocity 10^-4 deg/sec*/
	char    fill[2];/* to align sunstructs*/
	int	    posAz;	/* azimuth        position 10^-4 deg*/
	int	    posGr;	/* gregorian      position 10^-4 deg*/
	int	    posCh;	/* carriage house position 10^-4 deg*/
	} VTX_CBLK;	
/*
 *	here is the messsage
*/
typedef	struct {
	VTX_MSGPRE_RSP pre;
	VTX_CBLK       dat;		/* critical data block*/
	} VTX_RSP_CBLK;
/*
 ******************** full data block response*******************
*/
typedef struct {
	  unsigned short	auxMode;	/* if a motor/group shut down*/
	  unsigned short	ampStat;	/* amplifier status*/
	  unsigned short	motorStat;	/* motor status*/
	  unsigned short	equipStat;	/* equipment status*/
	} VTX_FBLK_AXIS_INFO;	

typedef struct {
	  int	     timeMs;	/* time in millisecs*/
	  VTX_FBLK_AXIS_INFO azI;
	  VTX_FBLK_AXIS_INFO grI;
	  VTX_FBLK_AXIS_INFO chI;

	  int		 encPosAz1;
	  int		 encPosAz2;
	  int		 encPosGr;
	  int		 encPosCh;

	  short      measTorqAz[8]; /* 11,12,51,52,41,42,81,82*/
	  short      measTorqGr[8]; /* 11,12,21,22,31,32,41,42*/
	  short      measTorqCh[2]; /* 1,2*/

	  unsigned char      plcInpStat[20];/* input status bytes plc*/
	  unsigned char      plcOutStat[24];/* ouptput tatus bytes plc*/

	  int		 posSetPointAz;  /* 10-4 deg*/
	  int		 posSetPointGr;  /* 10-4 deg*/
	  int		 posSetPointCh;  /* 10-4 deg*/
	  short      velSetPointAz; /* 4.06910^-4 deg/sec*/
	  short      velSetPointGr; /* 4.06910^-5 deg/sec*/
	  short      velSetPointCh; /* 4.06910^-5 deg/sec*/

	  short      bendingCompAz;
	  short      torqueBiasGr ;
	  short      gravityCompGr;
	  short      torqueBiasCh; 
	  short      gravityCompCh;

	  int		 posTravelLimAz;
	  int		 negTravelLimAz;
	  int		 posTravelLimGr;
	  int		 negTravelLimGr;
	  int		 posTravelLimCh;
  	  int   	 negTravelLimCh;
	
	  int		 encCorAz;	
	  int		 encCorGr;	
	  int		 encCorCh;	
	  short	     tmoutNoHostSec;/* no request from host.. secs*/
	  char		 fill[2];	
	  int  	     tmElapsedSec;  /* elapsed time counter*/
	} VTX_FBLK;

typedef struct {
	unsigned char	clkErr;	/* 0--> no error, 1,2,3,4..*/
	unsigned char	inpTm[3];/* 3 bytes input from clock*/
	int          	time_ms; /* that we just computed*/
	int          	time_lastms; /* last time in milliseconds*/
	} VTX_BADTM;
/* 
 *	here is the actual message
*/
typedef struct {
	  VTX_MSGPRE_RSP pre;		/* prefix of hdr*/
	  VTX_FBLK       dat;	/* full data block*/
	} VTX_RSP_FBLK;

#endif  /* vtxLogh */
