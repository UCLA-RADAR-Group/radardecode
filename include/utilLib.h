/*
 *	include phil for -l phil on aosun
 *  06nov06 - changed dcd.h -> dcdGl.h   Gl.h has the global defs
 *            that are needed for offline routines. Do not have to worry
 *            about all of the vxworks stuff in dcd.h
*/
#ifndef INCutilLibh
#define INCutilLibh

#include    <phlibExtras.h>
#include	<stdio.h>
#include	<sys/sem.h>
#include	<sys/shm.h>
#include    <semaphore.h>
#include	<time.h>

/*  following used by comppncode()
    and radar decode
*/
#define CODETYPE_PNC_SITE_AO   1
#define CODETYPE_PNC_SITE_DSN  2
#define CODETYPE_BARKER        3
/*
 * following used by people who call reportEr
*/
#define ERR_LEVEL_FATAL         1
#define ERR_LEVEL_WARNING       2
#define ERR_LEVEL_DEBUG         3
#define ERR_LEVEL_LOG           4


typedef struct  {
        int     num_reg;                /* registers for this code*/
        int     len;                    /* length of code*/
        int     num_fdback;             /* number feed backs this code*/
        int     fdback[4];              /* feed backs for this code*/
        } PNCODE_INFO;

/* structure for timing code. used by tmi_xxx routines */

typedef struct {
    double  minSecs;
    double  maxSecs;
    double  lastSecs;
    double  sumSecs;
    double  sumSqSecs;
          /* number summed for avg,rms */
    int     n;
    } AO_TMI;             

/*
 *	
*/
time_t  aogettime(int *pyear,int *pdayno,int *psecmid);
void    aomsg(int where,char *type,char *src,char *format,...);
void    aomsginit(void (*proc)(int,char*));
int     aoSemWait(sem_t *psemMx,int waitMs);
void	bitfieldflip(unsigned int *pval,char *str);
void	byteswap_2i(short *pval);
void	byteswap_2iu(unsigned short *pval);
void	byteswap_4i(int *pval);
void    byteswap_4iu(unsigned int *pval);
void	byteswap_4f(float *pval);
void	byteswap_8d(double *pval);
void	byteswap_8i(long long *pval);
int chkFileDate(char *filePrefix,char *psuffix,int *pdayNo,
      	FILE **pfp,char *curFileName);
int     compbarkercode(int codelen,int minval,int maxval,int *pcode);
int     comppnc_init(int codelen,int codetype,PNCODE_INFO *pcodeI);
int     comppnc_shiftit(int num_reg,int num_fdback,int fb1,int fb2,int fb3,
                        int fb4,int *shiftreg);
int     comppncode(int codelen,int codetype,int minval,int maxval,int *pcode);
const char 	*error_last(void);  
int     daemonStart(int ignSigChild);
int     filetype_fd(int fd);
int     filetype_p(char *path);
int     fitsCmpScl(char *outdata,double dmaxval,double dminval,double *pbscale,
                   double *pbzero);
int     fitsOutData(int usefptr,FILE *fptr,int fd,char *datatype,
                    char *outtype,int numwords,double bscale,double bzero,
                    char *buf);
int     fitsOutHdr(int usefptr,FILE *fptr,int fd,char *datatype,
                   int naxis,int numCols,int numRows,int naxis3 ,
                   double bscale,double bzero);
int     gets_fd(int fd,int maxbytes,char *buf);
int     hostNameVer(char *phostName); 
int     lockfileget(char *lockFileNm,int fileProt,int *ppidOwner,
            void (*msg)(const char *,...));
int     pathexp(char *path,int resultMaxLen,char *result);
int     read_anydev(int fd,int file_type,char *bufadr,int numbytes);
int     read_pipe(char *bufadr,int numbytes);
int     read_pipefd(int fd,char *bufadr,int numbytes);

void    reportErr(char *prgname,int level,int errnoRep,char *msg);

int  	semipc_cleanup(int  semId);    
int  	semipc_give(int semId,int semNum,int value);
int  	semipc_set(int semId,int semNum,int value);
int  	semipc_setAll(int semId,unsigned short *semValAr);
int  	semipc_setup(key_t  semkey,int numSem,int *psemId);
int  	semipc_take(int semId,int semNum,int value,int wait);
int  	semipc_waitZero(int semId,int semNum);


int     shmipc_cleanup(int shmid);
int     shmipc_setup(key_t shmkey,int shmsize,int *shmid,char **shmptr);
int     shmipc_setup2(key_t shm_key,int *shm_id,unsigned char **shm_ptr);
double  sleeptilltm(double secs1970);
int     so_tcpNDelay(int fdsock,int delayOff);
int     socki_accept(int fdsock);
int     socki_ainfo(int fdsock,unsigned long *paddr,int *pportnum);
int     socki_connect(char *hostname,char *service,int portnum);
int     socki_create(char *service,int portnum,char *hostname);
int     socki_create_reuse(char *service,int portnum,char *hostname);
int     socki_mcjoin(char *ipAdrDot,int portNum,void (*msg)(const char *,...));
int     socku_connect(char    *filename);
int     socku_create(char *filename);
int     ssystem(char *command,int resultlen,char *result);
double  timerint(double start,double stop);
int     timerstart(void);
double  timervalue(void);
double  tmget1(void);
double  tmget2(void);
void    tmi_init(AO_TMI *ptmI);
double  tmi_load(double tmStart,double tmEnd,AO_TMI *ptmI);
void    tmi_print(FILE *fp,AO_TMI *ptmI,int hdr,char *msg);
void    to_lowercase(char  *sptr);
void    to_uppercase(char  *sptr);
double  tsccalib(double secsToWait);
double  tscread(void);
#endif  /* INCutilLib */
