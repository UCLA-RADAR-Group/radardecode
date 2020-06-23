/*
 * hdrProc.h holds the header info set by tcl procedure..
*/
#ifndef INChdrProch
#define INChdrProch

#define HDRAO_PROC_GET(phdr)  ( \
         (HDRAO_PROC*) ( \
              ((char*)(phdr)) + \
              HDR_S_GET_OFF(((HDRAO_STD *)(phdr))->sec.misc)\
             ))


#define HDRAO_PROC_ID      "proc"
#define HDRAO_PROC_CUR_VER " 1.0"


typedef struct {
	char	id[4];		/* proc not null terminated*/
	char	ver[4];		/* version xx.0 not null terminated*/
	char	procName[12];		/* procedure name. not  null terminated*/
	char    procVer[4];			/* version not null terminated*/
	char	srcName[16];		/* source name*/
	double  dar[10]; 
	int		iar[10];
	char    car[10][8];
    } HDRAO_PROC; /*2*4 + 12+4+16+ 10*8 + 10*4+10*8==240 bytes*/

void    hdrPrProc(FILE *fptr,void *phdr);

#endif  /*INChdrProch */
