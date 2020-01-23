#!/bin/bash --norc
#  keyval.sc < inputfile key
# output value from key line to stdout if found
#
# inputfile format is:
# key value junk
#
#read input file a line at a time looking
#for a line that starts with key.
# If found, output value from that line and exit
#
key=$1
while  read keyIn value restofline; do
    if [[ $keyIn == $key ]] ; then
        echo $value
        break
    fi
done
