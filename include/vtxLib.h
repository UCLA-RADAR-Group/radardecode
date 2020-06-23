/* 
 *	include file for messages to send to vertex cpu.
 *	You need to worry about alignment mismatches for the structures
 *	that have odd number of shorts followed by an int. On vxWorks 
 *	m68k ints can will be aligned on two byte boundaries. On the 
 *	sun, the compiler will stuff filler into the struct so that
 *	ints are aligned on 4 bytes boundaries.
 *	see program vtxChkSize under vw/datatk/pnt/vtx
*/
#ifndef INCvtxLIBh
#define INCvtxLIBh
#include	"phlibExtras.h"
#include	<stdio.h>
/*
*history..
*24mar96,pjp	- added general command power on.
*               - added general commands rstaz,rstgr,rstch
*               - full data block . az torque order changed.
*	        - critical data block vel int--> short. length 56-->50
*27mar96,pjp    - added msgbit defines to uniquely define a bit for each
*		  msg. used in debugging output. turn on 1 or more
*		  msgs for debugging.	        
*06apr96,pjp    - added connect state defines.
*30apr96,pjp    - added master values..
*17jun96,pjp    - added sync message. This is a message that causes the
*                 vertex cpu to return an cmd error. It has a monitor req
*				 length but a cmdId of 99 (illegal).
*16sep96,pjp001 - changed cmpRsp format . added stat,time,position.
*16feb97,       - added define to convert encoder counts to degrees.
*                 this is needed to compute the bending difference in degrees.
*31dec99,       - added badtm struct definition. loaded at cast to 
*                 plcOutStat + 12
*/
/*	defines to fix the alignment problems cblock,fblock	*/


/*
 ******************** MESSAGE FORMAT ******************************* 
 * all messages have:
 * 4 bytes hdrid "<TT>"   4 bytes as an id
 * 2 bytes hdrlen         length of the msg in bytes including the header
 * 2 bytes msgType        Type of message cmd,modereq,monReq, cmdreply....
 * .... followed by message dependant data.
 *
*/
/*
 * hdrid "<TT>" as 4 byte word..
*/
#define	VTX_HDR_ID       0x3c54543e
#define	VTX_HDR_ID_STR   "<TT>"

/*
 ******************** PNEUMONICS FORMAT ******************************* 
 *
 * MSGT           message type
 * MSGL           message length
 *
 *            .. message types..
 *
 * GCMD		  general command
 * MSEL           mode select request 
 * REQ_CBLK	  request critcal block
 * REQ_FBLK	  request full  block
 * REQ_OPARM         operating paramters
 * RSP_MSG        response to msg request command / mode select  response    
 * RSP_CBLK       critical block response
 * RSP_FBLK       full block response
 * RSP_OPARM     operating params response
 *
 * 	      .. command requests       
 *
 * GLRFLT         global reset of faults
 * TC_LCU         transfer control to local    control unit (upstairs)
 * TC_OCU         transfer control to operator control unit (downstairs)
 * TC_PCU         transfer control to portable control unit (upstairs)
 * TC_VME         transfer control to vme (remote operation)(downstairs)
 * PTCLR          clear program track stack 
 * PTDT3          program track data transfer 3 axis
 * PTDT2          program track data transfer 2 axis
 * PTDT1          program track data transfer 1 axis
 * OPARM          upload operating parameters
 * PWRON          power on
 * RFLT_AZ        reset faults azimuth
 * RFLT_GR        reset faults gregorian 
 * RFLT_CH        reset faults carriage house
 *
 * 	      .. mode select 
 *
 * PT             program track mode
 * STOW           stow or survival position
 * AUX            auxilliary selection for motors 
 *
 *	FBLK..
 * AXSTAT	  axis status... either az, gr , or ch
 * AXMODE	  axis mode   .. either az, gr , or ch
*/
/******************** MESSAGE TYPES********************************* 
 *
 * every message has a message type that follows the mesage length
 *                of each msg to/from the vertex cpu.
*/
#define VTX_MSGT_GCMD 	           1
#define VTX_MSGT_MSEL              2
#define VTX_MSGT_REQ_CBLK          3
#define VTX_MSGT_REQ_FBLK          4
#define VTX_MSGT_REQ_OPARM         5
#define VTX_MSGT_RSP_MSG           6
#define VTX_MSGT_RSP_CBLK          7 
#define VTX_MSGT_RSP_FBLK          8
#define VTX_MSGT_RSP_OPARM         9
#define VTX_MSGT_SYNC             99
/*
 ******************** MESSAGE LENGTHS ****************************** 
 *
 * the message length follows the header id. It is the length of the 
 * message in bytes (including) the header. For some command requests, the
 * length differentiates between different types of requests.
 * These lengths assume a packed data structure (ints can be aligned on 
 * two byte boundaries). On the sun, this will not be true and the
 * sizeof operation for the structure will not match these lengths.
 *
*/
#define VTX_MSGL_GCMD_GLRFLT 	12
#define VTX_MSGL_GCMD_TC     	14
#define VTX_MSGL_GCMD_PTCLR  	12
#define VTX_MSGL_GCMD_PTDT3     28
#define VTX_MSGL_GCMD_PTDT2     26
#define VTX_MSGL_GCMD_PTDT1     22
#define VTX_MSGL_GCMD_OPARM     30
#define VTX_MSGL_GCMD_PWRON  	12
#define VTX_MSGL_GCMD_AXRFLT 	12
#define VTX_MSGL_GCMD_SIREN  	12

