# Radardecode

This repository contains a portable and compact version of the radar processing software developed at Arecibo.  Our goals are threefold:

1. to provide a self-contained version of the software that can be easily installed outside of Arecibo's computing environment.  The code base is an order of magnitude smaller than the aosoft code base.  
2. to improve the portability of the software.  We have introduced modifications that allow the code to compile and run on Linux and MacOS.  
3. to encourage development and facilitate maintenance.  The GitHub repository allows users to easily compare versions and create pull requests for bug fixes or new features.  


# Installation procedure

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

    OR For MacOS
    - sudo port install fftw-3-single
    - /opt/local/include/fftw3.h

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

# Credits

Most of the software was written by Phil Perillat.  This repository was created by Jean-Luc Margot and uploaded to a CVS server in 2005 and to GitHub in 2019.  It was brought back in sync with the current revision (r2007) of aosoft by Sanjana Prabhu Desai and Jean-Luc Margot in 2020.
