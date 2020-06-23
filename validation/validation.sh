
#run as : ./validation.sh <validation path_to_validation_folder>
#example : ./validation.sh ~/src
stem=$1 #like ~/src
cw_param_1=0
u4_param_1=0
#CW DATA====================
#1 run p1 data=============================
cd $stem/radardecode/validation/cw/
drv_cw.sc drvcw.result 1 1
sleep 2

od -f test.p1 > test.tmp1
od -f result.p1 > result.tmp1

head test.tmp1 | awk '{print $1}' > test_hd1p1.cmp
tail test.tmp1 | awk '{print $4}' > test_t14p1.cmp
head result.tmp1 | awk '{print $1}' > result_hd1p1.cmp
tail result.tmp1 | awk '{print $4}' > result_t14p1.cmp

paste test_hd1p1.cmp result_hd1p1.cmp > hd1p1.cmp
paste test_tl4p1.cmp result_tl4p1.cmp > tl4p1.cmp

od -f test.p2 > test.tmp2
od -f result.p2 > result.tmp2

head test.tmp2 | awk '{print $1}' > test_hd1p2.cmp
tail test.tmp2 | awk '{print $4}' > test_t14p2.cmp
head result.tmp2 | awk '{print $1}' > result_hd1p2.cmp
tail result.tmp2 | awk '{print $4}' > result_t14p2.cmp

paste test_hd1p2.cmp result_hd1p2.cmp > hd1p2.cmp
paste test_tl4p2.cmp result_tl4p2.cmp > tl4p2.cmp

cat hd1p1.cmp | awk '{if(($1-$2)>10000 || ($1-$2)<-10000) print ($1-$2)}' > err
cat tl4p1.cmp | awk '{if(($1-$2)>10000 || ($1-$2)<-10000) print ($1-$2)}' >> err
cat hd1p2.cmp | awk '{if(($1-$2)>10000 || ($1-$2)<-10000) print ($1-$2)}' >> err
cat tl4p2.cmp | awk '{if(($1-$2)>10000 || ($1-$2)<-10000) print ($1-$2)}' >> err

if [ $(du -k err | cut -f1) -eq "0" ];then cw_param_1=1; fi

#1k u4 DATA==============================
# 1 run========================================
cd $stem/radardecode/validation/u4/
export DRVSB=drv.1k
drv_all.sc 1 1
sleep 2
drv_mapmsc.sc 1 1 1 1
sleep 2
mv Fits/f1x1.fit Fits/result.fit
python3 ../pixvalue.py u4 > result.val1
paste result.val1 test.val1 > val1
cat val1 | awk '{if(($1-$2)>0.0001 || ($1-$2)<-0.0001) print ($1-$2)}' > err
if [ $(du -k err | cut -f1) -eq "0" ];then u4_param_1=1; fi


#=====================================================


echo "===========RESULT========="
if [ $cw_param_1 -eq 1 ]; then echo " doppler processing works "; fi
if [ $u4_param_1 -eq 1 ]; then echo " ri delay-doppler processing works"; fi

if [ $cw_param_1 -eq 0 ]; then echo " doppler processing does not work "; fi
if [ $u4_param_1 -eq 0 ]; then echo " ri delay-doppler processing does not work"; fi


