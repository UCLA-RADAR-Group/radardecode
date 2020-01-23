#include		<stdlib.h>
#include        <stdio.h>
#include		<unistd.h>
#include		<string.h>
#include        <fcntl.h>
#include        <malloc.h>
#include		<philLib.h>
/*
 *                         Filter to average data.
 *
 *    call 
 *
 *    avgdata  -d ii -l locavg -g glblen -h glbavg -i 
 *
 *  program acts as a filter.  reads from standard in, writes to standard out
 *
 *  The routine will average adjacent locations (locavg) 
 *   and it will also average together blocks of data (glbavg). 
 *  This can be thought of as averaging ipps. 
 *  The length of these blocks (before local averaging) is specified in
 *  glblen.
 * 
 *  The order of averaging is:
 *  1. average all blocks (ipps)
 *  2. after averaging a set of ipps, average pnts within the ipp.
 *
 *  The data type for input, output are specified by the -d option:
 *   -d      default is i1
 *
 *    i1      input/output is unsigned char
 *    i2      input/output is integer*2  
 *    i4      input/output is integer*4
 *    r4      input/output is real * 4
 *    r8      input/output is real * 8 
 *
 *   -l    # of adjacent pixels to average. default is 1
 *   -g    length of ipp 
 *   -h    number of ipps to avg (def 1).:q
 *         -1 --> avg all ipps till eof is hit.
 *   -i    ignore first ipp of each average.  (must set -h > 1 obviously)

 *        
 *      all averaging is done using real*4 variables. 
 *  
 * history:
 *      6/7/91... if eof and start of ipp, no need to output message output
 *                data not a multiple of avg ipp
 *      10/11/91..add -1 as a valid number of global ipps to avg. (-h).   
 *                if -1 is specified, then avg ipps till eof is hit. 
 *                Any partial ipps at the end will be ignored.
 *      15may061..addded -i option. ignore first record of each average
 *                (for radar processing. -h should be > 1 for this to work)
 *
*/
#define STDINP     0
#define STDOUT     1
#define ISAPIPE    1
#define PRGID      "avgdata"
#define TRUE       1
#define FALSE      0
int     inpbufwords;            /* each read*/
int     inpbufbytes;            /* depends on datatype*/
int     outbufwords;            /* each write*/
int     outbufbytes;    

void   avgi1(int locavg,int ippavg,int typebytes);
void   avgi2(int locavg,int ippavg,int typebytes);
void   avgi4(int locavg,int ippavg,int typebytes);
void   avgr4(int locavg,int ippavg,int typebytes,int ignorefirst);
void   avgr8(int locavg,int ippavg,int typebytes);
void    processargs(int argc,char **argv,char *datatype,int *locavg,
                    int     *glblen,int     *glbavg,int *ignorefirst);

