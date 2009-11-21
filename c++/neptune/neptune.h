/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Mon Jul 09 15:11:15 2001
 */
/* Compiler settings for neptune.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
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

#ifndef __neptune_h__
#define __neptune_h__

#ifdef __cplusplus
extern "C" {
#endif

	/* Forward Declarations */

#ifndef __IComputer_FWD_DEFINED__
#define __IComputer_FWD_DEFINED__
	typedef interface IComputer IComputer;
#endif 	/* __IComputer_FWD_DEFINED__ */


#ifndef __IStringUtil_FWD_DEFINED__
#define __IStringUtil_FWD_DEFINED__
	typedef interface IStringUtil IStringUtil;
#endif 	/* __IStringUtil_FWD_DEFINED__ */


#ifndef __Neptune_FWD_DEFINED__
#define __Neptune_FWD_DEFINED__

#ifdef __cplusplus
	typedef class Neptune Neptune;
#else
	typedef struct Neptune Neptune;
#endif /* __cplusplus */

#endif 	/* __Neptune_FWD_DEFINED__ */


	/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

	void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
	void __RPC_USER MIDL_user_free( void __RPC_FAR * );

#ifndef __IComputer_INTERFACE_DEFINED__
#define __IComputer_INTERFACE_DEFINED__

	/* interface IComputer */
	/* [unique][helpstring][uuid][object] */


	EXTERN_C const IID IID_IComputer;

#if defined(__cplusplus) && !defined(CINTERFACE)

	MIDL_INTERFACE("C7EFC9B2-E499-42a8-A465-AB645A02A77A")
IComputer :
	public IUnknown
	{
public:
		virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Name(
		    /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;

		virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_SystemDirectory(
		    /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;

	};

#else 	/* C style interface */

	typedef struct IComputerVtbl {
		BEGIN_INTERFACE

		HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )(
		    IComputer __RPC_FAR * This,
		    /* [in] */ REFIID riid,
		    /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);

		ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )(
		    IComputer __RPC_FAR * This);

		ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )(
		    IComputer __RPC_FAR * This);

		/* [helpstring][propget] */
		HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )(
		    IComputer __RPC_FAR * This,
		    /* [retval][out] */ BSTR __RPC_FAR *pVal);

		/* [helpstring][propget] */
		HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SystemDirectory )(
		    IComputer __RPC_FAR * This,
		    /* [retval][out] */ BSTR __RPC_FAR *pVal);

		END_INTERFACE
	} IComputerVtbl;

	interface IComputer
	{
		CONST_VTBL struct IComputerVtbl __RPC_FAR *lpVtbl;
	};



#ifdef COBJMACROS


#define IComputer_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IComputer_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IComputer_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IComputer_get_Name(This,pVal)	\
    (This)->lpVtbl -> get_Name(This,pVal)

