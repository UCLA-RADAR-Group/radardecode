#include <fftw.h>

/*
 * interface to fftw.
 * history..
 * added not in place option
 */

void fftwAo(
	float *inDat,			/* to xform*/
	float *outDat,  		/* NULL if inplace*/
	int lenxform,
	int direction,		/* sign of exponent*/
	int inplace 		/* 1 inplace, 0 no inplace*/
	)

{
  static fftw_plan planf=0, planr=0, planfni=0, planrni=0;
  static int oldlength=0;

  if(lenxform != oldlength) {
    oldlength = lenxform;
    if(planf) {
      fftw_destroy_plan(planf);
      fftw_destroy_plan(planr);
      fftw_destroy_plan(planfni);
      fftw_destroy_plan(planrni);
    }
    planf = fftw_create_plan(lenxform, -1, FFTW_ESTIMATE|FFTW_IN_PLACE);
    planr = fftw_create_plan(lenxform,  1, FFTW_ESTIMATE|FFTW_IN_PLACE);
    planfni = fftw_create_plan(lenxform, -1, FFTW_ESTIMATE|FFTW_OUT_OF_PLACE);
    planrni = fftw_create_plan(lenxform,  1, FFTW_ESTIMATE|FFTW_OUT_OF_PLACE);
  }

  if(direction > 0)
    if (inplace) {
       fftw_one(planr, (fftw_complex *) (inDat), NULL);
	} else {
       fftw_one(planrni, (fftw_complex *) (inDat),(fftw_complex *) (outDat));
	}
		
  else {
    if (inplace) {
    	fftw_one(planf, (fftw_complex *) (inDat), NULL);
	} else {
       fftw_one(planfni, (fftw_complex *) (inDat),(fftw_complex *) (outDat));
	}
  }
}