#define VTX_MSGL_MSEL_RATE      18 
#define VTX_MSGL_MSEL_POS       18 
#define VTX_MSGL_MSEL_STOW      14 
#define VTX_MSGL_MSEL_PT        14 
#define VTX_MSGL_MSEL_AUX       16 
#define VTX_MSGL_MSEL_STOP      14 
 
#define VTX_MSGL_REQ            10
/* <pjp001>
#define VTX_MSGL_RSP_MSG        14
*/
#define VTX_MSGL_RSP_MSG        32
#define VTX_MSGL_RSP_CBLK       50
#define VTX_MSGL_RSP_FBLK      202
#define VTX_MSGL_RSP_OPARM      26
#define VTX_MSGL_SYNC           10
/*
 ******************** MESSAGE TABLE INDEX ************************** 
 *
 * index into ao message table for each message. If you change the table
 * you should modify these indices to match it.
 *
*/
#define VTX_MTBLI_GLRFLT 	         0
#define VTX_MTBLI_TC_LCU 	         1
#define VTX_MTBLI_TC_OCU 	         2
#define VTX_MTBLI_TC_PCU 	         3
#define VTX_MTBLI_TC_VME 		 	 4
#define VTX_MTBLI_PTCLR    		     5
#define VTX_MTBLI_PTDT3			     6
#define VTX_MTBLI_PTDT2   		     7
#define VTX_MTBLI_PTDT1  		     8
#define VTX_MTBLI_OPARM   		     9
#define VTX_MTBLI_PWRON  		    10
#define VTX_MTBLI_AXRFLT		    11 
#define VTX_MTBLI_MS_STOP    		12
#define VTX_MTBLI_MS_RATE    		13
#define VTX_MTBLI_MS_POS     		14
#define VTX_MTBLI_MS_STOW    		15
#define VTX_MTBLI_MS_PT      	 	16	
#define VTX_MTBLI_MS_AUX     		17
#define VTX_MTBLI_REQ_CBLK         	18
#define VTX_MTBLI_REQ_FBLK         	19
#define VTX_MTBLI_REQ_OPARM       	20
#define VTX_MTBLI_RSP_MSG      		21
#define VTX_MTBLI_RSP_CBLK    		22
#define VTX_MTBLI_RSP_FBLK   		23
#define VTX_MTBLI_RSP_OPARM 		24
#define VTX_MTBLI_SYNC      		25
#define VTX_MTBLI_SIREN     		26
/*
 ******************** genereal command bits ****************************** 
 *	
*/
#define VTX_GCMDBITS_GLRFLT 	0x0001
#define VTX_GCMDBITS_TC_LCU 	0x0002
#define VTX_GCMDBITS_TC_OCU 	0x0004
#define VTX_GCMDBITS_TC_PCU 	0x0008
#define VTX_GCMDBITS_PTCLR  	0x0010
#define VTX_GCMDBITS_PTDT   	0x0020 
#define VTX_GCMDBITS_OPARM  	0x0040 
#define VTX_GCMDBITS_RST_EFLG   0x0080 
#define VTX_GCMDBITS_TC_VME 	0x0200
#define VTX_GCMDBITS_PWRON	    0x0400
#define VTX_GCMDBITS_RFLT_AZ    0x0800
#define VTX_GCMDBITS_RFLT_GR    0x1000
#define VTX_GCMDBITS_RFLT_CH    0x2000
#define VTX_GCMDBITS_SIREN_OFF  0x4000
/*
 ******************** mode select bits ****************************** 
 *	
*/
#define VTX_MSEL_STOP   	0x0000
#define VTX_MSEL_RATE   	0x0001
#define VTX_MSEL_POS    	0x0002
#define VTX_MSEL_STOW   	0x0004
#define VTX_MSEL_PT     	0x0008
#define VTX_MSEL_AUX    	0x0010
/*
 ******************** cmd response    ****************************** 
 *	
*/
#define VTX_RSP_MSG_STAT_COMPLETED		     	 1
#define VTX_RSP_MSG_STAT_PROCESSING     	 	 2
#define VTX_RSP_MSG_STAT_STARTED        	 	 3
#define VTX_RSP_MSG_STAT_INVALID_CMD    		 4
#define VTX_RSP_MSG_STAT_CMD_NOT_VALID_THIS_MODE 5
#define VTX_RSP_MSG_STAT_CMDPARM_OUT_OF_RANGE    6 
#define VTX_RSP_MSG_STAT_ACCEPTED                7 
/*
 ******************** critical data block**************************** 
 *	
*/
#define VTX_CBLK_GENSTAT_EMG_OFF		 		 0x0001
#define VTX_CBLK_GENSTAT_SIREN_OFF    	         0x0002
#define VTX_CBLK_GENSTAT_LIMIT_OVERRIDE          0x0004
#define VTX_CBLK_GENSTAT_PCU_COM_FAULT           0x0008
#define VTX_CBLK_GENSTAT_CP581_COM_FAULT         0x0010
#define VTX_CBLK_GENSTAT_AZ_BENDING_ERR          0x0020
#define VTX_CBLK_GENSTAT_EVENT_FLAG              0x0040
#define VTX_CBLK_GENSTAT_MAIN_OVER_UNDER_VOLTAGE 0x0080
#define VTX_CBLK_GENSTAT_OVERTEMP_DRV_CAB1       0x0100
#define VTX_CBLK_GENSTAT_OVERTEMP_DRV_CAB2       0x0200
#define VTX_CBLK_GENSTAT_CIR_BREAKER_FAULT       0x0400
#define VTX_CBLK_GENSTAT_24VOLT_PWRSUPPLY_FAULT  0x0800
#define VTX_CBLK_GENSTAT_BRAKE_PWRSUPPLY_FAULT   0x1000
#define VTX_CBLK_GENSTAT_PLC_PWRSUPPLY_FAULT     0x2000
#define VTX_CBLK_GENSTAT_DRIVES_PWR_OFF          0x4000
#define VTX_CBLK_GENSTAT_CABINET_DOOR_OPEN       0x8000

