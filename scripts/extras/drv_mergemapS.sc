#
# drv_mergemapS.sc  firstfile numfiles mapsperrow zoom
#	..   
#	merge scaled maps together output is in the same units as maps files
#	
#	firstfile... $infilexx 
#       numfiles ... to read in
#       files per row 
#	zoom factor
#	
# set verbose
set maxhorpix=1100	
set basefile=`ex.awk $DRVSB fbase`
set sufin=`ex.awk $DRVSB sufscl`
set sufout=$sufin
set rngbins=`ex.awk $DRVSB numbins`
set frqbins=`ex.awk $DRVSB spcfftkeep`
set parms=($*)              
if ( $#parms != 4 ) then
      echo "Usage: drv_mergemapS.sc  firstfile numfile mapsperrow zoom"
      exit(-1)
endif
#
set firstfile=$1
set numfiles=$2
set mapsinrow=$3
set zoom=$4
@ lastfile= $firstfile + $numfiles - 1
set outfile="${basefile}.${sufout}${firstfile}.${lastfile}"
@ bigcol= $mapsinrow * ( $frqbins + 1 )
@ bigrow= ( ( $numfiles + $mapsinrow - 1 ) / $mapsinrow ) * ( $rngbins + 1 )
@ bigcolz= $bigcol * $zoom
@ bigrowz= $bigrow * $zoom
set tmpfile="tmp1.$$"
set tmpmap="tmp2.$$"
set tmpawk="tmp3.$$"
touch $tmpfile 
#
#	build the tmp file with filenames
#
set fnum=$firstfile
@ lastfile= $firstfile + $numfiles - 1
while ( $fnum <=   $lastfile )
echo "${basefile}.${sufin}f${fnum}" >> $tmpfile
@ fnum+=1 
end
#
#	now call program to merge
#
# set
mapsmerge -r $rngbins -c $frqbins -h $mapsinrow -f $tmpfile -z >$outfile
# rm -f $tmpfile

