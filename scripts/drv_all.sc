#!/bin/bash
#   17feb12   Move default scaling to drv_fft
#   05jul11.. Change default to not delete raw data, added default
#             scaling MCN
#   25may99.. testing radardecodeN .. with multiple samples/baud
#             and transpose by block.
#	do the entire processing step from dcd to  output maps
#   31may99 .. added  unpacked keyword.. input data already unpacked, 1 pol
# 	put the data on tape first with drv_tapetodisc.sc
#
#	drv_all.sc [-d -c] 1st_file numfiles
#
#	suffixes:   
#set verbose
	Usage="Usaage: drv_all.sc [-c] [-d]  firstFileNum numfiles" 
    shortOpts="n,d,c,h"
    a=`getopt -o $shortOpts -- "$@"`
	remfile=""
	copt=""
	while true ; do
        case $1 in
        -n)remfile=""; shift 1;;
        -d)remfile="-d"; shift 1;;
        -c)copt="-c"; shift 1;;
        -h) echo $Usage ; exit 1;;
        '') break;;
        *)  if [[ ${1:0:1} != "-" ]] ;then 
                break
		    else 
			 shift # illegal option
	        fi ;;
       esac
   done
#
drv_decode.sc $remfile $1 $2	
#
#  -d would delete file but we've left it off
#
drv_fft_pwr.sc $copt $1 $2
