

/* this ALWAYS GENERATED file contains the proxy stub code */


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

#if !defined(_M_IA64) && !defined(_M_AMD64)


#pragma warning( disable: 4049 )  /* more than 64k source lines */
#if _MSC_VER >= 1200
#pragma warning(push)
#endif

#pragma warning( disable: 4211 )  /* redefine extern to static */
#pragma warning( disable: 4232 )  /* dllimport identity*/
#pragma warning( disable: 4024 )  /* array to pointer mapping*/
#pragma warning( disable: 4152 )  /* function/data pointer conversion in expression */
#pragma warning( disable: 4100 ) /* unreferenced arguments in x86 call */

#pragma optimize("", off )

#define USE_STUBLESS_PROXY


/* verify that the <rpcproxy.h> version is high enough to compile this file*/
#ifndef __REDQ_RPCPROXY_H_VERSION__
#define __REQUIRED_RPCPROXY_H_VERSION__ 475
#endif


#include "rpcproxy.h"
#ifndef __RPCPROXY_H_VERSION__
#error this stub requires an updated version of <rpcproxy.h>
#endif // __RPCPROXY_H_VERSION__


#include "iface.h"

#define TYPE_FORMAT_STRING_SIZE   61
#define PROC_FORMAT_STRING_SIZE   187
#define EXPR_FORMAT_STRING_SIZE   1
#define TRANSMIT_AS_TABLE_SIZE    0
#define WIRE_MARSHAL_TABLE_SIZE   1

typedef struct _misc_MIDL_TYPE_FORMAT_STRING {
	short          Pad;
	unsigned char  Format[ TYPE_FORMAT_STRING_SIZE ];
} misc_MIDL_TYPE_FORMAT_STRING;

typedef struct _misc_MIDL_PROC_FORMAT_STRING {
	short          Pad;
	unsigned char  Format[ PROC_FORMAT_STRING_SIZE ];
} misc_MIDL_PROC_FORMAT_STRING;

typedef struct _misc_MIDL_EXPR_FORMAT_STRING {
	long          Pad;
	unsigned char  Format[ EXPR_FORMAT_STRING_SIZE ];
} misc_MIDL_EXPR_FORMAT_STRING;


static RPC_SYNTAX_IDENTIFIER  _RpcTransferSyntax = {{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}};


extern const misc_MIDL_TYPE_FORMAT_STRING misc__MIDL_TypeFormatString;
extern const misc_MIDL_PROC_FORMAT_STRING misc__MIDL_ProcFormatString;
extern const misc_MIDL_EXPR_FORMAT_STRING misc__MIDL_ExprFormatString;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IMiscellaneous_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IMiscellaneous_ProxyInfo;


extern const USER_MARSHAL_ROUTINE_QUADRUPLE UserMarshalRoutines[ WIRE_MARSHAL_TABLE_SIZE ];

#if !defined(__RPC_WIN32__)
#error  Invalid build platform for this stub.
#endif

#if !(TARGET_IS_NT50_OR_LATER)
#error You need a Windows 2000 or later to run this stub because it uses these features:
#error   /robust command line switch.
#error However, your C/C++ compilation flags indicate you intend to run this app on earlier systems.
#error This app will fail with the RPC_X_WRONG_STUB_VERSION error.
#endif


