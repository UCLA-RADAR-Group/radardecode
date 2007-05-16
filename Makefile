#
#	Make one or more programs from the source
#       executables will be placed in GLOBDIR
#
# HOME=/home/pfs
SHELL=/bin/csh
GLOBDIR=$(HOME)/bin
CFLAGS=-O4 -I. -I${HOME}/include  -D_LARGEFILE_SOURCE -D_FILE_OFFSET_BITS=64
FFLAGS=-O
LPATH=$(HOME)/lib
CC=gcc

all: scripts radardecode rotate radarfft radarcplxfft selectpnts comppncode compdsncode compbarkercode scaletosigma makefits mapsmerge avgdata stripVme

FORCE:
	
scripts: FORCE
	chmod u+w scripts/*
	cp scripts/*.sc $(GLOBDIR)
	cp scripts/*.awk $(GLOBDIR)

radardecode: radardecode.c fftwAo.o unpriV_f4.o read_pipe.o timerstart.o timervalue.o
	$(CC) $(CFLAGS) radardecode.c fftwAo.o unpriV_f4.o read_pipe.o timerstart.o timervalue.o -L$(LPATH) ../pfs/libunpack.o -lfftw -lm -o $(GLOBDIR)/radardecode
#

rotate: rotate.c read_pipe.o
	$(CC) $(CFLAGS) rotate.c read_pipe.o -lm -o $(GLOBDIR)/rotate

radarfft: radarfft.c fftwAo.o read_pipe.o
	$(CC) $(CFLAGS) radarfft.c fftwAo.o read_pipe.o -L$(LPATH) -lfftw -lm -o $(GLOBDIR)/radarfft

radarcplxfft: radarcplxfft.c 
	$(CC) $(CFLAGS) radarcplxfft.c fftwAo.o read_pipe.o -L$(LPATH) -lfftw -lm -o $(GLOBDIR)/radarcplxfft

selectpnts: selectpnts.c writen.o read_pipe.o
	$(CC) $(CFLAGS) selectpnts.c writen.o read_pipe.o -lm -o $(GLOBDIR)/selectpnts

comppncode: comppncode.c
	$(CC) $(CFLAGS) comppncode.c -lm -o $(GLOBDIR)/comppncode

compdsncode: compdsncode.c
	$(CC) $(CFLAGS) compdsncode.c -lm -o $(GLOBDIR)/compdsncode

compbarkercode: compbarkercode.c
	$(CC) $(CFLAGS) compbarkercode.c -lm -o $(GLOBDIR)/compbarkercode

scaletosigma: scaletosigma.c read_pipe.o
	$(CC) $(CFLAGS) scaletosigma.c read_pipe.o -lm -o $(GLOBDIR)/scaletosigma

makefits: makefits.c read_pipe.o fitsCmpScl.o fitsOutData.o fitsOutHdr.o
	$(CC) $(CFLAGS) makefits.c read_pipe.o fitsCmpScl.o fitsOutData.o fitsOutHdr.o -lm -o $(GLOBDIR)/makefits

mapsmerge: mapsmerge.c
	$(CC) $(CFLAGS) mapsmerge.c -lm -o $(GLOBDIR)/mapsmerge

avgdata: avgdata.c read_pipe.o
	$(CC) $(CFLAGS) avgdata.c read_pipe.o -lm -o $(GLOBDIR)/avgdata

stripVme: stripVme.c read_pipe.o hdrLib.h
	$(CC) $(CFLAGS) -DLINUX stripVme.c read_pipe.o -o $(GLOBDIR)/stripVme

unpriVtoi4: unpriVtoi4.c read_pipe.o unpriV_i4.o
	$(CC) $(CFLAGS) unpriVtoi4.c read_pipe.o unpriV_i4.o -o $(GLOBDIR)/unpriVtoi4


fftwAo.o:	 fftwAo.c ;     $(CC) $(CFLAGS) -c fftwAo.c
writen.o:	 writen.c ;     $(CC) $(CFLAGS) -c writen.c
unpriV_f4.o:	 unpriV_f4.c ;  $(CC) $(CFLAGS) -c unpriV_f4.c
unpriV_i4.o:	 unpriV_i4.c ;  $(CC) $(CFLAGS) -c unpriV_i4.c
read_pipe.o:	 read_pipe.c ;	$(CC) $(CFLAGS) -c read_pipe.c
fitsCmpScl.o:	 fitsCmpScl.c ; $(CC) $(CFLAGS) -c fitsCmpScl.c
fitsOutData.o:	 fitsOutData.c ;$(CC) $(CFLAGS) -c fitsOutData.c
fitsOutHdr.o:	 fitsOutHdr.c ; $(CC) $(CFLAGS) -c fitsOutHdr.c
timerstart.o:	 timerstart.c ; $(CC) $(CFLAGS) -c timerstart.c
timervalue.o:	 timervalue.c ; $(CC) $(CFLAGS) -c timervalue.c
