/*-------------------------------------------
	Module	:	OurMacros.h
	Purpose	:	Global Macros
	Date		:	09/01/1997
-------------------------------------------*/

#ifndef _OURMACROS_H_
#define _OURMACROS_H_

#define DELETEGDIOBJECT(p)							\
					{								\
						if (p)						\
						{							\
						::DeleteObject(p);			\
						p = NULL;					\
						}							\
					}								\

#endif // _OURMACROS_H