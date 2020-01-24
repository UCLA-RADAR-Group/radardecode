/* 
 *	global include file for dcd 
 *  these things are independant of vxWorks.
 *  The normal dcd.h will include this file
 *  other linux/sun routines can just include this file if theay
 *  donot want all the online junk
 *
 *06nov06 - created
*/
#ifndef INCdcdGlh
#define INCdcdGlh

/*
 *  correlation product configurations
 *  note that CODE is the bottom 2 bits of the ram
 *  note that _POL sends same config as complex to correlator. 
 *       but processing programs hanle it differently.
*/
#define DCD_PROD_9X9_I         0
#define DCD_PROD_9X9_Q         1
#define DCD_PROD_9X3_IQ_CODE   2
#define DCD_PROD_3X3_RAM       3
#define DCD_PROD_3X3_CMPLX     4
#define DCD_PROD_3X3_IQ        5
#define DCD_PROD_3X3_INTLV_I   6
#define DCD_PROD_3X3_INTLV_Q   7
#define DCD_PROD_3X3_INTLV_IQ  8
#define DCD_PROD_9X9_IQ        9
#define DCD_PROD_3X3_POL      10
#define DCD_PROD_LAST         10

/*
 *	lag config structure. tell what each lag config can do
 *      In,Out difference is:
 *	 for 9 level you may have 4*2048 to work with but
 *	                          1*2048 after combination
*/
typedef	struct	{
	int	numSbcIn;	/* available this config	*/
	int	numSbcOut;	/* after processing	*/
	int	lagSbcInMax;	/* max lags/sbc input*/
	int	lagSbcOutMax;	/* max lags/sbc out after processing*/
	int	level;		/* 3,9*/
	int	decode;		/* decoder config*/	
	int	pol;		/* polarazation config*/
	int	ram;		/* uses ram both inputs*/
	int	intlv;		/* interleaved data*/
	int	complex;	/* complex sampled*/
	} DCD_CFINFO;
#endif	/* INCdcdGlh*/
