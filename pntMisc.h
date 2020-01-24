/*
 * grabbed info from pntProgState.h moved to pntMisc.h
 * we want to include this in 305m and 12m pointing routines
*/ 
#ifndef INCpntMisch
#define INCpntMisch

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

/* the fill values are to keep doubles/structures aligned on  8 byte
 * boundaries. this is to get around the different packing of structures
 * done by 68k and the sun.
 * Note: c1,c2 are in radians or radians/sec
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
/******************************************************************************
*	misc
******************************************************************************/
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

#endif  /*INCpntMisch */
