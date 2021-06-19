/*----------------------------------------
    Module	:	OLEMAC.H
    Date	: 	08/05/1997
    Purpose	:	Generic OLE Macros
----------------------------------------*/

#ifndef _OLEMAC_H_
#define _OLEMAC_H_

#define ReleaseInterface(p)\
        {\
            if (p)\
            {\
                p->Release();\
                p=NULL;\
            }\
        }

#define SetDefFormatEtc(fe, cf, med)\
        {\
            (fe).cfFormat	= cf;\
            (fe).dwAspect	= DVASPECT_CONTENT;\
            (fe).ptd		= NULL;\
            (fe).tymed		= med;\
            (fe).lindex		= -1;\
        }

#define SETEXCEPINFO(ei, excode, src, desc, file, ctx, func, scd) \
        {\
        (ei).wCode				= excode;\
        (ei).wReserved			= 0;\
        (ei).bstrSource			= src;\
        (ei).bstrDescription	= desc;\
        (ei).bstrHelpFile		= file;\
        (ei).dwHelpContext		= ctx;\
        (ei).pvReserved			= NULL;\
        (ei).pfnDeferredFillIn	= func;\
        (ei).scode				= scd;\
        }

#define INITEXCEPINFO(ei) \
        SETEXCEPINFO(ei,0,NULL,NULL,NULL,0L,NULL,S_OK)

#endif // _OLEMAC_H_
