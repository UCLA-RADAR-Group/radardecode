/*
 * ao queues for pthreads 
*/
#ifndef INC_AOQPTH
#define INC_AOQPTH
#include	<stdio.h>
#include <pthread.h>
#include "phlibExtras.h" 
#include "llAo.h"
#include "aotypes.h"

#define AOQPTH_NM_PREF "aoqP"

#ifndef MAX
#define MAX(a , b) (( (a) < (b) ) ? (b) : (a))
#endif

#ifndef MIN
#define MIN(a , b) (( (a) < (b) ) ? (a) : (b))
#endif

typedef struct  {
	LL_LIST	llhead;		/* head of linked list for queue*/
	pthread_mutex_t mutex;  /* mutex for access*/
	pthread_cond_t notEmptycv; /* condition variablel not empty*/
	s32    semInitStat;/* 2 --> both initialized. < 2 something wrong*/
    char    qname[12];  /* up to 8 characters we prepend aoqPth for id*/
    u32  m_numputs;  /* total number successfu puts to queue*/
    u32  m_numgets;  /* total number successful gets from queue*/
    u32  m_numgetsempty; /* number gets but queue empty*/
    u32  m_maxnum;   /* max number queue has held*/
    u32  m_minnum;   /* minimum number queue has held*/
    u32  m_curnum;   /* current number in queue*/
    }  AOQPTH;

typedef AOQPTH 	*AOQPTH_PTR;
/*
 * prototypes
*/
int    	aoqPthCheck(AOQPTH_PTR paoqPth);
int    	aoqPthGetNode(AOQPTH_PTR paoqPth,int waitMs,LL_NODE **ppnode);
STATUS 	aoqPthInit(AOQPTH_PTR paoqPth,char *qname);
void    aoqPthPrInfo(AOQPTH_PTR paoqPth,FILE *fp);
STATUS  aoqPthPutNode(AOQPTH_PTR paoqPth,LL_NODE *pnode,int waitMs);
STATUS  aoqPthPutNodeC(AOQPTH_PTR paoqPth,LL_NODE *pnode,int *pcount,
			 int waitMs);
int     aoqPthRemove(AOQPTH_PTR paoqPth);
int     pthLockSem(pthread_mutex_t *pmutex,int waitMs);
#endif