/*	az,gregorian, or ch status	*/

#define VTX_CBLK_AXSTAT_SERVO_FAILURE            0x0001
#define VTX_CBLK_AXSTAT_BRAKE_RELEASE_CMD        0x0002
#define VTX_CBLK_AXSTAT_DRV_ENA_POS              0x0004
#define VTX_CBLK_AXSTAT_DRV_ENA_NEG              0x0008
#define VTX_CBLK_AXSTAT_RUNAWAY                  0x0010
#define VTX_CBLK_AXSTAT_OVERTEMP_MOTOR           0x0020
#define VTX_CBLK_AXSTAT_ENCODER_FAILURE          0x0040
#define VTX_CBLK_AXSTAT_BRAKE_FAILURE            0x0080
#define VTX_CBLK_AXSTAT_NEG_LIMIT                0x0100 
#define VTX_CBLK_AXSTAT_NEG_PRELIMIT             0x0200 
#define VTX_CBLK_AXSTAT_OPERATING_RANGE          0x0400 
#define VTX_CBLK_AXSTAT_POS_LIMIT                0x0800 
#define VTX_CBLK_AXSTAT_POS_PRELIMIT             0x1000 
#define VTX_CBLK_AXSTAT_EMG_LIMIT                0x2000 
#define VTX_CBLK_AXSTAT_AZ_STOPPED_FOR_CBLCAR    0x4000 
#define VTX_CBLK_AXSTAT_BRAKE_RELEASED           0x8000 

