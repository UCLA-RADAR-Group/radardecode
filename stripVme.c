#include        <stdio.h>
#include        <stdlib.h>
#include        <string.h>
#include        <memory.h>
#include        <hdrLib.h>
#ifdef LINUX
#include		<byteswap.h>
#define	         linux  1
#else
#define          linux 0 
int				bswap_32(int );
#endif
#include        <unistd.h>
#include		<tarLib.h>
#include        <philLib.h>
 
#define         MAXBUFSIZE   1024*1024
#define  STDOUT 1
#define  FALSE 0
#define  TRUE  1
#define  PRGNAME "stripVme"

typedef struct {
	int		firstScan;		/* first scan number to process*/
	int		ordinalStart;   /* to start on . count from 1*/
	int		lastScan;		/* last scan number to process*/
	int		numScans;		/* number of scans to process*/
	int		quiet;	
	int		stripHdr;		/* true --> strip the header. output data only*/
	int		stripData;		/* true --> strip the data.   output hdr only*/
	int		scansOutput;	/* we've output*/
	int		curScanNum;		/* we are working with*/
	int		firstGrp;		/* first group to include in each scan*/
	int		lastGrp;		/* last gropu to include in each scan*/
	int		search;			/* if true then we search for good hdrid*/
	}STRIPVME_I;

