#include        <stdio.h>
#include        <fcntl.h>
#include        <malloc.h>
#include    <unistd.h>
#include    <philLib.h>

#define  STDIN 0
#define  STDOUT 1
#define  MAXMAPS 100
#define TRUE 1
#define FALSE 0
#define MIN(a,b) ((a)<(b))?(a):(b)

int     inputmaps(char *filelist,int bytesinmap,float **mapArr);
void    processargs(int argc,char **argv,int *pinRows,int *pinCols,
					int *pinNumMapsHor,char *fileList,int *pdoZero);

/* revision control variable */
static char const rcsid[] = 
"$Id$";

int main(int argc,char **argv)
{
/*
 *
 *      merge maps into a single map
 *
 *      mapsmerge -f filename -c cols -r rows -h mapsperrow -z 
 *      
 *      -f  filename with list of mapfiles        
 *      -c cols in each map 
 *      -r rows in each map
 *      -m how many maps to put horizontally
 *      -z add zero line between maps.
 *
 *      -f inputfile should have 1 filename per line. 
 *      
 *      * program reads in all maps into memory, then outputs the zoomed map
 *        1 line at a time.
 *      * all maps should be the same size.
 *      * input/output is real*4.
*/
        int     inRows,inCols;                  /* in map input*/
        int     outRows,outCols;                /* include any zeros*/
        int     inBytesInMap;                   /* size of a map*/
        int     numMaps;                        /* count number of files*/
        int     mapsDone;                       /* we`ve processed*/
        int     inNumMapsHor;                   /* inp maps in hor line*/ 
        int     inNumMapsVer;                   /* inp maps in ver line*/ 
        char    fileList[80];                   /* file with datanames*/
        float   *inMapArr[MAXMAPS];             /* pointers to each map*/
        float   *prow;
        int     doZero; 
        float   *zeroArr;                       /* hold out line of zeros*/
        int     bytesPerPixel;
        int     inBytesInRow;
        int     mapsThisLine;                   /* we're outputing*/
        
        int     i,j,krow;
        
        inRows=0;
		zeroArr=NULL;
        inCols=0;
        inNumMapsHor=0;
        fileList[0]=' ';
        doZero=FALSE;
        bytesPerPixel=sizeof(float);
        processargs(argc,argv,&inRows,&inCols,&inNumMapsHor,fileList,&doZero); 
        inBytesInMap= bytesPerPixel*inRows*inCols;
        inBytesInRow= bytesPerPixel*inCols;
/*
 *      input the maps
*/
        numMaps=inputmaps(fileList,inBytesInMap,inMapArr);
        inNumMapsVer=(numMaps + inNumMapsHor -1)/inNumMapsHor; /* rows of maps*/
        outCols= (doZero)? (inCols+1)*inNumMapsHor:inCols*inNumMapsHor;
        outRows= (doZero)? (inRows+1)*inNumMapsVer:inRows*inNumMapsVer;
/*
 *      allocate one line of zeros if dozero
*/
        if (doZero) {   
           zeroArr=(float *)malloc(bytesPerPixel*outCols);
           for (i=0;i<outCols;zeroArr[i++]=0.);
        }
/*
 *      now output the maps
*/
/*      
 *      loop over the rows of maps if last row partial, fill with zeros
*/
        for (i=0,mapsDone=0;i< inNumMapsVer;i++){        
/*
 *          loop over rows within a map
*/
            mapsThisLine=MIN(inNumMapsHor,numMaps-mapsDone);
            for (krow=0;krow<inRows;krow++){      
/*
 *              loop over maps on a horizontal line
*/       
                for (j=0;j<mapsThisLine;j++){
                    prow= inMapArr[i*inNumMapsHor +j] + krow*inCols; 
                    fwrite(prow,inBytesInRow,1,stdout);
                    if (doZero){
                       fwrite(zeroArr,bytesPerPixel,1,stdout);
                    }
                } 
/* 
 *      if last line we may have to zero the end of the lines
*/
                for (j=mapsThisLine;j<inNumMapsHor;j++){ /*zero fill last line*/
                    fwrite(zeroArr,inBytesInRow,1,stdout);
                    if (doZero){
                       fwrite(zeroArr,bytesPerPixel,1,stdout);
                    }
                }
            }
/* 
 *      put a blank line under each map?
*/
            if (doZero){
                fwrite(zeroArr,bytesPerPixel*outCols,1,stdout);
            }
            mapsDone+=mapsThisLine;
        }
        fprintf(stderr,"%d input maps of %d(cols) x %d(rows)\n",
                numMaps,inCols,inRows);
        fprintf(stderr,"output map %d(cols) x %d(rows)\n",
                outCols,outRows);
        exit(0);
}
/******************************************************************************/
/*                                                                            */
/******************************************************************************/
int     inputmaps
(
char    *filelist,                              /* holds filenames*/
int     bytesinmap,                             /* to read */
float   **mapArr)                               /* array of maps*/
{ 
        char    filedata[80];                   /* file with data*/
        int     fddata;                         /* file with data*/
        FILE    *pfilelist;                     /* read file with names*/
        int     numfiles;                       /* read in*/
        int     itemp;  
        int     bytesread;                      /* input this read*/
        
/*
 *      loop through file with list of names. open each file and read it in
*/
        if ((pfilelist=fopen(filelist,"r")) == NULL){
           perror("mapsmerger:list of filenames:");
           exit(ERROR);
        }
        for (numfiles=0;;numfiles++){   
            itemp=fscanf(pfilelist,"%s",filedata); /* get next filename*/
            if ((itemp==0) || (itemp== EOF)) break;        /* got them all*/
/*      
 *      now try to open data file 
*/
            if ((fddata=open(filedata,O_RDONLY)) < 0){
               fprintf(stderr,"mapsmerge:Can't read file %s\n",filedata);
               exit(ERROR);
            }
/*
 *      allocate space to read map in
*/
            if ((mapArr[numfiles]=(float *)malloc(bytesinmap))==NULL){
               perror("mapsmerge:allocating input buf");
               exit(ERROR);
            }
/*
 *      read it in
*/
            bytesread=read(fddata,(char *)(mapArr[numfiles]),bytesinmap);
            if (bytesread != bytesinmap){
               fprintf(stderr,
                "Requested %d bytes but only read %d bytes in map %s\n",
                 bytesinmap,bytesread,filedata);
                 exit(ERROR);
            }
            close(fddata);                      /* done this file*/
        }
        fclose(pfilelist);                      /* close file with names*/
        return(numfiles);                       /* return number of maps*/
}
/******************************************************************************/
/*      processargs                                                           */
/******************************************************************************/
void    processargs
(
int     argc,
char    **argv,
int     *pinRows,
int		*pinCols,                      /* number rows,cols*/
int     *pinNumMapsHor,                         /* fit on hor line*/
char    *fileList,                              /* holds list of files*/
int     *pdoZero)                               /* put line of zeros*/
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
        extern char *optarg;            /* if arg with option, this pts to it*/
        extern int opterr;              /* if 0, getopt won't output err mesg*/

        int c;                          /* Option letter returned by getopt*/
        char  *myoptions = "c:r:h:f:z"; /* options to search for. :--> needs
                                            an argument*/
        char *USAGE = 
"Usage: mapsmerge -c inpcols -r inprows -h mapshor -f filelist [-z]";

        opterr = 0;                             /* turn off there message*/
/* 
        loop over all the options in list
*/
        while ((c = getopt(argc,argv,myoptions)) != -1){ 
          switch (c) {
          case 'c':
                   sscanf(optarg,"%d",pinCols);   /* cols*/
                   break;
          case 'r':
                   sscanf(optarg,"%d",pinRows);    /* rows*/
                   break;
          case 'f':
                  strcpy(fileList,optarg);
                  break;
          case 'h':
                  sscanf(optarg,"%d",pinNumMapsHor);
                  break;
          case 'z':
                   *pdoZero=TRUE;
                   break;
          case '?':                     /*if c not in myoptions, getopt rets ?*/
             goto errout;
             break;
          }
        }
        if (( *pinCols < 1) || ( *pinRows < 1) || (*pinNumMapsHor < 1) ||
             (fileList[0] == ' ')) {
            goto errout;
        }
        return;
/*
        here if illegal option or argument
*/
errout: fprintf(stderr,"%s\n",rcsid);
        fprintf(stderr,"%s\n",USAGE);
        exit(1);
}
