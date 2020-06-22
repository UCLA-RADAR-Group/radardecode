
#run as : ./validation.sh <validation path_to_validation_folder>
#example : ./validation.sh ~/src
stem=$1 #like ~/src
cw_param_1=0
u4_param_1=0
#CW DATA====================
#1 run p1 data=============================
cd $stem/radardecode/validation/cw/
drv_cw.sc drvcw.test 1 1
sleep 2
od -f *.p1 > tmp1
od -f *.p2 > tmp2
head tmp1 | awk '{print $3}' > hdt_1_3
tail tmp1 | awk '{print $2}' > tlt_1_2
head tmp1 | awk '{print $3}' > hdt_2_3
paste hdt_1_3 hd_1_3 > hd
paste tlt_1_2 tl_1_2 > tl
paste hdt_2_3 hd_2_3 > hd2
cat hd | awk '{if(($1-$2)>10000 || ($1-$2)<-10000) print ($1-$2)}' > mo
if [ $(du -k mo | cut -f1) -eq "0" ];then cw_param_1=1; else cw_param_1=0; fi
if [ $cw_param_1 -eq 1 ]; then 
    cat tl | awk '{if(($1-$2)>10000 || ($1-$2)<-10000) print ($1-$2)}' > mo
    if [ $(du -k mo | cut -f1) -eq "0" ];then cw_param_1=1; else cw_param_1=0; fi
fi
if [ $cw_param_1 -eq 1 ]; then 
    cat hd2 | awk '{if(($1-$2)>10000 || ($1-$2)<-10000) print ($1-$2)}' > mo
    if [ $(du -k mo | cut -f1) -eq "0" ];then cw_param_1=1; else cw_param_1=0; fi
fi

#1k u4 DATA==============================
# 1 run========================================
cd $stem/radardecode/validation/u4/
export DRVSB=drv.1k
drv_all.sc 1 1
sleep 2
drv_mapmsc.sc 1 1 1 1
python3 ../pixvalue.py u4 > tmp
paste tmp val1 > vtmp
cat vtmp | awk '{if(($1-$2)>0.0001 || ($1-$2)<-0.0001) print ($1-$2)}' >mo
if [ $(du -k mo | cut -f1) -eq "0" ];then u4_param_1=1; fi


#=====================================================


echo "===========RESULT========="
if [ $cw_param_1 -eq 1 ]; then echo " doppler processing works "; fi
if [ $u4_param_1 -eq 1 ]; then echo " ri delay-doppler processing works"; fi

if [ $cw_param_1 -eq 0 ]; then echo " doppler processing does not work "; fi
if [ $u4_param_1 -eq 0 ]; then echo " ri delay-doppler processing does not work"; fi


