#ifndef INCconvLibh
#define INCconvLibh
#include	<phlibExtras.h>
/* 290ct93,pjp - all routines that handle h,m,s or d,m,s must pass in,or
*                pass back isign. This required some routines to have
*	         there number of arguments changed
*/

void    anglesToVec3(double c1Rad,double c2Rad,double* pvec3);
int     dmToDayNo(int day,int mon,int year);
void    dayNoTodm(int dayNo,int year,int* day,int *mon);
void    dnSecMidCnv(int year,int dayNo,int secMidnite,int *pmon,int *pday,
         	    int *phour,int *pmin,int *psec); 
void    fmtDms(int sign,int deg,int min,double sec,int secFracDig,
		char *cformatted);
void    fmtHmsD(int sign,int hour,int min,double sec,int secFracDig,
		char   *cformatted);
void    fmtHmsI(int sign,int hour,int min,int sec,char *cformatted);
void    fmtRdToDms(double dmsRd,int secFracDig,char *cformatted);
void    fmtRdToHmsD(double hmsRd,int secFracDig,char *cformatted);
void    fmtSMToHmsI(int secMidnite,char *cformatted);  
void    fmtSMToHmsD(double secMidnite,int secFracDig,char *cformatted);  


void   IsecMid_hms3(int isecs,int *hh,int *mm,int *iss);
void   secMid_hms3(double secs,int *hh,int *mm,double *ss);
void   sec1970_ymd_secMid(double sec1970,int *pyyyymmdd,double *psecMid);
int    isLeapYear(int year);
void   IminMid_hm2(int min,int *hh,int *mm);
int    hm2_IminMid(int hh,int mm);
int    hms3_IsecMid(int hh,int mm,int iss);
double hms3ToFrac(int h,int m,double s);


void   dms1_dms3(double ddmmss,int *isgn,int *id,int *im,double  *s);  
double dms1_rad(double  ddmmss);
double dms3_rad(int sign,int d,int m,double  s);
void   rad_dms3(double rad,int *sgn,int *dd,int *mm,double *ss);
/*
*/
void   hms1_hms3(double hhmmss,int *sgn,int *ih,int *im,double  *s);
int   hms1_IsecMid(int hhmmss);
double hms1_rad(double  hhmmss);
double hms3_rad(int sgn,int ih,int im,double s);
void   rad_hms3(double rad,int *sgn,int *hh,int *mm,double *ss);
void   setSign(int *hourDeg,int* psign);

double rad_deg(double rad);   

void   dmy1_dmy3(int ddmmyy,int *pdd,int *pmm,int *pyy);
void   ymd1_ymd3(int yymmdd,int *pyy,int *pmm,int *pdd);
void   vec3ToAngles(double* pvec3,int c1Pos,double* pc1,double* pc2);
double to0_2pi(double angleRd);
double dif0_pi(double aRd,double bRd);


#endif /*INCconvLibh*/

