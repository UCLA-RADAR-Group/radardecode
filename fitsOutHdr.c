#include	<stdio.h>
#include	<unistd.h>
#define OK 0
#define ERROR -1  
/*
 *	output fits header
 *	if ok, return 0
 *	if error return -1
*/

int	fitsOutHdr(
		int usefptr,	/* if true use fptr, else use fd*/
		FILE *fptr,	/* if non NULL output to file ptr*/
		int fd,		/* file descriptor*/
		char *datatype,	/* "i","s",16,32 bits/pixel on output*/
	 	int naxis,	/* of dimensions 1 or 2*/
		int numCols,	/* number of columns naxis 1*/
		int numRows,	/* number of rows naxis 2*/
		int naxis3 ,	/* number deep*/
		double bscale,	/* to scale*/
		double bzero)
{
	 char     hdr[2881],*phdr,*ptmp; /* + 1 for null!!*/
	 int 	bytesout;
	 int    bitsperpixel;

/*
 *      now output the header...
*/
	switch(datatype[0]){
	    case 's':
	    case 'S':
	       bitsperpixel=16;
	       break;
	    case 'i':
	    case 'I':
	       bitsperpixel=32;
	       break;
	    default:
	       fprintf(stderr,
			"fitsOutHdr:illegal data type:%c.legal value:s,i\n",datatype[0]);
	       return(ERROR);
	}
        phdr=hdr;
        ptmp="SIMPLE  =                    T /";
        sprintf(phdr,"%-80s",ptmp);
        phdr+=80;

        ptmp="BITPIX  =                   ";
        sprintf(phdr,"%-28s%2d /%-48s",ptmp,bitsperpixel," ");
        phdr+=80;

        ptmp="NAXIS   =                    ";
        sprintf(phdr,"%-29s%1d /%-48s",ptmp,naxis," ");
        phdr+=80;

        ptmp="NAXIS1  =                ";
        sprintf(phdr,"%-25s%5d /%-48s",ptmp,numCols," ");
        phdr+=80;

        ptmp="NAXIS2  =                ";
        sprintf(phdr,"%-25s%5d /%-48s",ptmp,numRows," ");
        phdr+=80;

	if (naxis > 2) {
          ptmp="NAXIS3  =                ";
          sprintf(phdr,"%-25s%5d /%-48s",ptmp,naxis3," ");
          phdr+=80;
	}
        ptmp="BSCALE  = ";
        sprintf(phdr,"%-10s%20.13e /%-48s",ptmp,bscale," ");
        phdr+=80;
 
        ptmp="BZERO   = ";
        sprintf(phdr,"%-10s%20.13e /%-48s",ptmp,bzero," ");
        phdr+=80;
 
        ptmp="END";
        sprintf(phdr,"%-80s",ptmp);
        phdr+=80;
        for (;phdr < hdr+2880;phdr+=80){
            sprintf(phdr,"%80s"," ");
        }
	if (!usefptr) {
           bytesout=write(fd,hdr,2880);
           if (bytesout != 2880) {
             fprintf(stderr,"Error outputing hdr. bytes req:%d written %d\n",
              		2880,bytesout);
             perror("writing fits hdr");
             return(ERROR);
	   }
        }
	else {			/* use file descriptor*/
           bytesout=fwrite(hdr,sizeof(char),2880,fptr);
           if (bytesout != 2880) {
             fprintf(stderr,"Error outputing hdr. bytes req:%d written %d\n",
             2880,bytesout);
             perror("writing fits hdr");
             return(ERROR);
	   }
        }
	return(OK);
}