/*	az,gregorian, or ch mode	*/

#define VTX_CBLK_AXMODE_STOP                     0x0000
#define VTX_CBLK_AXMODE_RATE                     0x0001
#define VTX_CBLK_AXMODE_POS                      0x0002 
#define VTX_CBLK_AXMODE_STOW                     0x0004
#define VTX_CBLK_AXMODE_PT                       0x0008
#define VTX_CBLK_AXMODE_MODE_MASK                0x000f

#define VTX_CBLK_AXMODE_PCU                      0x0100
#define VTX_CBLK_AXMODE_LCU                      0x0200
#define VTX_CBLK_AXMODE_OCU                      0x0400
#define VTX_CBLK_AXMODE_VME                      0x0800
#define VTX_CBLK_AXMODE_PCU_NOT_ACTIVE           0x2000
#define VTX_CBLK_AXMODE_LOCAL_ONLY               0x4000
/*
 ******************** full data block**************************** 
 *	
*/
#define VTX_FBLK_EQUIPSTAT_PWRSUPPLY1_FAULT	     0x0001
#define VTX_FBLK_EQUIPSTAT_PWRSUPPLY2_FAULT	     0x0002
#define VTX_FBLK_EQUIPSTAT_MAINCONTACTOR1_ON 	 0x0004
#define VTX_FBLK_EQUIPSTAT_MAINCONTACTOR2_ON 	 0x0008
#define VTX_FBLK_EQUIPSTAT_DC_BUS1_FAULT     	 0x0010 
#define VTX_FBLK_EQUIPSTAT_DC_BUS2_FAULT     	 0x0020
#define VTX_FBLK_EQUIPSTAT_BRAKES_GRP1_FUSE_BLWN 0x0040
#define VTX_FBLK_EQUIPSTAT_BRAKES_GRP2_FUSE_BLWN 0x0080
#define VTX_FBLK_EQUIPSTAT_LOCAL_DISABLE         0x1000
#define VTX_FBLK_EQUIPSTAT_PENDULUM_MOTION       0x8000
#define VTX_FBLK_EQUIPSTAT_COL_SW                0x8000
/*
 ******************** units **************************** 
 *	
*/
#define VTX_UNITS_POS_DEGS                       1e-4
#define VTX_UNITS_VEL_DEGS_P_SEC                 1e-4
/* i think these are converting from footlbs to amps */
#define VTX_UNITS_TORQUE_AZ_NM                   1.2375e-2
#define VTX_UNITS_TORQUE_GR_NM                   1.7492e-2
#define VTX_UNITS_TORQUE_CH_NM                   1.7492e-2
/* first is az, second is ch,gr. taken from ftext in lcu code*/
#define VTX_UNITS_VEL_SETPNT_DEGS_P_SEC          4.0690e-4
#define VTX_UNITS_VEL_SETPNT_DEGS_P_SEC_ZA       4.0690e-5
#define VTX_UNITS_BENDING_COMP_AZ_NM             3.0938e-2
#define VTX_UNITS_TORQUE_BIAS_GR_NM              4.3730e-2
#define VTX_UNITS_GRAV_COMP_GR_NM                4.3730e-2
#define VTX_UNITS_TORQUE_BIAS_CH_NM              4.3730e-2
#define VTX_UNITS_GRAV_COMP_CH_NM                4.3730e-2
/*   
 ******************** misc definitions ****************************** 
 *	
*/
/*	which bits in various statuses are considered errors	*/


