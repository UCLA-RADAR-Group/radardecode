#ifndef INCipich
#define INCipich
#include	<stdio.h>
#ifdef VXWORKS 
#include	<semLib.h>
#else
#include	<vxWorksEm.h>
#endif

#if !defined(CAST)
#define	CAST	(volatile char *)
#endif
#define	CASTSH	(volatile unsigned short *)
#if !defined(CAST)
#define	CASTINT (volatile int *)
#endif

#define IP_CTRL_BASE 		0xfffbc000
#define IP_A_LBUS_START         0xffc00000
#define IP_B_LBUS_START         0xffc10000
#define IP_C_LBUS_START         0xffc20000
#define IP_D_LBUS_START         0xffc30000

/* 	codes that my programs use */

#define	IP_IDSPACE		1
#define	IP_IOSPACE		2
#define	IP_MEMSPACE		3

#define	IP_CTRL_ADRS(reg)	( CAST   (IP_CTRL_BASE + reg))
#define	IP_CTRL_ADRS2(reg)	( CASTSH (IP_CTRL_BASE + reg))
#define	IP_CTRL_ADRS4(reg)	( CASTINT(IP_CTRL_BASE + reg))
#define	IP_CTRL_DMA_BASE(reg)	((volatile IP_DMA_CTRL *)(IP_CTRL_BASE + reg))

/*
 *	include file for industry pack  addresses on mv162
*/
#define	IP_A_IOSPACE_START	0xfff58000
#define	IP_A_IDSPACE_START	0xfff58080

#define	IP_B_IOSPACE_START	0xfff58100
#define	IP_B_IDSPACE_START	0xfff58180

#define	IP_C_IOSPACE_START	0xfff58200
#define	IP_C_IDSPACE_START	0xfff58280

#define	IP_D_IOSPACE_START	0xfff58300
#define	IP_D_IDSPACE_START	0xfff58380

#define	IP_AB_IOSPACE_START	0xfff58400
#define	IP_CD_IOSPACE_START	0xfff58500
/*
 *	control register addresses
*/
#define IP_CTRL_CHIP_ID        	(IP_CTRL_ADRS(0x0))
#define IP_CTRL_CHIP_REV       	(IP_CTRL_ADRS(0x1))
#define IP_CTRL_DMA_VEC_BASE   	(IP_CTRL_ADRS(0x3))
  
#define IP_CTRL_A_MEMBASE      	(IP_CTRL_ADRS2(0x04))
#define IP_CTRL_A_MEMBASE_UPPER	(IP_CTRL_ADRS(0x04))
#define IP_CTRL_A_MEMBASE_LOWER	(IP_CTRL_ADRS(0x05))

#define IP_CTRL_B_MEMBASE      	(IP_CTRL_ADRS2(0x06))
#define IP_CTRL_B_MEMBASE_UPPER	(IP_CTRL_ADRS(0x06))
#define IP_CTRL_B_MEMBASE_LOWER	(IP_CTRL_ADRS(0x07)) 

#define IP_CTRL_C_MEMBASE      	(IP_CTRL_ADRS2(0x08))
#define IP_CTRL_C_MEMBASE_UPPER	(IP_CTRL_ADRS(0x08))
#define IP_CTRL_C_MEMBASE_LOWER	(IP_CTRL_ADRS(0x09))

#define IP_CTRL_D_MEMBASE      	(IP_CTRL_ADRS2(0x0a))
#define IP_CTRL_D_MEMBASE_UPPER	(IP_CTRL_ADRS(0x0a))
#define IP_CTRL_D_MEMBASE_LOWER	(IP_CTRL_ADRS(0x0b)) 

#define IP_CTRL_A_MEMSIZE	(IP_CTRL_ADRS(0x0c))
#define IP_CTRL_B_MEMSIZE	(IP_CTRL_ADRS(0x0d))
#define IP_CTRL_C_MEMSIZE	(IP_CTRL_ADRS(0x0e))
#define IP_CTRL_D_MEMSIZE	(IP_CTRL_ADRS(0x0f))
 
#define IP_CTRL_A_INT0_CTRL	(IP_CTRL_ADRS(0x10))
#define IP_CTRL_A_INT1_CTRL	(IP_CTRL_ADRS(0x11))
#define IP_CTRL_B_INT0_CTRL	(IP_CTRL_ADRS(0x12))
#define IP_CTRL_B_INT1_CTRL	(IP_CTRL_ADRS(0x13))
#define IP_CTRL_C_INT0_CTRL	(IP_CTRL_ADRS(0x14))
#define IP_CTRL_C_INT1_CTRL	(IP_CTRL_ADRS(0x15))
#define IP_CTRL_D_INT0_CTRL	(IP_CTRL_ADRS(0x16))
#define IP_CTRL_D_INT1_CTRL	(IP_CTRL_ADRS(0x17))
 
