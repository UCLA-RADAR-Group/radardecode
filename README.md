# Radardecode

This repository contains a portable and compact version of the radar processing software developed at the Arecibo Observatory.  Our goals are threefold:

1. to provide a self-contained version of the software that can be easily installed outside of Arecibo's computing environment.  The code base is an order of magnitude smaller in size than the aosoft code base.  
2. to improve portability.  We introduced modifications that allow compilation and execution on both Linux and MacOS.  
3. to encourage development and facilitate maintenance.  This repository allows users to easily create branches and create pull requests for bug fixes or new features.  


# Requirements

- Compilation and execution require bash, csh, tcsh, make, gcc, Perl (for printbyteorder)
  
- FFTW (version >= 3.3.8)

    - Install with your package manager:

       - RedHat/CentOS:   
       (include file at /usr/include/, library at /usr/lib64/)    
       ```sh
       sudo yum install fftw fftw-devel  
       ```
    
       - Debian/Ubuntu:  
       (include file at /usr/include/, library at /usr/lib/)  
       ```sh
       sudo apt-get install libfftw3-3 libfftw3-dev  
       ```
    
       - MacOS:  
       (include file at /opt/local/include/, library at /opt/local/lib/)  
       ```sh
       sudo port install fftw-3-single  
       ```
    
    - Install from source:  
       ```sh
       wget http://www.fftw.org/fftw-3.3.8.tar.gz  
       tar xvf fftw-3.3.8.tar.gz  
       ./configure --enable-float  
       make; make install
       ```
  

# Installation procedure

- Download repository:  

  With https:  
  ```sh
  git clone https://github.com/UCLA-RADAR-Group/radardecode.git  
  cd radardecode  
  ```
  
  With ssh:  
  ```sh
  git clone git@github.com:UCLA-RADAR-Group/radardecode.git  
  cd radardecode  
  ```

- Specify the target location for scripts and executables:  
  Edit the value of `GLOBDIR` in the top-level [Makefile](Makefile) if necessary (default is `$(HOME)/bin`)
  
- Compile:  
  ```sh
  make  
  ```

- Run tests:
  ```sh
  make tests  
  ```

- Successfully tested on CentOS 7.3.1611/7.5.1804, Ubuntu 12.04.5/16.04.5/20.04, MacOS 10.11.6/10.15.5.  

# Basic usage

- To process continuous wave data into power spectra:  
  ```sh
  drv_cw.sc controlfile firstscan lastscan  
  [e.g.,] drv_cw.sc drvcw.dat 1 1  
  ```

- To process delay-doppler data into images:   
  ```bash
  export DRVSB=controlfile  
  drv_all.sc [-d -c] 1st_file numfiles    
  [e.g.,] drv_all.sc 1 1   
  drv_mapmsc.sc {opts} file1 numfiles toavg map/row {newRowLen} {newColLen}{colOff}  
  ```

  
# Credits

Most of the software was written by Phil Perillat.  This repository was created by Jean-Luc Margot and uploaded to a CVS server circa 2005 and to GitHub in 2019.  It was brought back in sync with the current revision (r2007) of aosoft by Sanjana Prabhu Desai and Jean-Luc Margot in 2020.

This version is based on aosoft GitHub version  
https://github.com/UCLA-RADAR-Group/aosoft/commit/fc8dec2e3263f7588f930bfde9a1ddfedb01f753  