static const misc_MIDL_PROC_FORMAT_STRING misc__MIDL_ProcFormatString = {
	0,
	{

		/* Procedure GetDate */

		0x33,		/* FC_AUTO_HANDLE */
		0x6c,		/* Old Flags:  object, Oi2 */
		/*  2 */	NdrFcLong( 0x0 ),	/* 0 */
		/*  6 */	NdrFcShort( 0x7 ),	/* 7 */
		/*  8 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
		/* 10 */	NdrFcShort( 0x0 ),	/* 0 */
		/* 12 */	NdrFcShort( 0x8 ),	/* 8 */
		/* 14 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
		0x2,		/* 2 */
		/* 16 */	0x8,		/* 8 */
		0x3,		/* Ext Flags:  new corr desc, clt corr check, */
		/* 18 */	NdrFcShort( 0x1 ),	/* 1 */
		/* 20 */	NdrFcShort( 0x0 ),	/* 0 */
		/* 22 */	NdrFcShort( 0x0 ),	/* 0 */

		/* Parameter pbstrDate */

		/* 24 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
		/* 26 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
		/* 28 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

		/* Return value */

		/* 30 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
		/* 32 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
		/* 34 */	0x8,		/* FC_LONG */
		0x0,		/* 0 */

		/* Procedure GetTime */

		/* 36 */	0x33,		/* FC_AUTO_HANDLE */
		0x6c,		/* Old Flags:  object, Oi2 */
		/* 38 */	NdrFcLong( 0x0 ),	/* 0 */
		/* 42 */	NdrFcShort( 0x8 ),	/* 8 */
		/* 44 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
		/* 46 */	NdrFcShort( 0x0 ),	/* 0 */
		/* 48 */	NdrFcShort( 0x8 ),	/* 8 */
		/* 50 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
		0x2,		/* 2 */
		/* 52 */	0x8,		/* 8 */
		0x3,		/* Ext Flags:  new corr desc, clt corr check, */
		/* 54 */	NdrFcShort( 0x4 ),	/* 4 */
		/* 56 */	NdrFcShort( 0x0 ),	/* 0 */
		/* 58 */	NdrFcShort( 0x0 ),	/* 0 */

		/* Parameter pbstrTime */

		/* 60 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
		/* 62 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
		/* 64 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

		/* Return value */

		/* 66 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
		/* 68 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
		/* 70 */	0x8,		/* FC_LONG */
		0x0,		/* 0 */

		/* Procedure GetDateTime */

		/* 72 */	0x33,		/* FC_AUTO_HANDLE */
		0x6c,		/* Old Flags:  object, Oi2 */
		/* 74 */	NdrFcLong( 0x0 ),	/* 0 */
		/* 78 */	NdrFcShort( 0x9 ),	/* 9 */
		/* 80 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
		/* 82 */	NdrFcShort( 0x0 ),	/* 0 */
		/* 84 */	NdrFcShort( 0x8 ),	/* 8 */
		/* 86 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
		0x2,		/* 2 */
		/* 88 */	0x8,		/* 8 */
		0x3,		/* Ext Flags:  new corr desc, clt corr check, */
		/* 90 */	NdrFcShort( 0x4 ),	/* 4 */
		/* 92 */	NdrFcShort( 0x0 ),	/* 0 */
		/* 94 */	NdrFcShort( 0x0 ),	/* 0 */

		/* Parameter pbstrDateTime */

		/* 96 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
		/* 98 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
		/* 100 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

		/* Return value */

		/* 102 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
		/* 104 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
		/* 106 */	0x8,		/* FC_LONG */
		0x0,		/* 0 */

		/* Procedure GetDriveSpace */

		/* 108 */	0x33,		/* FC_AUTO_HANDLE */
		0x6c,		/* Old Flags:  object, Oi2 */
		/* 110 */	NdrFcLong( 0x0 ),	/* 0 */
		/* 114 */	NdrFcShort( 0xa ),	/* 10 */
		/* 116 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
		/* 118 */	NdrFcShort( 0x0 ),	/* 0 */
		/* 120 */	NdrFcShort( 0x2c ),	/* 44 */
		/* 122 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
		0x3,		/* 3 */
		/* 124 */	0x8,		/* 8 */
		0x5,		/* Ext Flags:  new corr desc, srv corr check, */
		/* 126 */	NdrFcShort( 0x0 ),	/* 0 */
		/* 128 */	NdrFcShort( 0x1 ),	/* 1 */
		/* 130 */	NdrFcShort( 0x0 ),	/* 0 */

		/* Parameter bstrDrive */

		/* 132 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
		/* 134 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
		/* 136 */	NdrFcShort( 0x2e ),	/* Type Offset=46 */

		/* Parameter pBytes */

		/* 138 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
		/* 140 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
		/* 142 */	0xb,		/* FC_HYPER */
		0x0,		/* 0 */

		/* Return value */

		/* 144 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
		/* 146 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
		/* 148 */	0x8,		/* FC_LONG */
		0x0,		/* 0 */

		/* Procedure EnumDrives */

		/* 150 */	0x33,		/* FC_AUTO_HANDLE */
		0x6c,		/* Old Flags:  object, Oi2 */
		/* 152 */	NdrFcLong( 0x0 ),	/* 0 */
		/* 156 */	NdrFcShort( 0xb ),	/* 11 */
		/* 158 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
		/* 160 */	NdrFcShort( 0x0 ),	/* 0 */
		/* 162 */	NdrFcShort( 0x8 ),	/* 8 */
		/* 164 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
		0x2,		/* 2 */
		/* 166 */	0x8,		/* 8 */
		0x3,		/* Ext Flags:  new corr desc, clt corr check, */
		/* 168 */	NdrFcShort( 0x1 ),	/* 1 */
		/* 170 */	NdrFcShort( 0x0 ),	/* 0 */
		/* 172 */	NdrFcShort( 0x0 ),	/* 0 */

		/* Parameter pbstrDrives */

		/* 174 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
		/* 176 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
		/* 178 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

		/* Return value */

		/* 180 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
		/* 182 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
		/* 184 */	0x8,		/* FC_LONG */
		0x0,		/* 0 */

		0x0
	}
};

