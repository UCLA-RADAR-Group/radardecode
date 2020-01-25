
/****************************************************************************/
/*	timervalue  ... 		    			            */
/****************************************************************************/
#include <sys/time.h>
#include    <utilLib.h>

double timervalue(void)
{
/*	get the current value of the interval timer
	must call timerstart prior to this routine
*/
     	struct itimerval value;
	int istat;

	istat=getitimer(ITIMER_REAL,&value);
	if (istat == -1) return(0.);
	return(value.it_value.tv_sec*1.e6 + value.it_value.tv_usec);		
}
