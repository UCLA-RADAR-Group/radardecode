/*
 *	include phil for -l phil on aosun
 *  06nov06 - changed dcd.h -> dcdGl.h   Gl.h has the global defs
 *            that are needed for offline routines. Do not have to worry
 *            about all of the vxworks stuff in dcd.h
*/
#ifndef INCtapeLibh
#define INCtapeLibh

#include  <phlibExtras.h>
/*
 * tape 
*/
int     mt_bsf(int tapefd,int numfiles);
int     mt_bsr(int tapefd,int numrecs);
int     mt_fsf(int tapefd,int numfiles);
int     mt_fsr(int tapefd,int numrecs);
int 	mt_read(int tapefd,char *bufptr,int  numbytes);
int     mt_rew(int tapefd);
int 	mt_stat(int tapefd);
int     mt_statll(int tapefd,int *type,int *dsreg,int *errreg,int *rescnt);
int     mt_weof(int tapefd,int numfilemarks);
#endif  /* INCtapeLib */