int main(int argc,char **argv)
{
        char    datatype[3];
        int     locavg;                 /* number adjacent pnts to avg*/ 
        int     ipplen;                 /* length of ipp*/
        int     ippavg;                 /* ipps to avg*/
        int     typebytes;              /* bytes for our type*/
		int		ignorefirst;		    /* ignore 1st ipp in an average*/

		ignorefirst=FALSE;
        processargs(argc,argv,datatype,&locavg,&ipplen,&ippavg,&ignorefirst);
/*
 *      compute our constants here. 
 *     
*/
        inpbufwords =  ipplen;                  /* ipp length */
        outbufwords=  inpbufwords / locavg;      /* each ipp after locavg*/
        typebytes = datatype[1] - '0';          /* # of bytes data type*/
        inpbufbytes = inpbufwords*typebytes;
        outbufbytes = outbufwords*typebytes;

        if (!strcmp(datatype,"i1")){
           avgi1(locavg,ippavg,typebytes);
        }
        else if (!strcmp(datatype,"i2")) {
           avgi2(locavg,ippavg,typebytes);
        }
        else if (!strcmp(datatype,"i4")) {
           avgi4(locavg,ippavg,typebytes);
        }
        else if (!strcmp(datatype,"r4")) {
           avgr4(locavg,ippavg,typebytes,ignorefirst);
        }
        else if (!strcmp(datatype,"r8")) {
           avgr8(locavg,ippavg,typebytes);
        }
        exit(0);
        /*NOTREACHED*/
}
/*****************************************************************************
 *     avg1
*******************************************************************************/
void   avgi1
(
int     locavg,                         /* avg within an ipp*/
int     ippavg,                         /* ipps to avg*/
int     typebytes)                      /* this datatype*/              
{
        typedef unsigned char loctype;
        loctype  *in_buf,*out_buf;
        int     *avg_buf;       
        int     rowsoutput;             /* we output*/
        int     ipp,i,j,k;
        int     numbytes;               /* from read*/
        float   avginv;
        int     lasttime;               /* thru loop*/
        int     outbufwordssave;        
        int     ippavgloc;              /* local copy*/
/*
 *      allocate the input buffer, output buffer, add buffer
*/
        outbufwordssave = outbufwords;
        ippavgloc=(ippavg == -1)? 1000000000:ippavg;/*-1--> go till eof*/
        avginv = 1./(locavg*ippavg); /* if neg we fix later*/
        in_buf=(loctype *)calloc((unsigned)inpbufwords,sizeof(loctype));
        if (in_buf == NULL){
           perror("avgdata: allocate in_buf");
           exit(-1);
        }
        out_buf=(loctype *)calloc((unsigned)inpbufwords,sizeof(loctype));
        if (out_buf == NULL){
           perror("avgdata: allocate out_buf");
           exit(-1);
        }
        avg_buf=(int *)calloc((unsigned ) inpbufwords,sizeof(int));
        if (avg_buf == NULL){
           perror("avgdata: allocate out_buf");
           exit(-1);
        }
/*
 *      loop over all of the output rows in the map
*/
        lasttime = FALSE;
        for (rowsoutput=0;;){
/*
 *      loop over ipps to average
*/
            for (ipp=0;ipp< ippavgloc;ipp++){
/*
 *      input an ipp
*/
                numbytes=read_pipe((char *)in_buf,inpbufbytes);
                if ((numbytes==0) && (ipp==0)) goto done;
                if (numbytes != inpbufbytes){ 
                   if (numbytes  < 0) {
                      fprintf(stderr,"Input error row %d ipp %d\n",
                       rowsoutput,ipp+1);
                       perror("sys error:");
                      goto done;
                   }
                   if (ippavg == 1) {           /* ok, inlen was arbitrary*/    
                       inpbufbytes = numbytes;  
                       inpbufwords = inpbufbytes/typebytes;
                       outbufwords=  inpbufwords / locavg;
                       outbufbytes = outbufwords*typebytes;
                       lasttime = TRUE; 
                    }
/*
 *              reading till eof. this short record must be the end
*/
                    else if (ippavg == -1) {
                        ippavgloc=ipp;          /* number of ipps we've added*/
                        inpbufwords = 0;        /* ignore last partial ipp*/
                        lasttime = TRUE; 
                    }
                    else {
                    fprintf(stderr,"Data file is not a multiple of ipp len\n");
                    fprintf(stderr,"Last avg ipp not output\n");             
                       goto done;
                    }
                }
/*
 *      move or add it to average buffer
*/
                if (ipp == 0){
                    for (i=0;i<inpbufwords;i++){
                        avg_buf[i] =  in_buf[i];
                    }
                }
                else { 
                    for (i=0;i<inpbufwords;i++){
                        avg_buf[i] = in_buf[i] + avg_buf[i];
                    }
                }
            }
/*
 *      now average within an ipp
*/
            for (j=0,i=0;j< outbufwords;j++){
                 avg_buf[j]=avg_buf[i++];               /* move 1st value in*/
                 for (k=0;k<locavg-1;k++){
                     avg_buf[j] += avg_buf[i++];
                 } 
            }
/*
 *      now convert to output data type
*/
           if (ippavg == -1) avginv=1./(ippavgloc*locavg);
           for (j=0;j< outbufwords;j++){
                out_buf[j]=(loctype)(avg_buf[j]*avginv);
           }
           numbytes = write(STDOUT,(char *)out_buf,outbufbytes);
           rowsoutput++;
/*
           if ((rowsoutput % 50)== 1){
                fprintf(stderr,"Rows done: %d\n",rowsoutput);
           }
*/
           if (lasttime) goto done;
        }
done:   fprintf(stderr,"%d ipps each of length %d words output\n",rowsoutput,
                outbufwordssave);
        return;
}    
/*****************************************************************************
 *     avgi2
*******************************************************************************/
void   avgi2
(
int     locavg,                         /* avg within an ipp*/
int     ippavg,                         /* ipps to avg*/
int     typebytes)                      /* this datatype*/              
{
        typedef  short int loctype;
        loctype  *in_buf,*out_buf;
        int     *avg_buf;       
        int     rowsoutput;             /* we output*/
        int     ipp,i,j,k;
        int     numbytes;               /* from read*/
        float   avginv;
        int     lasttime;               /* thru loop*/
        int     outbufwordssave;        
        int     ippavgloc;
/*
 *      allocate the input buffer, output buffer, add buffer
*/
        outbufwordssave = outbufwords;
        ippavgloc=(ippavg == -1)? 1000000000:ippavg;/*-1--> go till eof*/
        avginv = 1./(locavg*ippavg); /* if < 0 we fix later*/
        in_buf=(loctype *)calloc((unsigned)inpbufwords,sizeof(loctype));
        if (in_buf == NULL){
           perror("avgdata: allocate in_buf");
           exit(-1);
        }
        out_buf=(loctype *)calloc((unsigned)inpbufwords,sizeof(loctype));
        if (out_buf == NULL){
           perror("avgdata: allocate out_buf");
           exit(-1);
        }
        avg_buf=(int *)calloc((unsigned ) inpbufwords,sizeof(int));
        if (avg_buf == NULL){
           perror("avgdata: allocate out_buf");
           exit(-1);
        }
/*
 *      loop over all of the output rows in the map
*/
        lasttime = FALSE;
        for (rowsoutput=0;;){
/*
 *      loop over ipps to average
*/
            for (ipp=0;ipp< ippavgloc;ipp++){
/*
 *      input an ipp
*/
                numbytes=read_pipe((char *)in_buf,inpbufbytes);
                if ((numbytes==0) && (ipp==0)) goto done;
                if (numbytes != inpbufbytes){ 
                   if (numbytes  < 0) {
                      fprintf(stderr,"Input error row %d ipp %d\n",
                       rowsoutput,ipp+1);
                       perror("sys error:");
                      goto done;
                   }
                   if (ippavg == 1) {           /* ok, inlen was arbitrary*/    
                       inpbufbytes = numbytes;  
                       inpbufwords = inpbufbytes/typebytes;
                       outbufwords=  inpbufwords / locavg;
                       outbufbytes = outbufwords*typebytes;
                       lasttime = TRUE; 
                    }
/*
 *              reading till eof. this short record must be the end
*/
                    else if (ippavg == -1) {
                        ippavgloc=ipp;          /* number of ipps we've added*/
                        inpbufwords = 0;        /* ignore last partial ipp*/
                        lasttime = TRUE;
                    }
                    else {
                     fprintf(stderr,"Data file is not a multiple of ipp len\n");
                     fprintf(stderr,"Last avg ipp not output\n");             
                       goto done;
                    }
                }
/*
 *      move or add it to average buffer
*/
                if (ipp == 0){
                    for (i=0;i<inpbufwords;i++){
                        avg_buf[i] =  in_buf[i];
                    }
                }
                else { 
                    for (i=0;i<inpbufwords;i++){
                        avg_buf[i] = in_buf[i] + avg_buf[i];
                    }
                }
            }
/*
 *      now average within an ipp
*/
            for (j=0,i=0;j< outbufwords;j++){
                 avg_buf[j]=avg_buf[i++];               /* move 1st value in*/
                 for (k=0;k<locavg-1;k++){
                     avg_buf[j] += avg_buf[i++];
                 } 
            }
/*
 *      now convert to output data type
*/
           if (ippavg == -1) avginv=1./(ippavgloc*locavg);
           for (j=0;j< outbufwords;j++){
                out_buf[j]=(loctype)(avg_buf[j]*avginv);
           }
           numbytes = write(STDOUT,(char *)out_buf,outbufbytes);
           rowsoutput++;
/*
           if ((rowsoutput % 50)== 1){
                fprintf(stderr,"Rows done: %d\n",rowsoutput);
           }
*/
           if (lasttime) goto done;
        }
done:   fprintf(stderr,"%d ipps each of length %d words output\n",rowsoutput,
                outbufwordssave);
        return;
}    
/*****************************************************************************
 *     avgi4
*******************************************************************************/
void   avgi4
(
int     locavg,                         /* avg within an ipp*/
int     ippavg,                         /* ipps to avg*/
int     typebytes)                      /* this datatype*/              
{
        typedef  int loctype;
        loctype  *in_buf,*out_buf;
        int     *avg_buf;       
        int     rowsoutput;             /* we output*/
        int     ipp,i,j,k;
        int     numbytes;               /* from read*/
        float   avginv;
        int     lasttime;               /* thru loop*/
        int     outbufwordssave;        
        int     ippavgloc;              /* local copy*/
/*
 *      allocate the input buffer, output buffer, add buffer
*/
        outbufwordssave = outbufwords;
        ippavgloc=(ippavg == -1)? 1000000000:ippavg;/*-1--> go till eof*/
        avginv = 1./(locavg*ippavg);
        in_buf=(loctype *)calloc((unsigned)inpbufwords,sizeof(loctype));
        if (in_buf == NULL){
           perror("avgdata: allocate in_buf");
           exit(-1);
        }
        out_buf=(loctype *)calloc((unsigned)inpbufwords,sizeof(loctype));
        if (out_buf == NULL){
           perror("avgdata: allocate out_buf");
           exit(-1);
        }
        avg_buf=(int *)calloc((unsigned ) inpbufwords,sizeof(int));
        if (avg_buf == NULL){
           perror("avgdata: allocate out_buf");
           exit(-1);
        }

/*
 *      loop over all of the output rows in the map
*/
        lasttime = FALSE;
        for (rowsoutput=0;;){
/*
 *      loop over ipps to average
*/
            for (ipp=0;ipp< ippavgloc;ipp++){
/*
 *      input an ipp
*/
                numbytes=read_pipe((char *)in_buf,inpbufbytes);
                if ((numbytes==0) && (ipp==0)) goto done;
                if (numbytes != inpbufbytes){ 
                   if (numbytes  < 0) {
                      fprintf(stderr,"Input error row %d ipp %d\n",
                       rowsoutput,ipp+1);
                       perror("sys error:");
                      goto done;
                   }
                   if (ippavg == 1) {           /* ok, inlen was arbitrary*/    
                       inpbufbytes = numbytes;  
                       inpbufwords = inpbufbytes/typebytes;
                       outbufwords=  inpbufwords / locavg;
                       outbufbytes = outbufwords*typebytes;
                       lasttime = TRUE; 
                    }
/*
 *              reading till eof. this short record must be the end
*/
                    else if (ippavg == -1) {
                        ippavgloc=ipp;          /* number of ipps we've added*/
                        inpbufwords = 0;        /* ignore last partial ipp*/
                        lasttime = TRUE;
                    }
                    else {
                     fprintf(stderr,"Data file is not a multiple of ipp len\n");
                     fprintf(stderr,"Last avg ipp not output\n");             
                       goto done;
                    }
                }
/*
 *      move or add it to average buffer
*/
                if (ipp == 0){
                    for (i=0;i<inpbufwords;i++){
                        avg_buf[i] =  in_buf[i];
                    }
                }
                else { 
                    for (i=0;i<inpbufwords;i++){
                        avg_buf[i] = in_buf[i] + avg_buf[i];
                    }
                }
            }
/*
 *      now average within an ipp
*/
            for (j=0,i=0;j< outbufwords;j++){
                 avg_buf[j]=avg_buf[i++];               /* move 1st value in*/
                 for (k=0;k<locavg-1;k++){
                     avg_buf[j] += avg_buf[i++];
                 } 
            }
/*
 *      now convert to output data type
*/
           if (ippavg == -1) avginv=1./(ippavgloc*locavg);
           for (j=0;j< outbufwords;j++){
                out_buf[j]=(loctype)(avg_buf[j]*avginv);
           }
           numbytes = write(STDOUT,(char *)out_buf,outbufbytes);
           rowsoutput++;
/*
           if ((rowsoutput % 50)== 1){
                fprintf(stderr,"Rows done: %d\n",rowsoutput);
           }
*/
           if (lasttime) goto done;
        }
done:   fprintf(stderr,"%d ipps each of length %d words output\n",rowsoutput,
                outbufwordssave);
        return;
}    
/*****************************************************************************
 *     avgr4
*******************************************************************************/
void   avgr4
(
int     locavg,                         /* avg within an ipp*/
int     ippavg,                         /* ipps to avg*/
int     typebytes,                      /* this datatype*/              
int     ignorefirst)                    /* ignore first ipp*/
{
        typedef  float loctype;
        loctype  *in_buf,*out_buf;
        float   *avg_buf;       
        int     rowsoutput;             /* we output*/
        int     ipp,i,j,k;
        int     numbytes;               /* from read*/
        float   avginv;
        int     lasttime;               /* thru loop*/
        int     outbufwordssave;        
        int     totbytesread;
        int     ippavgloc;              /* local copy*/
        int     ijunk; 
/*
 *      allocate the input buffer, output buffer, add buffer
*/
        outbufwordssave = outbufwords;
        ijunk=0;
        totbytesread=0;
        ippavgloc=(ippavg == -1)? 1000000000:ippavg;/*-1--> go till eof*/
        avginv = (ignorefirst)? 1./(locavg*(ippavg-1)):1./(locavg*ippavg);
        in_buf=(loctype *)calloc((unsigned)inpbufwords,sizeof(loctype));
        if (in_buf == NULL){
           perror("avgdata: allocate in_buf");
           exit(-1);
        }
        out_buf=(loctype *)calloc((unsigned)inpbufwords,sizeof(loctype));
        if (out_buf == NULL){
           perror("avgdata: allocate out_buf");
           exit(-1);
        }
        avg_buf=(float *)calloc((unsigned ) inpbufwords,sizeof(float));
        if (avg_buf == NULL){
           perror("avgdata: allocate out_buf");
           exit(-1);
        }
/*
 *      loop over all of the output rows in the map
*/
        lasttime = FALSE;
/*  debug...
        fprintf(stderr,"ippavg: %d\n",ippavg);
*/
        for (rowsoutput=0;;){
/*
 *      loop over ipps to average
*/
            for (ipp=0;ipp< ippavgloc;ipp++){
/*
 *      input an ipp
*/
                numbytes=read_pipe((char *)in_buf,inpbufbytes);
                if ((numbytes==0) && (ipp==0)) goto done;
                if (numbytes > 0) totbytesread+=numbytes;
                if (numbytes != inpbufbytes){ 
                   if (numbytes  < 0) {
                      fprintf(stderr,"Input error row %d ipp %d\n",
                       rowsoutput,ipp+1);
                       perror("sys error:");
                      goto done;
                   }
                   if (ippavg == 1) {           /* ok, inlen was arbitrary*/    
                       inpbufbytes = numbytes;  
                       inpbufwords = inpbufbytes/typebytes;
                       outbufwords=  inpbufwords / locavg;
                       outbufbytes = outbufwords*typebytes;
                       lasttime = TRUE; 
                    }
/*
 *              reading till eof. just ignore this last record
*/
                    else if (ippavg == -1) {
                        ippavgloc=ipp;          /* number of ipps we've added*/
                        inpbufwords = 0;        /* ignore last partial ipp*/
                        lasttime = TRUE;
                    }
                    else {
                    fprintf(stderr,
     "Data file:%d bytes,is not a multiple of ipp*glbal avg:%d. last rd=%d\n",
                               totbytesread,inpbufbytes*ippavgloc,numbytes);
                    fprintf(stderr,"Last avg ipp not output\n");             
                       goto done;
                    }
                }
/*
 *      move or add it to average buffer
*/
				if (ignorefirst && (ipp == 0)){  /* skip first ipp*/
				} else {
				  if ((ipp == 0) || ((ipp == 1) && (ignorefirst))) {
                     ijunk=1;
                     for (i=0;i<inpbufwords;i++){
                        avg_buf[i] =  in_buf[i];
                    }
                  }
                  else { 
                    if (inpbufwords > 0) ijunk++;
                    for (i=0;i<inpbufwords;i++){
                        avg_buf[i] = in_buf[i] + avg_buf[i];
                    }
                  }
			   }
            }
/*
 *      now average within an ipp
*/
            for (j=0,i=0;j< outbufwords;j++){
                 avg_buf[j]=avg_buf[i++];               /* move 1st value in*/
                 for (k=0;k< (locavg-1);k++){
                     avg_buf[j] += avg_buf[i++];
                 } 
            }
/*
 *      now convert to output data type
*/
           if (ippavg == -1) avginv=1./(ippavgloc*locavg);
           for (j=0;j< outbufwords;j++){
                out_buf[j]=(loctype)(avg_buf[j]*avginv);
           }
           numbytes = write(STDOUT,(char *)out_buf,outbufbytes);
           rowsoutput++;
/*
           if ((rowsoutput % 50)== 1){
                fprintf(stderr,"Rows done: %d\n",rowsoutput);
           }
*/
           if (lasttime) goto done;
        }
done:   fprintf(stderr,"%d ipps each of length %d words output\n",rowsoutput,
                outbufwordssave);
        return;
}    
/*****************************************************************************
 *     avgr8
*******************************************************************************/
void   avgr8
(
int     locavg,                         /* avg within an ipp*/
int     ippavg,                         /* ipps to avg*/
int     typebytes)                      /* this datatype*/              
{
        typedef  double loctype;  
        loctype  *in_buf,*out_buf;
        double  *avg_buf;       
        int     rowsoutput;             /* we output*/
        int     ipp,i,j,k;
        int     numbytes;               /* from read*/
        double  avginv;
        int     lasttime;               /* thru loop*/
        int     outbufwordssave;        
        int     ippavgloc;              /* local copy*/
/*
 *      allocate the input buffer, output buffer, add buffer
*/
        outbufwordssave = outbufwords;
        ippavgloc=(ippavg == -1)? 1000000000:ippavg;/*-1--> go till eof*/
        avginv = 1./((double)(locavg*ippavg));
        in_buf=(loctype *)calloc((unsigned)inpbufwords,sizeof(loctype));
        if (in_buf == NULL){
           perror("avgdata: allocate in_buf");
           exit(-1);
        }
        out_buf=(loctype *)calloc((unsigned)inpbufwords,sizeof(loctype));
        if (out_buf == NULL){
           perror("avgdata: allocate out_buf");
           exit(-1);
        }
        avg_buf=(double *)calloc((unsigned ) inpbufwords,sizeof(double));
        if (avg_buf == NULL){
           perror("avgdata: allocate out_buf");
           exit(-1);
        }
/*
 *      loop over all of the output rows in the map
*/
        lasttime = FALSE;
        for (rowsoutput=0;;){
/*
 *      loop over ipps to average
*/
            for (ipp=0;ipp< ippavgloc;ipp++){
/*
 *      input an ipp
*/
                numbytes=read_pipe((char *)in_buf,inpbufbytes);
                if ((numbytes==0) && (ipp==0)) goto done;
                if (numbytes != inpbufbytes){ 
                   if (numbytes  < 0) {
                      fprintf(stderr,"Input error row %d ipp %d\n",
                       rowsoutput,ipp+1);
                       perror("sys error:");
                      goto done;
                   }
                   if (ippavg == 1) {           /* ok, inlen was arbitrary*/    
                       inpbufbytes = numbytes;  
                       inpbufwords = inpbufbytes/typebytes;
                       outbufwords=  inpbufwords / locavg;
                       outbufbytes = outbufwords*typebytes;
                       lasttime = TRUE; 
                    }
/*
 *              reading till eof. this short record must be the end
*/
                    else if (ippavg == -1) {
                        ippavgloc=ipp;          /* number of ipps we've added*/
                        inpbufwords = 0;        /* ignore last partial ipp*/
                        lasttime = TRUE;
                    }
                    else {
                    fprintf(stderr,
                    "Data file is not a multiple of ipp len\n");
                    fprintf(stderr,"Last avg ipp not output\n");             
                       goto done;
                    }
                }
/*
 *      move or add it to average buffer
*/
                if (ipp == 0){
                    for (i=0;i<inpbufwords;i++){
                        avg_buf[i] =  in_buf[i];
                    }
                }
                else { 
                    for (i=0;i<inpbufwords;i++){
                        avg_buf[i] = in_buf[i] + avg_buf[i];
                    }
                }
            }
/*
 *      now average within an ipp
*/
            for (j=0,i=0;j< outbufwords;j++){
                 avg_buf[j]=avg_buf[i++];               /* move 1st value in*/
                 for (k=0;k<locavg-1;k++){
                     avg_buf[j] += avg_buf[i++];
                 } 
            }
/*
 *      now convert to output data type
*/
           if (ippavg == -1) avginv=1./(ippavgloc*locavg);
           for (j=0;j< outbufwords;j++){
                out_buf[j]=(avg_buf[j]*avginv);
           }
           numbytes = write(STDOUT,(char *)out_buf,outbufbytes);
           rowsoutput++;
/*
           if ((rowsoutput % 50)== 1){
                fprintf(stderr,"Rows done: %d\n",rowsoutput);
           }
*/
           if (lasttime) goto done;
        }
done:   fprintf(stderr,"%d ipps each of length %d words output\n",rowsoutput,
                outbufwordssave);
        return;
}    
/******************************************************************************/
/*    process args                                                            */
/******************************************************************************/
void    processargs
(
int     argc,
char    **argv,
char    *datatype,
int     *locavg,
int             *glblen,
int             *glbavg,
int		*ignorefirst)
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
        char  *myoptions = "d:g:l:h:i";  /* options to search for. :--> needs
                                            an argument*/
