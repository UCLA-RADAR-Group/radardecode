/*
 *	include file for rilib.h
 *
 * history:
 * 20feb93 - created
*/
#ifndef INCriLibh
#define INCriLibh
#ifdef	VXWORKS
#include	<vxWorks.h>
#include	<stdioLib.h>
#else
#include	<vxWorksEm.h>
#include	<stdio.h>
#endif
#include "ri.h"

/*	defines		*/

/*	riPlToConf	 pl index for particular values */

#define PLEXTTIME  0
#define PLSMPMODE  1
#define PLFORM     2
#define PLPACK     3
#define PLSUBCYC   4
#define PLGWCNT    5
#define PLFIFO     6
#define PLBLT      7
#define PLSEQLEN   8
#define PLSINWAV   9
#define PLMUXDATA  10
   
/*
 * 	prototypes for functions
*/
STATUS  plToConf(double *ppl,RI_CONFIG *pcf);
void    riBitsPrint(FILE *fptr,int numsamples,int fifoForRead,
                   int *digIBits1,int *digQBits1,int *digIBits2,int *digQBits2);
void    riBitsTest(FILE *fptr,int numsamples,int fifoForRead,int *inbuf);
void    riBitsUsed(int numsamples,int numchan,int zeroIt,int *inbuf,
                   int *digIBits1,int *diqQBits1,int *digIBits2,int *digQBits2);
int     riCmdDigBeg(int clrIppFlag);
STATUS  riCmdReadBeg(int fifo,int useBlt,int clrIppFlag,int *pcmd);
void    riFitSW(float freqtouse,int numpoints_fit,float* x,float* y,
		float* pamp,float* pphase,float* poffset,float* prms,float* pa,
          	float* pb,float* pc);
void    riPrConfig(FILE *fp,RI_CONFIG *pcf);
void    riPrintStat(FILE *fptr,int ristatus);
int 	riPrIoRate(int packing,int numFifo,double ippUsec,int spIpp,
      		int numPairs,int ippsPerBuf);
int     riQScImmMode(RI_SC *sc);
int     riQScIppMode(RI_SC *sc);
STATUS  riRmtGetConf(int fdsock,RI_CONFIG *priconf,int *pdsc);
STATUS  riRmtRead(int fdsock,char *databuf,int bytesForRead,int *pdsc);
STATUS  riRmtSndConf(int fdsock,RI_CONFIG *pcf,int *pdsc);
void    riScSetEnaMuxSW(int enableSineWave,RI_SC *psc);
void    riScSetExtTiming(int extTiming,RI_SC *psc);
STATUS  riScSetForm(char *formatter,RI_SC *psc);
void    riScSetGwCountOn(int gwCountOn,RI_SC *psc);
STATUS  riScSetMuxSWChan(int sineWaveChan,RI_SC *psc);
STATUS  riScSetPacking(int packing,RI_SC *psc);
STATUS  riScSetSmpMode(char *smpMode,RI_SC *psc);
void    riScSetSubCycle(int subCycle,RI_SC *psc);
void    riSetBlt(int useBlt,RI_CONFIG *pcf);
STATUS  riSetConf(int extTiming,char* cformatter,int gwCount,int packing,
         char*  csmpMode,int subCycleOn,int seqLen,int fifoForRead,
	 int useBltRead,int muxSineWave,RI_MUXCF *pmuxcf,RI_CONFIG *pconf);
STATUS  riSetFifo(int fifo,RI_CONFIG *pcf);
STATUS  riSetGwCount(int gwCount,RI_CONFIG *pcf);
STATUS riSetMuxSW(int sineWaveChan,RI_CONFIG *pcf);
STATUS  riSetSc(int extTiming,char *csmpMode,char *cformMode,
                int packing,int subCycleOn,int gwCountOn,int muxSWChan,
                int enableMuxSW,RI_SC *psc);
STATUS  riSetSeqLen(int seqLen,RI_CONFIG *pcf);
STATUS  riSetSubCycle(int subCycLen,RI_CONFIG *pcf);
STATUS  unpriSep_d8(int numwrds,int numFifos,int bits,int iqSepReg,char *inPtr,
                  double *outPtr1,double *outPtr2,double *outPtr3,
		  double *outPtr4);
STATUS  unpri_d8(int numwrds,int numFifos,int bits,char *inPtr,double *outPtr1,
                 double *outPtr2) ;
STATUS  unpri_f4(int numwrds,int numFifos,int bits,char *inPtr,float *outPtr1,
                 float *outPtr2) ;
STATUS  unpri1Chn_f4(int numwrds,char *pol,int bits,char *inPtr,float *outPtr1,
		     float *outPtr2);
STATUS  unpri_i2(int numwrds,int numFifos,int bits,char *inPtr,short *outPtr1,
	         short *outPtr2);
STATUS  unpri_i4(int numwrds,int numFifos,int bits,char *inPtr,int *outPtr1,
                 int *outPtr2);
STATUS  unpriV_d8(int numwrds,int numFifos,int bits,int iqSepReg,
			char *inPtr,double *outPtr1,double *outPtr2,double *outPtr3,
     		double *outPtr4);
STATUS  unpriV_f4(int numwrds,int numFifos,int bits,int iqSepReg,
	    		  char *inPtr,float *outPtr1,float *outPtr2,float *outPtr3,
				  float *outPtr4);
STATUS  unpriV_i2(int numwrds,int numFifos,int bits,int iqSepReg,
			char*inPtr,short *outPtr1,short *outPtr2,short *outPtr3,
 	     	short *outPtr4);
STATUS  unpriV_i4(int numwrds,int numFifos,int bits,int iqSepReg,
			char *inPtr,int *outPtr1,int *outPtr2,int *outPtr3,
    		int  *outPtr4);
#endif	/*INCriLibh*/  