#define IP_CTRL_A_GEN_CTRL 	(IP_CTRL_ADRS(0x18))
#define IP_CTRL_B_GEN_CTRL 	(IP_CTRL_ADRS(0x19))
#define IP_CTRL_C_GEN_CTRL 	(IP_CTRL_ADRS(0x1a))
#define IP_CTRL_D_GEN_CTRL 	(IP_CTRL_ADRS(0x1b))
#define IP_CTRL_IP_CLOCK        (IP_CTRL_ADRS(0x1d))
#define IP_CTRL_DMA_ARB_CTRL    (IP_CTRL_ADRS(0x1e))
#define IP_CTRL_RESET      	(IP_CTRL_ADRS(0x1F))

#define IP_CTRL_DMA_ASTAT      	(IP_CTRL_ADRS(0x20))
#define IP_CTRL_DMA_BSTAT      	(IP_CTRL_ADRS(0x38))
#define IP_CTRL_DMA_CSTAT      	(IP_CTRL_ADRS(0x50))
#define IP_CTRL_DMA_DSTAT      	(IP_CTRL_ADRS(0x68))
#define IP_CTRL_DMA_A		(IP_CTRL_DMA_BASE(0x20))
#define IP_CTRL_DMA_B		(IP_CTRL_DMA_BASE(0x38))
#define IP_CTRL_DMA_C		(IP_CTRL_DMA_BASE(0x50))
#define IP_CTRL_DMA_D		(IP_CTRL_DMA_BASE(0x68))
 
#define IP_PACER_INT_CTRL	(IP_CTRL_ADRS(0x80))
#define IP_PACER_GEN_CTRL	(IP_CTRL_ADRS(0x81))
#define IP_PACER_TIMER  	(IP_CTRL_ADRS2(0x82))
/*
 *	some constants
*/ 
#define	IP_WIDTHCODE_8		(1 << 2)
#define	IP_WIDTHCODE_16		(2 << 2)
#define	IP_WIDTHCODE_32	        0

#define IP_BTD_ON		(2)
#define IP_BTD_OFF	        (0)

#define	IP_RECTIMECODE_0	0
#define	IP_RECTIMECODE_2	1
#define	IP_RECTIMECODE_4	2
#define	IP_RECTIMECODE_8	3

#define	IP_MEN                  1;
/*
 *	dma control reg constants
*/
/*	dma stat reg		*/

#define	IP_DMA_STAT_DONE	0x01
#define	IP_DMA_STAT_TIMEOUT_IP	0x02
#define	IP_DMA_STAT_CHN_RD_ERR  0x04
#define	IP_DMA_STAT_CHN_INT     0x08
#define	IP_DMA_STAT_DMAEND_IP   0x10
#define	IP_DMA_STAT_TIMEOUT_HOST 0x40

/*	interrupt control	*/

#define	IP_DMA_INT_CLR		0x08
#define	IP_DMA_INT_ENA		0x10

#define IP_DMA_ENABLE		0x01

/*	control reg 1	*/

#define IP_DMA_CTRL1_AC_CH1	0x02
#define IP_DMA_CTRL1_DIRECT	0x00
#define IP_DMA_CTRL1_CHN   	0x20
#define IP_DMA_CTRL1_CHNHALT	0x80

/*	control reg 2	*/


#define IP_DMA_CTRL2_READ  	 0x00
#define IP_DMA_CTRL2_WRITE 	 0x04
#define IP_DMA_CTRL2_ENA_TIMEOUT 0x08
#define IP_DMA_CTRL2_DRV_DMAEND  0x10
#define IP_DMA_CTRL2_RCV_DMAEND  0x20

/*
 *	 interrupt constants
*/	
#define IP_INTNUM_BASE          0xf0
#define IP_INTNUM_DMA_A		IP_INTNUM_BASE | 0 
#define IP_INTNUM_DMA_B		IP_INTNUM_BASE | 1
#define IP_INTNUM_DMA_C		IP_INTNUM_BASE | 2
#define IP_INTNUM_DMA_D		IP_INTNUM_BASE | 3
#define IP_INTNUM_PACER 	IP_INTNUM_BASE | 4
#define IP_INTLEV_DMA_A		0x3
#define IP_INTLEV_DMA_B		0x3
#define IP_INTLEV_DMA_C		0x3
#define IP_INTLEV_DMA_D		0x3
#define IP_INTLEV_PACER         0x3

/*
 *	interrupt MACROS
*/
#define IP_IRQ_CTRL_CLR		(1 << 3)
#define IP_IRQ_CTRL_ENA		(1 << 4)
#define IP_IRQ_CTRL_INT 	(1 << 5)
#define IP_IRQ_CTRL_EDGE	(1 << 6)