char *USAGE = "Usage: avgdata -d datatype -l locavg -g globlen -h globavg -i";

        opterr = 0;                             /* turn off there message*/
        strcpy(datatype,"i1");                  /* default data type*/
        *locavg = 1;
        *glblen = -999;                 /* if -g spec. must specify -h too*/
        *glbavg = -999;
/* 
        loop over all the options in list
*/
        while ((c = getopt(argc,argv,myoptions)) != -1){ 
          switch (c) {
          case 'd':
                   strncpy(datatype,optarg,2);          /* get new datatype*/
                   break;
          case 'g':
                   sscanf(optarg,"%d",glblen);          /* get global avg*/
                   break;
          case 'h':
                   sscanf(optarg,"%d",glbavg);          /* get global len*/
                   break;
          case 'l':
                   sscanf(optarg,"%d",locavg);          /* get local avg*/
                   break;
		  case 'i':
                   *ignorefirst = TRUE;     /* ignore first ipp in an average */
                   break;

          case '?':                     /*if c not in myoptions, getopt rets ?*/
             goto errout;
             break;
          }
        }
/*
 *      -h and -l must be specified together
*/
        if  (((*glbavg == -999) && (*glblen != -999)) ||
             ((*glblen == -999) && (*glbavg != -999))) {   
             fprintf(stderr,"-h and -l options must be specified together\n");
             goto errout;   
        }