#define IComputer_get_SystemDirectory(This,pVal)	\
    (This)->lpVtbl -> get_SystemDirectory(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



	/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IComputer_get_Name_Proxy(
	    IComputer __RPC_FAR * This,
	    /* [retval][out] */ BSTR __RPC_FAR *pVal);


	void __RPC_STUB IComputer_get_Name_Stub(
	    IRpcStubBuffer *This,
	    IRpcChannelBuffer *_pRpcChannelBuffer,
	    PRPC_MESSAGE _pRpcMessage,
	    DWORD *_pdwStubPhase);


	/* [helpstring][propget] */
	HRESULT STDMETHODCALLTYPE IComputer_get_SystemDirectory_Proxy(
	    IComputer __RPC_FAR * This,
	    /* [retval][out] */ BSTR __RPC_FAR *pVal);


	void __RPC_STUB IComputer_get_SystemDirectory_Stub(
	    IRpcStubBuffer *This,
	    IRpcChannelBuffer *_pRpcChannelBuffer,
	    PRPC_MESSAGE _pRpcMessage,
	    DWORD *_pdwStubPhase);



#endif 	/* __IComputer_INTERFACE_DEFINED__ */


#ifndef __IStringUtil_INTERFACE_DEFINED__
#define __IStringUtil_INTERFACE_DEFINED__

	/* interface IStringUtil */
	/* [unique][helpstring][uuid][object] */


	EXTERN_C const IID IID_IStringUtil;

#if defined(__cplusplus) && !defined(CINTERFACE)

	MIDL_INTERFACE("77D29F5F-B2B5-48cc-84DC-F71D281ECD77")
IStringUtil :
	public IUnknown
	{
public:
		virtual /* [helpstring][vararg] */ HRESULT STDMETHODCALLTYPE FormatString(
		    /* [in] */ BSTR fmt,
		    /* [out] */ BSTR __RPC_FAR *output,
		    /* [in] */ SAFEARRAY __RPC_FAR * __RPC_FAR *args) = 0;

	};

#else 	/* C style interface */

	typedef struct IStringUtilVtbl {
		BEGIN_INTERFACE

		HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )(
		    IStringUtil __RPC_FAR * This,
		    /* [in] */ REFIID riid,
		    /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);

		ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )(
		    IStringUtil __RPC_FAR * This);

		ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )(
		    IStringUtil __RPC_FAR * This);

		/* [helpstring][vararg] */
		HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FormatString )(
		    IStringUtil __RPC_FAR * This,
		    /* [in] */ BSTR fmt,
		    /* [out] */ BSTR __RPC_FAR *output,
		    /* [in] */ SAFEARRAY __RPC_FAR * __RPC_FAR *args);

		END_INTERFACE
	} IStringUtilVtbl;

	interface IStringUtil
	{
		CONST_VTBL struct IStringUtilVtbl __RPC_FAR *lpVtbl;
	};



#ifdef COBJMACROS


#define IStringUtil_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IStringUtil_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IStringUtil_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IStringUtil_FormatString(This,fmt,output,args)	\
    (This)->lpVtbl -> FormatString(This,fmt,output,args)

#endif /* COBJMACROS */


#endif 	/* C style interface */



	/* [helpstring][vararg] */ HRESULT STDMETHODCALLTYPE IStringUtil_FormatString_Proxy(
	    IStringUtil __RPC_FAR * This,
	    /* [in] */ BSTR fmt,
	    /* [out] */ BSTR __RPC_FAR *output,
	    /* [in] */ SAFEARRAY __RPC_FAR * __RPC_FAR *args);


	void __RPC_STUB IStringUtil_FormatString_Stub(
	    IRpcStubBuffer *This,
	    IRpcChannelBuffer *_pRpcChannelBuffer,
	    PRPC_MESSAGE _pRpcMessage,
	    DWORD *_pdwStubPhase);



#endif 	/* __IStringUtil_INTERFACE_DEFINED__ */



#ifndef __NeptuneLib_LIBRARY_DEFINED__
#define __NeptuneLib_LIBRARY_DEFINED__

	/* library NeptuneLib */
	/* [helpstring][version][uuid] */


	EXTERN_C const IID LIBID_NeptuneLib;

	EXTERN_C const CLSID CLSID_Neptune;

#ifdef __cplusplus

	class DECLSPEC_UUID("51017D31-9CEF-42bd-B6C4-2A3270DE3C97")
				Neptune;
#endif
#endif /* __NeptuneLib_LIBRARY_DEFINED__ */

	/* Additional Prototypes for ALL interfaces */

	unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long __RPC_FAR *, unsigned long            , BSTR __RPC_FAR * );
	unsigned char __RPC_FAR * __RPC_USER  BSTR_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * );
	unsigned char __RPC_FAR * __RPC_USER  BSTR_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * );
	void                      __RPC_USER  BSTR_UserFree(     unsigned long __RPC_FAR *, BSTR __RPC_FAR * );

	unsigned long             __RPC_USER  LPSAFEARRAY_UserSize(     unsigned long __RPC_FAR *, unsigned long            , LPSAFEARRAY __RPC_FAR * );
	unsigned char __RPC_FAR * __RPC_USER  LPSAFEARRAY_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, LPSAFEARRAY __RPC_FAR * );
	unsigned char __RPC_FAR * __RPC_USER  LPSAFEARRAY_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, LPSAFEARRAY __RPC_FAR * );
	void                      __RPC_USER  LPSAFEARRAY_UserFree(     unsigned long __RPC_FAR *, LPSAFEARRAY __RPC_FAR * );

	/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
