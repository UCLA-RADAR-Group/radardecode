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
set remfile=0
if ( "$1" == "-d") then 
set remfile=1
shift
endif
set fnum=$1
set numloop=$2
set fbase=`ex.awk $DRVSB fbase`
set sufin=`ex.awk $DRVSB sufraw`
set sufout=`ex.awk $DRVSB sufdcd`
set codelen=`ex.awk $DRVSB codelen`
set bits=`ex.awk $DRVSB bits`
set smpperbaud=`ex.awk $DRVSB smpperbaud`
set numpol=`ex.awk $DRVSB numpol`
set pol=`ex.awk $DRVSB poltouse`
set bin1=`ex.awk $DRVSB bin1`
set numbins=`ex.awk $DRVSB numbins`
set dcdfftlen=`ex.awk $DRVSB dcdfftlen`
set codestodecode=`ex.awk $DRVSB codestodecode`
set removedc=`ex.awk $DRVSB removedc`
set codeprog=`ex.awk $DRVSB compcodeprog`
set cohavg=`ex.awk $DRVSB cohavg`
# set unpacked=`ex.awk $DRVSB unpacked`
set machine=`ex.awk $DRVSB machine`
if ( "$smpperbaud" == "" ) then
	set smpperbaud=1
endif
if ( "$removedc" == "" ) then
	set removedc=0
endif
if ( "$machine" == "" ) then
	set machine="ri"
endif
if ( "$codeprog" == "" ) then
	set codeprog="/usr/local/bin/comppncode"
endif
set decodeprog="radardecode"
while ( $numloop > 0 )
#	output to header file
set hdr=${fbase}.hdrf$fnum
set infile=${fbase}.${sufin}f$fnum
set outfile=${fbase}.${sufout}f$fnum
echo "drv_decode.sc START            :`date`" >>  $hdr
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
${codestodecode}
${removedc}
${cohavg}
${machine}
${codeprog}
Eof

if ( "$remfile" == "1" ) rm ${infile}
echo "Done with ${infile}"
chmod 0664 ${outfile}
#
#  append info to header file...
#
echo "    decoding progam            : $decodeprog ">> $hdr
echo "    1st range bin kept         : $bin1" >> $hdr
echo "    number of range bins kept  : $numbins" >> $hdr
echo "    samples per baud           : $smpperbaud" >> $hdr
echo "    numPol, pol Used           : $numpol,$pol" >> $hdr
echo "    fftlength used for decoding: $dcdfftlen" >> $hdr
echo "    remove Dc                  : $removedc"  >> $hdr
echo "    coherent average pre FFT   : $cohavg "  >> $hdr
echo "    machine                    : $machine "  >> $hdr
echo "    codeprog                   : $codeprog "  >> $hdr
echo "    maximum # codes to decode  : $codestodecode">> $hdr
echo "    input file                 : ${infile} " >> $hdr
echo "    output file                : ${outfile}" >> $hdr
echo "drv_decode.sc  END             :`date`" >>  $hdr
@ fnum=$fnum + 1
@ numloop=$numloop - 1
end
