#!/bin/tcsh
#
#	drv_mapavg.sc   firstfile numfiles filesavg filenumout {maps,map}
#	..   
#	average map or maps files together 
#
#	firstfile... $mapfn    1st input file
#   numfiles ... to read operate on
#	filesavg ... each output file is average of this many input files
#	1stfilenumout... mapfxx   where you probably want xx to be 100 ...
#           	will generate f100 f101 f102 ...numfiles/filesavg files
#       map,maps  .. use map or maps files. default is maps
#   output file names:
#		map(s)xxx  where we set xxx to start at a large number
#               map(s)xxx.fits  same, but made into fits for ease of viewing
# 2012feb17 added auto-fits MCP/PT
#
#set verbose
#unset noclobber #todospd leave it?
#unalias rm
set basefile=`ex.awk $DRVSB fbase`
set sufin=`ex.awk $DRVSB sufspc`
set rngbins=`ex.awk $DRVSB numbins`
set frqbins=`ex.awk $DRVSB spcfftkeep`
@   pntsmap= ${rngbins} * ${frqbins}
set tmpfile="${basefile}_tmp$$"
set parms=($*)              
if ( $#parms == 4 || $5 == "maps") then
   set sufin=`ex.awk $DRVSB sufscl`
else if ( $5 == "map") then
   set sufin=`ex.awk $DRVSB sufspc`
else
  echo "Usage:drv_mapavg.sc 1stfile numfile filestoavg 1stfilenumout (maps/map)"
  exit(-1)
endif
set sufout=`ex.awk $DRVSB sufspc`
set outbase="${basefile}.${sufin}f"
set outbase0="${basefile}.${sufout}f"
set inbase="${basefile}.${sufin}f"
set fnum=$1
set numfiles=$2
set filesavg=$3
set fnumout=$4
#
@ lastfile= $fnum + $numfiles
if ( $fnumout < $lastfile )  then
echo "Output files can't overwrite input files. change outfilenum"
echo "Usage: drv_mapavg.sc firstfile numfile filestoavg 1stfilenumout"
exit(0)
endif
#
@ numloop= ${numfiles} / ${filesavg}
#
# loop for the number of output maps
#
while ( $numloop > 0 )
rm -f $tmpfile
set outfile0="${outbase0}${fnumout}"
set outfile="${outbase}${fnumout}"
set fitsfile="${outbase}${fnumout}.fits"
cp ${basefile}.hdrf${fnum} ${basefile}.hdrsf${fnumout}
#     
#  1. push files to avg for 1 map to temp file
#
@ lastfile= $fnum + $filesavg - 1
while ( $fnum <= $lastfile )
  set infile="${inbase}${fnum}"
  cat ${infile} >> $tmpfile
@ fnum+=1
end 
#
#  2. now average and output to file
#
avgdata -d r4 -g $pntsmap -h $filesavg < $tmpfile > $outfile0
if ( $#parms == 4 || $5 == "maps") then
   drv_scale.sc $fnumout 1
endif
makefits -c $frqbins -r $rngbins < $outfile > $fitsfile
@ fnumout+=1
@ numloop-=1
end
rm -f $tmpfile
