/*
 *	include phil for -l phil on aosun
*/
#ifndef INCphilLibh
#define INCphilLibh
#include	<vxWorksEm.h>
#include	<stdio.h>
#include    <sys/types.h>
#include    "convLib.h"
#include    <dcd.h>
/*
 *	datatk last edited 21may 94
*/
#define	IQADJ	1
#define	IQSEP	2

/*
 * tape 
*/
int     daemonStart(int ignSigChild);
int     f_mt_bsf_(int *tapefd,int *numfiles);
int     f_mt_bsr_(int *tapefd,int *numrecs);   
int     f_mt_fsf_(int *tapefd,int *numfiles);
int     f_mt_fsr_(int *tapefd,int *numrecs);
int 	f_mt_read_(int *tapefd,char *bufptr,int *numbytes);
int     f_mt_rew_(int  *tapefd);
int  	f_mt_stat_(int *tapefd);
int     f_mt_statll_(int *tapefd,int *type,int *dsreg,int *errreg,int *rescnt); 
int     f_mt_weof_(int *tapefd,int *numfilemarks);
int 	f_mt_write_(int *tapefd,int *numbytes,char *bufptr);
int     mt_bsf(int tapefd,int numfiles);
int     mt_bsr(int tapefd,int numrecs);
int     mt_fsf(int tapefd,int numfiles);
int     mt_fsr(int tapefd,int numrecs);
int 	mt_read(int tapefd,char *bufptr,int  numbytes);
int     mt_rew(int tapefd);
int 	mt_stat(int tapefd);
int     mt_statll(int tapefd,int *type,int *dsreg,int *errreg,int *rescnt);
int     mt_weof(int tapefd,int numfilemarks);
/*
 *	util last edited: 08aug96
*/
char 	*error_last(void);  
void 	f_error_last_(char *cbuf);
int     f_read_(int *fd,char *inbuf,int *numbytes);
int     f_read_pipe_(char *inbuf,int *numbytes);
double  f_timerint_(double *start,double *stop);
int     f_timerstart_(void);
double  f_timervalue_(void);
int     f_write_(int *fd,char *outbuf,int *numbytes);
int     fbinfo(int *type,int *height,int *width,int *depth,int *cmsize,
		int *totsize);
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
int     hostNameVer(char *phostName); 
void    move_bytes(char *to_ptr,char *from_ptr,int numbytes);
STATUS  pathexp(char *path,int resultMaxLen,char *result);
int     read_anydev(int fd,int file_type,char *bufadr,int numbytes);
int     read_pipe(char *bufadr,int numbytes);
int     read_pipefd(int fd,char *bufadr,int numbytes);

int  	sem_cleanup(int  semId);    
int  	sem_give(int semId,int semNum,int value);
int  	sem_set(int semId,int semNum,int value);
int  	sem_setAll(int semId,unsigned short *semValAr);
int  	sem_setup(key_t  semkey,int numSem,int *psemId);
int  	sem_take(int semId,int semNum,int value,int wait);
int  	sem_waitZero(int semId,int semNum);


int     shm_cleanup(int shmid);
int     shm_setup(key_t shmkey,int shmsize,int *shmid,char **shmptr);
int     shm_setup2(key_t shm_key,int *shm_id,unsigned char **shm_ptr);
STATUS  so_tcpNDelay(int fdsock,int delayOff);
int     socki_accept(int fdsock);
int     socki_ainfo(int fdsock,unsigned long *paddr,int *pportnum);
int     socki_connect(char *hostname,char *service,int portnum);
int     socki_create(char *service,int portnum,char *hostname);
int     socku_connect(char    *filename);
int     socku_create(char *filename);
int     ssystem(char *command,int resultlen,char *result);
double  timerint(double start,double stop);
int     timerstart(void);
double  timervalue(void);
void    to_lowercase(char  *sptr);
void    to_uppercase(char  *sptr);

/*
 *	datatk last edited 29feb96
*/
void    acf_3lev_cor(int lenacf,float bias,int digthreshold,float   *acf);
void    chn_get_bc(int numlags,int getbinv,unsigned char *inp_buf,float *b,
				   float   *c);
void    chn_hdr1(int *hdr,int *numlags,int *numblk2731,int *dumpsperblk,
    			 int *bytespc,int *byteslag,int *bytesrec);
