/*hdrIfLo.h - include file for if/lo portion of headers
*  %W%    %G%
*/
/*modification history:
----------------------
x.x,14nov98 started
*/
#ifndef INChdrIfLoh
#define INChdrIfLoh
#include <stdio.h>
#include "hdrLib.h"

#define HDRAO_IFLO_ID      "iflo"
#define HDRAO_IFLO_CUR_VER " 1.0"
/*
 *      IfLo config info for headers
modification history:
version date
1.0     24jun99 - started.
1.0     18feb05 - added useAlfa, sigSrc to if2.stat1 bitmap
*/

/*
 *      pass in start of header, return ptr to start of ifLo Portion of header
*/
#define IFLOHDR_GET(phdr)  ( \
         (HDRAO_IFLO*) ( \
              ((char*)(phdr)) + \
              HDR_S_GET_OFF(((HDRAO_STD *)(phdr))->sec.iflo)\
             ))
/******************************************************************************
* if1 info
******************************************************************************/
/*
 * first status word
*/
typedef struct {
    unsigned int    rfNum     :5;   /* rf number 1->16*/
    unsigned int    ifNum     :3;   /* 1--> 5*/
    unsigned int    hybridIn  :1;   /* 1--> 10ghz hybrid in*/
    unsigned int    lo1Hsd    :1;   /* 1--> lo1 is high side lo*/
    unsigned int    lbwLinPol :1;   /* 1-->linear pol lbw*/
    unsigned int    syn1RfOn  :1;   /* 1--> synth outputs rf*/
    unsigned int    syn2RfOn  :1;   /* 1--> synth outputs rf*/
    unsigned int    lbFbA     :9;   /* lb filter used polA*/
    unsigned int    lbFbB     :9;   /* lb filter used polB*/
    unsigned int    useFiber  :1;   /* 1--> come down on fiber*/
    } IF1_HDR_STAT1;
/*
 *   2nd status word
*/
typedef struct {
    unsigned int    calRcvMux :4;   /* rcv num for mux 0..15*/
    unsigned int    calType   :4;   /* type of cal used 0..15. def:if1Con.h*/

    unsigned int    ac1PwrSw  :4;   /* 1--> on . 3 devices*/
    unsigned int    ac2PwrSw  :4;   /* 1--> on . 4 devices*/

    unsigned int    zmNormal  :1;   /* 1--> not switched*/
    unsigned int    zmDiodeOn :1;    /* 1--> zm diode on*/
    unsigned int    zmDiodeToA:1;   /* 1--> added to chan A*/

    unsigned int    sbShClosed:1;   /* 1--> sband shutter closed*/
    unsigned int    lo2Hsd    :4;   /* bitmap 1=hisd. b0 1st syn*/
    unsigned int    unused    :8;
    } IF1_HDR_STAT2; 
/*
 *  attenuators
*/
typedef struct {
    char    rf[2];  /* polA/B rf attn 1 db steps 0..11*/
    char    ifA[2]; /* polA/B if attn 1 db steps 0..11*/
    char    zm[2];  /* polA/B zm attn .1 db steps 0..15 = 0 1.5 db*/
    char    zmNDLev;    /* zm noise diode level 0..165. .1db steps*/
    char    fill;
    } IF1_HDR_ATTN;
/*
 *  if1 header structure
*/
typedef struct {
    IF1_HDR_STAT1   st1;      /* first stat word                        [ 0]*/
    IF1_HDR_STAT2   st2;      /* 2nd stat word                          [ 4]*/
    double         rfFrq;     /* rf Freq topoCentric hz                 [ 8]*/
    double         lo1;       /* 1st lo in hz                           [16]*/
    IF1_HDR_ATTN   attn;      /* attenuators                            [24]*/
    float          pwrDbm[2]; /* power meter polA,B in dbm              [32]*/
    int            pwrTmStamp;/* second midnite pwr meter reading       [40]*/
    unsigned char  hybLoPh;   /*10ghz lo phase offset binary units 1    [44]*/
    unsigned char  hybSigPh;  /*10ghz signal phase offset binary units  [45]*/
    char           fill[2];   /* filler                                 [46]*/
    } HDRAO_IF1;              /* 48 bytes, 12 4byte integers                */

/******************************************************************************
* if2 header info
******************************************************************************/
/*
 *  if2 status word.
*/
typedef struct {
    unsigned int    ifInpFreq :2;   /*inp freq. 0,1,2,3->spare,300,750,1500*/
    unsigned int    vlbaInpFrq:1;   /* 0-750,1:2000                        */
    unsigned int    xferNormal:1;   /* 1-normal, 0-switched                */
    unsigned int    sbDopTrack:1;   /* 1--> true, 0 false(now 430Blank)    */
    unsigned int    noiseSrcOn:1;   /* 1--> on, 0 off                      */
    unsigned int    dualPol30 :1;   /* 30mhzIf 2 pol, 1-true, 0 - 4 polA   */
    unsigned int    vis30Mhz  :1;   /* 1--> greg, 0 ch                     */
    unsigned int    calttlSrc :4;   /* 1-->8 cal ttl level source          */
    unsigned int    pwrMToIf  :1;   /* power meter swithed to IF input     */
    unsigned int    useAlfa   :1;   /* if set then ignore ifinFreq         */
    unsigned int    sigSrc    :2;   /* signal src 0-gr,1-ch,2=noise        */
    unsigned int    unused    :16;
    } IF2_HDR_STAT1;
/*
 *   status word 1 for each mixer
*/
typedef struct {
    unsigned int    synDest  :2;   /* 1-260to30,2-vlba/sb,3-mixers,0-fp    */
    unsigned int    mixerCfr :2;   /*mixFreq. 0,1,2,3->750,1250,1500,1750  */
    unsigned int    ampInpSrc:2;   /*0,1=syn,2=heliax,3=300 if             */
    unsigned int    ampExtMsk:7;   /* bitmask 1-> ext input, 0-> from if/lo*/
    unsigned int    unused   :19;
    } IF2_HDR_STAT4;
/*
 *  if2 stucture
*/
typedef struct {
    double          synFreq[4];   /* 4 synth freq in hZ                 [ 0]*/
    IF2_HDR_STAT1   st1;          /* stat word, general                 [32]*/
    IF2_HDR_STAT4   st4[4];       /* stat 1 for each mixer              [36]*/
    float           pwrDbm[2];    /* power meter polA,B                 [52]*/ 
    int             pwrTmStamp;   /* seconds from midnite when pwr meas [60]*/
    char            gain[2];      /* gain polA  -11 to 30 db            [64]*/
    char            fill[6];      /* filler                             [66]*/
    } HDRAO_IF2;            /* 72 bytes. 18 4byte integers*/
/*
 * structure for if/lo
*/
typedef struct  {
	char		id[4];		  /* iflo no null terminated*/
	char		ver[4];		      /* xx.x version num. not null terminated*/
    HDRAO_IF1   if1;              /* if1 lo                             [ 0]*/
    HDRAO_IF2   if2;              /* if2 lo                             [48]*/
    char        fill[8];          /* filler                            [120]*/
    }   HDRAO_IFLO;               /* 136 bytes, 34 4byte  integers           */

void    hdrPrIfLo(FILE *fptr,void *phdr);
void    hdrDToIfLo(double *pd,HDRAO_IFLO *phdr);
void    hdrIfLoToD(HDRAO_IFLO *phdr,double *pd);
#endif /*INChdrIfLoh*/
