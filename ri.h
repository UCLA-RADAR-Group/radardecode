/*
 *	include file for ri 
 * history:
 * 8oct93 - changed fifo len words to 32768
*/
#ifndef INCrih
#define INCrih
#include	"aoErrNum.h"
/*
 *	ioctl requests
 *   why does 0x12 not make it into the driver??. changed to 0x13
*/
#define RIIOCWAITINT		0x5
#define RIIOCSTAT		0x6
#define RIIOCDEBUG              0xa
#define RIIOCENAINT             0xb 
#define RIIOCRESET              0xf
#define RIIOCLDADR              0x10
#define RIIOCLDWC               0x11
#define RIIOCSNDCMD             0x13
#define RIIOCSFW                0x14
#define RIIOCLDMUX              0x15
#define RIIOCRDMUX              0x16
#define RIIOCRDAUXSTAT          0x17
#define RIIOCLDGWLEN            0x18
#define RIIOCLDSEQLEN           0x19
#define RIIOCLDSMPCONFIG        0x1a
#define RIIOCSERLOOPBACK        0x1b
#define RIIOCGETSAMPCONFIG      0x1c
#define RIIOCFIFOFORREAD        0x1d
#define RIIOCBLTFORREAD         0x1e
#define RIIOCSTATATINT          0x1f
#define RIIOCGETCONFIG          0x20
#define RIIOCLDADRWC            0x21
#define RIIOCLDCONFIG           0x22
/*
 *	Address in vp1 board.. duplicates due to read/write...
*/
#define RI_A32_ADR_REG 		0
#define RI_A32_RD_STAT_REG      0
#define RI_A32_WC_REG		4
#define RI_A32_CMD_REG		8
#define RI_A32_SW_FIFO_REG    0xc
/* 
 * commands
*/
#define RI_CMD_BITS_MASK     0xff
#define RI_CMD_CLEAR   	     0x01
#define RI_CMD_START_SINGLE  0x02
#define RI_CMD_START_BLT     0x04
#define RI_CMD_DISA_XFERS    0X06
#define RI_CMD_ENA_FIFO1     0x08
#define RI_CMD_ENA_FIFO2     0x10
#define RI_CMD_ENA_FIFO12    0x18
#define RI_CMD_DISA_TEST     0x20
#define RI_CMD_ENA_TEST      0x40     
#define RI_CMD_CLR_IPPFLG    0x80     
/*
 *	status bits ri from vp1 board
*/
#define	RI_STAT_FIFO_EMPTY    0x80000000
#define	RI_STAT_FIFO_OVERFLOW 0x40000000
#define	RI_STAT_FIFO_HFULL    0x20000000
#define	RI_STAT_GWCNT_ERR     0x10000000
#define	RI_STAT_SAMPLING_ENA  0x08000000
#define	RI_STAT_RI_RCVR_PE    0x04000000
#define	RI_STAT_CLEAR_ENA     0x02000000
#define	RI_STAT_IPP_FLAG      0x01000000
#define RI_STAT_WC 	      0x00ffffff
/*
 *	auxilliary status bits ri from serial line
*/
#define	RI_AUXSTAT_PE_RCVR       0x00002000
#define	RI_AUXSTAT_P15V_BAD      0x00001000
#define	RI_AUXSTAT_M15V_BAD      0x00000800
#define	RI_AUXSTAT_P5VLIN_BAD    0x00000400
#define	RI_AUXSTAT_M5VLIN_BAD    0x00000200
#define	RI_AUXSTAT_P5VSW_BAD     0x00000100
/* 
 *	opcodes for serial line 
*/
#define RI_SOPC_SMPCONFIG    0x00000000
#define RI_SOPC_LDMUX        0x00200000
#define RI_SOPC_LDGW_LSB     0x00400000
#define RI_SOPC_LDGW_MSB     0x00600000
#define RI_SOPC_LDSEQLEN     0x00800000
#define RI_SOPC_RDAUXSTAT    0x00a00000
#define RI_SOPC_CLRPE        0x00c00000
/*
 *	macros to fill in bits in serial command words
*/
#define RI_LDMUX_ADR(adr)       (((adr) & 0x1fff) << 8 )
#define RI_LDMUX_DATA(data)     ( (data) & 0xff) 
#define RI_AUXSTAT_LOOPBACK     0x00080000
#define RI_AUXSTAT_RDAUXSTAT    0x00000000
#define RI_AUXSTAT_MUXADR(adr)  (adr & 0x1fff)
#define RI_SC_EXTTIME(val)      ((val == 0) ? 0 : (1<<19))
#define RI_SC_SAMPLEMODE(val)   ((val & 3 ) << 17)
#define RI_SC_FFTEST(val)       ((val & 3 ) << 15)
#define RI_SC_PACKING(val)      ((val & 7 ) << 12)
#define RI_SC_SUBCYCLE(val)     ((val == 0) ? 0 : (1<<11))
#define RI_SC_GWCNT(val)        ((val == 0) ? 0 : (1<<10))
#define RI_SC_MUXTSTCHAN(val)   ((val & 7 ) << 7)
#define RI_SC_ENA_SINEWAVE(val) ((val == 0) ? 0 : (1<<6 ))
/*
 *	constants        
*/
/*
 *	sampler config
*/
#define RI_SCV_SAMPLEMODE_DISABLE      0x0
#define RI_SCV_SAMPLEMODE_ARMIPP       0x1
#define RI_SCV_SAMPLEMODE_ARMIMD       0x2
#define RI_SCV_SAMPLEMODE_SOFTGW       0x3
#define RI_SCV_FORMATTER_STAIRTST      0x0
#define RI_SCV_FORMATTER_TOGGLETST     0x1
#define RI_SCV_FORMATTER_NORMAL        0x2
#define RI_SCV_FORMATTER_ZEROTST       0x3
#define RI_SCV_PACKING_12              0x0
#define RI_SCV_PACKING_8               0x1
#define RI_SCV_PACKING_4               0x2
#define RI_SCV_PACKING_2               0x3
#define RI_SCV_PACKING_1               0x7
/*
 *	other
*/
#if FALSE
commented out 26may93. pjp. i thing they are not used
#define	RIPORT_HP	 0
#define RIPORT_RTG      1
#define RIPORT_RMUX     2
#define RIPORT_LOOPBACK 7
#endif
#define	RIDEVNAME "/ri"
#define RI_FIFO_LEN_WDS  32768
#define RI_MUXMEM_MAXLOC 8192 
#define RI_GWCNT_MAX 16777215
#define RI_SEQLEN_MAX 65535
/*	max mux locations ri_config can hold	*/
#define RI_MUXCF_MAXDATA	8
/*	seqlen min = 1 for mux, 2 for cycle mode	*/
#define RI_SEQLEN_MIN    1
/*
 *      structure for interrupt info
*/
typedef struct {
        int     late;           /* for interupt*/
        int     timeout;        /* for wait in ticks*/
        int     intcount;
	int     statAtInt;	/* status at last interrupt*/
        }  RI_INTINFO;
