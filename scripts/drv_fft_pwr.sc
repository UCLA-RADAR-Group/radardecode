#!/bin/sh 
# \
if [ -x /usr/S2local/bin/tclsh8.3 ];then exec /usr/S2local/bin/tclsh8.3 $0 "$@" ; else exec /usr/bin/tclsh $0 "$@" ;fi
#
# drv_fft_pwr.sc [-d -c ] firstfile numfiles
#	..   
#	operate on decoded files.
#	1.transpose the data one block of rangebins*fftlen at a time
#   2.transform the data
#   3. compute the power
#   4 average the power incoherently
#   5.rotate so dc is in the center
#   6. output
#
#	for each file requested
# history:
# 12/16/92 - if fft > than number of points, zero fill. all other cases, 
#	     drop the last points
#
# 25may99  - converted to use radarfft. transpose done block at a time.
#		   - can not delete decode file from here
#	           input, fft, power,  repeat....
# 20jun99  - added pdata (packed data) to read correlator output. 
#			 0 --> data is float already. 1,2,4 -->data is char,short,int.
# 04aug99  - used test version radarfft
# 07aug99  - if dcdpacked, select the polarization of interest
#			 assume headers on on input file
#		     converted to be a tcl script
# 09feb12    print byteorder
# 17feb12    also run drv_scale so that we always make maps files MCN/PT
#	
#set verbose
global tcl_precision
set tcl_precision 17
#
set argi 0
set remfile 0
set copt ""
# we default to output power.. 4 byte floats
set smpBytesOut 4
if { [lsearch -exact $argv -c] >= 0 } {
	set copt "-c"
#    output is complex (2 floats = 8 bytes)
    set smpBytesOut 8
	incr argi
}
if { [lsearch -exact $argv -d] >= 0 } {
	set remfile=1
	incr argi
}
# i guess we ignore -d  :)
set remfile 0
set basefile [exec keyval.sc < $env(DRVSB) fbase]
set sufin    [exec keyval.sc < $env(DRVSB) sufdcd]
set sufout   [exec keyval.sc < $env(DRVSB) sufspc]
set numbins  [exec keyval.sc < $env(DRVSB) numbins]
set lenfft   [exec keyval.sc < $env(DRVSB) spcfftlen]
set lenkeep  [exec keyval.sc < $env(DRVSB) spcfftkeep]
set numpol   [exec keyval.sc < $env(DRVSB) numpol]
set poltouse [exec keyval.sc < $env(DRVSB) poltouse]
set xoff     [exec keyval.sc < $env(DRVSB) xoff]
set tmsmp    [exec keyval.sc < $env(DRVSB) tmsmp]
set dcdpacked [exec keyval.sc < $env(DRVSB) dcdpacked]
if { ("$dcdpacked" == "") || ($dcdpacked == 0) } {
	set dcdpacked 0
	set packFactor 1
} else {
	set packFactor $dcdpacked
}
#
if { ( $argc  - $argi) != 2  } {
  puts "Usage: drv_fft_pwr.sc -c firstfile numfile"
  exit 0
}
set fnum     [lindex $argv $argi]
set numloop  [lindex $argv [expr $argi + 1 ]]
set nfirst $fnum
#
# if xoff supplied we also need tmsmp
#
	set xoffOpt ""
	if { ("$xoff" != "") && ("$xoff" != 0) } {
		if { ($tmsmp == "") || ($tmsmp == 0) } {
           puts "You must specify tmsmp in drv.dat when using xoff"
		   exit 0
        }
		set xoffOpt "-x $xoff -t $tmsmp"
    } 
#
# 02nov10
# switched so freq swap done in radarfft, got rid of rotate program
#
# dc is now always lenkeep/2 +1 points from the left
# for old pfs routines (pre 02nov10)
# - dc was lenkeep/2 + 2 points if lenfft even and lenkeep odd
#   after selectpnts below..
#   All other combinations. dc= lenkeep/2 + 1 points from left
#
# The counting below is 1 based since selectpnts -f firstxx is 1 based
set dcPnt    [expr $lenfft / 2 + 1]
set firsttokeep [expr $dcPnt - $lenkeep/2]