void    processargs(int argc,char **argv,STRIPVME_I *pI);
static int searchForHdrL(char *hdrBuf);
int main(int argc,char **argv) 
{
/*
        stripVme  -h -d -q -n numscans -f firstscan -l lastscan -g 1stgrp lastgrp
        Filter to select a subset  of the scans in a file and then 
        optionally strip off the header or data.
        data records

       -q   run quiet.. no monitoring info
       -h   strip off the headers 
       -d   strip off the data
	   -f   first scan to include
	   -g   first last  group of each scan to include. 
						For the ri, groups are recs,
						for the correlator groups are a single integration that
						may contain more than 1 rec.
						Note: "first last" must be in quotes..
	   -l   last scan to include
	   -o   ordinal scan number to start on 1..n
	   -n   number of scans to include (-o reset each other)
	   -b   if set and we find a bad headerid, then search forward
			for the start of the next valid record byte by byte.

	   for a scan to be output , it must meet the criteria for all of them
		 defaults set so all scans included

        input is from standard in, output to standard out.
        ASSUMPTIONS:
        - Std vme header (common part and optional).          
        
        The filter grabs the 1st header id, get the record length, and 
        then pumps out the header and/or data,
 *
 *history start
 *    21jan93 .. copied from stripdata.
 *    29jun98 .. added -o option
 *    11feb99 .. remove -h as default. if nothing requested, then
 *			     just pass through the requested scans.
 *    25may99 .. added option for selective groups
 *    11oct02 .. added -b option. update maxbufsize 128K -> 1mb
 *    14jul03 .. added code to run on linux
 *              need -DLINUX  in the compile line
 *history end  
*/
        char          hdrbuf[MAXBUFSIZE];               /* input buffer*/
        char          *cptr;
        int           bytesread;                        /* input this read*/
        int           byteswritten;                     /* actually written*/
        int           bytesreq;
        int           recnum;                           /* our counter*/
        int           hlenGenB;
        int           dataToReadB;
        char          hdrid[5];
        HDRAO_STD     hdrg;                     /* generic headers*/
        HDRAO_STD     *phdrg;                     /* generic headers*/
		int			  monRec;
		STRIPVME_I    strI;
		int			  scan;
		int			  scanCount;
		int			  istat;
		int			  markerOk,recLenOk,hdrLenOk;
		int			  reclen,hdrlen;
		int			  itemp;				/* for swapping*/
        
        hlenGenB= sizeof(hdrg);
		monRec=25;
		scanCount=0;
	    scan=0;
        processargs(argc,argv,&strI) ;
        if (!strI.quiet){
            fprintf(stderr,"Starting up stripVme..\n");
			fprintf(stderr,"1st,lastgrp: %d %d\n",
			strI.firstGrp, strI.lastGrp);
		}
		

        recnum=0;       
/*
 *      loop till we read eof... first get the header
*/
        while ((bytesread = read_pipe((char *)hdrbuf,hlenGenB))!=0){
            recnum++; 
			phdrg=(HDRAO_STD *)hdrbuf;
            memcpy((char *)&hdrg,hdrbuf,sizeof(hdrg));
            if (!strI.quiet && ( recnum%monRec == 0)){
                fprintf(stderr,"rec: %6d \r",recnum);
				if (recnum > 5000)monRec=100; 
				if (recnum > 25000)monRec=500; 
				if (recnum > 50000)monRec=1000; 
			}
            if (bytesread < 0) {
                fprintf(stderr,"%s error on hdr read rec %d\n",
                        PRGNAME,recnum);
                perror(PRGNAME);
                goto errout;
            }
/*
 *      see if hdr_ in first word
*/
			while (1) {
		    	markerOk=(strncmp((char *)hdrbuf,(char *)HDR_MARKER,4)==0);
				reclen=(linux)?bswap_32(phdrg->reclen):phdrg->reclen;
				hdrlen=(linux)?bswap_32(phdrg->hdrlen):phdrg->hdrlen;
		    	recLenOk=(reclen >= 128)  && (reclen < 5e6);
		    	hdrLenOk=(hdrlen >= 128)  && (hdrlen < 4000);
				if ((!markerOk) || (!recLenOk) || (!hdrLenOk)) {/*hdr_ ?*/
                	strncpy((char *)hdrid,(char *)hdrbuf,4);/* copy header*/
               		hdrid[4]=(char)0;
               		fprintf(stderr,
			"%s Bad hdr rec# %d..marker: %s recLen:0x%x hdrLen:0x%x\n",
                PRGNAME,recnum,hdrid,reclen,hdrlen);
					istat=-1;
					if (strI.search) {
						istat=searchForHdrL(hdrbuf);
						if (istat == 0) {
            				memcpy((char *)&hdrg,hdrbuf,sizeof(hdrg));
                            recnum++; 
				    	} else {
							goto errout;
						}
					} else {
						goto errout;
			    	}
				} else {
					break;
				}
            }
/*
 *      Total record length and extended header length.
*/
		    reclen=(linux)?bswap_32(hdrg.reclen):hdrg.reclen;
            dataToReadB=reclen - hlenGenB; /* data left to read*/
            cptr=&(hdrbuf[hlenGenB]); /* where to put rest of data*/
/*
 *      get the rest of this record
*/
            if ((bytesread = read_pipe((char *)cptr,dataToReadB)) !=
                        dataToReadB) {
               fprintf(stderr,"%s: read error data record: %d\n",PRGNAME,
                        recnum);
               perror(PRGNAME);
               goto errout;
            }
		/*
		 * see if we output this record
		*/
		itemp=(linux)?bswap_32(hdrg.scanNumber):hdrg.scanNumber;
		if (scan!= itemp){
			scanCount++;
		}
		scan=itemp;
		if (scan < strI.firstScan)continue; /* not there yet*/
		if ((strI.ordinalStart != 0 )&& (scanCount < strI.ordinalStart))
				continue;
		if (strI.curScanNum == 0)strI.curScanNum=scan;
		/*
 		 * if new scan output old and increment counters
		*/
		if (strI.curScanNum != scan) {
			strI.scansOutput++;
			if (strI.scansOutput >= strI.numScans) break;/* done */
			strI.curScanNum= scan;
			if (strI.curScanNum > strI.lastScan) break; /* done*/
		}
/*
 *      now output the data or header
*/
		 itemp=(linux)?bswap_32(hdrg.grpNum):hdrg.grpNum;
		 if  ((itemp < strI.firstGrp) || (itemp > strI.lastGrp)) continue;
         if (!strI.stripHdr) {
             bytesreq=(linux)?bswap_32(hdrg.hdrlen):hdrg.hdrlen;
             if (( byteswritten = write(STDOUT,(char *)hdrbuf,bytesreq)) !=
                   bytesreq){
                fprintf(stderr,
                "%s:Bad hdrlength write rec %d. req: %d, actual:%d\n",
                        PRGNAME,recnum,bytesreq, byteswritten);
                goto errout;
             }
         }
         if (!strI.stripData) {
			 if (linux) {
             	bytesreq= bswap_32(hdrg.reclen) - bswap_32(hdrg.hdrlen);
                cptr= hdrbuf + bswap_32(hdrg.hdrlen);
			} else {
             	bytesreq= hdrg.reclen - hdrg.hdrlen;
                cptr= hdrbuf + hdrg.hdrlen;
			}
             if (( byteswritten = write(STDOUT,cptr,bytesreq)) !=
                   bytesreq){
                fprintf(stderr,
                "%s:Bad datalen write rec %d. req: %d, actual:%d\n",
                        PRGNAME,recnum,bytesreq, byteswritten);
                goto errout;
             }
        }
      }
      exit(0);
errout: fflush(stderr);
	  fprintf(stderr,"exit stripVme.. status: -1\n");
	  fflush(stderr);
		exit(-1);
        /*NOTREACHED*/
}
/****************************************************************************/
/*   processargs                                                            */
/****************************************************************************/
void    processargs
	(
		int argc,
		char **argv,
		STRIPVME_I 	*pI
	)
{
/*
        function to process a programs input command line.
        This is a template that can be customized for individual programs
        To use it you should:

        - pass in the parameters that may be changed.
        - edit the case statement below to correspond to what you want.
        - stdio.h must be added for this routine to work

        Don't forget the ** on the arguments coming in (since you want to 
        pass back data.
*/
        int getopt();                   /* c lib function returns next opt*/ 
		int	itemp;
        extern int opterr;              /* if 0, getopt won't output err mesg*/
		extern char *optarg;
			

       int c;                          /* Option netter returned by getopt*/
        char  *myoptions = "bqhdf:l:n:o:g:";/* options to search for. :--> needs*/

        char *USAGE = 
"Usage:stripVme -d -h -b -q -o ordScanSt -f fscan -l lastscan -n numscans -g \"1st lastgrp\"";

        opterr = 0;                             /* turn off there message*/
		/*
		 * set the defaults
		*/
		pI->firstScan  =0;
		pI->ordinalStart=0;
		pI->lastScan   =1000000000;		/* larger than largest scan number*/
		pI->numScans   =99999999;
		pI->quiet	   =FALSE;
		pI->stripHdr   =FALSE;
		pI->stripData  =FALSE;
		pI->curScanNum =0;
		pI->scansOutput=0;
		pI->firstGrp=1;
		pI->search=0;
		pI->lastGrp=2000000000;			/* hopefully larger than any group number*/
/* 
        loop over all the options in list
*/
        while ((c = getopt(argc,argv,myoptions)) != -1){ 
          switch (c) {
          case 'd':
                  pI->stripData=TRUE;
                  break;
          case 'h':
                  pI->stripHdr=TRUE;
                  break;
          case 'q':
                  pI->quiet=1;
                  break;
          case 'f':
                   sscanf(optarg,"%d",&pI->firstScan);
				   pI->ordinalStart=0;
                   break;
          case 'g':
                   itemp=sscanf(optarg,"%d%d",&pI->firstGrp,&pI->lastGrp);
				   if (pI->firstGrp<1) pI->firstGrp=1;
				   if (pI->lastGrp < pI->firstGrp) pI->lastGrp=pI->firstGrp;
                   break;
          case 'l':
                   sscanf(optarg,"%d",&pI->lastScan);
                   break;
          case 'n':
                   sscanf(optarg,"%d",&pI->numScans);
                   break;
          case 'o':
                   sscanf(optarg,"%d",&pI->ordinalStart);
				   pI->firstScan=0;
                   break;
          case 'b':
                  pI->search=TRUE;
                  break;
          case '?':                     /*if c not in myoptions, getopt rets ?*/
             goto errout;
             break;
          }
        }
		if ((pI->stripHdr)&&(pI->stripData)){
			fprintf(stderr,"stripVme: noHdr and no data --> no output!!\n");
			goto  errout;
		}
        return;
/*
        here if illegal option or argument
*/
errout: fprintf(stderr,"%s\n",USAGE);
        exit(1);
}
/****************************************************************************
 *   search for header												
 ****************************************************************************/