static const misc_MIDL_TYPE_FORMAT_STRING misc__MIDL_TypeFormatString = {
	0,
	{
		NdrFcShort( 0x0 ),	/* 0 */
		/*  2 */
		0x11, 0x4,	/* FC_RP [alloced_on_stack] */
		/*  4 */	NdrFcShort( 0x1c ),	/* Offset= 28 (32) */
		/*  6 */
		0x13, 0x0,	/* FC_OP */
		/*  8 */	NdrFcShort( 0xe ),	/* Offset= 14 (22) */
		/* 10 */
		0x1b,		/* FC_CARRAY */
		0x1,		/* 1 */
		/* 12 */	NdrFcShort( 0x2 ),	/* 2 */
		/* 14 */	0x9,		/* Corr desc: FC_ULONG */
		0x0,		/*  */
		/* 16 */	NdrFcShort( 0xfffc ),	/* -4 */
		/* 18 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
		/* 20 */	0x6,		/* FC_SHORT */
		0x5b,		/* FC_END */
		/* 22 */
		0x17,		/* FC_CSTRUCT */
		0x3,		/* 3 */
		/* 24 */	NdrFcShort( 0x8 ),	/* 8 */
		/* 26 */	NdrFcShort( 0xfff0 ),	/* Offset= -16 (10) */
		/* 28 */	0x8,		/* FC_LONG */
		0x8,		/* FC_LONG */
		/* 30 */	0x5c,		/* FC_PAD */
		0x5b,		/* FC_END */
		/* 32 */	0xb4,		/* FC_USER_MARSHAL */
		0x83,		/* 131 */
		/* 34 */	NdrFcShort( 0x0 ),	/* 0 */
		/* 36 */	NdrFcShort( 0x4 ),	/* 4 */
		/* 38 */	NdrFcShort( 0x0 ),	/* 0 */
		/* 40 */	NdrFcShort( 0xffde ),	/* Offset= -34 (6) */
		/* 42 */
		0x12, 0x0,	/* FC_UP */
		/* 44 */	NdrFcShort( 0xffea ),	/* Offset= -22 (22) */
		/* 46 */	0xb4,		/* FC_USER_MARSHAL */
		0x83,		/* 131 */
		/* 48 */	NdrFcShort( 0x0 ),	/* 0 */
		/* 50 */	NdrFcShort( 0x4 ),	/* 4 */
		/* 52 */	NdrFcShort( 0x0 ),	/* 0 */
		/* 54 */	NdrFcShort( 0xfff4 ),	/* Offset= -12 (42) */
		/* 56 */
		0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
		/* 58 */	0xb,		/* FC_HYPER */
		0x5c,		/* FC_PAD */

		0x0
	}
};

static const USER_MARSHAL_ROUTINE_QUADRUPLE UserMarshalRoutines[ WIRE_MARSHAL_TABLE_SIZE ] = {

	{
		BSTR_UserSize
		,BSTR_UserMarshal
		,BSTR_UserUnmarshal
		,BSTR_UserFree
	}

};



/* Object interface: IUnknown, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: IDispatch, ver. 0.0,
   GUID={0x00020400,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: IMiscellaneous, ver. 0.0,
   GUID={0x813C3190,0x4E36,0x11d1,{0xB1,0xD5,0x00,0x00,0x00,0x00,0x00,0x00}} */

#pragma code_seg(".orpc")
static const unsigned short IMiscellaneous_FormatStringOffsetTable[] = {
	(unsigned short) -1,
	(unsigned short) -1,
	(unsigned short) -1,
	(unsigned short) -1,
	0,
	36,
	72,
	108,
	150
};

