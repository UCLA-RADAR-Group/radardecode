# Radardecode

The goals of this repository are to facilitate the maintenance and improve the portability of the radar processing software developed at Arecibo.  The repository allows for the software to be installed and run outside of the Arecibo environment. 

# Installation procedure

prerequisites:  
- need "make", "csh", "gcc", perl  
  
- Also need fftw library version 3 (3.3.8) :  
    steps from source:  
    - ./configure --enable-float --prefix=${HOME}  
    -  make  
    -  make install  
  
    OR For Ubuntu :  
    - sudo apt-get install fftw3    
    - sudo apt-get install fftw3-dev    
  
    - /usr/lib/libfftw3f.a  
    - /usr/lib/libfftw3f.so  
    - /usr/include/fftw3.h  
  
    OR For CentOS :  
    - sudo yum install fftw3    
    - sudo yum install fftw3-devel  
  
    - /lib64/libfftw3f.a    
    - /lib64/libfftw3f.so.3  
    - /usr/include/fftw3.h  
  
- git clone git@github.com:UCLA-RADAR-Group/radardecode.git  
    make in radardecode folder

#updated according to:  
https://github.com/UCLA-RADAR-Group/aosoft/commit/fc8dec2e3263f7588f930bfde9a1ddfedb01f753  

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
- [x] automatically use/install fftw3 (updated instructions)
- [x] A validation procedure should be added to enable testing of new installations  

# Credits

Most of the software was initially written by Phil Perillat.  
