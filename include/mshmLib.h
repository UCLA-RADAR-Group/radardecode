#ifndef INCmshmLibh
#define INCmshmLibh
/*
* include file for monShm. declares shared memory format
*history.. this takes the data from the fiber scramnet and puts it in
*          system 5 shared memory.
*10nov97, pjp.. increased maxnumsem to 25..
*/
#include	"phlibExtras.h"
// #include	"scramBlks.h"

#define		MSHM_SHMKEY		0x101
#define		MSHM_SEMKEY		0x101
#define	    MC_DATATK_IP   "224.1.1.4"
#define	    MC_DATATK_PORT 2007

/*
 * status set by master
*/
#define	   MSHM_STAT_EXIT        0 
#define	   MSHM_STAT_OK          1 
#define	   MSHM_STAT_STARTUP     2 
#define	   MSHM_STAT_PNT_NOT_RESPONDING 3 
#define	   MSHM_STAT_LAST        3

/*
 * read data status these can be orred together. newdata only if all zeros
*/
#define MSHM_READ_NEWDATA		  0
#define MSHM_READ_COLLISION   	  1
#define MSHM_READ_MODCNT_NOCHANGE 2

#define    MSHM_MAX_NUM_SEMS    25

/*
 * indices to locate structure locations in shared memory
*/

#define MSHM_IND_AGC			0
#define MSHM_IND_TT 			1
#define MSHM_IND_TIE 			2 
#define MSHM_IND_PNT 			3 
#define MSHM_IND_IF2 			4 
#define MSHM_IND_IF1 			5 
#define MSHM_IND_SB723 			6 
#define MSHM_IND_ALFM  			7 
#define MSHM_IND_LAST			7

/*	typedefs		*/

/*
 * free list for semaphores
*/
typedef struct {
	int		semNum;  			/* semaphore number*/
	int		pid;				/* processin use or -1*/
	} MSHM_SEM_FL;
/*
 * shared memory header
*/
typedef struct {
    int            status;         /* of daemon*/
    int             maxNumSems;
	int				blkLen;			/* in bytes*/
	int				shmLenUsed;		/* shared memory length in use*/
	int				shmLenAlloc;	/* shared memory length allocated*/
    int             curDataBlkOff;  /* bytes offset, start of shared mem*/
	int			    numEntry;	    /* we have defined in each  block*/
	int				getTmTimeOut;
	int				getTmErrs;
	int				filler;			/* to be on 8 byte boundary*/
    MSHM_SEM_FL     semFl[MSHM_MAX_NUM_SEMS];
	} MSHM_SHM_HDR;
/*
 * Each block starts with an array of these headers
*/
typedef struct {
	int		index;		/* for this block.. mainly to catch memory overwrites*/
	int		offset;		/* for the data portion of struct from start of
						   shared memory*/
	int		bytesData;  /* of data in struct */
	int		modCnt;	    /* last modCnt copied from */
	int		readStat;   /* 0 new data, 1 collision,2 modCnt didnt change*/
	int		readColTot;	/* totalread collisions when we tried to copy it*/
	} MSHM_ENTRY_HDR;
/*
 * structure filled in when attaching to shared memory and semaphore
*/
typedef struct {
	MSHM_SHM_HDR  	*pshmHdr;		/* ptr to shared memory*/
	int			    shmId;			/* shared memory id*/
	int			    semId;			/* semaphore id*/
	int				semNum;			/* 0 thru max -1*/
	} MSHM_ACCESS_INFO; 
/*
 * multicast reqeust
*/
typedef struct {
	char	key[8];	      /* hold jeffs magic key*/
	char    dat[8184];   /* the data (8192-8) */
} MC_BUF; 
typedef struct {
	char	blkName[8];	/* name of block to access*/
	int	    bytesRead; /* we got (excluding magic key in front)*/
	int		fill;	   /* so buf starts on 8 byte boundary*/
	MC_BUF	buf;	  /* hold the data we read key , and */
} MC_REQ_BLK;
/* 
 * 	prototypes 
 * moved to datkLib.h 
*/
#if FALSE
STATUS  mshmCon(MSHM_ACCESS_INFO *paccess);
STATUS  mshmWait(MSHM_ACCESS_INFO *paccess,int *pnumEntry,
					MSHM_ENTRY_HDR **pentryHdrAr);
STATUS  mshmCpu(void);
STATUS  mcGetBlk(int fdSock,int numBlkReq,MC_REQ_BLK *preqAr);
int     mcJoin(void);
#endif
#endif
