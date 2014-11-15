/////////////////////////////////////////////////////////////////////////////
//
// MAKEPOOLHANDLER.CPP : Pool creation handler
//
// Copyright(c) 2006 Thomas A. Rieck, All Rights Reserved
//

#include "stdafx.h"
#include "Conn.h"
#include "BEObject.h"
#include "Dictionary.h"
#include "Integer.h"
#include "Handler.h"
#include "MakePoolHandler.h"
#include "Elog.h"
#include "Proto.h"
#include "ObjectDB.h"

/////////////////////////////////////////////////////////////////////////////
MakePoolHandler::MakePoolHandler()
{
}

/////////////////////////////////////////////////////////////////////////////
MakePoolHandler::~MakePoolHandler()
{
}

/////////////////////////////////////////////////////////////////////////////
void MakePoolHandler::Call(LPDICTIONARY request, LPDICTIONARY response)
{
    // Make a new pool
    ObjectDB *pDB = ObjectDB::instance();
    LPCSTR poolid = pDB->MakePool();
    if (poolid == NULL) {
        response->Set(KEY_RESPONSE_CD, E_CANT_CREATE);
        response->Set(KEY_RESPONSE_MSG, lasterror());
        return;
    }

    response->Set(KEY_RESPONSE_CD, INT64(E_OK));
    response->Set(KEY_RESPONSE_MSG, poolid);
}
