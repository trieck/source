/*---------------------------------------
	Module	:	COMTYPES.H
	Date	:	11/01/1997
	Purpose	:	COM Data type definitions
----------------------------------------*/

#ifndef __COMTYPES_H__
#define __COMTYPES_H__

typedef void**				PPVOID;
typedef IUnknown*			LPUNKNOWN;
typedef IClassFactory*		LPCLASSFACTORY;
typedef IDispatch*			LPDISPATCH;
typedef ITypeLib*			LPTYPELIB;
typedef ITypeInfo*			LPTYPEINFO;
typedef ISupportErrorInfo*	LPSUPPORTERRORINFO;
typedef SAFEARRAY**			PPSAFEARRAY;
typedef void (*PFNDESTROYED)(void);

#endif // __COMTYPES_H__
