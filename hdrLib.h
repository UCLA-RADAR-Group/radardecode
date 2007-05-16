/* hdrLib.h - include file for headers 					*/
/* %W%		%G%
modification history:
--------------------- 
current length: 3nov94: 32words or 128bytes
delta   program version
	version 1.1...currently set via .exe tcl script.
1.1  4jun94 added header sections.
        include file for datataking headers
1.2  19jun94	outstanding
     15sep94    V1.2.. added grpNum,grpRecTot,grpCurRec
		version number now set from #define in this header
	        removed version from hdrSetStdFixed, hdrStdInit
	        added dataType...
     24nov94    changed spare location before sec to stScanTime
	        it is the seconds from midnite when the scan was started.
		The other date/time refers two the time that the read for
		that records data completed.
     02feb95    Version 2.0
		output order for sections in headers switched to:
	        std
		inp
		proc
		time
	        misc
		pnt
	        out
		This caused a switch in rawDat since it had time/inp order.
		The HDRAO_SEC structure stays the same.
               -  changed version format from Vx.x to xx.x to correspond to
	        version formats. Was V1.2. now version  2.0.
 	21jul97 .. added az,za,tmstamp for end of record.
	08jan98 .. added azCor,zaCor in milliarcs secs little circle
			   this is the offset adde to computed position by
			   model and encoder tables
	27nov98 .. removed azCor,zaCor since they werenot being loaded 
2.1 24jun99 sec.out --> sec.iflo .. added HDR_S_TYPE_IND_IFLO
 *         i don't think that sec.out was ever used..
	14jan00 testing.
*/
/*
DESCRIPTION
The data taking header is prepended to each data record. It consists of a
Standard part followed by optional sections. The standard part will be contained
in all headers. The sections will be optionally included depending on the
program that is being run. The standard part allows for up to 5 sections.
They are:

inp	- header used by input program eg. riProg
out     - header used by output program eg. tpProg
proc    - header used by processing of data eg. apProg
time    - header used by timing information. spsProg, rtgProg.
misc    - header used by program dependant portion.

The HDR_SECT struct contains an entry for each of these sections. Each 
element in this structure is coded as:

8bits   program code   (most significant bits)
12bits  offset section from start of std header in bytes.
12bits  length of section in bytes.

If a section is not used, it will contain zeros.
*/
#ifndef INChdrLibh
#define INChdrLibh
#ifdef	VXWORKS
#include	<vxWorks.h>
#else
#include	<vxWorksEm.h>
#endif
#include	<string.h>
#include	<stdio.h>

/*	defines		*/
/* for hdr_std_version.. you need to recompile the routines in hdr/std
 * and then recompile riProg, etc... the hdrAoVw should probably be a load
 * module which would save 1 set of recompiles.
*/
#define HDR_MARKER "hdr_"
#define HDR_STD_VERSION " 2.1"
#define HDR_MAX_LEN  4096
#define HDR_MAX_SEC  6    


#define HDR_S_OFF_MASK   0x00fff000
#define HDR_S_LEN_MASK   0x00000fff
#define HDR_S_CODE_MASK  0xff000000

#define	HDR_S_SET_CODE(a)  ( (a) & HDR_S_CODE_MASK )
#define	HDR_S_SET_OFF(off)  ( ((off) << 12) & HDR_S_OFF_MASK )	
#define	HDR_S_SET_LEN(len)  ( (len)  & HDR_S_LEN_MASK )	
#define	HDR_S_GET_CODE(a)  ( (a) & HDR_S_CODE_MASK )
#define	HDR_S_GET_OFF(s)  ( ((s) >> 12) & 0xfff )	
#define	HDR_S_GET_LEN(s)  (  (s)  & 0xfff )	
#define HDR_S_MAKE(code,off,len) ( HDR_S_SET_CODE(code) | HDR_S_SET_OFF(off) | HDR_S_SET_LEN(len) )

