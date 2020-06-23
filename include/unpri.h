/*
 *	include file for riunpack routines
 *
*/
#ifndef INCUnprih
#define INCUnprih

#define   unpri_1(val,outptr,inc)  \
          *(outptr)=lkup_1[(val)&1];\
          (val)>>=1;\
          (outptr)+=(inc);\
          *(outptr)=lkup_1[(val)&1];\
          (val)>>=1;\
          (outptr)+=(inc);\
          *(outptr)=lkup_1[(val)&1];\
          (val)>>=1;\
          (outptr)+=(inc);\
          *(outptr)=lkup_1[(val)&1];\
          (val)>>=1;\
          (outptr)+=(inc);\
          *(outptr)=lkup_1[(val)&1];\
          (val)>>=1;\
          (outptr)+=(inc);\
          *(outptr)=lkup_1[(val)&1];\
          (val)>>=1;\
          (outptr)+=(inc);\
          *(outptr)=lkup_1[(val)&1];\
          (val)>>=1;\
          (outptr)+=(inc);\
          *(outptr)=lkup_1[(val)&1];\
          (val)>>=1;\
          (outptr)+=(inc);\
          *(outptr)=lkup_1[(val)&1];\
          (val)>>=1;\
          (outptr)+=(inc);\
          *(outptr)=lkup_1[(val)&1];\
          (val)>>=1;\
          (outptr)+=(inc);\
          *(outptr)=lkup_1[(val)&1];\
          (val)>>=1;\
          (outptr)+=(inc);\
          *(outptr)=lkup_1[(val)&1];\
          (val)>>=1;\
          (outptr)+=(inc);\
          *(outptr)=lkup_1[(val)&1];\
          (val)>>=1;\
          (outptr)+=(inc);\
          *(outptr)=lkup_1[(val)&1];\
          (val)>>=1;\
          (outptr)+=(inc);\
          *(outptr)=lkup_1[(val)&1];\
          (val)>>=1;\
          (outptr)+=(inc);\
          *(outptr)=lkup_1[(val)&1];\
          (outptr)+=(inc);

#define   unpri_2(val,outptr,inc)  \
          *(outptr)=lkup_2[(val)&3];\
          (val)>>=2;\
          (outptr)+=(inc);\
          *(outptr)=lkup_2[(val)&3];\
          (val)>>=2;\
          (outptr)+=(inc);\
          *(outptr)=lkup_2[(val)&3];\
          (val)>>=2;\
          (outptr)+=(inc);\
          *(outptr)=lkup_2[(val)&3];\
          (val)>>=2;\
          (outptr)+=(inc);\
          *(outptr)=lkup_2[(val)&3];\
          (val)>>=2;\
          (outptr)+=(inc);\
          *(outptr)=lkup_2[(val)&3];\
          (val)>>=2;\
          (outptr)+=(inc);\
          *(outptr)=lkup_2[(val)&3];\
          (val)>>=2;\
          (outptr)+=(inc);\
          *(outptr)=lkup_2[(val)&3];\
          (outptr)+=(inc);

#define   unpri_4(val,outptr,inc)  \
          *(outptr)=lkup_4[(val) & 0xf];\
          (val)>>=4;\
          (outptr)+=(inc);\
          *(outptr)=lkup_4[(val) & 0xf];\
          (val)>>=4;\
          (outptr)+=(inc);\
          *(outptr)=lkup_4[(val) & 0xf];\
          (val)>>=4;\
          (outptr)+=(inc);\
          *(outptr)=lkup_4[(val) & 0xf];\
          (outptr)+=(inc);

#define   unpri_8(val,outptr,inc)  \
          *(outptr) =((val & 0xff)> 0x7f)?((val) & 0xff) - 256:(val) & 0xff;\
          (val)>>=8;\
          (outptr)+=(inc);\
          *(outptr) =((val & 0xff)> 0x7f)?((val) & 0xff) - 256:(val) & 0xff;\
          (outptr)+=(inc);

#define   unpri_12(val,outptr,inc)  \
          *outptr = val;\
          (outptr)+=(inc);

#endif	/*INCunprih*/  
