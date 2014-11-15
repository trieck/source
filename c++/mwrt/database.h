/////////////////////////////////////////////////////////////////////////////
//
// DATABASE.H : Encapsulates an ADO database connection
//
// Copyright(c) 2008 Thomas A. Rieck, All Rights Reserved
//

#ifndef __DATABASE_H__
#define __DATABASE_H__

#import "c:\Program Files\Common Files\System\ADO\msado27.tlb" \
	rename("EOF", "EndOfFile")

typedef ADODB::_RecordsetPtr  RecPtr;
typedef ADODB::_ConnectionPtr ConnPtr;
typedef ADODB::FieldsPtr FieldsPtr;
typedef ADODB::FieldPtr FieldPtr;

/////////////////////////////////////////////////////////////////////////////
class Database {
// Construction / Destruction
public:
    Database();
    ~Database();

// Interface
    void open(LPCTSTR uid, LPCTSTR pwd, LPCTSTR connStr) throw();
    void open(LPCTSTR provider, LPCTSTR path) throw();
    void close() throw();
    RecPtr execute(LPCTSTR command) throw();

// Implementation
private:
    ConnPtr m_Conn;
};

/////////////////////////////////////////////////////////////////////////////

#endif // __DATABASE_H__