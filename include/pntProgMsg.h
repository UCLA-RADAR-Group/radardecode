#ifndef INCpntProgMsgh 
#define INCpntProgMsgh
/*
* include file for messages sent only to pntProg 
* pntProg also rcvs messages sent to agcProg, tttProg
*history..
* 15sep99 - include pnt_tie_pat_autotrack
* 14jul01 - <pjp026> changes for tertiary
*/
/*
 * send tracking point to pntProg for agc
 * just use pnt_COORD.
*/
#define	PNT_TR_REQ_CLRPTQ 	1
#define	PNT_TR_REQ_SEND 	2
#define	PNT_TR_REQ_HOLD 	3
#define	PNT_TR_REQ_PNT  	4

/*
 *  turret/tiedown  pattern request codes will replace constants below...
*/
#define         PNT_TTT_PAT_NO_CMD 0
#define         PNT_TTT_PAT_SIN    1
#define         PNT_TTT_PAT_PV     2
#define         PNT_TTT_PAT_SCAN   3
#define         PNT_TTT_PAT_TIETRK 4

#if FALSE
/*  delete from here ....<pjp026>
 * 	tell pnt to do a pattern with the turret.
*/
#define	PNT_TUR_CODE_PATSIN		1
#define	PNT_TUR_CODE_PATPV 		2
#define	PNT_TUR_CODE_PATSCAN	3
/*  
 * 	tell pnt to do a pattern with the tiedowns
*/

#define	PNT_TIE_CODE_PATSIN		1
#define	PNT_TIE_CODE_PATPV 		2
#define	PNT_TIE_CODE_PATSCAN	3
#define	PNT_TIE_CODE_PATTRK     4

#endif

/* to here ...
 PRFOFF .. only offset, p,r,focus applied.
 */

#define PNT_TIE_PATTRK_TEMP		1
#define PNT_TIE_PATTRK_HGHT  	2
#define PNT_TIE_PATTRK_POS  	3
#define PNT_TIE_PATTRK_POSTEMP 	4
#define PNT_TIE_PATTRK_PRFOFF  	5
#define PNT_TIE_PATTRK_ALL  	9
/*
 * tertiary coordinate systems
 * 1: encoder units
 * 2: dome centerline coordinate system
 *    z up, x along az, y towards stairwell, 0 at
 * 3: z along focus direction of feed/secondary:
 *    y towards stairwell
 *    x up along azimuth
 * 4: offset inches from center position of encoders (501000)
 * coordinate order:
 * if 3 coords: x,y,z
 *              v,h,tilt
 * if 5 coords: vl,vr,hl,hr,tilt
*/
#define PNT_TER_CRD_ENC     	1
#define PNT_TER_CRD_IN_OFFSET   2
#define PNT_TER_CRD_DOM_CENLIN 	3
#define PNT_TER_CRD_FOCUS      	4
/*
 * tur pattern requests. map onto  pnt_tie_pat
*/
typedef struct {
        float   c[4];       /* coordinate info*/
        } PNT_TUR_PAT;

/*  sin motion  */

typedef struct {
    float       posStRd;     /* start posiition in radians*/
    float       ampRd;          /* amplitude in radians*/
    float       frqW;          /* frequency rd/sec*/
    float       phaseRd;        /* phase offset radians*/
    } PNT_TUR_PAT_SIN;

/* position and constant velocity*/

typedef struct {
    float       posStRd;        /* start posiition radians*/
    float       velRdSec;       /* velocity rd/sec*/
    float       filler[2];
    } PNT_TUR_PAT_PV;

/*  scan between two points with constant time*/

typedef struct {
    float       pos1Rd;     /* start posiition in radians*/
    float       pos2Rd;     /* end position in radians*/
    float       timeMovSec; /* time to move between two points*/
    float       filler;
    } PNT_TUR_PAT_SCAN;

typedef struct {
    int patCode;    /* 1,2,3 */
    int filler;
    double  startTime;  /* sec midnite*/
    PNT_TUR_PAT pat;
    } PNTMSG_TUR_PAT;

/*
 * tiedown pattern requests. map onto  pnt_tie_pat
*/
typedef struct {
        float   c[8];       /* coordinate info*/
        } PNT_TIE_PAT;

/*  sin motion  */

typedef struct {
    float       posStIn[3];     /* start posiition in inches*/
    float       ampIn;          /* amplitude in inches*/
    float       frqW;          /* frequency rd/sec*/
    float       phaseRd;        /* phase offset radians*/
	float		filler[2];
    } PNT_TIE_PAT_SIN;
 
/* position and constant velocity*/
 
typedef struct {
    float       posStIn[3];        /* start posiition inches*/
    float       velInSec[3];       /* velocity inches/sec*/
	float		filler[2];
    } PNT_TIE_PAT_PV;
 
/*  scan between two points with constant time*/
 
typedef struct {
    float       pos1In[3];     /* start posiition in radians*/
    float       pos2In[3];     /* end position in radians*/
    int         timeMovSec; /* time to move between two points*/
	int         startTm;	/* seconds from midnite 23jul01 not used???*/
    } PNT_TIE_PAT_SCAN;

typedef struct {
	int			icode;			/* 1-temp,2-az/za,3-both*/
    float       offsetIn[3];   /* from std position in inches*/
	float	    offsetTempF;   /* offset from std temp in defF*/
	float		filler[3];
    } PNT_TIE_PAT_TRK;

typedef struct {
	int	patCode;	/* 1,2,3 */	
	int	filler;
	double	startTime;	/* sec midnite*/
	PNT_TIE_PAT pat;
	} PNTMSG_TIE_PAT;
/*--------------------------------------------------
 * <pjp026> below
 * tertiary pattern requests. map onto  pnt_ter_pat
 * note that pntmsg_ter_pat has a variable that defines the coordinate
 * system that we are passing in. The coordinate array [3] holds
 * the axis order: encoder units: [0]-vertical, [1]-horizontal,[2]-tilt
 * We will probably need an offset between drives on one axis since we
 * donot pass separate values for right,left drives..
 * line the values axis 
*/
typedef struct {
        float   c[12];       /* coordinate info*/
        } PNT_TER_PAT;

/*  sin motion  */

typedef struct {
    float       posSt[5];     /* start posiition in inches*/
    float       amp[3];       /* amplitude in inches*/
    float       frqW[3];      /* frequency rd/sec*/
    float       phaseRd;      /* phase offset radians*/
    } PNT_TER_PAT_SIN;

/* position and constant velocity*/

typedef struct {
    float       posSt[5];        /* start posiition inches*/
    float       vel[3];          /* velocity something/sec*/
    float       filler[4];
    } PNT_TER_PAT_PV;

/*  scan between two points with constant time*/

typedef struct {
    float       pos1[5];     /* start posiition */
    float       pos2[5];     /* end position*/
    int         timeMovSec; /* time to move between two points*/
    int         filler;    /* seconds from midnite*/
    } PNT_TER_PAT_SCAN;


typedef struct {
    int  patCode;    /* 1,2,3 */
	char coord;		 /* coordinated system of data passed in*/
    char filler[3];
    double  startTime;  /* sec midnite*/
    PNT_TER_PAT pat;
    } PNTMSG_TER_PAT;
#endif
