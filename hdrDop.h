/*
 *	include file for pntProg.h  
 *  This is the state of pntProg that can be run on vxWorks or sun os.
 * 10dec99 - changed velObsProj to single double.
 *
*/
#ifndef INChdrDoph
#define INChdrDoph

#define HDRAO_DOP_GET(phdr)  ( \
         (HDRAO_DOP*) ( \
              ((char*)(phdr)) + \
              HDR_S_GET_OFF(((HDRAO_STD *)(phdr))->sec.proc)\
             ))

#define HDRAO_DOPST_VELTYPE_VEL 0
#define HDRAO_DOPST_VELTYPE_ZO  1 
#define HDRAO_DOPST_VELTYPE_ZR  2

#define HDRAO_DOP_ID      "dop "
#define HDRAO_DOP_CUR_VER " 1.0"


typedef struct {
    unsigned int  dopCorAllBands:1;/* 1 yes, 0 just center of band*/
    unsigned int  velCrdSys:4;     /* 1-geo,2-helio,3-lsr */
    unsigned int  velType:2;       /* 0-vel,1-zo,2-zr*/
	unsigned int  fill:25;
    } HDRAO_DOP_STAT_WORD;

typedef struct {
	char	id[4];		/* DOP not null terminated*/
	char	ver[4];		/* version xx.0 not null terminated*/
    double  dopFactor; /* frqOutBCtopo=dopFactor*frqBCR rest frame*/

    double  velOrZ;    /* km/sec or z..see stat.velType*/

    double  freqBCRest;  /* rest freq band center Mhz*/
    double  freqOffsets[4];/* Mhz to compute center freq of each band.
							*1. if dopCorall, then add to freqBCRest to 
								get the  rest frequencies center each band.
							*2. if dopCorall false, then add to freqBCTopo
								to get the topocentric center each band.
								(should match value in iflo.
							*/
    double  velObsProj; /* velocity of observer in vel coord system
						 projected along the line of site*/

    int     tmDop;      /* when doppler was computed. sec Mid*/
	HDRAO_DOP_STAT_WORD stat; /* stat word*/
	int		fill[2];	/* free bytes*/
    } HDRAO_DOP; /*2*4+ 8*8 + 2*4 + 2*4==88 bytes*/

void    hdrPrDop(FILE *fptr,void *phdr);

#endif  /*INChdrDoph */
