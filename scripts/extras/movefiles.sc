#
#	movefiles filestart numfiles outdirectory
set parms=($*)
if ( $#parms != 3 ) then
echo "Usage: movefiles.sc firstfile numfiles outputdirectory"
exit(0) 
endif 
set fnum=$1
set numloop=$2
set outbase=$3
set inbase=`pwd`
#
while ( $numloop > 0) 
mv  ${inbase}/*f${fnum} $outbase
@ fnum=$fnum + 1
@ numloop=$numloop - 1
end
