/////////////////////////////////////////////////////////////////////////////
//
// OBJECTDATABASE.H : Object Database application
//
// Copyright(c) 2006 Thomas A. Rieck, All Rights Reserved
//

#ifndef __OBJECTDATABASE_H__
#define __OBJECTDATABASE_H__

/////////////////////////////////////////////////////////////////////////////
class ObjectDatabase {
    // Construction / Destruction
private:
    ObjectDatabase();
public:
    virtual ~ObjectDatabase();

    typedef auto_ptr<ObjectDatabase> ObjectDatabasePtr;

// Interface
    static ObjectDatabase *instance();
    int Run(int argc, char **argv);

// Implementation
private:
    static ObjectDatabasePtr This;
    Service *pservice;
};
/////////////////////////////////////////////////////////////////////////////

#endif // __OBJECTDATABASE_H__