/*  which bits in various statuses are considered errors    */

#define VTX_ERRS_CBLK_GEN_MASK        0xff3f
#define VTX_ERRS_CBLK_AXIS_MASK       0x7bf7
#define VTX_ERRS_FBLK_AMPSTAT_MASK_AZ 0xffff
#define VTX_ERRS_FBLK_AMPSTAT_MASK_GR 0xffff
#define VTX_ERRS_FBLK_AMPSTAT_MASK_CH 0x000f
#define VTX_ERRS_FBLK_AUXSTAT_MASK_AZ 0x0003
#define VTX_ERRS_FBLK_AUXSTAT_MASK_GR 0x00ff
#define VTX_ERRS_FBLK_AUXSTAT_MASK_CH 0x0003
#define VTX_ERRS_FBLK_MOTSTAT_MASK_AZ 0x00ff
#define VTX_ERRS_FBLK_MOTSTAT_MASK_GR 0x00ff
#define VTX_ERRS_FBLK_MOTSTAT_MASK_CH 0x0003
#define VTX_ERRS_FBLK_EQPSTAT_MASK    0x80f3
/*
 *  describe seqNum, 1st, send args after seqnumor msgtype (if no seqnum)
*/
#define VTX_ARG1_MASK      0x000f
#define VTX_ARG1_CMDID     0x0001 
#define VTX_ARG1_MODE      0x0002 
#define VTX_ARG1_CMDRSP    0x0004 
#define VTX_ARG1_MON       0x0008 
#define VTX_ARG2_MASK      0x00f0
#define VTX_ARG2_AXIS      0x0010 
#define VTX_ARG2_CMDSTAT   0x0020 
#define VTX_ARG2_MON       0x0040 
#define VTX_ARG2_MISC      0x0080 
#define VTX_ARG_SEQNUM     0x0100

#define VTX_CNV_RAD_TO_POS      (C_RAD_TO_DEG*10000.) 
#define VTX_CNV_POS_TO_RAD      (C_DEG_TO_RAD*1e-4)

#define VTX_CNV_RADPSEC_TO_VEL  (C_RAD_TO_DEG*10000.) 
#define VTX_CNV_VEL_TO_RADPSEC  (C_DEG_TO_RAD*1e-4)

/* pg 1-16 vertex vol 3, sect 1
 * 127ft - rackdiameter,
 * 2.5in - pinion diameter
 * 609.6 = 127ft/(2.5in*12)
 *4096   - counts/encoder revolution
 * encToDeg= (360.)/609.6/4096.
 *
*/
#define VTX_CNV_AZ_ENC_TO_DEG    1.441775344488189e-4 
#define VTX_CNV_DEG_TO_AZ_ENC    6.935893333333334e3  
/*
 * 840.9375 ft diameter --> rack gear effective radius at 420.46875 ft
 * 9.5in - pinion diameter
 * 1062.236842 = 840.9375/(9.5in/12)
 * 4096   - counts/encoder revolution
 * encToDeg= (360.)/1062.236842/4096.
*/
#define VTX_CNV_EL_ENC_TO_DEG    8.274108138e-5 
#define VTX_CNV_DEG_TO_EL_ENC    1.275733333333333e4  


/*	typedefs	*/

/*	preamble start of each message except response cblk,fblk,oparams.*/

typedef struct {
	int	hdrId;		/* "<TT>" in 4 bytes, no null termination*/
	short   msgLenB;/* length in bytes including header*/
	short   msgType;/* type of msg*/
	unsigned short seqNum;
	} VTX_MSGPRE;

#include	"vtxLog.h"

/*
 ******************** command requests*******************************
*/
/*	global fault reset	*/

typedef struct {
	VTX_MSGPRE  pre;	/* prefix of hdr*/
	short	    cmdReq;
	} VTX_GCMD_GLRFLT;	

