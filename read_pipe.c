#include	<stdio.h>
#include	<unistd.h>
#define	STDINP     0
/******************************************************************************/
/*      read from a pipe              			 		      */
/******************************************************************************/
int	read_pipe(char	*bufadr,int numbytes)
{
/*
 *	read numbytes from stdinput. This routine will loop on the 
 * 	read until the requested byte count is completed, or eof is 
 *	returned. 
 *	The number of bytes actually read will be returned
*/
	int bytesread;				/* left to read*/
	int bytesleft;				/* left to read*/
	char *bufadrl;

             bytesleft = numbytes;
	     bufadrl = bufadr;
	     while (bytesleft > 0) {
	 	bytesread=read(STDINP,bufadrl,bytesleft);
	        bufadrl+=bytesread;			/* next spot in buf*/
	        if (bytesread > 0){
               	    bytesleft = bytesleft - bytesread;
		}
		else if (bytesread == 0 ) {
		    return (numbytes - bytesleft);	
		}
	        else {
	            perror("read_pipe:");
	            return(-1);
	        }
	      }
	      return(numbytes);
}
