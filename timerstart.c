/****************************************************************************/
/*	timerstart        			 		            */
/****************************************************************************/
#include <sys/time.h>
int     timerstart(void)
{
/*	 start the timer running. will generate an interrupt in 100000 seconds.
*/
	struct itimerval value;
	long   sec,usec;

	sec = 100000;
	usec= 0;
        value.it_value.tv_sec  = sec;
        value.it_value.tv_usec = usec;
        value.it_interval.tv_sec  = sec;
        value.it_interval.tv_usec = usec;
	return(setitimer(ITIMER_REAL,&value,0));		
}  
