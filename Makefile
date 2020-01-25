#
#	Make one or more programs from the source
#       executables will be placed in GLOBDIR
#
# HOME=/home/pfs
SHELL=/bin/csh
GLOBDIR=$(HOME)/bin
CFLAGS=-O4 -I. -I${HOME}/include  -D_LARGEFILE_SOURCE -D_FILE_OFFSET_BITS=64 -DLINUX
FFLAGS=-O
LPATH=$(HOME)/lib
CC=gcc

all: libunpack scripts radardecode rotate radarfft radarcplxfft selectpnts comppncode compdsncode compbarkercode scaletosigma makefits mapsmerge avgdata stripVme unpriV unpriVtoi4 i4tor4 zerofill fftfilter power power_ao convdatatype

FORCE:
	
scripts: FORCE
	chmod u+w scripts/*
	cp scripts/*.sc $(GLOBDIR)
	cp scripts/printbyteorder $(GLOBDIR)
	cp scripts/*.awk $(GLOBDIR)

libunpack:     unp_pfs_pc_edt.c; $(CC) $(CFLAGS) -c unp_pfs_pc_edt.c -o libunpack.o

radardecode: radardecode.c fftwAo.o unpriV_f4.o read_pipe.o timerstart.o timervalue.o
	$(CC) $(CFLAGS) radardecode.c fftwAo.o unpriV_f4.o read_pipe.o timerstart.o timervalue.o -L$(LPATH) libunpack.o -lfftw -lm -o $(GLOBDIR)/radardecode
#
rotate: rotate.c read_pipe.o
	$(CC) $(CFLAGS) rotate.c read_pipe.o -lm -o $(GLOBDIR)/rotate

rotate: rotate.c read_pipe.o
	$(CC) $(CFLAGS) rotate.c read_pipe.o -lm -o $(GLOBDIR)/rotate

radarfft: radarfft.c fftwAo.o read_pipe.o
	$(CC) $(CFLAGS) radarfft.c fftwAo.o read_pipe.o -L$(LPATH) -lfftw -lm -o $(GLOBDIR)/radarfft

radarcplxfft: radarcplxfft.c 
	$(CC) $(CFLAGS) radarcplxfft.c fftwAo.o read_pipe.o -L$(LPATH) -lfftw -lm -o $(GLOBDIR)/radarcplxfft

selectpnts: selectpnts.c read_pipe.o
	$(CC) $(CFLAGS) selectpnts.c read_pipe.o -lm -o $(GLOBDIR)/selectpnts

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


avgdata: avgdata.c read_pipe.o to_lowercase.o
	$(CC) $(CFLAGS) avgdata.c read_pipe.o to_lowercase.o -lm -o $(GLOBDIR)/avgdata

stripVme: stripVme.c read_pipe.o hdrLib.h
	$(CC) $(CFLAGS) stripVme.c read_pipe.o -o $(GLOBDIR)/stripVme
unpriV: unpriV.c read_pipe.o unpriV_i4.o unpriV_f4.o unpriV_i2.o unpriV_d8.o 
	$(CC) $(CFLAGS) unpriV.c read_pipe.o unpriV_i4.o unpriV_f4.o unpriV_i2.o unpriV_d8.o -o $(GLOBDIR)/unpriV

unpriVtoi4: unpriVtoi4.c read_pipe.o unpriV_i4.o
	$(CC) $(CFLAGS) unpriVtoi4.c read_pipe.o unpriV_i4.o -o $(GLOBDIR)/unpriVtoi4

i4tor4: i4tor4.c
	$(CC) $(CFLAGS) i4tor4.c -lm -o $(GLOBDIR)/i4tor4

zerofill: zerofill.c read_pipe.o
	$(CC) $(CFLAGS) zerofill.c read_pipe.o -lm -o $(GLOBDIR)/zerofill

fftfilter: fftfilter.c read_pipe.o
	$(CC) $(CFLAGS) fftfilter.c read_pipe.o -L$(LPATH) -lfftw3f -lm -o $(GLOBDIR)/fftfilter

power: power.c read_pipe.o 
	$(CC) $(CFLAGS) power.c read_pipe.o -lm -o $(GLOBDIR)/power

power_ao: power_ao.c read_pipe.o 
	$(CC) $(CFLAGS) power_ao.c read_pipe.o -lm -o $(GLOBDIR)/power_ao

convdatatype: convdatatype.c 
	$(CC) $(CFLAGS) convdatatype.c read_pipe.o to_lowercase.o -lm -o $(GLOBDIR)/convdatatype

fftwAo.o:	 fftwAo.c ;     $(CC) $(CFLAGS) -c fftwAo.c
writen.o:	 writen.c ;     $(CC) $(CFLAGS) -c writen.c
unpriV_f4.o:	 unpriV_f4.c ;  $(CC) $(CFLAGS) -c unpriV_f4.c
unpriV_i4.o:	 unpriV_i4.c ;  $(CC) $(CFLAGS) -c unpriV_i4.c
unpriV_i2.o:	 unpriV_i2.c ;  $(CC) $(CFLAGS) -c unpriV_i2.c
unpriV_d8.o:	 unpriV_d8.c ;  $(CC) $(CFLAGS) -c unpriV_d8.c
read_pipe.o:	 read_pipe.c ;	$(CC) $(CFLAGS) -c read_pipe.c
fitsCmpScl.o:	 fitsCmpScl.c ; $(CC) $(CFLAGS) -c fitsCmpScl.c
fitsOutData.o:	 fitsOutData.c ;$(CC) $(CFLAGS) -c fitsOutData.c
fitsOutHdr.o:	 fitsOutHdr.c ; $(CC) $(CFLAGS) -c fitsOutHdr.c
timerstart.o:	 timerstart.c ; $(CC) $(CFLAGS) -c timerstart.c
timervalue.o:	 timervalue.c ; $(CC) $(CFLAGS) -c timervalue.c
timervalue.o:	 timervalue.c ; $(CC) $(CFLAGS) -c timervalue.c
to_lowercase.o:	 to_lowercase.c ; $(CC) $(CFLAGS) -c to_lowercase.c
