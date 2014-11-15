/////////////////////////////////////////////////////////////////////////////
//
// SETHANDLER.CPP : Object value set handler
//
// Copyright(c) 2006 Thomas A. Rieck, All Rights Reserved
//

#include "stdafx.h"
#include "Conn.h"
#include "BEObject.h"
#include "Dictionary.h"
#include "Integer.h"
#include "Handler.h"
#include "SetHandler.h"
#include "Elog.h"
#include "Proto.h"
#include "ObjectDB.h"

/////////////////////////////////////////////////////////////////////////////
SetHandler::SetHandler()
{
}

/////////////////////////////////////////////////////////////////////////////
SetHandler::~SetHandler()
{
}

/////////////////////////////////////////////////////////////////////////////
void SetHandler::Call(LPDICTIONARY request, LPDICTIONARY response)
{
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

    LPBEOBJECT pObjectID = request->Get(KEY_OBJECT_ID);
    if (pObjectID == NULL) {
        response->Set(KEY_RESPONSE_CD, E_INC_REQUEST);
        response->Set(KEY_RESPONSE_MSG, RESP_NO_OBJECTID);
        return;
    }

    if (pObjectID->GetType() != BEObject::BET_STRING) {
        response->Set(KEY_RESPONSE_CD, E_BAD_REQUEST);
        response->Set(KEY_RESPONSE_MSG, RESP_OBJ_FMT);
        return;
    }

    string objectid = *static_cast<LPSTRING>(pObjectID);

    LPBEOBJECT pObject = request->Get(KEY_OBJECT_VAL);
    if (pObject == NULL) {
        response->Set(KEY_RESPONSE_CD, E_INC_REQUEST);
        response->Set(KEY_RESPONSE_MSG, RESP_NO_OBJECTVAL);
        return;
    }

    // Set object value in the database
    ObjectDB *pDB = ObjectDB::instance();
    BOOL result = pDB->SetObject(poolid,
                                 objectid, pObject);
    if (!result) {
        response->Set(KEY_RESPONSE_CD, E_CANT_SET);
        response->Set(KEY_RESPONSE_MSG, lasterror());
        return;
    }

    response->Set(KEY_RESPONSE_CD, INT64(E_OK));
}
