/////////////////////////////////////////////////////////////////////////////
//
// GETHANDLER.CPP : Object value retrieval handler
//
// Copyright(c) 2006 Thomas A. Rieck, All Rights Reserved
//

#include "stdafx.h"
#include "Conn.h"
#include "BEObject.h"
#include "Dictionary.h"
#include "Integer.h"
#include "Handler.h"
#include "GetHandler.h"
#include "Elog.h"
#include "Proto.h"
#include "ObjectDB.h"

/////////////////////////////////////////////////////////////////////////////
GetHandler::GetHandler()
{
}

/////////////////////////////////////////////////////////////////////////////
GetHandler::~GetHandler()
{
}

/////////////////////////////////////////////////////////////////////////////
void GetHandler::Call(LPDICTIONARY request, LPDICTIONARY response)
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

    // Retrieve object from the database
    ObjectDB *pDB = ObjectDB::instance();
    LPBEOBJECT pObject = pDB->GetObject(poolid, objectid);
    if (pObject == NULL) {
        response->Set(KEY_RESPONSE_CD, E_CANT_GET);
        response->Set(KEY_RESPONSE_MSG, lasterror());
        return;
    }

    response->Set(KEY_RESPONSE_CD, INT64(E_OK));
    response->Set(KEY_RESPONSE_MSG, pObject->Copy());
}
