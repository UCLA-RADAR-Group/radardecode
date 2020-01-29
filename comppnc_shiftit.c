/* 
 *Routine  to do the register shifts for comppncode:
*/
#include <utilLib.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <string.h>
/*****************************************************************************/
/*comppnc_shiftit                                                      */
/*****************************************************************************/
int comppnc_shiftit
(
int     num_reg,                        /* total*/
int     num_fdback,                     /* feed back registers*/
int     fb1,
int		fb2,
int		fb3,
int		fb4,                /* feed back locations start at 1*/
int     *shiftreg)
{
/*
 *    shift then return position 1 as the value
*/
        int newvalue;
        int i;
        
		newvalue=0;
        if (num_fdback == 1) {
           newvalue = ~shiftreg[fb1];
        }
        else if (num_fdback == 2) {
           newvalue = ~(shiftreg[fb1] ^ shiftreg[fb2]);
        }
        else if (num_fdback == 4){
           newvalue = ~((shiftreg[fb1] ^ shiftreg[fb2]) ^
                        (shiftreg[fb3] ^ shiftreg[fb4]));
        } 
/*
 *      now shift the register
*/
      for (i=num_reg;i>1;i--){
        shiftreg[i]=shiftreg[i-1];
      }
      shiftreg[1]=newvalue;
      return(newvalue);
}