typedef struct {
	unsigned char	stat;		/* dma status*/
	unsigned char	intCtrl;	/* interrupt control*/
	unsigned char	enable;		/* enable dma*/
	unsigned char   rsvd1;		/* not used*/
	unsigned char   ctrlReg1;	/* control reg #1*/
	unsigned char   ctrlReg2;	/* control reg #2*/
	unsigned char   rsvd2;		/* not used*/
	unsigned char   rsvd3;		/* not used*/
	unsigned char	*locBusAdr;	/* to send/rcv data*/
	unsigned char	*ipBusAdr;	/* for ip. set to zero for std xfer*/
	int	        bytesToXfer;	/* byte count*/
	unsigned char   *tableChainAdr; /* for chaining*/
	} IP_DMA_CTRL;
/*
 *      dma info for each dma controller
 *      used by ipicLib and dcdLocProg...
*/
#ifdef 	VXWORKS
typedef struct {
        volatile IP_DMA_CTRL *pdmaBlk;    /* pnt to dma block in memory*/
        unsigned char intLvl;       /* level A interrupt*/
	    int           intNum;	    /* int num 00 to ff for vector */
        int      intCnt;                  /* interrupt count*/
        int      waitIntCnt;              /* wait interrupt count*/
        SEM_ID   intSem;                  /* interrupt semaphore*/
        int      statAtInt;             /* status at last interrupt*/
        unsigned char dmaCtrl1;         /* control reg 1 for dma*/
        unsigned char dmaCtrl2;         /* control reg 2 for dma*/
        } IP_DMA_INFO;
#endif

typedef	struct	{
	unsigned char	chipId;
	unsigned char	chipRev;
	unsigned char  dmaVecBase;	/* dma vector for iack upper 5 bits*/
	unsigned short ip_a_memBase;
	unsigned short ip_b_memBase;
	unsigned short ip_c_memBase;
	unsigned short ip_d_memBase;
	unsigned char  ip_a_size;
	unsigned char  ip_b_size;
	unsigned char  ip_c_size;
	unsigned char  ip_d_size;
	unsigned char  ip_a_int0;
	unsigned char  ip_a_int1;
	unsigned char  ip_b_int0;
	unsigned char  ip_b_int1;
	unsigned char  ip_c_int0;
	unsigned char  ip_c_int1;
	unsigned char  ip_d_int0;
	unsigned char  ip_d_int1;
	unsigned char  ip_a_gen;
	unsigned char  ip_b_gen;
	unsigned char  ip_c_gen;
	unsigned char  ip_d_gen;
	unsigned char  ip_clock;	/* 1--> 32mhz*/
	unsigned char  dmaArbCtrl;	/* dma arbitration control*/
	} IP_INFO;
/*
 *	structure to hold id prom info,
*/

typedef struct {
	char	nm[5];		/* null terminated*/
	int     manId;		/* manufactures id*/
	int     modelNum;	/* model number*/
	int     revision;	/* revision*/
	int 	rsvd;
	int 	drvId;
	int 	bytesUsed;
	int    crc;
	} IP_ID_PROM;
/*
 *   	protypes
*/

void   ip_getInfo(IP_INFO *pipInfo);
STATUS ip_init(char *ipDev1,int memSize1,int ipWidth1,int ipRecTime1,
	       char *ipDev2,int memSize2,int ipWidth2,int ipRecTime2);
STATUS ip_IdPromRd(char *ipdev,IP_ID_PROM *pprom);
void  ip_IdPromPr(FILE *fp,IP_ID_PROM *pidProm);
void  ip_prInfo(FILE *fp,IP_INFO *pipInfo);
void  ip_prDmaInfo(char *ipToUse,FILE *fp);
int   ip_rdIdSpace(int numbytes,int offsetBytes,char *devName,
                unsigned char  *inbuf);
int   ip_rdIoSpace(int numbytes,int offsetBytes,char *devName,int width,
                unsigned char *inbuf);
int   ip_rdMemSpace(int numbytes,int offsetBytes,char *devName,
                    unsigned char *inbuf);
void  ipReset(void);
int   ip_dmaRead(char   *ipToUse,int wordsToRead,int *pinpDat,int *pwordsRead);
int   ip_dcdDmaRead(char *ipToUse,volatile unsigned int *pdcdAdr,
		unsigned int dcdVal,int wordsToRead,int *pinpDat,
		int *pwordsRead);
int ip_dmaWrite(char *ipToUse,int wordsToWrite,int *poutDat,int timeout,
				volatile unsigned int *pstarCmdAdr,unsigned int starCmdData);

#ifdef	VXWORKS
IP_DMA_INFO *ip_retDmaI(char *ipInUse);
#endif

int   ip_waitDmaIntA(int timeOutTicks,int *statAtInt);
int   ip_waitDmaIntC(int timeOutTicks,int *statAtInt);
 

#endif /*INCipich*/

