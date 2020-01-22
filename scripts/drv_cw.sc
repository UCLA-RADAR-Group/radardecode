#!/bin/csh
#
# drv_cw.sc fileNumfirstfile numfiles
#	..   
#	process cw information.. input setup info from $DRVSBCW file
# history:
# 29jun98 - started
# 25may98 - added 1st/last record option. will proc
# 13apr00 - added -n option to zerofill. no longer zero fills last buf.
#			just throws it away.
#
# set verbose
set basefile=`ex.awk $DRVSBCW fbase`
set inpfile=`ex.awk $DRVSBCW inpfile`
set bits=`ex.awk $DRVSBCW bits`
set fftlen=`ex.awk $DRVSBCW spcfftlen`
set numpol=`ex.awk $DRVSBCW numpol`
set firstrec=`ex.awk $DRVSBCW firstrec`
set lastrec=`ex.awk $DRVSBCW lastrec`
if ( "$firstrec" == "" ) then
set firstrec=1
endif
if ( "$lastrec" == "" ) then
set lastrec=2000000000
endif

set sufout=`ex.awk $DRVSBCW cwsufspc`
#
set parms=($*)              
if ( $#parms != 2 ) then
echo "Usage: drv_cw.sc firstfileNum numfile"
exit(0)
endif 
set fnum=$1
set numloop=$2
@ flast= $fnum + $numloop - 1
@ torotate= $fftlen / 2 
#
set hdr=${basefile}.hdrf${fnum}_$flast
set outfile1="${basefile}.${sufout}p1f${fnum}_$flast"
set outfile2="${basefile}.${sufout}p2f${fnum}_$flast"
rm -f $outfile1
rm -f $outfile2
#set
#setenv
touch $hdr
echo "drv_cw.sc START       : `date`" >> $hdr
while ( $numloop > 0 )
#     
#  
#
set fifoToUse=1
while ( $fifoToUse <= $numpol ) 
	set outfile="${basefile}.${sufout}p${fifoToUse}f$1_$flast"
	touch $outfile
	stripVme -h -o $fnum -n 1 -g "$firstrec $lastrec" < $inpfile |\
	unpriVtoi4 -b $bits -i $numpol -f $fifoToUse -d 3|\
	i4tor4|zerofill -n -b 8 -i $fftlen -o $fftlen|\
	fftfilter -d f -n $fftlen |power|avgdata -d r4 -g $fftlen -h -1|\
	rotate -i $fftlen -r $torotate >> $outfile
@ fifoToUse= $fifoToUse + 1
end
#
echo "Done with filenum ${fnum}"
@ fnum=$fnum + 1
@ numloop=$numloop - 1
end
echo "    length fft             : ${fftlen} " >> $hdr
echo "    numPol                 : ${numpol} ">> $hdr
echo "    input file             : ${inpfile} ">> $hdr
echo "    file1,filelast         : $1 $flast">> $hdr
echo "     rec1,reclast          : $firstrec $lastrec">> $hdr
echo "drv_cw.sc END         : `date`" >> $hdr
