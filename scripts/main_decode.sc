#
#
#	decode radar data. 
#	input from tape (may also work from disc.. using dd... check it out)
#	unpack, decode, select a group of continuous channels,
#	and write them out to a file... 
#
# history:
#       6/17/91.. added env variable $decodesky. 
#               if set... will use sky ap decodeing
#	          program.
#   25may99 - added samples/baud.. note. 1st channel and channels to keep
#			  now have units of samples rather than bauds.
#     4aug99 - changes for -m cbr ri unpacked, -p numPol poltouse
#
#	set some variables
#
#set verbose
#set echo
#	variables used
#	inputfile	inputfile name
#	outputfile	outputfile name
#	codelen		!length of code to use
#	bits		number of bits in sampling
#   smpperbaud  samplesper baud
#	numpol		# of polarizations to use 1,2
#	pol             if numpol=2, then must be 1 or 2, else 1
#   bin1           First channel to keep..
#	numbins         to keep. 	
#	fftlen		length fft to use in decoding
#	numcodes	to process
#	removeDc
#	machinetype    ri,cbr,pfs,bytes,floats
#   compcodeprog   /home/pfs/bin/comppncode
#	
set debugopt=""
set decodeprog="radardecode"
set validbits=(1 2  4 8 12)
# sneak in 13 as a valid code since barker code 13 is used
set validcodes=(1 3 7 13 15 31 63 127 255 511 1023 2047 4095 8191 16383 32767 65535 131071)
set validlenfft=(2 4 8 16 32 64 128 256 512 1024 2048 4096 8192 16384 32768                      65536 131072 262144 524288 1048576)
#
#	get input filename
echo "Enter input filename"
set inputfile=$<   
if (!(-r $inputfile)) then 
   echo "can't read from $inputfile"
   goto done
endif #
#	get output filename
#
echo "Enter output filename"
set outputfile=$<  
#
#	get codelen
#
echo "Enter codelen"
set codelen=$<
unset gotit
foreach var ($validcodes)
	if ( `expr $var = $codelen` ) then    
           set gotit
	   break 
	endif 
end
if (!($?gotit)) then
   	echo "illegal code $codelen"
   	goto done
endif
#
#	get # of bits
#
echo "Enter # of bits for sampling"
set bits=$<
unset gotit
foreach var ($validbits)
	if ( `expr $var = $bits` ) then    
           set gotit
	   break 
	endif 
end
if (!($?gotit)) then
   	echo "illegal number of bits $bits requested"
   	goto done
endif
#
#	samples/baud
#
echo "Enter # of samples per baud"
set smpperbaud=$<
@ codelenused= $codelen * $smpperbaud 
#
# 	get number of polarizations
#
echo "enter number of polarizations (1,2)"
set numpol=$<
if ( `expr $numpol = 1 `) then
    set pol=$<
else 
    echo "Enter polarization to decode (1,2)"
	set pol=$<
#	if ( `expr (($pol != 1) & ($pol != 2)) `) then
#	   echo "illegal pol to use $pol"
#	   goto done
#	endif
endif
#
# 	get 1st range bin to save
#
echo "enter 1st range bin to save (start counting at 1)"
set chan1=$<
if ( `expr  $chan1 \< 1  `) then
	   echo "illegal 1st channel  $chan1"
	   goto done
endif
#
# 	get number of channels to save
#
echo "enter number of range bins to save (starting at $chan1)"
set numchan=$<
if ( `expr \( $numchan \< 1 \) \| \( $numchan \> $codelenused \) ` ) then
	   echo "illegal number of channels to store $numchan"
	   goto done
endif
#
#	get fftlen
#
echo "Enter length for fft (power of 2)"
set fftlen=$<
unset gotit
foreach var ($validlenfft)
	if ( `expr $var = $fftlen` ) then    
           set gotit
	   break 
	endif
end
if (!($?gotit)) then
   	echo "illegal fftlen $fftlen"
   	goto done
endif
#
#	records to process
#
echo "Enter number of codes to decode"
set numcodes=$<
#
#	remove dc    
#
echo "Remove dc (0,1)"
set removedc=$<
if ( $removedc == 0) then
	set rmdc=""
else
	set rmdc="-r"
endif
#echo "removedc: $rmdc"
#
#       get number of codes to incoherently  avg
#
echo "Enter number of codes to coherently add (1..)"
set cohavg=$<
    if ( `expr $cohavg \<= 0 `) then
       echo "illegal number of coherent additions: $cohavg "
       goto done
    endif
#
#
#	machine type
#
echo "machine type (ri,cbr,pfs,bytes,floats)"
set machinetype=$<
if ( $machinetype == 0) then
	set machinetype="ri"
else
	set machinetype="$machinetype"
endif
echo "machinetype: $machinetype"
#
#	code program
#
echo "codeprog"
set codeprog=$<
echo "codeprog: $codeprog"
#
set numffts=`expr 1 + $numcodes \* $codelenused / \( $fftlen - $codelenused + 1 \) `
@ codelen2= $codelen * 2
@ discsize=$numcodes * $numchan * 8
echo "doing $numffts ffts to decode $numcodes codes"
echo "disc file will be $discsize bytes"
#
#	now the work begins
#	
#  line 1. remove unwanted polarization if there
#  line 2. unpack data convert to real*4
#  line 3. decode
#  line 4. compute power
#  line 5. incoherentyl avg power to 1 code
#  line 6. convert to real *8 for analyz.
#  set pol to 1 or 2 for pol 1 or 2. if only 
echo " # pol=${numpol},using pol:${pol}. decode prog:${decodeprog}"
echo "start:`date`."
# some verbosity added by jlm
echo $decodeprog  -b $bits -c $codelen -l $fftlen -n $numcodes -o .5 -s $smpperbaud  $rmdc $debugopt -m $machinetype -p $numpol $pol -a $codeprog
#if ( `expr  \( $numpol = 2 \) \& \( $machinetype = "ri" \) ` ) then    
#        dd if=$inputfile bs=64k | \
#	selectpnts -b 4 -f $pol -s $numpol | \
#$decodeprog -b $bits -c $codelen -l $fftlen -n $numcodes -o .5 -s $smpperbaud    $rmdc -a $codeprog |\
#	selectpnts -b 8 -f $chan1 -g $numchan -s $codelenused > $outputfile
#
# jlm changes ri dual-pol option to cohavg option
# ri dual-pol data no longer supported
# if you really want it, uncomment previous 5-line block and comment out next 5-line block
if (`expr  \( $cohavg > 1 \)`) then 
        dd if=$inputfile bs=64k | \
 $decodeprog  -b $bits -c $codelen -l $fftlen -n $numcodes -o .5 -s $smpperbaud  $rmdc $debugopt -m $machinetype -p $numpol $pol -a $codeprog |\
	avgdata -d r4 -g $codelen2 -h $cohavg |\
 	selectpnts -b 8 -f $chan1 -g $numchan -s $codelenused > $outputfile
else
        dd if=$inputfile bs=64k | \
 $decodeprog  -b $bits -c $codelen -l $fftlen -n $numcodes -o .5 -s $smpperbaud  $rmdc $debugopt -m $machinetype -p $numpol $pol -a $codeprog |\
 	selectpnts -b 8 -f $chan1 -g $numchan -s $codelenused > $outputfile
endif
echo "end  :`date`"



done:

