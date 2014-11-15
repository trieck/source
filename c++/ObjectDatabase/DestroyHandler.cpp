/////////////////////////////////////////////////////////////////////////////
//
// DESTROYHANDLER.CPP : Object destruction handler
//
// Copyright(c) 2006 Thomas A. Rieck, All Rights Reserved
//

#include "stdafx.h"
#include "Conn.h"
#include "BEObject.h"
#include "Dictionary.h"
#include "Integer.h"
#include "Handler.h"
#include "DestroyHandler.h"
#include "Elog.h"
#include "Proto.h"
#include "ObjectDB.h"

/////////////////////////////////////////////////////////////////////////////
DestroyHandler::DestroyHandler()
{
}

/////////////////////////////////////////////////////////////////////////////
DestroyHandler::~DestroyHandler()
{
}

/////////////////////////////////////////////////////////////////////////////
void DestroyHandler::Call(LPDICTIONARY request, LPDICTIONARY response)
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

    LPBEOBJECT object = request->Get(KEY_OBJECT_ID);
    if (object == NULL) {	// no object id supplied
        response->Set(KEY_RESPONSE_CD, E_INC_REQUEST);
        response->Set(KEY_RESPONSE_MSG, RESP_NO_OBJECTID);
        return;
    }

    if (object->GetType() != BEObject::BET_STRING) {
        response->Set(KEY_RESPONSE_CD, E_BAD_REQUEST);
        response->Set(KEY_RESPONSE_MSG, RESP_OBJ_FMT);
        return;
    }

    string objectid = *static_cast<LPSTRING>(object);

    // Destroy the object
    ObjectDB *pDB = ObjectDB::instance();
    BOOL result = pDB->DestroyObject(poolid, objectid);
    if (!result) {
        response->Set(KEY_RESPONSE_CD, E_CANT_DESTROY);
        response->Set(KEY_RESPONSE_MSG, lasterror());
        return;
    }

    response->Set(KEY_RESPONSE_CD, INT64(E_OK));
}
