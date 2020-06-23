#
#	Make one or more programs from the source
#       executables will be placed in GLOBDIR
#
SHELL=/bin/csh
GLOBDIR=$(HOME)/bin
CFLAGS=-O4 -I. -I./include -I${HOME}/include  -D_LARGEFILE_SOURCE -D_FILE_OFFSET_BITS=64 -DLINUX -I/opt/local/include
FFLAGS=-O
LFLAGS=-L$(HOME)/lib -L/opt/local/lib
CC=gcc

all: scripts src 

FORCE:
	
scripts: FORCE
	chmod u+w scripts/*
	cp scripts/*.sc $(GLOBDIR)
	cp scripts/printbyteorder $(GLOBDIR)

src: FORCE
	cd src; make

tests:
	cd validation; ./validate.sh

