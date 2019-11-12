# Radardecode

The goals of this repository are to facilitate the maintenance and improve the portability of the radar processing software developed at Arecibo.  The repository allows for the software to be installed and run outside of the Arecibo environment. 

# Installation procedure

- % git clone https://github.com/UCLA-RADAR-Group/radardecode
- Specify installation directory in Makefile
- % make

# Test 
 In Ubuntu 18.10
	need "make", "csh", "gcc", fftw library version 2.1.5 : ./configure --enable-float --prefix=${HOME},a ~/bin ~/lib folder

# Task list

- [ ] Most of this code was collected from multiple directories into a single location around 2005.  Current versions of the programs from /pkg/aosoft/common/bin/ and elsewhere should be integrated.
- [ ] Some of this code probably relies on version 2 of the FFTW library.  Changes should be made to support version 3 of the FFTW library.   (branch and . work)
- [ ] A validation procedure should be added to enable testing of new installations.  

- [ ] initial bin folder creation or a special folder . eliminate the manual step
- [ ] warnings when making (related to adding string.h stdlib.h)
- [ ] check which unpack.h is best and make changes in unp_pfs_pc_edt.c accordingly
# Credits

Most of the software was initially written by Phil Perillat.  
