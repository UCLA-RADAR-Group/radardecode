#ifndef INCvxWorksEmh
#define INCvxWorksEmh
/*
	couple of handy emulations for sun code to use with vxWorks.
*/
typedef	int	STATUS;
#define LOCAL   static
#define OK	0
#define ERROR  (-1)

#if     !defined(NULL)
#define NULL            0
#endif

#if     !defined(EOF) || (EOF!=(-1))
#define EOF             (-1)
#endif

#if     !defined(FALSE) || (FALSE!=0)
#define FALSE           0
#endif

#if     !defined(TRUE) || (TRUE!=1)
#define TRUE            1
#endif

#if     !defined(IMPORT) 
#define IMPORT          extern
#endif
/*
 *	some functions
*/
#define printErr  printf 
#define truncDtoI(a)	((int)(a))
#if	!defined(BCOPY)
#define	bcopy(s1,s2,n)   memcpy(s1,s2,n)
#endif 

/*
 *	some func typedefs
*/
typedef int             (*FUNCPTR) ();     /* ptr to function returning int */
typedef void            (*VOIDFUNCPTR) (); /* ptr to function returning void */
typedef double          (*DBLFUNCPTR) ();  /* ptr to function returning double*/
typedef float           (*FLTFUNCPTR) ();  /* ptr to function returning float */
typedef void           *(*VOIDPTRFUNCPTR) ();/* ptr to function ret char* */
#endif  /*INCvxWorksEmh*/