/*
 *	codes for all known programs
*/
#define HDR_S_RI    ( 0x01000000 )
#define HDR_S_TAPE  ( 0x02000000 )
#define HDR_S_SPSBG ( 0x03000000 )
#define HDR_S_PWR   ( 0x04000000 )
#define HDR_S_CLP   ( 0x05000000 )
#define HDR_S_MRACF ( 0x06000000 )
#define HDR_S_TIME  ( 0x07000000 )
#define HDR_S_COR   ( 0x08000000 )
#define HDR_S_PT    ( 0x09000000 )
#define HDR_S_IFLO  ( 0x0a000000 )
#define HDR_S_PNT   ( 0x0b000000 )
#define HDR_S_DOP   ( 0x0c000000 )
#define HDR_S_PROC  ( 0x0d000000 )
/*
 *	offsets into header section for the 6 types
 * note that iflo in place of out.
*/
#define	 HDR_S_TYPE_IND_INP	0
#define	 HDR_S_TYPE_IND_OUT	1
#define	 HDR_S_TYPE_IND_IFLO	1
#define	 HDR_S_TYPE_IND_PROC	2
#define	 HDR_S_TYPE_IND_TIME    3
#define	 HDR_S_TYPE_IND_PNT     4 
#define	 HDR_S_TYPE_IND_MISCINP	5
/*
 * data types codes for dataType location in header
 *      UNS --> unsigned,M->mixed up..p--> packed.. ints/floats  are 32 bits...
 *      packed all ri data will be packed even though it has 16 or 8 bits.
*/
#define  HDR_DATATYPE_BYTE      "b  "
#define  HDR_DATATYPE_BYTE_UNS  "bu "
#define  HDR_DATATYPE_SHORT     "s  "
#define  HDR_DATATYPE_SHORT_UNS "su "
#define  HDR_DATATYPE_INT	"i  "
#define  HDR_DATATYPE_INT_UNS	"iu "
#define  HDR_DATATYPE_FLOAT     "f  "
#define  HDR_DATATYPE_DOUBLE    "d  "
#define  HDR_DATATYPE_MIXED     "m  "
#define  HDR_DATATYPE_PACKED    "p  "
/*
 *	test that it is a header
*/
#define  HDRAO_IS_HDR(phdr) ( strncmp((char*)(phdr),HDR_MARKER,4)==0)
/*
 *	header sections
 *	note keep it a multiple of 8 bytes just in case..
*/
typedef struct {
	int	inp;		/* input prog header info (ri, etc)*/
#if FALSE
	int	out;		/* output prog header info(tape, etc)*/
#endif
	int	iflo;		/* if/lo */
	int	proc;		/* processing prog header info (ap etc)*/
	int	time;		/* timing prog header info (sps,rtg etc)*/
	int	pnt;		/* pointing header info*/
	int	misc;		/* misc prog header info (program dep)*/
	} HDRAO_SEC;
/*
	standard section entries:

sec.inp:
	HDR_S_RI    
	HDR_S_COR   
	HDR_S_PT     not used
sec.iflo:
	HDR_S_IFLO  
	HDR_S_TAPE   (not used) 
sec.proc
	HDR_S_PWR   	 aeronomy
	HDR_S_CLP   
	HDR_S_MRACF 

	HDR_S_DOP        astronomy.. requested freq
sec.time
	HDR_S_SPSBG 	 aeronomy sbs buffer
sec.pnt 
	HDR_S_PNT   
sec.misc
	HDR_S_PROC    loaded via procedure  with hdrld procedures.
*/

