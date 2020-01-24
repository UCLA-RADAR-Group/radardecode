/*hdrPnt.h - include file for pntProg portion of headers
*  %W%    %G%
*/
/*modification history:
----------------------
x.x,10jan98 started
*/
#ifndef INChdrPnth
#define INChdrPnth
#include        "hdrLib.h"
/*
 *      Pnt config info for headers
*/

/*
 *      pass in start of header, return ptr to start of pnt Portion of header
*/
#define PNTHDR_GET(phdr)  ( \
         (HDRAO_PNT*) ( \
              ((char*)(phdr)) + \
              HDR_S_GET_OFF(((HDRAO_STD *)(phdr))->sec.pnt)\
             ))
/*
 * some constants
*/
#define	 PNTHDR_VER   	"1.0 "
#define	 PNTHDR_MARKER 	"pnt "
/*
 * codes to specify a coordinate system
*/
#define PNTHDR_CRD_NOT_IN_USE              0
#define PNTHDR_CRD_GAL                     1
#define PNTHDR_CRD_B1950                   2
#define PNTHDR_CRD_J2000                   3
#define PNTHDR_CRD_BECLIPTIC               4
#define PNTHDR_CRD_JECLIPTIC               5
#define PNTHDR_CRD_CURRENT                 6
#define PNTHDR_CRD_HA_DEC                  7
#define PNTHDR_CRD_AZZA_SRC                8
#define PNTHDR_CRD_AZZA_FEED               9
#define PNTHDR_CRD_AZZA_NOMOD             10
#define PNTHDR_CRD_AZZA_GC                11
#define PNTHDR_CRD_MAX_NUM                11
/*
 * actual positions
*/
typedef struct {
   /*
    * actual readings..
   */
   /* agcProg 													   */
   int azTTD;      /* az position end rec. 1/10000 degrees     [ 0]*/
   int grTTD;      /* gr position end rec. 1/10000 degrees     [ 1]*/
   int chTTD;      /* za position end rec. 1/10000 degrees     [ 2]*/
   int agcTmStamp; /* above time stamp position millisecs      [ 3]*/

   /* ttProg turret */

   float   turPosRd; /* turret position radians				   [ 4]*/
   int     turTmStamp;/*millisecs							   [ 5]*/


   /* tdProg */
   float tdPosIn[3]; /* jack position						   [ 6]*/
   int   tdTmStamp[3];/*										   [ 9]*/

   /* lrProg*/
   float platformHgt[3]; /* platform height feet			   [12]*/
   float platformTemp;	 /* deg F						       [15]*/
   int   platformTmStamp;/* 								   [16]*/

   /* terProg*/

   float terPos[3];    /* tertiary position  				   [17]*/
   int   terTmStamp;   /* 									   [20]*/
   int   filler[3];    /* 									   [21]*/
	}  PNTHDR_MEASURED;  /* 24*4 = 96bytes*/

/*
 * requested things
*/
typedef struct {
	/*
	 * time info for requested point 
	*/
	double  ut1Frac;	/* fraction of day ut1 				   [ 0]*/
	double  lastRd;		/* local apparent siderial time        [ 2]*/
	int		mjd;		/* modified julian day(ut1)            [ 4]*/
/* compute utcFrac as secMid/86400 +4/24						   */
/* compute dut1 as (ut1Frac - utcFrac)  checking for crossovers    */
	int		yearDaynum;	/* ast yyyyddd 						   [ 5]*/ 
	/*
	 * positions
	*/
	float	reqPosRd[2];/* 									   [ 6]*/
	float   reqOffRd[2];/*							           [ 8]*/
	float   reqRateRdSec[2];/* 							       [10]*/
	double	dayNumAstRateStart;/*when rate applied             [12]*/
	/*
	 * resultant position back computed from az,za computed
	*/
	float     raJCumRd;/*									   [14]*/
	float     decJCumRd;/*									   [15]*/
 	double geoVelProj; 	/* fraction of c  					   [16]*/	
 	double helioVelProj;/* 								       [18]*/

	float    posCorrectionRd[2];/* az,za position correction. model or
							encoffset, rd                      [20]*/
	float    modelLocDeg[2];  /* location where model evaluated degrees [22]*/
	int     secMid;	    /* seconds from midnight ast           [24]*/
	int		filler;		/* filler						       [25]*/
    }  PNTHDR_REQ; /* 26*4 == 104 bytes							   */
/*
 * 	statword 
*/
typedef struct {
		    unsigned int    filler:9;
		    unsigned int    modelCor:1;  /* 1--> model, 0--> encoder offset*/
			unsigned int	grMaster:1;  /* 1--> gregorian master*/ 
			unsigned int	tracking:1;  /* within tolerance and settled*/
		/* 
		 * PNTCOORD
		*/ 
			unsigned int  	coordValid :1; /* the requested point is valid*/
			unsigned int  	coordSysPos:4; /* 0..15 coordsys*/	
			unsigned int  	coordSysOff:4; /*           	*/
			unsigned int  	coordSysRate:4;	
		/*
 		 * data we read from scramnet was ok
		*/
			unsigned int	allOk:1;	/* and of all below*/
			unsigned int	tdOk:1;
			unsigned int	turOk:1;
			unsigned int	terOk:1;
			unsigned int	lrOk:1;
			unsigned int	pntOk:1;
			unsigned int	agcOk:1;
		} PNTHDR_STAT;

typedef struct {
/*
 *      heres the pnt specific junk
 *      extra space at bottom makes multiple of 8 bytes and can be used
 *      for additions later on
*/
        char     id[4];  /*no null termination  				    [ 0]*/
        char    ver[4]; /*xx.x version...   				        [ 1]*/
		/*
		 * actual readings..
		*/
		PNTHDR_MEASURED m;	/* measure things. 24 words,96 bytes    [ 2]*/
		/*
		 * requested positions
		*/
		PNTHDR_REQ      r;	/* req positions   26 words,104 bytes    [26]*/
		/* 
		 * pointing error
		*/
		float	errAzRd;   /* little circle						    [52]*/
		float	errZaRd;   /* great circle 				            [53]*/
		PNTHDR_STAT	stat;/*										    [54]*/
		int				filler[5];/*								[55]*/
        } HDRAO_PNT; /* 60*4 = 240 bytes   */

void    hdrPrPnt(FILE *fptr,void *phdr);
#endif /*INChdrPnth*/