#
for { set i 0 } { $i < $numloop } { incr i } {
#     
#  1.grab only the points within the file to use, throw out any at 
#	   end that aren't a multiple of fft len
#  2. xform and compute power
#  3. for each range, avg all the ffts from one file then write to output file
#
	set hdr       ${basefile}.hdrf${fnum}
	set hdrfile [open $hdr a+ ]
	set infile  "${basefile}.${sufin}f${fnum}"
    set outfile "${basefile}.${sufout}f${fnum}"
	set filesize [file size $infile]
#
#	packed decoder data
#
	if { $dcdpacked != 0 } {
		set reclen [exec od -A n -t u4 -N 4 -j 8 $infile]
		set hdrlen [exec od -A n -t u4 -N 4 -j 4 $infile]
		set datalen [expr $reclen - $hdrlen]
		if { $numpol == 2 } {
      	   set numtimpnts [expr round(((1.* $packFactor*$datalen)* $filesize)/ \
				( 16. *$numbins * $reclen))]
		} else {
      	   set numtimpnts [expr round(((1.*$packFactor*$datalen)*$filesize )/ \
			(8.*$numbins*$reclen))]
		}
    	set fftinfile [expr $numtimpnts / $lenfft]
		if { $fftinfile <  1  } {
 			incr fftinfile 
		}
    	set numtimpntsout [expr  $fftinfile * $lenfft ]
		puts $hdrfile "drv_fft_pwr.sc START       : [exec date]"
	  	if  { $numpol > 1 } {
		set retval [catch \
{exec  stripVme -h -q  < $infile | selectpnts -b $datalen -f $poltouse -s 2 | \
		radarfft $copt -l $lenfft -r $numbins -p $dcdpacked $xoffOpt | \
        selectpnts -b $smpBytesOut -f $firsttokeep -g $lenkeep -s $lenfft     > $outfile } msg ]
		puts "$msg"
		flush stdout
		} else {
			set retval [catch \
{exec  stripVme -h -q < $infile| \
		radarfft $copt -l $lenfft -r $numbins -p $dcdpacked $xoffOpt| \
        selectpnts -b $smpBytesOut -f $firsttokeep -g $lenkeep -s $lenfft     > $outfile } msg ]
		puts $msg
		flush stdout
		}
#
#	not packed data
#
	} else { 
		set numtimpnts [expr round(((1.*$packFactor) * $filesize) / \
				( 8.* $numbins ))]
		set fftinfile  [expr $numtimpnts / $lenfft]
		if { $fftinfile <  1 } {
			incr fftinfile
		}
	    set numtimpntsout [expr  $fftinfile * $lenfft ]
#  
	  	puts $hdrfile "drv_fft_pwr.sc START       : [exec date]"
#
#		puts "lenfft: $lenfft numbins:$numbins dcdpacked:$dcdpacked"
#		flush stdout
		set retval [catch \
 	    { exec radarfft $copt -l $lenfft -r $numbins -p $dcdpacked $xoffOpt < $infile | \
 		selectpnts -b $smpBytesOut -f $firsttokeep -g $lenkeep -s $lenfft     > $outfile } msg ]
		puts $msg
		flush stdout
	}
#
puts $hdrfile [exec printbyteorder "    fft byteorder          :"]
puts $hdrfile "    samples/rbin input     : $numtimpnts"
puts $hdrfile "    samples/rbin used      : $numtimpntsout"
puts $hdrfile "    length fft             : $lenfft " 
puts $hdrfile "    dcd packed data        : $dcdpacked "
	if { "$copt" != "" } {
puts $hdrfile "    cmplx ffts output      : $fftinfile*$numbins "
	} else {
puts $hdrfile "    ffts added incoherently: $fftinfile "
	}
puts $hdrfile "    xoff freq correction   : $xoff "
puts $hdrfile "    freq points kept       : $lenkeep "
puts $hdrfile "    input file             : $infile "
puts $hdrfile "    output file            : $outfile "
puts $hdrfile "drv_fft_pwr.sc END         : [exec date]"
#
	puts $hdrfile "Done with ${infile}"
	flush $hdrfile
	close $hdrfile
	incr fnum

}
#
#   Make an initial stab at the scaling.
#
exec drv_scale.sc $nfirst $numloop