void    chn_scale(int dumplen,int numdumps,float *binv,float *c,float *lagdata);
void    chn_unp_pc(int frqhitolow,int numdumps,unsigned char *inptr,
				   float *outptr);
void    comp_a_d_s(float lag01s,float *alphadsigma,float *alphadsigmaratio); 
float   erfcn(int indx,float a); 
void 	f_chn_get_bc_(int *numlags,int *getbinv,unsigned char *inp_buf,float *b,
    				  float   *c);
void 	f_chn_hdr1_(int *hdr,int *numlags,int *numblk2731,int *dumpsperblk,
    				int *bytespc,int *byteslag,int *bytesrec);
void 	f_chn_scale_(int *dumplen,int *numdumps,float *binv,float *c,
					float *lagdata);
void 	f_chn_unp_pc_(int *freqhitolow,int *numdumps,unsigned char *inbuf,
    				  float *outbuf);
int 	f_findhdr_(int *fd,char *header,int *hdrlen,char *hdr_id,int *maxbytes,
    			   int cheaderlen,int chdr_idlen);
void   	f_hcnv_adg_(char *inbuf,int *outbuf);
void   	f_hcnv_chn_(char  *inbuf,int   *outbuf);
void   	f_hcnv_hi_(char   *inbuf,int   *outbuf);
void   	f_hcnv_int_(char  *inbuf,int   *outbuf);
void   	f_hcnv_low_(char   *inbuf, int   *outbuf);
void   	f_hcnv_lowa_(char   *inbuf,int   *outbuf);
void    f_hcnv_main_(char   *inbuf, int   *outbuf);
void   	f_hcnv_mars_(char   *inbuf,int   *outbuf);
void   	f_hcnv_moon_(char   *inbuf,int   *outbuf);
void    f_hcnv_spec_(char   *inbuf,int   *outbuf);
void    f_hcnv_win_(char   *inbuf, int   *outbuf);
void    f_hcnva_adg_(char   *inbuf,double *outbuf);
void   	f_hcnva_chn_( char   *inbuf, double *outbuf);
void   	f_hcnva_hi_(char   *inbuf, double *outbuf);
void    f_hcnva_int_(char   *inbuf, double *outbuf);
void    f_hcnva_low_(char   *inbuf, double *outbuf);
void    f_hcnva_lowa_(char   *inbuf, double *outbuf);
void    f_hcnva_main_(char   *inbuf, double *outbuf);
void    f_hcnva_mars_(char   *inbuf, double *outbuf);
void    f_hcnva_moon_(char   *inbuf,double *outbuf);
void    f_hcnva_spec_(char   *inbuf, double *outbuf);
void    f_hcnva_win_(char   *inbuf,double *outbuf);

void 	f_hc_to_sc_(int *numbers,int *fill,u_char *input,u_char  *output);
void 	f_hi_to_si2_(int *numbers,u_char *input,u_char *output);
void 	f_hi_to_si4_(int *numbers,u_char *input,int  *output);
void 	f_hr_to_sr4_(int *numbers,u_char *input,float *output);
void	f_hr_to_sr8_(int *numbers,u_char *input,double  *output);
int  	f_spec_dofft_(float   *data,int *numsbc,int *lensbc,int *numsbcgrp,
    				int *usedoublenyquist,int *levelcorrection,
					float *integtime,float *dumptime,int *digthresholds);
void 	f_unp_12_i2_(int *numwrds,char *pol,unsigned char *inbuf,short *outbuf,
    				 int cpollen,int cinbuflen);
void 	f_unp_12_i4_(int *numwrds,char *pol,unsigned char *inbuf,short *outbuf,
			      int cpollen,int cinbuflen);
void 	f_unp_12_i4r_(int *numwrds,char *pol,unsigned char *inbuf,int *outbuf,
    				   int cpollen,int cinbuflen);
void 	f_unp_1_i2_(int *numwrds,char *pol,unsigned char *inbuf,short *outbuf,
	    			int cpollen,int cinbuflen);
void 	f_unp_1_i4_(int *numwrds,char *pol,unsigned char *inbuf,int *outbuf,
    				int cpollen,int cinbuflen);
void	f_unp_2_i2_(int *numwrds,char *pol,unsigned char *inbuf,short *outbuf,
    				int cpollen,int cinbuflen);
void 	f_unp_2_i4_(int *numwrds,char *pol,unsigned char *inbuf,int *outbuf,
    				int cpollen,int cinbuflen);
void 	f_unp_3_i2_(int *numwrds,char *pol,unsigned char *inbuf,short *outbuf,
				    int cpollen,int cinbuflen);
void 	f_unp_3_i4_(int *numwrds,char *pol,unsigned char *inbuf,int *outbuf,
    				int cpollen,int cinbuflen);
void 	f_unp_4_i2_(int *numwrds,char *pol,unsigned char *inbuf,short *outbuf,
    				int cpollen,int cinbuflen);
void 	f_unp_4_i4_(int *numwrds,char *pol,unsigned char *inbuf,int *outbuf,
    				int cpollen,int cinbuflen);
void 	f_unp_4z_r4_(int *num4bit,unsigned char *inbuf,float *outbuf);
void 	f_unp_6_i2_(int *numwrds,char *pol,unsigned char *inbuf,short *outbuf,
					int	cpollen,int cinbuflen);
void 	f_unp_6_i4_(int *numwrds,char *pol,unsigned char *inbuf,int *outbuf,
    				int cpollen,int cinbuflen);
int 	findhdr(int fd,char *header,int hdrlen,char *hdr_id,int maxbytes);
int  	getVmeRec(int fd,char *prgName,int *precnum,char *buf);


void   hcnv_adagio(char *inbuf,int *outbuf);
void   hcnv_chirp(char *inbuf,int *outbuf);
void   hcnv_corchn(char *inbuf,int *outbuf);
void   hcnv_corhi(char *inbuf,int *outbuf);
void   hcnv_corint(char *inbuf,int *outbuf);
void   hcnv_corwin(char *inbuf,int *outbuf);
void   hcnv_dopsy(char *inbuf,int *outbuf);
void   hcnv_lowatm(char *inbuf,int *outbuf);
void   hcnv_lowwin(char *inbuf,int *outbuf);
void   hcnv_main(char *inbuf,int *outbuf);
void   hcnv_mars(char *inbuf,int *outbuf);
void   hcnv_moon(char *inbuf,int *outbuf);
void   hcnv_nurad(char *inbuf,int *outbuf);
void   hcnv_rdrdcd(char *inbuf,int *outbuf);
void   hcnv_rdrmap(char *inbuf,int *outbuf);
void   hcnv_rdrms(char *inbuf,int *outbuf);
void   hcnv_spec(char *inbuf,int *outbuf);
void   hcnva_adagio(char *inbuf,double *hdr);
void   hcnva_chirp(char *inbuf,double *hdr);
void   hcnva_corchn(char *inbuf,double *hdr);
void   hcnva_corhi(char *inbuf,double *hdr);
void   hcnva_corint(char *inbuf,double *hdr);
void   hcnva_corwin(char *inbuf,double *hdr);
void   hcnva_dopsy(char *inbuf,double *hdr);
void   hcnva_lowatm(char *inbuf,double *hdr);
void   hcnva_lowwin(char *inbuf,double *hdr);
void   hcnva_main(char *inbuf,double *hdr);
void   hcnva_mars(char *inbuf,double *hdr);
void   hcnva_moon(char *inbuf,double *hdr);
void   hcnva_nurad(char *inbuf,double *hdr);
void   hcnva_rdrdcd(char *inbuf,double *hdr);
void   hcnva_rdrmap(char *inbuf,double *hdr);
void   hcnva_rdrms(char *inbuf,double *hdr);
void   hcnva_spec(char *inbuf,double *hdr);

void 	hc_to_sunc(int numbers,int fill,u_char *input,u_char  *output);
void 	hi_to_suni2(int numbers,u_char *input,u_char *output);
void 	hi_to_suni4(int numbers,u_char *input,int *output);
void 	hr_to_sunr4(int numbers,u_char *input,float *output);
void 	hr_to_sunr8(int numbers,u_char *input,double *output);

