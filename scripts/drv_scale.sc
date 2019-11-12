#!/bin/csh
#
# drv_scale.sc  firstfile numfiles  firstcol lastcol {firstrow lastrow}
#	..   
#	operate on map file, remove avg and scale to sigma
#
#	
#	firstfile... $infilexx 
#       numfiles ... to read in
#set verbose
set basefile=`ex.awk $DRVSB fbase`
set sufin=`ex.awk $DRVSB sufspc`
set sufout=`ex.awk $DRVSB sufscl`
set numbins=`ex.awk $DRVSB numbins`
set numfreq=`ex.awk $DRVSB spcfftkeep`
#echo "drvsb:$DRVSB, basefile:$basefile"
#exit(0)
#
set firstrow=1
set lastrow=$numbins
set parms=($*)              
if ( $#parms == 6 ) then
	set fistrow=$5 
	set lastrow=$6 
else if ( $#parms != 4 ) then
echo "Usage: drv_scale.sc firstfile numfile firstcolumn lastcolumn {firstRow lastRow}"
exit(0)
endif
set fnum=$1
set numloop=$2
set firstcol=$3
set lastcol=$4
 
set tmpfile=tmp$$
#
while ( $numloop > 0 )
#     
#  1.grab only the points within the file to use, throw out any at 
#	   end that aren't a multiple of fft len
#  2. xform and compute power
#  3. for each range, avg all the ffts from one file then write to output file
#
set hdr=${basefile}.hdrf${fnum}
set infile="${basefile}.${sufin}f${fnum}"
set outfile="${basefile}.${sufout}f${fnum}"
#  
echo "drv_scale.sc   START       : `date`" >> $hdr
#
scaletosigma -r $numbins -c $numfreq -f $firstcol -l $lastcol -F $firstrow \
			 -L $lastrow -t $tmpfile < ${infile} > ${outfile}
#
set avg=`ex.awk $tmpfile avg`
set sig=`ex.awk $tmpfile sig`
echo "    average removed        : ${avg}"  >> $hdr
echo "    1 sigma scaling        : ${sig}" >> $hdr
echo "    1st/last frqbin        : ${firstcol} ${lastcol}" >> $hdr
echo "    1st/last rangebin      : ${firstrow} ${lastrow}" >> $hdr
echo "drv_scale.sc END           : `date`" >> $hdr
#
echo "Done with ${infile}"
@ fnum=$fnum + 1
@ numloop=$numloop - 1
end
rm -f $tmpfile
