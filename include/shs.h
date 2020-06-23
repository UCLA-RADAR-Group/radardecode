/* 
 *	include file for shs radar header
 *  the ascii header gets  unpacked into these
 *  structures by some of the shs routines.
*/
#ifndef INCshsH
#define INCshsH

// 16 bytes then x=xvaluelen
#define SHS_HDR_KEY_LEN 16
#define SHS_HDR_VAL_LEN 16

// value starts col 19 (count from 0)
#define SHS_HDR_VAL_COLST 19

// each table has 2 96 byte \n terminates lines at end of table
#define SHS_TABLE_SLOP_END 192
/*
 *primary header
 * note strings are null terminated.
*/

typedef struct {

	int		littleEndian;  /* 1 true, 0 false*/
	char    configFile[SHS_HDR_VAL_LEN+1]; 
	char    observer[SHS_HDR_VAL_LEN+1]; 
	char    object[SHS_HDR_VAL_LEN+1]; // what is being observerd 
	char    telescope[SHS_HDR_VAL_LEN+1];// 'ARECIBO'
	char    instrument[SHS_HDR_VAL_LEN+1];// 'ARECIBO'
	char    bwmode[SHS_HDR_VAL_LEN+1]; // 'WIDEBAND'
	int     nchan;                     // number channels used 1,2
	char    colmode[SHS_HDR_VAL_LEN+1];// 'BURST MODE'
	char    gatesrc[SHS_HDR_VAL_LEN+1];// 'EXTERNAL'
	char    gateplr[SHS_HDR_VAL_LEN+1];// 'POSITIVE'
	int     burstcounter;              // 
	int     delaycount;                // 
	char    sync[SHS_HDR_VAL_LEN+1];   // 'COHERENT-SIA'
	char    dataformat[SHS_HDR_VAL_LEN+1]; // '16 BIT COMPLEX'
	double  clockrate;                  // freq in Mhz
	int     decimation;                 // 
	double  sampleTmUsec;			   // sample time in usecs 1/outputrate
	double  nco1;					   // freq in Mhz
	double  nco2;					   // freq in Mhz
	double  nco3;					   // freq in Mhz
	double  nco4;					   // freq in Mhz
	int     ipp;                       // in millsecs
	char    resampler[SHS_HDR_VAL_LEN+1]; // 'OFF'
	char    txmode[SHS_HDR_VAL_LEN+1]; // 'CLP'
	} SHS_PHEADER;

/*
 * data header
*/
typedef struct {
	int 	tablenum;	// table number in current file. count from 0
	int 	tablesize;	// table size in units of datawidth(short=2)
	int 	datawidth;	// datetype width in bytes
	char    datatype[SHS_HDR_VAL_LEN+1]; // short 
	int 	numdims;	// number of dimensions for table
	int 	dim0;	    // length first dimension (units datatype) (1ipp)
	int 	dim1;	    // 2nd dimension (number of ipps)
	int 	nchan;	    // number of channels
//        warning below "samples" are units of shorts
//        there are two of these for a single complex number for a time sample
	int 	txStart;	// txStart units of datatype (2 datatype for 1 complex num)
	int 	txSize ;	// number of datatype tx samples
	int 	dataStart;	// dataStart. units of datatype (2 datatype for 1 complex num)
	int 	dataSize ;	// number of datatype  data samples
	int 	noiseStart;	// noiseStart. units of datatype (2 datatype for 1 complex num)
	int 	noiseSize ;	// number of datatype  noise samples
	int 	year      ;	// year
	int 	daynum    ;	// daynum
	int 	secMid    ;	// seconds from AST MIDNITE this block
	float 	azimuth   ;	// in degrees
	float 	gregpos   ;	// gregorian position deg
	float 	chpos     ;	// ch position deg
	} SHS_DHEADER;

#endif	/* INCshsH*/
