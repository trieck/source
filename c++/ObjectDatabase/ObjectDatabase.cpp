/////////////////////////////////////////////////////////////////////////////
//
// OBJECTDATABASE.CPP : Object Database application
//
// Copyright(c) 2006 Thomas A. Rieck, All Rights Reserved
//

#include "stdafx.h"
#include "service.h"
#include <atlutil.h>
#include "wthread.h"
#include "conn.h"
#include "ObjectDatabase.h"
#include "BEObject.h"
#include "Dictionary.h"
#include "Integer.h"
#include "List.h"
#include "String.h"
#include "Handler.h"
#include "ODBService.h"

ObjectDatabase::ObjectDatabasePtr ObjectDatabase::This;

/////////////////////////////////////////////////////////////////////////////
ObjectDatabase::ObjectDatabase()
{
    pservice = new ODBService();
}

/////////////////////////////////////////////////////////////////////////////
ObjectDatabase::~ObjectDatabase()
{
    delete pservice;
}

/////////////////////////////////////////////////////////////////////////////
ObjectDatabase* ObjectDatabase::instance()
{
    if (This.get() == NULL) {
        This = ObjectDatabasePtr(new ObjectDatabase());
    }

    return This.get();
}

/////////////////////////////////////////////////////////////////////////////
int ObjectDatabase::Run(int argc, char **argv)
{
    if (!pservice->Execute(argc, argv))
        return -1;

    return pservice->GetExitCode();
}

/////////////////////////////////////////////////////////////////////////////
// application entry point
int main(int argc, char **argv)
{
    ObjectDatabase *odb = ObjectDatabase::instance();
    return odb->Run(argc, argv);
}