/*
 *	default header for data taking programs
 *
 *	program up into the following parts
 *	 
 *	1. program independant header info
 *	2. program dependant header info
 *  10/1/94 current size 32 words=128 bytes
*/
typedef struct {
	char    hdrMarker[4]; 	/* holds the 4 characters "HDR_"    [ 0]*/
	int	hdrlen;		/* bytes in header	                        [ 1]*/
	int	reclen;		/* hdr + data in bytes 				        [ 2]*/
	char	id[8];		/* not null terminated like sp2048 		[ 3-4]*/
	char	version[4]; 	/* program version  like v2.1  		[ 5]*/
	int	date;		/* yyyyddd rec end time						[ 6]*/
 	int time;		/* seconds since midnite rec end time       [ 7]*/
	int	expNumber;/* to identify experiment                     [ 8]*/
	int	scanNumber;	/* to identify this part of data ydddxxxxx  [ 9]*/
	int	recNumber;  /* should increase linearly in each scan    [10]*/
	int     stScanTime; /* sec from midnite when scan started   [11]*/
	HDRAO_SEC sec;		/* header sections included				[12-17]*/
	int	free14;	    /* unused location							[18]*/
	int	free13;	    /* unused location							[19]*/
	int	free12;	    /* unused location							[20]*/
	int	free11;	    /* unused location used by gioProg			[21]*/
	int	grpNum;	    /* group number within scan 				[22]*/
	int	grpTotRecs; /* records in a group (expected)			[23]*/
	int	grpCurRec;  /* current record of group (start at 1)		[24]*/
	char    dataType[4];/* type of data.. seed DATA_TYPE codes above[25]*/
	int	azTTD;	    /* az position end rec. 1/10000 degrees		[26]*/
	int	grTTD;	    /* gr position end rec. 1/10000 degrees		[27]*/
	int	chTTD;	    /* za position end rec. 1/10000 degrees		[28]*/
	int	posTmMs;    /* time stamp position millisecs			[29]*/
	int	free2;      /*                                          [30]*/
	int	free1;	    /*                                          [31]*/
#if FALSE
	int	azCor;      /* model/enc cor. milliarcsecs little circle[30]*/
	int	zaCor;	    /* model/enc cor. milliarcsecs              [31]*/
#endif
	}	HDRAO_STD;

#define	HDRAO_STD_LEN  sizeof(HDRAO_STD)
/*
 *      prototypes for routines to access the header
*/

int     hdrGDate(HDRAO_STD *phdr);	
int     hdrGHdrLen(HDRAO_STD *phdr);
void    hdrGHdrVer(HDRAO_STD *phdr,char *version);
int     hdrGRecLen(HDRAO_STD *phdr);
int     hdrGRecNum(HDRAO_STD *phdr);
int     hdrGScan(HDRAO_STD *phdr);
int     hdrGTime(HDRAO_STD *phdr);
STATUS	hdrIsHdr(char *phdr);
void    hdrPrAll(FILE *fptr,HDRAO_STD *phdr);
void    hdrPrStd(FILE *fptr,HDRAO_STD *phdr);
/*
 *	VXWORKS routines to set locations in the header
 *	these routines should only be called from vxWorks
*/

void    hdrCopy(HDRAO_STD *hdrFrom,HDRAO_STD *hdrTo);
int     hdrNewScan(void);
int     hdrSetDate(HDRAO_STD *phdr);
void    hdrSetHdrLen(HDRAO_STD *phdr,int hdrlen);
void    hdrSetRec(HDRAO_STD *phdr,int RecNum);
void    hdrSetScan(HDRAO_STD *phdr,int scanNum);
int     hdrSetScanTm(HDRAO_STD *phdr);
int     hdrSetSecs(HDRAO_STD *phdr);
void    hdrSetStdFixed(HDRAO_STD *phdr,int hdrlen,int datalen,char *id,
                int  experiment_number);
STATUS  hdrStdInit(HDRAO_STD *phdr,char *id,HDRAO_SEC *psecs);
void    hdrStdToD(HDRAO_STD *phdr,double *pdata);
void    hdrDToStd(double *pdata,HDRAO_STD *phdr);
#endif /*INChdrLibh*/
