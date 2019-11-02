

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 7.00.0499 */
/* at Mon Oct 19 13:27:46 2009
 */
/* Compiler settings for misc.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data
    VC __declspec() decoration level:
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __iface_h__
#define __iface_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */

#ifndef __IMiscellaneous_FWD_DEFINED__
#define __IMiscellaneous_FWD_DEFINED__
typedef interface IMiscellaneous IMiscellaneous;
#endif 	/* __IMiscellaneous_FWD_DEFINED__ */


#ifndef __Miscellaneous_FWD_DEFINED__
#define __Miscellaneous_FWD_DEFINED__

#ifdef __cplusplus
typedef class Miscellaneous Miscellaneous;
#else
typedef struct Miscellaneous Miscellaneous;
#endif /* __cplusplus */

#endif 	/* __Miscellaneous_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"
#include "oaidl.h"

#ifdef __cplusplus
extern "C" {
#endif


#ifndef __IMiscellaneous_INTERFACE_DEFINED__
#define __IMiscellaneous_INTERFACE_DEFINED__

/* interface IMiscellaneous */
/* [oleautomation][dual][unique][helpstring][uuid][object] */


EXTERN_C const IID IID_IMiscellaneous;

#if defined(__cplusplus) && !defined(CINTERFACE)

MIDL_INTERFACE("813C3190-4E36-11d1-B1D5-000000000000")
IMiscellaneous :
public IDispatch {
public:
    virtual HRESULT STDMETHODCALLTYPE GetDate(
        /* [retval][out] */ BSTR *pbstrDate) = 0;

    virtual HRESULT STDMETHODCALLTYPE GetTime(
        /* [retval][out] */ BSTR *pbstrTime) = 0;

    virtual HRESULT STDMETHODCALLTYPE GetDateTime(
        /* [retval][out] */ BSTR *pbstrDateTime) = 0;

    virtual HRESULT STDMETHODCALLTYPE GetDriveSpace(
        /* [string][in] */ const BSTR bstrDrive,
        /* [retval][out] */ __int64 *pBytes) = 0;

    virtual HRESULT STDMETHODCALLTYPE EnumDrives(
        /* [retval][out] */ BSTR *pbstrDrives) = 0;

};

#else 	/* C style interface */

typedef struct IMiscellaneousVtbl {
    BEGIN_INTERFACE

    HRESULT ( STDMETHODCALLTYPE *QueryInterface )(
        IMiscellaneous * This,
        /* [in] */ REFIID riid,
        /* [iid_is][out] */
        __RPC__deref_out  void **ppvObject);

    ULONG ( STDMETHODCALLTYPE *AddRef )(
        IMiscellaneous * This);

    ULONG ( STDMETHODCALLTYPE *Release )(
        IMiscellaneous * This);

    HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )(
        IMiscellaneous * This,
        /* [out] */ UINT *pctinfo);

    HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )(
        IMiscellaneous * This,
        /* [in] */ UINT iTInfo,
        /* [in] */ LCID lcid,
        /* [out] */ ITypeInfo **ppTInfo);

    HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )(
        IMiscellaneous * This,
        /* [in] */ REFIID riid,
        /* [size_is][in] */ LPOLESTR *rgszNames,
        /* [range][in] */ UINT cNames,
        /* [in] */ LCID lcid,
        /* [size_is][out] */ DISPID *rgDispId);

    /* [local] */
    HRESULT ( STDMETHODCALLTYPE *Invoke )(
        IMiscellaneous * This,
        /* [in] */ DISPID dispIdMember,
        /* [in] */ REFIID riid,
        /* [in] */ LCID lcid,
        /* [in] */ WORD wFlags,
        /* [out][in] */ DISPPARAMS *pDispParams,
        /* [out] */ VARIANT *pVarResult,
        /* [out] */ EXCEPINFO *pExcepInfo,
        /* [out] */ UINT *puArgErr);

    HRESULT ( STDMETHODCALLTYPE *GetDate )(
        IMiscellaneous * This,
        /* [retval][out] */ BSTR *pbstrDate);

    HRESULT ( STDMETHODCALLTYPE *GetTime )(
        IMiscellaneous * This,
        /* [retval][out] */ BSTR *pbstrTime);

    HRESULT ( STDMETHODCALLTYPE *GetDateTime )(
        IMiscellaneous * This,
        /* [retval][out] */ BSTR *pbstrDateTime);

    HRESULT ( STDMETHODCALLTYPE *GetDriveSpace )(
        IMiscellaneous * This,
        /* [string][in] */ const BSTR bstrDrive,
        /* [retval][out] */ __int64 *pBytes);

    HRESULT ( STDMETHODCALLTYPE *EnumDrives )(
        IMiscellaneous * This,
        /* [retval][out] */ BSTR *pbstrDrives);

    END_INTERFACE
} IMiscellaneousVtbl;

interface IMiscellaneous
{
    CONST_VTBL struct IMiscellaneousVtbl *lpVtbl;
};



#ifdef COBJMACROS


#define IMiscellaneous_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) )

#define IMiscellaneous_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) )

#define IMiscellaneous_Release(This)	\
    ( (This)->lpVtbl -> Release(This) )


#define IMiscellaneous_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) )

#define IMiscellaneous_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) )

#define IMiscellaneous_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) )

#define IMiscellaneous_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) )


#define IMiscellaneous_GetDate(This,pbstrDate)	\
    ( (This)->lpVtbl -> GetDate(This,pbstrDate) )

#define IMiscellaneous_GetTime(This,pbstrTime)	\
    ( (This)->lpVtbl -> GetTime(This,pbstrTime) )

#define IMiscellaneous_GetDateTime(This,pbstrDateTime)	\
    ( (This)->lpVtbl -> GetDateTime(This,pbstrDateTime) )

#define IMiscellaneous_GetDriveSpace(This,bstrDrive,pBytes)	\
    ( (This)->lpVtbl -> GetDriveSpace(This,bstrDrive,pBytes) )

#define IMiscellaneous_EnumDrives(This,pbstrDrives)	\
    ( (This)->lpVtbl -> EnumDrives(This,pbstrDrives) )

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMiscellaneous_INTERFACE_DEFINED__ */



#ifndef __MiscLib_LIBRARY_DEFINED__
#define __MiscLib_LIBRARY_DEFINED__

/* library MiscLib */
/* [helpstring][version][uuid] */


EXTERN_C const IID LIBID_MiscLib;

EXTERN_C const CLSID CLSID_Miscellaneous;

#ifdef __cplusplus

class DECLSPEC_UUID("813C3191-4E36-11d1-B1D5-000000000000")
    Miscellaneous;
#endif
#endif /* __MiscLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long, BSTR * );
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * );
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * );
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * );

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