/*	transfer control */

typedef struct {
	VTX_MSGPRE  pre;	/* prefix of hdr*/
	short	    cmdReq;
	short		axis;
	} VTX_GCMD_TC;

typedef struct {
	VTX_MSGPRE  pre;	/* prefix of hdr*/
	short	    cmdReq;
	} VTX_GCMD_PWRON;	

typedef struct {
	VTX_MSGPRE  pre;	/* prefix of hdr*/
	short	    cmdReq;
	} VTX_GCMD_SIREN;	

/*	program track generic. large enough to hold a 1,2,or 3axis msg.	*/

typedef struct {
	VTX_MSGPRE  pre;	/* prefix of hdr*/
	short	    cmdReq;	
	int			data[4];
	} VTX_GCMD_PTDT;	

/*	program track 3 axis 	*/

typedef struct {
	VTX_MSGPRE  pre;	/* prefix of hdr*/
	short	    cmdReq;	
	int	    	timeMs;	/* in millisecond*/
	int	    	posAz;	/* position azimuth*/
	int	    	posGr;	/* position gregorian*/
	int	    	posCh;	/* position carriage house*/
	} VTX_GCMD_PTDT3;	

/*	program track 2 axis 	order az,greg,ch */

typedef struct {
	VTX_MSGPRE  pre;	/* prefix of hdr*/
	short	    cmdReq;	
	short	    axis;	/* axis to use ..*/
	int	    	timeMs;	/* in millisecond*/
	int	    	posAxis1;	/* position axis 1*/
	int	    	posAxis2;	/* position axis 2*/
	} VTX_GCMD_PTDT2;	

/*	program track 1 axis 	order az,greg,ch */

typedef struct {
	VTX_MSGPRE  pre;	/* prefix of hdr*/
	short	    cmdReq;
	short	    axis;	/* axis to use ..*/
	int	    	timeMs;	/* in millisecond*/
	int	    	posAxis;	/* position axis 1*/
	} VTX_GCMD_PTDT1;	

/*	clear program track */

typedef struct {
	VTX_MSGPRE  pre;	/* prefix of hdr*/
	short	    cmdReq;	
	} VTX_GCMD_PTCLR;	

/*	upload operating parameters 	*/

typedef struct {
	VTX_MSGPRE  pre;	/* prefix of hdr*/
	short	    cmdReq;
	int		    encCorTTD[3];	/* az,gr,ch TTD*/
	short	    tmoutNoHostSec;/* no request from host.. secs*/
	int	        tmoffsetPTMs;  /*time offset prog track millisecs*/
	} VTX_GCMD_OPARM;


/*	reset axis	*/

typedef struct {
	VTX_MSGPRE  pre;	/* prefix of hdr*/
	short	    cmdReq;
	} VTX_GCMD_AXRFLT;
/*
 ******************** mode select *******************************
*/

/*	mode select 	*/

typedef union {
	int	posVel;
	short   aux;
	} UN_SH_INT;

typedef	struct {
	VTX_MSGPRE  pre;	/* prefix of hdr*/
	short	    mode;	/* to select */
	short	    axis;	/* to select 1,2,4 az,gr,ch*/	
	UN_SH_INT   u; 	/* int or short parameter*/   
	} VTX_MSEL;
/*
 ******************** monitor request *******************************
*/
typedef	struct {
	VTX_MSGPRE  pre;	/* prefix of hdr*/
	} VTX_REQ;
/*
 ******************** sync request *******************************
*/
typedef	struct {
	VTX_MSGPRE  pre;	/* prefix of hdr*/
	} VTX_SYNC;
/*
 ******************** msg response ******************************
*/
typedef struct {
	short	status;
	unsigned short   genStat;	/* general status*/
	int		timeMs;			    /* time in millisecs*/
	int	    posAz;				/* azimuth        position 10^-4 deg*/
	int	    posGr;				/* gregorian      position 10^-4 deg*/
	int	    posCh;				/* carriage house position 10^-4 deg*/
	} VTX_RSP_MSG_DATA;

