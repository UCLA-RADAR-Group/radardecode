/*
 * ao queues are linked lists with semaphores protecting them
*/
#ifndef INC_AOQSHM
#define INC_AOQSHM
#include	<stdio.h>
#include "phlibExtras.h"           
#include "llAo.h"
#include "aotypes.h"
#include <semaphore.h>

#define AOQSHM_NM_PREF "aoqS"

#ifndef MAX
#define MAX(a , b) (( (a) < (b) ) ? (b) : (a))
#endif
#ifndef MIN
#define MIN(a , b) (( (a) < (b) ) ? (a) : (b))
#endif

#define	AOQSHM_GETPSHM(paoqShm) (char *)((char*)(paoqShm) - (paoqShm->qshmOffset))

 
typedef struct  {
	LLSHM_LIST	llhead;		/* head of linked list for queue*/
	sem_t	semMx;		/* mutual exclusion semaphore to manipulate queue*/
	sem_t	semCntEntry;/* counts entries in queue. 0 when empty*/
	s32	    semInitStat;/* 2 --> both initialized. < 2 something wrong*/
    char    qname[12];  /* up to 8 characters we prepend aoqShm for id*/
    u32     qshmOffset; /* offset start shm for this queue struct*/
    u32     m_numputs;  /* total number successfu puts to queue*/
    u32     m_numgets;  /* total number successful gets from queue*/
    u32     m_numgetsempty; /* number gets but queue empty*/
    u32     m_maxnum;   /* max number queue has held*/
    u32     m_minnum;   /* minimum number queue has held*/
    u32     m_curnum;   /* current number in queue*/
	         int  filler  ;   /* stay aligned on 8 byte boundaries*/
    }  AOQSHM;

typedef AOQSHM 	*AOQSHM_PTR;
/*
 * prototypes
*/
int    	aoqShmCheck(AOQSHM_PTR paoqShm);
int    	aoqShmGetNode(AOQSHM_PTR paoqShm,int waitMs,LLSHM_NODE **ppnode);
STATUS 	aoqShmInit(AOQSHM_PTR paoqShm,char *qname,char *pshm);
void    aoqShmPrInfo(AOQSHM_PTR paoqShm,FILE *fp);
STATUS  aoqShmPutNode(AOQSHM_PTR paoqShm,LLSHM_NODE *pnode,int waitMs);
STATUS  aoqShmPutNodeC(AOQSHM_PTR paoqShm,LLSHM_NODE *pnode,int *pcount,
			 int waitMs);
int     aoqShmRemove(AOQSHM_PTR paoqShm);
#endif