void   hpr_adagio(FILE *fpout,int *inbuf);
void   hpr_chirp(FILE *fpout,int *inbuf); 
void   hpr_corchn(FILE *fpout,int *inbuf);
void   hpr_corhi(FILE *fpout,int *inbuf); 
void   hpr_corint(FILE *fpout,int *inbuf);
void   hpr_corwin(FILE *fpout,int *inbuf);
void   hpr_dopsy(FILE *fpout,int *inbuf); 
void   hpr_lowatm(FILE *fpout,int *inbuf);
void   hpr_lowwin(FILE *fpout,int *inbuf);
void   hpr_main(FILE *fpout,int *inbuf);  
void   hpr_mars(FILE *fpout,int *inbuf);
void   hpr_moon(FILE *fpout,int *inbuf);
void   hpr_nurad(FILE *fpout,int *inbuf);
void   hpr_rdrdcd(FILE *fpout,int *inbuf);
void   hpr_rdrmap(FILE *fpout,int *inbuf);
void   hpr_rdrms(FILE *fpout,int *inbuf); 
void   hpr_spec(FILE *fpout,int *inbuf); 
void   hpra_adagio(FILE *fpout,double *inbuf);
void   hpra_chirp(FILE *fpout,double *inbuf); 
void   hpra_corchn(FILE *fpout,double *inbuf);
void   hpra_corhi(FILE *fpout,double *inbuf); 
void   hpra_corint(FILE *fpout,double *inbuf);
void   hpra_corwin(FILE *fpout,double *inbuf);
void   hpra_dopsy(FILE *fpout,double *inbuf); 
void   hpra_lowatm(FILE *fpout,double *inbuf);
void   hpra_lowwin(FILE *fpout,double *inbuf);
void   hpra_main(FILE *fpout,double *inbuf);  
void   hpra_mars(FILE *fpout,double *inbuf);
void   hpra_moon(FILE *fpout,double *inbuf);
void   hpra_nurad(FILE *fpout,double *inbuf);
void   hpra_rdrdcd(FILE *fpout,double *inbuf);
void   hpra_rdrmap(FILE *fpout,double *inbuf);
void   hpra_rdrms(FILE *fpout,double *inbuf); 
void   hpra_spec(FILE *fpout,double *inbuf); 

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

int 	pos_tape(int tapefd,FILE *fpmsg,int scanreq,int recreq,char *hdridreq);
int     pos_tpinfo(int tapefd,int *scan,int *rec,char *hdrid,int *hiteof,
				   int *hiteot,int *readerror);

int     spec_dofft(float *data,int numsbc,int lensbc,int numsbcgrp,
				   int usedoublenyquist,int levelcorrection,float   integtime,
    			   float dumptime,int *digthresholds);
void    unp_12_i2(int numwds24,char *inptr,short int *outptr);
void    unpack_12_i2(int numwds24,char *pol,char *inptr,short int *outptr);
void    unpack_12_i4(int numwds24,char *pol,char *inptr,int  *outptr);
void    unpack_12_i4r(int numwds24,char *pol,char *inptr,int *outptr);
void    unpack_1_i2(int numwrds,char *pol,unsigned char *inbuf,short *outbuf);
void 	unpack_1_i4(int numwrds,char *pol,unsigned char *inbuf,int *outbuf);
void 	unpack_2_i2(int numwrds,char *pol,unsigned char *inbuf,short *outbuf);
void 	unpack_2_i4(int numwrds,char *pol,unsigned char *inbuf,int *outbuf);
void 	unpack_3_i2(int numwrds,char *pol,unsigned char *inbuf,short *outbuf);
void 	unpack_3_i4(int numwrds,char *pol,unsigned char *inbuf,int *outbuf);
void 	unpack_4_i2(int numwrds,char *pol,unsigned char *inbuf,short *outbuf);
void  	unpack_4_i4(int numwrds,char *pol,unsigned char *inbuf,int *outbuf);
void 	unp_4z_r4(int num4bit,unsigned char *inbuf,float   *outbuf);
void 	unpack_6_i2(int  numwrds,char *pol,unsigned char *inbuf,
					short int*outbuf);
void 	unpack_6_i4(int numwrds,char *pol,unsigned char *inbuf,int *outbuf);
void    unpack_to_i4(int bits,int numwds24,char *pol,char *inptr,int *outptr);

/*
 *	dtvme..
*/
STATUS  dtReadGrp(int fd,char *pinBuf,int inBufMax,char *pretBuf,int retBufMax,
         	  int *precNum);
int     dtReadRec(int fd,char *buf,int bufMaxLen,int *precNum);
#endif  /* INCphilLib */


