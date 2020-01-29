# Radardecode

The goals of this repository are to facilitate the maintenance and improve the portability of the radar processing software developed at Arecibo.  The repository allows for the software to be installed and run outside of the Arecibo environment. 

# Installation procedure
- need "make", "csh", "gcc", perl 
- fftw library version 3 (3.3.8) : 
- %./configure --enable-float --prefix=${HOME}
- % make
- % make install
- % git clone https://github.com/UCLA-RADAR-Group/radardecode
- Specify installation directory in Makefile
- % make

# Test 
 In Ubuntu 18.10, CentOS Linux 7

# Basic usage

- for cw data to get the fft powers in two polarizations:
- %drv_cw.sc controlfile firstscan lastscan


- for delay-doppler data to get the images:
- %export DRVSB=controlfile OR sbdrv controlfile
- %drv_all.sc [-d -c] 1st_file numfiles
- %drv_mapmsc.sc {opts} file1 numfiles toavg map/row {newRowLen} {newColLen}{colOff}

# Task list

- [x] Most of this code was collected from multiple directories into a single location around 2005.  Current versions of the programs from /pkg/aosoft/common/bin/ and elsewhere should be integrated.
- [x] Some of this code probably relies on version 2 of the FFTW library.  Changes should be made to support version 3 of the FFTW library.   (branch and . work)
- [ ] A validation procedure should be added to enable testing of new installations.  

# Credits

Most of the software was initially written by Phil Perillat.  
