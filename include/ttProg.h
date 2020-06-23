#ifndef 	INCttProgh
#define 	INCttProgh
#include	"mathCon.h"
#include	"tttProgs.h"
/*
 * include file for ttProg.h, holds the program specific  msg formats to 
 * communicate with the turret and tertiary. The generic junk is in 
 * tttProgs.h
*/
/* 
 * max num microcontroller for each program
*/
#define TT_MAX_NUM_DEV				4		
#define TT_MAX_FAULT_NUM           30


/*	device addresses on the  485 networks  */
/*	note  ter1: horizontal x
		  ter2: tilt
		  ter3: vertical   z
*/
#define	TT_SLVADR_TUR	1
#define	TT_SLVADR_TER1  2
#define	TT_SLVADR_TER2  1
#define	TT_SLVADR_TER3  2
/*
 *   coordinate conversetions
*/
/*		turret   */

#define TUR_RAD_TO_ENC_UNITS  ( (4096. * 210. / 5.0) / (C_2PI) )
#define TUR_ENC_UNITS_TO_RAD  ( (C_2PI) / ( (4096. * 210. / 5.0)))
#define TUR_DEG_TO_ENC_UNITS  ( (4096. * 210. / 5.0) / (360.) )
/* (5000rpm/2048)*(1pinionrev/93.165mtrrpm)*(1flrrev/17.5pinrev)*360*1/60*/
#define TUR_DEGSEC_TO_DA_CNT  (1./.00898464)
#define TUR_DEGSEC2_TO_DA_CNTIN5MS (1./1.79692711)

/* 	tertiary 	*/
#define TER_C1_INCHES_TO_ENC_UNITS  1.
#define TER_C2_INCHES_TO_ENC_UNITS  1.
#define TER_C3_INCHES_TO_ENC_UNITS  1.
/*
 * turret specific commands from vme to slave microprocessor.
*/
#define TUR_SLV_CMD_AUTO_SCAN   0x9

/*		device specific indices into block returned by get status*/

#define TTT_GSIND_TUR_S_I_MON      7 
#define TTT_GSIND_TUR_S_S_MON      8 
#define TTT_GSIND_TT_DI_UIO3      15 
#define TTT_GSIND_TUR_DRVSTAT_S   19 
/*
 * slave status word 
*/
#define TT_PROGSTSLV_INUSE         0x00000001
#define TT_PROGSTSLV_LASTIO_OK     0x00000002
#define TT_PROGSTSLV_PT            0x00000004

typedef struct {
    unsigned int    inUse       :1;
    unsigned int    lastIoOk    :1;
    unsigned int    modeReq     :3;
    unsigned int    fill        :27;
    }  TT_PRGSLV_STATWD;

/* 
 * reply message from slave  TURRET/TERTIARY
*/ 
typedef struct { 
	int				timeMs;		/* milliseconds from midnite*/	
	int				position; 
	unsigned short  devStat;	/* device status*/ 
	short           dataValue;	/* data value.. signed and unsigned.*/
	char			optData[256];/* optional data could by multi byte*/
} TT_MSG_FROM_SLV;
/*
 * get status reply in optional data turret ...
*/
typedef struct {
	unsigned	short	aI_ps24P;
	unsigned	short	aI_ps24N;
	unsigned	short	aI_psB24P;
	unsigned	short	aI_psEnc5P;
	unsigned	short	aI_VelFB;
	unsigned	short	aI_mAmpCurMon;
	unsigned	short	aI_mAmpSpdMon;
	unsigned	short	aI_sAmpCurMon;
	unsigned	short	aI_sAmpSpdMon;
	unsigned	short	aI_accel;
	unsigned	short	aI_ratePotPcu;

	unsigned	short	aO_velCmd;

	unsigned    short   dI_LS;			/* little star */
	unsigned    short   dI_uio1;		/* universal i/o 1*/
	unsigned    short   dI_uio2;		/* universal i/o 2*/
	unsigned    short   dI_uio3;		/* universal i/o 2*/

	unsigned    short   dO_LSuio1;		/* little star and uio 1*/
	unsigned    short   dO_uio2_3;	    /* universal i/o 2,3*/

	unsigned    short   st_mDrv;        /* master drive*/
	unsigned    short   st_slvDrv;      /* slave drive*/
	unsigned    short   st_safLimLockAxis;      /* slave drive*/
	unsigned    short   st_fault;      /* fault*/
	} TUR_GET_STATUS_DATA;
#endif
