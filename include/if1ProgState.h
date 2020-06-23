/*if1ProgState.h - include file for if1Prog.c
*  %W%    %G%
*/
/*modification history:
----------------------
x.x,16may99 started
x.x,19nov99 added lbwPolLin in state2
x.x,15apr01 added lbnFbNum, lbnfbfreq
x.x,17jun03 added if1_iffrq if1 freq
x.x,10mar04 added stat2.terAcOn
*/
#ifndef INCif1ProgStateh
#define INCif1ProgStateh
#include	<stdio.h>

/*
 *      IfLo config info for headers
*/

/*
 *      pass in start of header, return ptr to start of ifLo Portion of header
*/
#define IFLOHDR_GET(phdr)  ( \
         (HDRAO_IFLO*) ( \
              ((char*)(phdr)) + \
              HDR_S_GET_OFF(((HDRAO_STD *)(phdr))->sec.iflo)\
             ))
/*
 *		if1 status word 1
*/
typedef struct {
	unsigned int    rfNum     :5;   /* rf number 1->16*/
	unsigned int	ifNum	  :3;   /* 1--> 5*/
	unsigned int	hybridIn  :1;   /* 1--> 10ghz hybrid in*/
	unsigned int	lo1Hsd    :1;   /* 1--> lo1 is high side lo*/
	unsigned int	lbwLinPol :1;   /* 1--> lbw lin,0-->circular*/
	unsigned int	syn1RfOn  :1;   /* 1--> synth outputs rf*/
	unsigned int	syn2RfOn  :1;   /* 1--> synth outputs rf*/
	unsigned int	lbFbA     :9;   /* fbankpolA lb,sbw,430. key on rfnum*/
	unsigned int	lbFbB     :9;   /* fbankPolB lb,sbw,430. key on rfnum*/
	unsigned int	useFiber  :1;   /* 1--> come down on fiber*/
	} IF1_ST_STAT1;
/*
 *		if1 status word 2
*/
typedef struct {
	unsigned int	calRcvMux :4;   /* rcv num for mux 0..15*/
	unsigned int	calType   :4;   /* type of cal used 0..15*/

	unsigned int	ac1PwrSw  :4;   /* 1--> on . 3 devices not used..*/
	unsigned int	ac2PwrSw  :4;   /* 1--> on . 4 devices*/

	unsigned int    zmNormal  :1;	/* 1--> not switched*/
	unsigned int	zmDiodeOn :1;    /* 1--> zm diode on*/
	unsigned int	zmDiodeToA:1;   /* 1--> added to chan A*/
	unsigned int	sbShClosed:1;   /* 1--> sband shutter closed*/
	unsigned int	lo2Hsd    :4 ;

	unsigned int	shClosed  :1;     /* 1--> non-sband  sband shutter closed*/
	unsigned int	cbLinPol  :1;   /* 1-> cband linear, 0->cband circular*/
	unsigned int	alfaFb    :1;   /* 0 wb, 1-filter in (100 Mhz)*/
	unsigned int	free      :1;   /* no longer in use*/
	unsigned int	if750nb   :1;   /* 1--> if1 750 narrow band filter*/
	unsigned int	if2ghzwb  :1;   /* 1--> 2_12 ghz if wide band (2ghz)*/
	unsigned int	terAcOn   :1;   /* 1 --> tertiary ac is on */
	unsigned int	tilt      :1;   /* 1 mon tilt, 0 montemp*/
	} IF1_ST_STAT2;

/*
 * synthesizers
*/

typedef struct {
	double freqHz[2];
	int    ampDb[2];		/* units .01 db*/
	int	   errLastIo[2];
	int	   cumIoErrCnt[2];
	} IF1_ST_SYN; 
/*
 * power meter
*/
typedef struct {
    float   pwrDbm[2];
    int     statLastRead;
    int     timeStamp;      /* last read*/
    } IF1_ST_PWRM;
/*
 * hp3488 state
*/
typedef struct {
    short   numslots;       /* in use pol A,B*/
    short   slotOk;         /* bit 0->n 1 if slot ok to use*/
    int     errLastIo;  /* OK or error last i/o*/
    int     cumIoErrCnt;/* cumulative count of errors*/
    unsigned short data[5];/* 0-4 polA, 5-9 polB*/
	unsigned short fill;
    } IF1_ST_3488;

typedef struct {
	char	rf[2];	/* polA/B rf attn 1 db steps 0..11*/
	char	ifA[2];	/* polA/B if attn 1 db steps 0..11*/
	char	zm[2];	/* polA/B zm attn .1 db steps 0..15 = 0 1.5 db*/
	char	zmNDLev;	/* zm noise diode level 0..165. .1db steps*/
	char	fill;		
	} IF1_ST_ATTN;
	
/*
 * not included:
 * rcmvAdr   0-127  rcvm address
 * rcmvDewar 0-10 dewar address
 * IF1_ST_3488   hp3488_2I
*/
/*
 * if1 info
*/
typedef struct {
/*
 *      here's the pnt specific junk
 *      extra space at bottom makes multiple of 8 bytes and can be used
 *      for additions later on
*/
		IF1_ST_SYN	   synI;   /* 2 20ghz synths. 1st lo, 2nd sband 40    [ 0]*/
		IF1_ST_PWRM    pwrmI;  /* power meter info                  16    [40]*/
		double         rfFreq; /* rf frequency hz. topo centric		 8   [ 56]*/
        IF1_ST_STAT1   stat1;  /*   								 4   [ 64]*/
        IF1_ST_STAT2   stat2;  /*                                    4   [ 68]*/
		IF1_ST_ATTN	   attnI;  /*                                    8   [ 72]*/
		float		   ifBwMhz;/* at input to fiber optics           4   [ 80]*/
	    int			   hp87130CumErrs; /* cumlative error count      4   [ 84]*/

		unsigned char  hybLoPh;/* 10 ghz lo phase offset binary units 1  [ 88]*/
		unsigned char  hybSigPh;/*10 ghz signal phase offset binary units[ 89]*/
		short          lbnFbFreq;/*freq Mhz for lbn variable filter  2   [ 90]*/
		int	           fill2;      /*                                4   [ 92]*/
		double         if1FrqMhz;/*if1 freq Mhz                      8   [ 96]*/
		IF1_ST_3488   hp3488I;/* actual bit values output          24   [104]*/
	 	} IF1_PROG_STATE;	   /* 128  bytes, 36 4byte integers            */
		
#endif /*INChdrIfLoh*/
