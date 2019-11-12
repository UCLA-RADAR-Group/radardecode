#!/bin/csh
#   25may99.. testing radardecodeN .. with multiple samples/baud
#             and transpose by block.
#	do the entire processing step from dcd to  output maps
#   31may99 .. added  unpacked keyword.. input data already unpacked, 1 pol
# 	put the data on tape first with drv_tapetodisc.sc
#
#	drv_all.sc [-n] 1st file numfiles
#
#	suffixes:   
#set verbose
set remfile="-d"
if ( "$1" == "-n") then
set remfile=""
shift
endif
#
drv_decode.sc $remfile $1 $2	
#
#  -d would delete file but we've left it off
#
drv_fft_pwr.sc $1 $2 
