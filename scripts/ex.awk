#!/bin/sh
#
#	awk script to extract a keyword value from a file 
#	 
#	call: 
#	ex.awk file  keyword
#
#	output is keyword value or null
#
#	assumptions on input file:
#	1.  key   value
#	    value is written to standard out
#
#
if [ $# -lt 2 ] 
   then
   echo "Usage: ex.awk file keyword"
   exit 1
fi
awk  ' BEGIN {
	      key="'`echo "$2"`'"
	}
       {
	     if ($1 == key) {
	         print $2
	         exit(0)
	     }
       }
	' $1
