#!/bin/csh
#                       1      2        3      4          5             6   7
#drv_mapmsc.sc {opts} file1 numfiles toavg map/row 
#                     {newRowLen} {newColLen}{colOff}
#
#   -s c1 c2   .. scale to sigmas using col1 thru col 
#   -S r1 r2   .. use row1 row2 for scaling.
#   -r bins    .. rotate by bins positive pushes to farther range gates.
#   file1     first file to operate on
#   numfiles  numfiles to operate on
#   toavg     files to average together
#   mapsperrow in mosaic
#   newRowLen (number of freqs to keep about new center)
#   newColLen (number of ranges to keep about the center)
#			  (note this is after rotation)
#   colOffset column offset for maps
# ----------------
#set verbose
set basefile=`ex.awk $DRVSB fbase`
set    sufin=`ex.awk $DRVSB sufscl`
set  rngbins=`ex.awk $DRVSB numbins`
set  frqbins=`ex.awk $DRVSB spcfftkeep`
set  smpperbaud=`ex.awk $DRVSB smpperbaud`
set  makemaps=0
set  newRowLen=$frqbins
set  newColLen=$rngbins
set  colOffset=0
set  torotate=0
set row1scale=1
set row2scale=$rngbins
set  hdr=$basefile.hdrmsc 
set usage="Usage drv_mapmsc.sc {-s col1 col2 -S row1 row2} file1 numFiles toAvg \n                                mapsPerrow {newRowLen} {newColLen} {colOffset} "
#
#	should we rescale the the maps files ??
#
echo "drv_mapmsc.sc START       :`date`" >>  $hdr
set doneopt=0
while ( $doneopt == 0 ) 
	if ( "$1" == "-s") then
	 	set col1scale=$2
		set col2scale=$3
		set makemaps=1
		shift;shift;shift
	else if ( "$1" == "-S") then
	 	set row1scale=$2
		set row2scale=$3
		set makemaps=1
		shift;shift;shift
	else if ( "$1" == "-r" ) then
		set torotate=$2
		shift;shift
	else
		set doneopt=1
	endif
end
#
set parms=($*)
if ( ($#parms < 4) || ($#parms > 7)) then
	/bin/echo "$usage"
	exit -1
endif
#
set          file1=$1
set       numfiles=$2
set     filesToAvg=$3
set     mapsPerRow=$4
# 
#	optional args
#
if ( $#parms > 4 ) then
	set newRowLen=$5
endif
if ( $#parms > 5) then
	set newColLen=$6
endif
if ( $#parms > 6) then
	set colOffset=$7
endif
#
# fits name   fmapsInrowxrows.fit 
#          if 1 file .. ffilenum

@ numRows= (($numfiles / $filesToAvg ) + $mapsPerRow - 1 ) / $mapsPerRow
set  bname=`basename $basefile`
set  dname=`dirname $basefile`
#
if ( $numfiles == 1 ) then
	set  fitsName=$dname/Fits/f${file1}.fit
else
	set  fitsName=$dname/Fits/f${numRows}x${mapsPerRow}.fit
endif
#
#  if we make the maps files, to it here
#
if ( $makemaps != 0 ) then
	drv_scale.sc $file1 $numfiles $col1scale $col2scale $row1scale $row2scale
endif
#
# if we rotate the maps files, do it 
#
if ( $torotate != 0 ) then
	drv_rotrange.sc $file1 $numfiles $torotate
endif
#
# if we avg maps.. store averages in $tempavg$$.n
#
if ( $filesToAvg > 1 ) then
	set fileNumOut=900
	drv_mapavg.sc $file1 $numfiles $filesToAvg $fileNumOut maps
else 
	set fileNumOut=$file1
endif
@ mapsInMos= $numfiles / $filesToAvg 
#
# now merge map create fits file
#
drv_mergemaps3.sc -f $fitsName $fileNumOut $mapsInMos $colOffset $newRowLen $newColLen $mapsPerRow
#
# log in $fbase.mschdr what we did
#
#echo "headerfile:$hdr"
echo "   basefile               : $basefile"         >> $hdr
echo "   fits filename          : $fitsName"        >> $hdr
echo "   1st file, numfiles     : $file1 $numfiles" >> $hdr
echo "   orig frq,range bins    : $frqbins $rngbins">> $hdr
echo "   kept frq,range bins    : $newRowLen $newColLen">> $hdr
echo "   frq bin offset,smp/baud: $colOffset $smpperbaud">> $hdr
echo "   rotate range bins      : $torotate" >> $hdr
echo "   maps avged             : $filesToAvg " >> $hdr
echo "   maps per row           : $mapsPerRow" >> $hdr
echo "drv_mapmsc.sc END         :" >>  $hdr
