#!/bin/bash
#run as : ./validate.sh

cw_param_1=0
u4_param_1=0
#CW DATA====================
#1 run p1 data=============================
cd cw
drv_cw.sc drvcw.result 1 1

od -f test_64.p1 > test.tmp1
od -f result_64.p1 > result.tmp1

head test.tmp1 | awk '{print $2}' > test_hd2p1.cmp
tail test.tmp1 | awk '{print $4}' > test_tl4p1.cmp
head result.tmp1 | awk '{print $2}' > result_hd2p1.cmp
tail result.tmp1 | awk '{print $4}' > result_tl4p1.cmp

paste test_hd2p1.cmp result_hd2p1.cmp > hd2p1.cmp
paste test_tl4p1.cmp result_tl4p1.cmp > tl4p1.cmp

cat hd2p1.cmp | awk '{if(($1-$2)>10000 || ($1-$2)<-10000) print ($1-$2)}' > err
cat tl4p1.cmp | awk '{if(($1-$2)>10000 || ($1-$2)<-10000) print ($1-$2)}' >> err

od -f test_64.p2 > test.tmp2
od -f result_64.p2 > result.tmp2

head test.tmp2 | awk '{print $2}' > test_hd2p2.cmp
tail test.tmp2 | awk '{print $4}' > test_tl4p2.cmp
head result.tmp2 | awk '{print $2}' > result_hd2p2.cmp
tail result.tmp2 | awk '{print $4}' > result_tl4p2.cmp

paste test_hd2p2.cmp result_hd2p2.cmp > hd2p2.cmp
paste test_tl4p2.cmp result_tl4p2.cmp > tl4p2.cmp

cat hd2p2.cmp | awk '{if(($1-$2)>10000 || ($1-$2)<-10000) print ($1-$2)}' >> err
cat tl4p2.cmp | awk '{if(($1-$2)>10000 || ($1-$2)<-10000) print ($1-$2)}' >> err


if [ $(du -k err | cut -f1) -eq "0" ];then # if err is 0 then cw works
        cw_param_1=1; 
fi

if [ $(du -k result_hd2p1.cmp | cut -f1) -eq "0" ];then # if even a single file is 0 then the code didn't work but prev if would have given a correct result
    cw_param_1=0;
fi

cd ..

#1k u4 DATA==============================
# 1 run========================================
cd u4
export DRVSB=drv.1k
drv_all.sc 1 1
drv_mapmsc.sc 1 1 1 1
mv Fits/f1x1.fit Fits/result.fits

# unscaled images
od -f test.1k.mapf1 | head > test.tmp1
od -f result.mapf1 | head > result.tmp1

cat test.tmp1 | awk '{print $2}' > test_hd2.cmp
cat result.tmp1 | awk '{print $2}' > result_hd2.cmp

paste result_hd2.cmp test_hd2.cmp > unscaled.cmp

cat unscaled.cmp | awk '{if(($1-$2)>0.0001 || ($1-$2)<-0.0001) print ($1-$2)}' > err
if [ $(du -k err | cut -f1) -eq "0" ];then u4_param_1=1; else u4_param_1=0; fi


# scaled images
od -f test.1k.mapsf1 | head > test.tmp1
od -f result.mapsf1 | head > result.tmp1

cat test.tmp1 | awk '{print $2}' > test_hd2.cmp
cat result.tmp1 | awk '{print $2}' > result_hd2.cmp

paste result_hd2.cmp test_hd2.cmp > scaled.cmp

cat scaled.cmp | awk '{if(($1-$2)>0.0001 || ($1-$2)<-0.0001) print ($1-$2)}' > err
if [ $(du -k err | cut -f1) -eq "0" ];then u4_param_1=1; else u4_param_1=0; fi


#=====================================================


echo "================================================="
echo "=                    RESULTS                    ="
echo "================================================="
if [ $cw_param_1 -eq 1 ]; then echo " doppler processing works "; fi
if [ $u4_param_1 -eq 1 ]; then echo " delay-doppler processing works"; fi

if [ $cw_param_1 -eq 0 ]; then echo " doppler processing does not work "; fi
if [ $u4_param_1 -eq 0 ]; then echo " delay-doppler processing does not work"; fi

cd ..
