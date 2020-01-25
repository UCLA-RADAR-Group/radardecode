#!/bin/csh
#
# drv_scale.sc  firstfile numfiles  firstcol lastcol {firstrow lastrow}
#	..   
#	operate on map file, remove avg and scale to sigma
#
# <mcn001> Correct spelling of firstrow in arg list  2002 June 19
# 2012feb09  print byteorder
# 2012feb17  set default cols to 1..n/5
#	
#	firstfile... $infilexx 
#       numfiles ... to read in
#set verbose
set basefile=`keyval.sc< $DRVSB fbase`
set sufin=`keyval.sc< $DRVSB sufspc`
set sufout=`keyval.sc< $DRVSB sufscl`
set numbins=`keyval.sc< $DRVSB numbins`
set numfreq=`keyval.sc< $DRVSB spcfftkeep`
#echo "drvsb:$DRVSB, basefile:$basefile"
#exit(0)
#
set firstrow=1
set lastrow=$numbins
set firstcol=1
@ lastcol = $numfreq / 5
if ($lastcol == 0) set lastcol=1
set parms=($*)              
if ( $#parms == 6 ) then
# <mcn001>
	set firstrow=$5 
	set lastrow=$6 
   set firstcol=$3
    set lastcol=$4
else if ($#parms == 4) then
# 20120217 MCN/PT
    set firstcol=$3
    set lastcol=$4
else if ( $#parms != 2 ) then
echo "Usage: drv_scale.sc firstfile numfile firstcolumn lastcolumn {firstRow lastRow}"
exit(0)
endif
set fnum=$1
set numloop=$2
 
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
set avg=`keyval.sc< $tmpfile avg`
set sig=`keyval.sc< $tmpfile sig`
printbyteorder "    scaling byteorder      :" >> $hdr
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
/bin/rm -f $tmpfile
