#!/bin/bash
#run as : ./validate.sh

cw_param_1=0
u4_param_1=0

# Test 1: CW DATA

cd cw
drv_cw.sc drvcw.result 1 1

od -f correct_64.p1 | head -100 > correct.tmp1
od -f result_64.p1  | head -100 > result.tmp1

cat correct.tmp1 | awk '{print $2}' > correct_hdp1.cmp
cat result.tmp1  | awk '{print $2}' > result_hdp1.cmp

paste correct_hdp1.cmp result_hdp1.cmp > hdp1.cmp

cat hdp1.cmp | awk '{if(($1-$2)/$1>0.0001 || ($1-$2)/$1<-0.0001) print ($1-$2)/$1}' > err

od -f correct_64.p2 | head > correct.tmp2
od -f result_64.p2  | head > result.tmp2

head correct.tmp2 | awk '{print $2}' > correct_hdp2.cmp
head result.tmp2  | awk '{print $2}' > result_hdp2.cmp

paste correct_hdp2.cmp result_hdp2.cmp > hdp2.cmp

cat hdp2.cmp | awk '{if(($1-$2)/$1>0.0001 || ($1-$2)/$1<-0.0001) print ($1-$2)/$1}' >> err


if [ $(du -k err | cut -f1) -eq "0" ];then # test passed because comparison shows no meaningful differences
        cw_param_1=1; 
fi

if [ $(du -k result_hdp1.cmp | cut -f1) -eq "0" ];then # test failed because output file size is 0
    cw_param_1=0;
fi

# clean up
rm err *tmp1 *tmp2 *cmp
rm result*

cd ..

# Test 2: delay-Doppler data (1023 code, 4 us baud)

cd u4
export DRVSB=drv.1k
drv_all.sc 1 1
#drv_mapmsc.sc 1 1 1 1
#mv Fits/f1x1.fit Fits/result.fits

# unscaled images
# od -f correct.1k.mapf1 | head > correct.tmp1
# od -f result.mapf1 | head > result.tmp1

# cat correct.tmp1 | awk '{print $2}' > correct_hd.cmp
# cat result.tmp1 | awk '{print $2}' > result_hd.cmp

# paste correct_hd.cmp result_hd.cmp > unscaled.cmp

# cat unscaled.cmp | awk '{if(($1-$2)/$2>0.001 || ($1-$2)/$2<-0.001) print ($1-$2)/$1}' > err
# if [ $(du -k err | cut -f1) -eq "0" ];then u4_param_1=1; else u4_param_1=0; fi


# scaled images
od -f correct.1k.mapsf1 | head -100 > correct.tmp1
od -f result.mapsf1  | head -100 > result.tmp1

cat correct.tmp1 | awk '{print $2}' > correct_hd.cmp
cat result.tmp1 | awk '{print $2}' > result_hd.cmp

paste correct_hd.cmp result_hd.cmp > scaled.cmp

cat scaled.cmp | awk '{if(($1-$2)/$1>0.001 || ($1-$2)/$1<-0.001) print ($1-$2)/$1}' > err

if [ $(du -k err | cut -f1) -eq "0" ];then # test passed because comparison shows no meaningful differences
    u4_param_1=1; else u4_param_1=0;
fi

# clean up
rm err *tmp1 *cmp
rm result.dcdf1 result.hdrf1 result.mapf1 result.mapsf1

cd ..

#=====================================================


echo "================================================="
echo "=                    RESULTS                    ="
echo "================================================="
if [ $cw_param_1 -eq 1 ]; then echo " doppler processing test PASSED "; fi
if [ $u4_param_1 -eq 1 ]; then echo " delay-doppler processing test PASSED "; fi

if [ $cw_param_1 -eq 0 ]; then echo " doppler processing test FAILED "; fi
if [ $u4_param_1 -eq 0 ]; then echo " delay-doppler processing test FAILED "; fi



