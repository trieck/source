

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0622 */
/* at Mon Jan 18 22:14:07 2038
 */
/* Compiler settings for DrawObject.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.01.0622 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */



/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 500
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif /* __RPCNDR_H_VERSION__ */

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __DrawObject_i_h__
#define __DrawObject_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IDrawObject_FWD_DEFINED__
#define __IDrawObject_FWD_DEFINED__
typedef interface IDrawObject IDrawObject;

#endif 	/* __IDrawObject_FWD_DEFINED__ */


#ifndef __DrawObject_FWD_DEFINED__
#define __DrawObject_FWD_DEFINED__

#ifdef __cplusplus
typedef class DrawObject DrawObject;
#else
typedef struct DrawObject DrawObject;
#endif /* __cplusplus */

#endif 	/* __DrawObject_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "shobjidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IDrawObject_INTERFACE_DEFINED__
#define __IDrawObject_INTERFACE_DEFINED__

/* interface IDrawObject */
/* [unique][nonextensible][uuid][object] */ 


EXTERN_C const IID IID_IDrawObject;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("f206ac00-005c-11d1-b1c9-000000000000")
    IDrawObject : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Load( 
            /* [in] */ BSTR filename) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Randomize( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetBounds( 
            /* [in] */ LPRECT bounds) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetColor( 
            /* [in] */ COLORREF color) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetColor( 
            /* [out][in] */ LPCOLORREF pColor) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IDrawObjectVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDrawObject * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDrawObject * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDrawObject * This);
        
        HRESULT ( STDMETHODCALLTYPE *Load )( 
            IDrawObject * This,
            /* [in] */ BSTR filename);
        
        HRESULT ( STDMETHODCALLTYPE *Randomize )( 
            IDrawObject * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetBounds )( 
            IDrawObject * This,
            /* [in] */ LPRECT bounds);
        
        HRESULT ( STDMETHODCALLTYPE *SetColor )( 
            IDrawObject * This,
            /* [in] */ COLORREF color);
        
        HRESULT ( STDMETHODCALLTYPE *GetColor )( 
            IDrawObject * This,
            /* [out][in] */ LPCOLORREF pColor);
        
        END_INTERFACE
    } IDrawObjectVtbl;

    interface IDrawObject
    {
        CONST_VTBL struct IDrawObjectVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDrawObject_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDrawObject_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDrawObject_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDrawObject_Load(This,filename)	\
    ( (This)->lpVtbl -> Load(This,filename) ) 

#define IDrawObject_Randomize(This)	\
    ( (This)->lpVtbl -> Randomize(This) ) 

#define IDrawObject_SetBounds(This,bounds)	\
    ( (This)->lpVtbl -> SetBounds(This,bounds) ) 

#define IDrawObject_SetColor(This,color)	\
    ( (This)->lpVtbl -> SetColor(This,color) ) 

#define IDrawObject_GetColor(This,pColor)	\
    ( (This)->lpVtbl -> GetColor(This,pColor) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDrawObject_INTERFACE_DEFINED__ */



#ifndef __DrawObjectLib_LIBRARY_DEFINED__
#define __DrawObjectLib_LIBRARY_DEFINED__

/* library DrawObjectLib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_DrawObjectLib;

EXTERN_C const CLSID CLSID_DrawObject;

#ifdef __cplusplus

class DECLSPEC_UUID("60f75e71-0039-11d1-b1c9-000000000000")
DrawObject;
#endif
#endif /* __DrawObjectLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

unsigned long             __RPC_USER  BSTR_UserSize64(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal64(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal64(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree64(     unsigned long *, BSTR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