static int  searchForHdrL
    (
        char	*hdrBuf
	)
{
	int	genHdrLen;
	char tomatch[5];
	int	i,im,toRead,bytesRead;
	int	istart,tocopy;
	int totread;
	HDRAO_STD     *phdrg;

	strcpy(tomatch,"hdr_");
	genHdrLen=sizeof(HDRAO_STD);
	i=0;
	im=0;
	totread=0;
    while (1) {
		if (i == genHdrLen) {
			toRead=genHdrLen-im;
/*
 *	  	if we are matching 2nd,3rd, etc.. put to start of buf then
 *      read hdrlen-this amount
*/
			if (im > 0) memcpy(hdrBuf, hdrBuf+i-im,im);
			bytesRead = read_pipe((char *)hdrBuf+im,toRead);
			if (bytesRead < toRead) goto hiteof;
			totread+=bytesRead;
			i=im;
			if ((totread % 10000) == 0){
				 fprintf(stderr,"searching for header:%d\r",totread);
		  	 	fflush(stderr);
			}
		}
		if (hdrBuf[i] == tomatch[im]) {
			im++;
			if (im >= 4) break;		/* got all 4*/
		} else if (im > 0)  {
			i=i-1;					/* so we look at this 1 again*/
			im=0;
		}
		i++;
	}
/*
 * got a match, i points at the location of _ in the hdrbuf
*/
	if  (i != 3) {
		istart=i-3;
	   	tocopy=genHdrLen-istart;
		memcpy(hdrBuf,hdrBuf+istart,tocopy);
		bytesRead = read_pipe((char *)hdrBuf+tocopy,istart);
	}
	phdrg=(HDRAO_STD*)hdrBuf;
	return(0);
hiteof: return(-1);
}