static const MIDL_STUBLESS_PROXY_INFO IMiscellaneous_ProxyInfo = {
	&Object_StubDesc,
	misc__MIDL_ProcFormatString.Format,
	&IMiscellaneous_FormatStringOffsetTable[-3],
	0,
	0,
	0
};


static const MIDL_SERVER_INFO IMiscellaneous_ServerInfo = {
	&Object_StubDesc,
	0,
	misc__MIDL_ProcFormatString.Format,
	&IMiscellaneous_FormatStringOffsetTable[-3],
	0,
	0,
	0,
	0
};
CINTERFACE_PROXY_VTABLE(12) _IMiscellaneousProxyVtbl = {
	&IMiscellaneous_ProxyInfo,
	&IID_IMiscellaneous,
	IUnknown_QueryInterface_Proxy,
	IUnknown_AddRef_Proxy,
	IUnknown_Release_Proxy ,
	0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfoCount */ ,
	0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfo */ ,
	0 /* (void *) (INT_PTR) -1 /* IDispatch::GetIDsOfNames */ ,
	0 /* IDispatch_Invoke_Proxy */ ,
	(void *) (INT_PTR) -1 /* IMiscellaneous::GetDate */ ,
	(void *) (INT_PTR) -1 /* IMiscellaneous::GetTime */ ,
	(void *) (INT_PTR) -1 /* IMiscellaneous::GetDateTime */ ,
	(void *) (INT_PTR) -1 /* IMiscellaneous::GetDriveSpace */ ,
	(void *) (INT_PTR) -1 /* IMiscellaneous::EnumDrives */
};


static const PRPC_STUB_FUNCTION IMiscellaneous_table[] = {
	STUB_FORWARDING_FUNCTION,
	STUB_FORWARDING_FUNCTION,
	STUB_FORWARDING_FUNCTION,
	STUB_FORWARDING_FUNCTION,
	NdrStubCall2,
	NdrStubCall2,
	NdrStubCall2,
	NdrStubCall2,
	NdrStubCall2
};

CInterfaceStubVtbl _IMiscellaneousStubVtbl = {
	&IID_IMiscellaneous,
	&IMiscellaneous_ServerInfo,
	12,
	&IMiscellaneous_table[-3],
	CStdStubBuffer_DELEGATING_METHODS
};

static const MIDL_STUB_DESC Object_StubDesc = {
	0,
	NdrOleAllocate,
	NdrOleFree,
	0,
	0,
	0,
	0,
	0,
	misc__MIDL_TypeFormatString.Format,
	1, /* -error bounds_check flag */
	0x50002, /* Ndr library version */
	0,
	0x70001f3, /* MIDL Version 7.0.499 */
	0,
	UserMarshalRoutines,
	0,  /* notify & notify_flag routine table */
	0x1, /* MIDL flag */
	0, /* cs routines */
	0,   /* proxy/server info */
	0
};

const CInterfaceProxyVtbl * _misc_ProxyVtblList[] = {
	( CInterfaceProxyVtbl *) &_IMiscellaneousProxyVtbl,
	0
};

const CInterfaceStubVtbl * _misc_StubVtblList[] = {
	( CInterfaceStubVtbl *) &_IMiscellaneousStubVtbl,
	0
};

PCInterfaceName const _misc_InterfaceNamesList[] = {
	"IMiscellaneous",
	0
};

const IID *  _misc_BaseIIDList[] = {
	&IID_IDispatch,
	0
};


#define _misc_CHECK_IID(n)	IID_GENERIC_CHECK_IID( _misc, pIID, n)

int __stdcall _misc_IID_Lookup( const IID * pIID, int * pIndex )
{

	if (!_misc_CHECK_IID(0)) {
		*pIndex = 0;
		return 1;
	}

	return 0;
}

const ExtendedProxyFileInfo misc_ProxyFileInfo = {
	(PCInterfaceProxyVtblList *) & _misc_ProxyVtblList,
	(PCInterfaceStubVtblList *) & _misc_StubVtblList,
	(const PCInterfaceName * ) & _misc_InterfaceNamesList,
	(const IID ** ) & _misc_BaseIIDList,
	& _misc_IID_Lookup,
	1,
	2,
	0, /* table of [async_uuid] interfaces */
	0, /* Filler1 */
	0, /* Filler2 */
	0  /* Filler3 */
};
#pragma optimize("", on )
#if _MSC_VER >= 1200
#pragma warning(pop)
#endif


#endif /* !defined(_M_IA64) && !defined(_M_AMD64)*/

