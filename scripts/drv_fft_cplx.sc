#!/usr/bin/tclsh
#
# drv_fft_cplx.sc [-d] firstfile numfiles
#	..   
#	operate on decoded files.
#	1.transpose the data one block of rangebins*fftlen at a time
#       2.transform the data
#       6. output
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
# 23apr01  - jlm adapted to radarcplxfft
#          - eliminated rotate (frequency swap is done in radarcplxfft)
#set verbose
global tcl_precision
set tcl_precision 17
#
set argi 0
set remfile 0
if { "[lindex $argv 0 ]" == "-d" } {
	set remfile=1
	incr argi
}
set remfile 0
set basefile [exec ex.awk $env(DRVSB) fbase]
set sufin    [exec ex.awk $env(DRVSB) sufdcd]
set sufout   [exec ex.awk $env(DRVSB) sufslc]
set numbins  [exec ex.awk $env(DRVSB) numbins]
set lenfft   [exec ex.awk $env(DRVSB) spcfftlen]
set lenkeep  [exec ex.awk $env(DRVSB) spcfftkeep]
set numpol   [exec ex.awk $env(DRVSB) numpol]
set poltouse [exec ex.awk $env(DRVSB) poltouse]
set xoff     [exec ex.awk $env(DRVSB) xoff]
set dcdpacked [exec ex.awk $env(DRVSB) dcdpacked]
if { ("$dcdpacked" == "") || ($dcdpacked == 0) } {
	set dcdpacked 0
	set packFactor 1
} else {
	set packFactor $dcdpacked
}
#
if { ( $argc  - $argi) != 2  } {
  puts "Usage: drv_fft_cplx.sc firstfile numfile"
  exit 0
}
set fnum     [lindex $argv $argi]
set numloop  [lindex $argv [expr $argi + 1 ]]
set torotate [expr $lenkeep / 2 ]
set firsttokeep [expr ($lenfft - $lenkeep) / 2 + 1]
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
		puts $hdrfile "drv_fft_cplx.sc START       : [exec date]"
	  	if  { $numpol > 1 } {
		set retval [catch \
{exec  stripVme -h -q  < $infile | selectpnts -b $datalen -f $poltouse -s 2 | \
		radarcplxfft -l $lenfft -r $numbins -p $dcdpacked | \
		selectpnts -b 8 -f $firsttokeep -g $lenkeep -s $lenfft     > $outfile } msg ]
		puts "$msg"
		flush stdout
		} else {
			set retval [catch \
{exec  stripVme -h -q < $infile| \
                radarcplxfft -l $lenfft -r $numbins -p $dcdpacked | \
                selectpnts -b 8 -f $firsttokeep -g $lenkeep -s $lenfft     > $outfile } msg ]
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
	  	puts $hdrfile "drv_fft_cplx.sc START       : [exec date]"
#
#		puts "lenfft: $lenfft numbins:$numbins dcdpacked:$dcdpacked"
#		flush stdout
		set retval [catch \
 	    { exec radarcplxfft -l $lenfft -r $numbins -p $dcdpacked -x $xoff < $infile | \
 		selectpnts -b 8 -f $firsttokeep -g $lenkeep -s $lenfft     > $outfile } msg ]
		puts $msg
		flush stdout
	}
#
puts $hdrfile "    samples/rbin input     : $numtimpnts"
puts $hdrfile "    samples/rbin used      : $numtimpntsout"
puts $hdrfile "    length fft             : $lenfft " 
puts $hdrfile "    dcd packed data        : $dcdpacked "
puts $hdrfile "    freq points kept       : $lenkeep "
puts $hdrfile "    input file             : $infile "
puts $hdrfile "    output file            : $outfile "
puts $hdrfile "drv_fft_cplx.sc END         : [exec date]"
#
	puts $hdrfile "Done with ${infile}"
	flush $hdrfile
	close $hdrfile
	incr fnum

}
