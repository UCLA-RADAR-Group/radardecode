#include	<ctype.h>
#include    <utilLib.h>

/*****************************************************************************/
/*	to_lowercase						             */
/*****************************************************************************/
void to_lowercase(char	*sptr)
{
/*
	convert null terminated string pointed to by sptr to lower case
*/
 	for  (;(*sptr != 0);sptr++){
	   if (isascii(*sptr) && isupper(*sptr))
			*sptr=tolower(*sptr);
	}
	return;
}