/*
 *      glbavg can be -999, -1 or > 0
*/

        if ((*glbavg < 0 ) && ((*glbavg != -999) && (*glbavg != -1))){
           fprintf(stderr,
           "Illegal value for -h. legal values are:nothing, -1, or > 0\n");
           goto errout;
        }
/*
 *      glblen can be -999,  > 0
*/
        if ((*glblen < 0 ) && (*glblen != -999)){
           fprintf(stderr,
           "Illegal value for -l. legal values are:nothing,  or > 0\n");
           goto errout;
        }
/*
 *      default -g = 1024 (but divisisble by locavg), -h = 1 
*/
        if ( *glbavg == -999){
            *glblen = (1024 / *locavg) * (*locavg);
            *glbavg = 1;
        }
        to_lowercase(datatype);
        if ( strcmp(datatype,"i1") && strcmp(datatype,"i2") &&
             strcmp(datatype,"i4") && strcmp(datatype,"r4") &&
             strcmp(datatype,"r8")) {
             fprintf(stderr,"Illegal datatype\n");
             goto errout;
        }
        if (((*glblen / *locavg)* *locavg) != *glblen) {
             fprintf(stderr,"Local avg %d must divide into ipp length %d\n",
                     *locavg,*glblen);
             goto errout; 
        }
		if (*ignorefirst && *glbavg == 1) {
     		fprintf(stderr,"Can't drop first ipp if global avg = %d\n",
        			 *glbavg);
  		    goto errout;
		}

        return;
/*
 *      here if error occured
*/
errout: ;
        fprintf(stderr,"%s\n",USAGE);
        exit(1);
        /*NOTREACHED*/
}
