/////////////////////////////////////////////////////////////////////////////
//
// CREATEHANDLER.CPP : Object creation handler
//
// Copyright(c) 2006 Thomas A. Rieck, All Rights Reserved
//

#include "stdafx.h"
#include "Conn.h"
#include "BEObject.h"
#include "Dictionary.h"
#include "Integer.h"
#include "Handler.h"
#include "CreateHandler.h"
#include "Elog.h"
#include "Proto.h"
#include "ObjectDB.h"

/////////////////////////////////////////////////////////////////////////////
CreateHandler::CreateHandler()
{
}

/////////////////////////////////////////////////////////////////////////////
CreateHandler::~CreateHandler()
{
}

/////////////////////////////////////////////////////////////////////////////
void CreateHandler::Call(LPDICTIONARY request, LPDICTIONARY response)
{
    LPBEOBJECT otype = request->Get(KEY_REQUEST_OTYPE);
    if (otype == NULL) {	// no object type supplied
        response->Set(KEY_RESPONSE_CD, E_INC_REQUEST);
        response->Set(KEY_RESPONSE_MSG, RESP_NO_OTYPE);
        return;
    }

    if (otype->GetType() != BEObject::BET_INTEGER) {
        response->Set(KEY_RESPONSE_CD, E_BAD_REQUEST);
        response->Set(KEY_RESPONSE_MSG, RESP_OBJ_FMT);
        return;
    }

    int ntype = *static_cast<LPINTEGER>(otype);
    if (ntype < OT_INTEGER || ntype > OT_DICT) {
        response->Set(KEY_RESPONSE_CD, E_BAD_REQUEST);
        response->Set(KEY_RESPONSE_MSG, RESP_BAD_OTYPE);
        return;
    };

    LPBEOBJECT pool = request->Get(KEY_POOL_ID);
    if (pool == NULL) {	// no pool id supplied
        response->Set(KEY_RESPONSE_CD, E_INC_REQUEST);
        response->Set(KEY_RESPONSE_MSG, RESP_NO_POOLID);
        return;
    }

    if (pool->GetType() != BEObject::BET_STRING) {
        response->Set(KEY_RESPONSE_CD, E_BAD_REQUEST);
        response->Set(KEY_RESPONSE_MSG, RESP_OBJ_FMT);
        return;
    }

    string poolid = *static_cast<LPSTRING>(pool);

    // object id is an optional parameter
    LPBEOBJECT pObjectID = request->Get(KEY_OBJECT_ID);
    if (pObjectID != NULL &&
            pObjectID->GetType() != BEObject::BET_STRING) {
        response->Set(KEY_RESPONSE_CD, E_BAD_REQUEST);
        response->Set(KEY_RESPONSE_MSG, RESP_OBJ_FMT);
        return;
    }

    LPSTRING pObjectKey = pObjectID == NULL ? NULL:
                          static_cast<LPSTRING>(pObjectID);

    // object value is an optional parameter
    LPBEOBJECT pValue = request->Get(KEY_OBJECT_VAL);

    // Create a new object
    ObjectDB *pDB = ObjectDB::instance();
    LPCSTR objectid = pDB->CreateObject(
                          poolid,
                          ntype,
                          pObjectKey,
                          pValue);
    if (objectid == NULL) {
        response->Set(KEY_RESPONSE_CD, E_CANT_CREATE);
        response->Set(KEY_RESPONSE_MSG, lasterror());
        return;
    }

    response->Set(KEY_RESPONSE_CD, INT64(E_OK));
    response->Set(KEY_RESPONSE_MSG, objectid);
}
