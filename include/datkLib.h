/*
 *	include phil for -l phil on aosun
 *  06nov06 - changed dcd.h -> dcdGl.h   Gl.h has the global defs
 *            that are needed for offline routines. Do not have to worry
 *            about all of the vxworks stuff in dcd.h
 * 10oct14  - remove include pntProgState.h.. addded pntMisc.h
 *            so 12meter code can also use things here.
*/
#ifndef INCdatkLibh
#define INCdatkLibh
#include	"phlibExtras.h"
#include	"dcdGl.h"
#include	"vtxLib.h"
#include	"scramBlks.h"
#if FALSE
#include	"agcProgState.h"
#include	"if1ProgState.h"
#include	"if2ProgState.h"
/*#include	"pntProgState.h" */
#include    "tieProgState.h"
#include    "ttProgState.h"
#endif
#include	"pntMisc.h"
#include    "tieLog.h"
#include	"hdrCor.h"
#include	"hdrDop.h"
#include 	"hdrIfLo.h"
#include	"hdrLib.h"
#include    "hdrPnt.h"
#include    "hdrProc.h"
#include	"mshmLib.h"
#include	"aoqPth.h"
#include    "aoqShm.h"
#include    "shs.h"
/*
 *	datatk last edited 19mar06.. for linux
*/
void    comp_a_d_s(float lag01s,float *alphadsigma,float *alphadsigmaratio); 
STATUS  dcdLagCfInfo(int    lagConfig,DCD_CFINFO *pcfI);
float   erfcn(int indx,float a); 
int  	getVmeRec(int fd,char *prgName,int *precnum,char *buf);
STATUS  nc_3lev(int do3levCor,int lenSbc,int lagConfig,DCD_CFINFO *pcfI,
		double integCycles,float *pinbuf,float *acf,float *pads);

STATUS  nc_D_3lev(int do3levCor,int lenSbc,int lagConfig,DCD_CFINFO *pcfI,
		double integCycles,double *pinbuf,double *acf,double *pads);

void    nc_3levCor(int lenacf,int numAcf,double integCycles, float *acf,
		   float *pads);
void    nc_3levXCor(int lencf,double integCycles, float *pdata,float *pads);
void    nc_D_3levCor(int lenacf,int numAcf,double integCycles, double *acf,
		     double *pads);
void    nc_D_3levXCor(int lenacf,double integCycles, double *acf,double *pads);
void    nc_spec3lev(int do3levCor,int lenSbcIn,int lagConfig,DCD_CFINFO *pcfI,
		    double integCycles,float *pinbuf,float *data,float *pads);

void    nc_spec9lev(int *acfInp,int lenacfIn,int lagConfig,DCD_CFINFO *pcfI,
		    double integCycles,float *data,float *lag0);
void    nc_specCmplx(int  lenSbcIn,float *pdata);
void    nc_stokes(int do3levCor,int lenSbcIn,double integCycles,float *pinbuf,
		  float *pscratch,float *pI,float *pV,float *pQ,float *pU,
	          float *pads);
STATUS  nc_9lev(int *pinbuf,int lenSbcIn,int lagConfig,DCD_CFINFO *pcfI,
	 	double integCycles,float *pdata);
int     pntFmtPnt(PNT_COORD *ppnt,PNT_CS_INFO *pcsI,char *buf,int maxLenBuf);
STATUS  searchForHdr(int fd, char* hdrbuf);
STATUS  shsGetKeyValLine(int fd,char *pkey,int maxLine,int *pcurLine,int retVal,
						char *valbuf);
int     shsInpDhdr(int fd,SHS_DHEADER *phdr);
int     shsInpPhdr(int fd,SHS_PHEADER *phdr);
void    swapagc(AGC_STATE *pagc);
void    swapcorhdr(HDRAO_STD *phdr);
void    swapexec(EXECSHM *pexec);
void    swapalfa(ALFASHM *palfa);
void    swaphcor(HDRAO_CORV2 *phdr);
void    swaphdop(HDRAO_DOP *phdr);
void    swaphiflo(HDRAO_IFLO *phdr); 
void    swaphpnt(HDRAO_PNT *phdr);
void    swaphproc(HDRAO_PROC *phdr);
void    swaphstd(HDRAO_STD *phdr);
void    swapif1(IF1_PROG_STATE *pif1);
void    swapif2(IF2_PROG_STATE *pif2);
void    swappnt(PNT_STATE *ppnt);
void    swaptie(TIE_STATE *ptie);
void    swaptielog(TIE_LOG *ptie);
void    swaptur(TT_STATE *ptur);
void    swapvtxcblk(VTX_CBLK *pcblk);
void    swapvtxfblk(VTX_FBLK *pfblk);
void    ttPrAnaVal(FILE *fp,int dev, short *pval);
int     unpriV_f4(int numwrds,int numFifos,int bits,int iqSepReg,char *inPtr,
                  float *outPtr1,float *outPtr2,float *outPtr3,float *outPtr4);
int     unpriV_d8(int numwrds,int numFifos,int bits,int iqSepReg,char *inPtr,
                  double *outPtr1,double *outPtr2,double *outPtr3,
				  double *outPtr4);
int     unpriV_i2(int numwrds,int numFifos,int bits,int iqSepReg,char *inPtr,
                  short *outPtr1,short *outPtr2,short *outPtr3,short *outPtr4);
int     unpriV_i4(int numwrds,int numFifos,int bits,int iqSepReg,char *inPtr,
                  int *outPtr1,int *outPtr2,int *outPtr3,int *outPtr4);
// from aopfs:/home/pfs/src/pfs then changed output char* to float*
void unpack_pfs_2c2b_f4 (unsigned char *buf, float *outbuf, int bufsize);
void unpack_pfs_2c4b_f4 (unsigned char *buf, float *outbuf, int bufsize);
void unpack_pfs_2c8b_f4 (unsigned char *buf, float *outbuf, int bufsize);
void unpack_pfs_4c4b_rcp_f4 (unsigned char *buf, float *rcp, int bufsize);
void unpack_pfs_4c4b_lcp_f4 (unsigned char *buf, float *lcp, int bufsize);
void unpack_pfs_signed16bits_f4(char *buf, float *outbuf, int bufsize);
void unpack_pfs_4c2b_rcp_f4 (unsigned char *buf, float *rcp, int bufsize);
void unpack_pfs_4c2b_lcp_f4 (unsigned char *buf, float *lcp, int bufsize);

void unpack_pdev_2c4b_f4 (unsigned char *buf, float *outbuf, int bufsize);
void unpack_pdev_4c4b_rcp_f4 (unsigned char *buf, float *rcp, int bufsize);
void unpack_pdev_4c4b_lcp_f4 (unsigned char *buf, float *lcp, int bufsize);

STATUS  mshmCpu(void);
STATUS  mcGetBlk(int fdSock,int numBlkReq,MC_REQ_BLK *preqAr);
int     mcJoin(void);

#include	"if1ProgState.h"


#endif  /* INCdatkLib */
