#
#	remove files from current directory... use after copyfile.sc
#
#	rmfiles filestart numfiles 
#
set parms=($*)
if ( $#parms != 2 ) then
echo "Usage: rmfiles.sc firstfile numfiles"
exit(0) 
endif 
@ lastfile= $1 + $2 - 1
echo "removing files number $1 to $lastfile, yes to continue "
set ans=$<
if ( $ans != "yes") then
  echo "no files deleted"
  exit(-1)
endif
set fnum=$1
set numloop=$2
set outbase=$3
set inbase=`pwd`
#
while ( $numloop > 0) 
rm  ${inbase}/*f${fnum}
@ fnum=$fnum + 1
@ numloop=$numloop - 1
end
