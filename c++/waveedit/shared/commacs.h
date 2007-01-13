/*---------------------------------------
	Module	:	COMMACS.H
	Date	:	11/10/1997
	Purpose	:	Custom COM Macros
----------------------------------------*/

#ifndef __COMMACS_H__
#define __COMMACS_H__

#define DeleteInterfaceImp(p)\
		{\
            if (p)\
            {\
				delete p;\
                p=NULL;\
            }\
        }
#define ReleaseInterface(p)\
        {\
            if (p)\
			{\
				p->Release();\
                p=NULL;\
            }\
		}

#endif // __COMMACS_H__
