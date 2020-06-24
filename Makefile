#
#       all scripts and executables will be placed in GLOBDIR
#       compilation and link flags are defined in src/Makefile
#
SHELL=/bin/csh
CC=gcc
GLOBDIR=$(HOME)/bin
export

all: scripts src 

FORCE:
	
scripts: FORCE
	chmod u+w scripts/*
	cp scripts/*.sc $(GLOBDIR)
	cp scripts/printbyteorder $(GLOBDIR)

src: FORCE
	cd src && $(MAKE)

tests:
	cd tests; ./validate.sh

clean:
	cd src && $(MAKE) clean