typedef	struct {
	VTX_MSGPRE  pre;			/* prefix of hdr*/
	short	    mtypeReq;		/* msg type of request*/
	VTX_RSP_MSG_DATA dat;		
	} VTX_RSP_MSG;
/*
 ******************** old full data block response (before 8sept97)***
*/
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

#if FALSE
	  int		 posSetPointAz;  /* 10-4 deg*/
	  int		 posSetPointGr;  /* 10-4 deg*/
	  int		 posSetPointCh;  /* 10-4 deg*/
#endif
	  short      velSetPointAz; /* 4.06910^-4 deg/sec*/
	  short      velSetPointGr; /* 4.06910^-4 deg/sec*/
	  short      velSetPointCh; /* 4.06910^-4 deg/sec*/

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
	} VTX_FBLK_V0;
/*
 ******************** operating params  response*******************
*/
typedef struct {
	int		       encCorTTD[3];	/* az,gr,ch TTD*/
	short		   tmoutNoHostSec;/* no request from host.. secs*/
	int	           tmoffsetPTMs;  /*time offset prog track millisecs*/
	} VTX_OPARM;
/*
 * 	and the actual msg
*/
typedef struct {
	VTX_MSGPRE_RSP  pre;	    /* prefix of hdr*/
    VTX_OPARM       dat;		/* actual data block*/ } 
	VTX_RSP_OPARM;
/*
 ******************** ao message table format*******************
argTypes...
 
0xxxx0 : no  1st arg
0x0001 : 1st arg cmdReq
0x0002 : 1st arg mode
0x0004 : 1st arg cmdRsp
0x0008 : 1st arg mon
 
0xxx0x : no second arg
0x0010 : 2nd arg axis
0x0020 : 2nd arg cmdRsp 
0x0040 : 2nd arg mon
0x0080 : 2nd arg misc

0x0100: has seq number

*/

typedef union {
        int     gcmdBit;
        int     mode;
        } VTX_CMD_MODE;

typedef struct {
        int          msgBit;            /* to identify this message*/
        int          msgLen;            /* in bytes this message*/
        VTX_CMD_MODE u;			/* mode or gencmd bits*/ 
		int	     argTypes;  /*t/f --> has axis argument*/
        int          msgType;   /* gcmd,monreq,mode,reply*/
        char         label[5];
        char         descr[20];
        } VTX_MSGI;
/*
 *  to hold list of errors from a status
*/
typedef struct {
    int numErrs;        /* found*/
    int maxErrs;        /* allowed*/
    int *perrs;         /* user should allocate to hold maxErrs*/
    } VTX_ERR_LIST;
/*
 * VTX_ERR_LIST_SCRM added to get rid of int *perrs which is only
 *                   used online. Offline it screws up size on 64 bit
 *                   machines with 8 byte ptrs.
*/
typedef struct {
    int numErrs;        /* found*/
    int maxErrs;        /* allowed*/
    int fill;         /* was a pnter online*/
    } VTX_ERR_LIST_SCRM;


/*
 * 	callable on both systems
*/
int    vtxChkErrs(VTX_CBLK *pcblk,VTX_FBLK *fblk,VTX_ERR_LIST *errGen,
                  VTX_ERR_LIST *errAz,VTX_ERR_LIST *errGr,VTX_ERR_LIST *errCh);
STATUS vtxDcdMsg(char *pmsg,int *ptblInd);

STATUS vtxPrMsg(VTX_MSGI *pmTbl, FILE *fp,int msgMask,int msgInd,char *pmsg);
void   vtxPrCblk(FILE *fp,VTX_CBLK *pcblk);
void   vtxPrFblk(FILE *fp,VTX_FBLK *pfblk);
void   vtxPrStatWd(FILE *fp,short istat,char **pstr,int usedLine);
void   vtxSPrCblk(char *pbuf,VTX_CBLK *pcblk);
void   vtxSPrFblk(char *pbuf,VTX_FBLK *pfblk);
void   vtxSPrStatWd(char *pbuf,short istat,char **pstr,int usedLine);

#endif  /* vtxLIBh */
