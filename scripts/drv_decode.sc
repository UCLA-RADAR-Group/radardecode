#!/bin/csh
unset noclobber
#  25may99 testing out radardecodeN with multiple samples/baud
#
#	driver program for main_decode.sc
#	drv_decode.sc [-d]  filestart numfiles
#	-d remove input files when done
#	parm1 .. 1st file
#	parm2 .. num of files...
#
#	note only setup to work with 1 polarization... 
#       history:
#	3/5/92 . chmod .dcd file to 0444 so we can't accidently delete it.
#   4aug99 .. mods for -m cbr -p numpol poltouse
#set verbose
#set echo
set decodeprog_sng="radardecode"
set decodeprog_thr="radardecode_thr"
set set decodeprog=$decodeprog_sng
#
set remfile=0
if ( "$1" == "-d") then 
set remfile=1
shift
endif
set fnum=$1
set numloop=$2
set fbase=`keyval.sc< $DRVSB fbase`
set sufin=`keyval.sc< $DRVSB sufraw`
set sufout=`keyval.sc< $DRVSB sufdcd`
set codelen=`keyval.sc< $DRVSB codelen`
set bits=`keyval.sc< $DRVSB bits`
set smpperbaud=`keyval.sc< $DRVSB smpperbaud`
set numpol=`keyval.sc< $DRVSB numpol`
set pol=`keyval.sc< $DRVSB poltouse`
set bin1=`keyval.sc< $DRVSB bin1`
set numbins=`keyval.sc< $DRVSB numbins`
set dcdfftlen=`keyval.sc< $DRVSB dcdfftlen`
set curval=1
while ( $curval < $dcdfftlen )
@ curval=$curval * 2
end
set dcdfftlen=$curval
set numthreads=`keyval.sc< $DRVSB numthreads`
if ( "$numthreads" == "") then 
	set numthreads=1
endif
if ( $numthreads > 1 ) then
    set decodeprog=$decodeprog_thr
endif

set codestodecode=`keyval.sc< $DRVSB codestodecode`
set removedc=`keyval.sc< $DRVSB removedc`
set codetype=`keyval.sc< $DRVSB codetype`
set cohavg=`keyval.sc< $DRVSB cohavg`
if ( $cohavg == 0 ) then
	set cohavg=1
endif
# set unpacked=`keyval.sc< $DRVSB unpacked`
set machine=`keyval.sc< $DRVSB machine`
if ( "$smpperbaud" == "" ) then
	set smpperbaud=1
endif
if ( "$removedc" == "" ) then
	set removedc=0
endif
if ( "$machine" == "" ) then
	set machine="ri"
endif
if ( "$codetype" == "" ) then 
	set codetype=aopnc
endif
#
while ( $numloop > 0 )
#	output to header file
set hdr=${fbase}.hdrf$fnum
set infile=${fbase}.${sufin}f$fnum
set outfile=${fbase}.${sufout}f$fnum
#
#  append info to header file...
#
echo "drv_decode.sc START            :`date`" >>  $hdr
set cpuName=`uname -n`
printbyteorder "    decoding byteorder         :" >> $hdr
echo "    cpu                        : $cpuName">> $hdr
echo "    decoding progam            : $decodeprog ">> $hdr
echo "    1st range bin kept         : $bin1" >> $hdr
echo "    number of range bins kept  : $numbins" >> $hdr
echo "    samples per baud           : $smpperbaud" >> $hdr
echo "    numPol, pol Used           : $numpol,$pol" >> $hdr
echo "    fftlength used for decoding: $dcdfftlen" >> $hdr
echo "    # of threads for   decoding: $numthreads" >> $hdr
echo "    remove Dc                  : $removedc"  >> $hdr
echo "    coherent average per FFT   : $cohavg "  >> $hdr
echo "    machine                    : $machine "  >> $hdr
echo "    codetype                   : $codetype "  >> $hdr
echo "    maximum # codes to decode  : $codestodecode">> $hdr
echo "    input file                 : ${infile} " >> $hdr
echo "    output file                : ${outfile}" >> $hdr
#
main_decode.sc <<Eof
${infile}
${outfile}
${codelen}
${bits}
${smpperbaud}
${numpol}    
${pol}    
${bin1}
${numbins}
${dcdfftlen}
${numthreads}
${codestodecode}
${removedc}
${cohavg}
${machine}
${codetype}
Eof

if ( "$remfile" == "1" ) /bin/rm ${infile}
echo "Done with ${infile}"
chmod 0664 ${outfile}
echo "drv_decode.sc  END             :`date`" >>  $hdr
@ fnum=$fnum + 1
@ numloop=$numloop - 1
end
