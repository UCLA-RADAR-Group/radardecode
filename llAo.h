/*
 * doubly linked list lib. a la vxWorks
*/
#ifndef INC_LLAO
#define INC_LLAO

#ifndef NULL
#define NULL (void *)0 
#endif

//  empty for offset version 

#define LLSHM_EMPTY 0 
// wait is in millisecs
#define SHM_WAITSEC   1000
#define SHM_NOWAIT       0
#define SHM_WAITFOREVER -1
#define SHM_WAITMS       1

/* type definitions */

typedef struct llnode    /* Node of a linked list. */
    {
    struct llnode *next;      /* Points at the next node in the list */
    struct llnode *prev;      /* Points at the previous node in the list */
    } LL_NODE;


typedef struct          /* Header for a linked list. */
    {
    LL_NODE node;          /* Header list node */
	int	    count;			/* nodes in list*/
    } LL_LIST;

typedef struct     /* Node of a linked list. */
    {
    unsigned long shmnext;    /* offset shm for next node*/
    unsigned long shmprev;    /* offset shm for previous node*/
    } LLSHM_NODE;


typedef struct          /* Header for a linked list. */
    {
    LLSHM_NODE node;          /* Header list node */
    int     count;          /* nodes in list*/
    unsigned long llshmOffset;/* offset this struct start shm*/
    } LLSHM_LIST;


#define LLSHM_GETPSHM(plist)   (char *)((char*)(plist) - (plist->llshmOffset))

#define llCount(plist) (plist->count)

extern void      llAdd (LL_LIST *pList, LL_NODE *pNode);
extern LL_NODE*  llGet (LL_LIST *pList);
extern void      llInit (LL_LIST *pList);

extern void      llshmAdd (LLSHM_LIST *pList, LLSHM_NODE *pNode,int tohead);
extern LLSHM_NODE*  llshmGet (LLSHM_LIST *pList,int fromtail); 
extern int       llshmInit (LLSHM_LIST *pList,char *pshm);
LLSHM_NODE *llshmNext(LLSHM_LIST *plist,LLSHM_NODE *pnode);
/*
extern int      llCount (LIST *pList);
extern void     lstDelete (LIST *pList, NODE *pNode);
extern void     lstInsert (LIST *pList, NODE *pPrev, NODE *pNode);
*/
#endif
