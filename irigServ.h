/*
 *	include file for irigServ. the message format is defined here
*/
#ifndef INCirigServh
#define INCirigServh

/*	defines			*/

#define IRIGSERV_PORT 		801
#define IRIGSERV_CPU  		"pnt"
/* beware if you change the dot notation, chage the non dot address to
 * note that BIN address is in host order
*/

#define IRIGSERV_IPADR_BIN   0xc0a0ae03
#define IRIGSERV_IPADR_DOT  "192.160.174.3"

/*	typedefs		*/

typedef struct {
	int    userNum;     /* client fills in, we echo..*/
    int    istat;       /* OK, or errnum*/
	int    year;        /* 4 digits*/
	int    dayNum;      /* daynumber of year. count from 1*/
	int    secMidnite;  /* seconds from midnite*/
	int    usecs;       /* usecs from last second*/
    } IRIGSERV_MSG;

#endif  /* irigServh */