/*
 *	send/receive structure .
*/
typedef struct {
	int	port; 	         	/* port 0-7*/
	int	wordsout;		/* when doing output*/
	int	*pdataout;		/* data out ptr*/
	int	inpcmd; 		/* command for input*/
	int	*pdatain;		/* if receiving, put here*/
	} RI_SENDRCV;
/*
 *	sampler config structure
*/
typedef struct {
    	int extTiming;       /* gw pulses rtg/external false/true*/
    	char csmpMode[8];    /*0"dis"
                               1"ipp", arm,    enabled on next ipp
                               2"imm enable, start immediately after clr*
                               3"soft", soft gw*/
    	char cformMode[8];   /*  "stair" case test
                                "toggle"  test
                                "normal" sampling from a/d
                                "zero"   test*/
     	int packing;         /*0 12 bit sign ext to 16 bits
                                  1 8 bit 
				  2 4 bit 
				  3 2 bit 
				  7 1 bit */ 
	int subCycleOn;     /*0 disable subcycle mode 
			       1 enable subcycle mode */ 
	int gwCountOn ;      /*0 disable gw counting 
			       1 enable gw counting*/
    	int muxSWChan;	     /*0-7 mux port for sine wave test*/
        int enableMuxSW;     /*0 disable sine wave test
                               1 enable sine wave test*/
	int scCoded;		/* coded sampler config (loaded by driver)*/
	} RI_SC;	
/*
 *	RI_MUXCF will hold a max of 8 mux locations. It is included in 
 *	RI_CONFIG. This lets you load up to the first 8 locations in mux
 *	when RI_CONFIG is sent. If you need to load more locations, set
 *	numToUpdate to 0, and then load the mux separately via one of the
 *	supplied routines.
*/
typedef	struct {
	int	numAdr;	 	/* number in following list to load into mux*/
	int 	data[RI_MUXCF_MAXDATA];/* for mux loc 0-maxsize-1*/
	} RI_MUXCF;
/*
 *	RI_CONFIG struct
*/
typedef struct {
	RI_SC  sc;		/* sampler config*/
	unsigned int gwCount;	/* gatewidth count if used*/
	int    seqLen;		/* for mux and cycle mode*/
	int      fifoForRead;	/* if read used, fifo ...*/
	int      bltForRead;	/* read ioctl ... true, false*/
	RI_MUXCF mux;
	} RI_CONFIG;
	

#endif	/* INCridrvh*/
