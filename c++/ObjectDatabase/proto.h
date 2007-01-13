/////////////////////////////////////////////////////////////////////////////
//
// PROTO.H : Object database wire protocol
//
// Copyright(c) 2006 Thomas A. Rieck, All Rights Reserved
//

#ifndef __PROTO_H__
#define __PROTO_H__

/////////////////////////////////////////////////////////////////////////////

/* request / response keys */
#define KEY_REQUEST_FNC		"function"
#define KEY_REQUEST_OTYPE	"object_type"
#define KEY_POOL_ID			"pool_id"
#define KEY_OBJECT_ID		"object_id"
#define KEY_OBJECT_VAL		"object_val"

/* function identifiers */

/* make a new object pool */
#define FNC_MKPOOL			(0x001)

/* create a new object in the pool */
#define FNC_CREATE			(0x002)

/* destroy an object in the pool */
#define FNC_DESTROY			(0x003)

/* get an object from the pool */
#define FNC_GET				(0x004)

/* set an object value in the pool */
#define FNC_SET				(0x005)

/* tear down a pool */
#define FNC_KILLPOOL		(0x006)

/* object types */
#define OT_INTEGER			(0x001)
#define OT_STRING			(0x002)
#define OT_LIST				(0x003)
#define OT_DICT				(0x004)

/* response codes */
#define E_OK				(0x000)
#define E_BAD_REQUEST		(0x001)
#define E_INC_REQUEST		(0x002)
#define E_BAD_FNC			(0x003)
#define E_CANT_CREATE		(0x004)
#define E_CANT_DESTROY		(0x005)
#define E_CANT_GET			(0x006)
#define E_CANT_SET			(0x007)

/* response specific keys */
#define KEY_RESPONSE_CD		"response_code"
#define KEY_RESPONSE_MSG	"response_msg"

/* response message strings */
#define RESP_OBJ_FMT		"bad format for request."
#define RESP_NO_FNC			"function not supplied."
#define RESP_BAD_FNC		"unknown function."
#define RESP_NO_OTYPE		"object type not supplied."
#define RESP_BAD_OTYPE		"bad object type."
#define RESP_NO_POOLID		"pool id not supplied."
#define RESP_NO_OBJECTID	"object id not supplied."
#define RESP_NO_OBJECTVAL	"object value not supplied."

/////////////////////////////////////////////////////////////////////////////

#endif // __PROTO_H__

