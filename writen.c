#ifdef VXWORKS
#include	<vxWorks.h>
#include	<ioLib.h>
#else
#include	<vxWorksEm.h>
#include	<unistd.h>
#endif 
#include	<tarLib.h>
/******************************************************************************/
/*      write to a pipe or socket n bytes 			 	      */
/******************************************************************************/
int	writen(int fd,char *bufadr,int numbytes)
{
/*
 *	write numbytes to fd or socket
 * 	write until the requested byte count is completed.
 *	if eof on a write, return 0
 *	if error on a write return neg num
*/
	int byteswritten;		 	/* written*/
	int bytesleft;				/* left to write*/

             bytesleft = numbytes;
	     while (bytesleft > 0) {
	 	byteswritten=write(fd,bufadr,(unsigned int)bytesleft);
	        if (byteswritten<=0)
               	    return(byteswritten);
		bufadr+=byteswritten;
		bytesleft-=byteswritten;
	     }
	     return(numbytes-bytesleft);
}
