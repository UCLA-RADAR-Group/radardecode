/*
 *	include file for phil's tarlib.a (target library routines)
 *
 * history:
 * 4/7/92  - created
*/
#ifndef INCtarLib
#define INCtarLib
#ifdef	VXWORKS
#include	<vxWorks.h>
#else
#include	<vxWorksEm.h>
#endif
#include	<stdio.h>
#include	<irigServ.h>
/* 
 * 	function prototypes in lib
 *	vxWorks and sun routines
*/
IMPORT  STATUS  chkFpFileDate(char *filePrefix,char *psuffix,int *pdayNo,
      					FILE **pfp,int *pfd,char *curFileName);
IMPORT  int     getPriority(char *prgname);
IMPORT  int     intToBCD(int dec);
IMPORT  char    *strtokAo(char *ptok,char *delims,char **pstrTokAo);
IMPORT	int     timeDiffInt(int time1,int time2);
IMPORT	double  timeDiffDbl(double time1,double time2);
IMPORT	void	tolowerS(char *string);
IMPORT	void	toupperS(char *string);
IMPORT  void	errRepStr(char* buf);
IMPORT  int     readn(int fd,char *buf,int numBytes);
IMPORT  int     readnTo(int fd,char *buf,int numBytes,int timeoutUsecs);
IMPORT  int     writen(int fd,char *buf,int numBytes);
IMPORT  STATUS  irigSvTime(IRIGSERV_MSG *pmsg);
/*
 *	routines only defined for vxWorks
*/
#ifdef VXWORKS
IMPORT  STATUS  aoBoltAdmin(char *confFile,int numBolts);
STATUS  devExists(char* devName);
IMPORT  int     exeCmdAO(char* cmdline);
IMPORT  void    inetNetToDot(int  ipAdr,char* ipAdrDot);
IMPORT  int     isSocket(int fd);
IMPORT  STATUS  flushWrite(int fd);
IMPORT STATUS   monFileGrow(char *fname,int curSize,int growSize,
    			int chkRes,int maxLoop,volatile int *pgetOut,int *pnewSize);
IMPORT  STATUS  nfsSync(int fd);
IMPORT  int     read_pipefd(int fd,char *bufadr,int numbytes);
IMPORT	int	servGetByName(char *servreq);
IMPORT  STATUS  setMyPriority(char *prgname);
IMPORT  int	socki_accept(int fdsock);
IMPORT  int	socki_ainfo(int fdsock,unsigned long *paddr,int *pportnum);
IMPORT  int	socki_connect(char *hostname,char *service,int portnum);
IMPORT  int	socki_create(char *service, int portnum);
IMPORT  STATUS  so_getLinger(int fdsock,int *plingerOn,int *plingerValue);
IMPORT  STATUS  so_tcpNDelay(int fdsock,int delayOff);
IMPORT  int     strSystem(char *host,char *cmd,char *result,int resultlen);
IMPORT  FUNCPTR symLkupFunc(char *funcName);
IMPORT  STATUS  symLkup(char *objName,char** pobjAdr,int* pisFunc);
IMPORT  int     taskDShow (int taskId);
IMPORT  int     taskEPAct(char *taskEntryPnt);
IMPORT	int 	truncDtoI(double dd);
IMPORT  STATUS  vmeSnpWP(int slaveMapReg,int snpCode, int writePost);
IMPORT	void	vxWperror(char *string);
/*
 *	function prototypes not in lib but in some modules
*/
IMPORT	double	timerValue(void); 		/* in time/timerAux.c*/
IMPORT	double	timerValueT(void); 		/* in time/timerAux.c*/
#endif
#endif	/*INCtarLib*/  
