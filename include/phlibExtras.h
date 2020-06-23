#ifndef INCPHLIBEXTRAS
#define INCPHLIBEXTRAS
/*
 * some defines
*/
#define LOCAL   static
#define	OK	0
#define ERROR (-1)

#if     !defined(FALSE) || (FALSE!=0)
#define FALSE           0
#endif

#if     !defined(TRUE) || (TRUE!=1)
#define TRUE            1
#endif
/*
 * some typedefs
*/

typedef int	STATUS;

#endif
