#                       1      2        3  
#drv_makefits.sc  file1 numfiles  {maps }
#
#   file1     first file to operate on
#   numfiles  numfiles to operate on
#   maps      if maps, then use the scaled maps, else the mapfiles
# ----------------
# set verbose
set usage="Usage drv_makefits.sc  rows cols {maps} "
set parms=($*)
if ( ( $#parms < 2 ) || ( $#parms > 3 ) ) then
	/bin/echo "$usage"
	exit -1
endif
set  maptouse=sufspc
if ( ( $#parms == 3 ) && ( $3 == "maps" ) ) then
	set  maptouse=sufscl
endif
set basefile=`ex.awk $DRVSB fbase`
set    sufin=`ex.awk $DRVSB $maptouse`
# echo "sufin: $sufin .. maptouse: $maptouse"
set  rngbins=`ex.awk $DRVSB numbins`
set  frqbins=`ex.awk $DRVSB spcfftkeep`
#
set       filenum=$1
set       numloop=$2
set       dname=`dirname $basefile`

# 
while ( $numloop > 0 ) 
#
	set  fname="${basefile}.${sufin}f$filenum"
	set  fitsName=$dname/Fits/f${filenum}.fit
	makefits -f -c $frqbins -r $rngbins < $fname > $fitsName 
@ filenum=$filenum + 1
@ numloop=$numloop - 1
end
