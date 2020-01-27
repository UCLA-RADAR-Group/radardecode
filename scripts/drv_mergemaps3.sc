#
# drv_mergemaps3.sc [-F] [-f fitsFilename] firstfile numfiles colcenOff newcollen newrnglen mapsperrow 
#	..   
#	merge maps together. use scaled maps files.
#   will take a subset of range, freq.. and will allow an offset in freq
#   from the center of the map.
#	
#   [-F] flip top to bottom. (needs to be first arg if used)
#   [-f fitsfilename] make a fits file rather than a float output map
#	firstfile... $infilexx 
#   numfiles ... to read in
#   colcenoff... offset center from input maps in pixels 
#	colmap   ... keep this many cols per map 
#	rowmap   ... keep this many rows per map 
#   files per row 
#
# 27may99 .. removed zoom, revmoed -r, added -f make fits file
#	
# set verbose
unset noclobber
unalias rm
unalias mv
set sufout="img"
set Flip=""
if ( "$1" == "-F") then
    set Flip=" -f "
	shift;
endif
set makFits=0
if ( "$1" == "-f") then
	set makFits=1
	set fitsName=$2
	shift;shift
endif
set maxhorpix=1100	
set basefile=`keyval.sc< $DRVSB fbase`
set sufin=`keyval.sc< $DRVSB sufscl`
set rngbins=`keyval.sc< $DRVSB numbins`
set frqbins=`keyval.sc< $DRVSB spcfftkeep`
set parms=($*)              
if (( $#parms != 6) && ($#parms != 7) ) then
 echo "Usage: drv_mergemaps3.sc [-f fitsname] 1stfile nfiles freqOffset newfrqlen newrnglen  mapsperrow
      exit(-1)
endif
#
set firstfile=$1
set numfiles=$2
set freqoffset=$3
set newfrqlen=$4
set newrnglen=$5
set mapsinrow=$6
@ lastfile= $firstfile + $numfiles - 1
set outfile="${basefile}.${sufout}${firstfile}.${lastfile}"
set tmpfile="tmp1.$$"
touch $tmpfile
set tmpcopy="tmpmap.$$"
#
#	copys subset of files requested then put file list in tmpfile
#
set fnum=$firstfile
@ lastfile= $firstfile + $numfiles - 1
@ bufsize= $frqbins * 4
@ rngskip=  ($rngbins - $newrnglen) / 2
@ frqstart=  ($frqbins - $newfrqlen) / 2 + 1 + $freqoffset
#
while ( $fnum <=   $lastfile )
set fname="${basefile}.${sufin}f${fnum}"
#
set tfname="${tmpcopy}.f${fnum}"
# 
dd if=$fname bs=$bufsize skip=$rngskip count=$newrnglen | \
selectpnts  -b 4  -f $frqstart -g $newfrqlen -s $frqbins  >  $tfname
echo "$tfname" >> $tmpfile
@ fnum+=1 
end
#
#	now call program to merge
#
mapsmerge -r $newrnglen -c $newfrqlen -h $mapsinrow -f $tmpfile -z> $outfile
#
# cleanup the files we created
#
rm -f $tmpfile
set fnum=$firstfile
@ lastfile= $firstfile + $numfiles - 1
while ( $fnum <=   $lastfile )
set tfname="${tmpcopy}.f${fnum}"
rm -f $tfname
@ fnum+=1 
end
#
# if we make a fits file.. do it here..
# we've added 1 pixel to the right of each map,
# we've added 1 pixel below each map
#
if ($makFits == 1) then
@ bigcol= $mapsinrow * ( $newfrqlen + 1 )
@ bigrow= ( ( $numfiles + $mapsinrow - 1 ) / $mapsinrow ) * ( $newrnglen + 1 )
    makefits $Flip -c $bigcol -r $bigrow < $outfile > $fitsName
	rm $outfile
    echo "fits file :$fitsName rng:$newrnglen frq:$newfrqlen"
else 
    echo"map in :$outfile rng:$newrnglen frq:$newfrqlen"
endif
