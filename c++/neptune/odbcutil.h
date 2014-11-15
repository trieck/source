///////////////////////////////////////////////////////////////////////////////// ODBCUTIL.H : ODBC utility classes//#ifndef __ODBCUTIL_H__#define __ODBCUTIL_H__/////////////////////////////////////////////////////////////////////////////class Environment {public:// Construction / Destruction    Environment();    virtual ~Environment();// Interface    operator SQLHENV() const;// implementationprotected:    bool allocenv();    bool freeenv();private:    SQLHENV hEnv;};/////////////////////////////////////////////////////////////////////////////inline Environment::operator SQLHENV() const{    return hEnv;}// forward declarationsclass Recordset;typedef vector<Recordset *> RecordsetVec;/////////////////////////////////////////////////////////////////////////////class Connection {public:// Construction / Destruction    Connection();    virtual ~Connection();// Interface    bool setAttributes(SQLINTEGER Attribute, SQLPOINTER ptr, SQLINTEGER len);    bool connect(LPCTSTR server, LPCTSTR uid, LPCTSTR pwd);    bool disconnect();    operator SQLHDBC() const;// implementationprotected:    bool allocconn();    bool freeconn();    void append(Recordset *R);    void remove(Recordset *R);    void closesets();private:    RecordsetVec recordsets;    static Environment E;    SQLHDBC hDbc;    DWORD loginTimeout;    friend class Recordset;};//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////inline Connection::operator SQLHDBC() const{    return hDbc;}#define MAX_FNAME_LEN	256 // Max size of field namestypedef struct {    SQLCHAR name[MAX_FNAME_LEN + 1];    SWORD type;    UDWORD precision;    SWORD scale;    SWORD nullable;} FieldInfo;// forward declarationsclass DBVariant;/////////////////////////////////////////////////////////////////////////////class Recordset {public:// Construction / Destruction    Recordset(Connection *conn);    virtual ~Recordset();// Interface    bool open(LPCTSTR sql);    bool close();    void reset();    void getFieldValue(LPCTSTR name, DBVariant & V);    void getFieldValue(int index, DBVariant & V);    operator SQLHSTMT() const;// implementationprotected:    bool allocstmt();    bool freestmt();    bool fetchRowset();    static void* getDataBuffer(DBVariant& varValue, short fieldtype,                               int* pnLen, short sqltype, UDWORD precision);    static int getTextLen(short sqltype, UDWORD precision);    long getData(short fieldindex, short fieldtype, LPVOID pvData,                 int len);    int getFieldIndex(LPCTSTR name) const;private:    Connection *C;    SQLHSTMT hStmt;    SQLSMALLINT columns;    FieldInfo *fieldinfo;};//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////inline Recordset::operator SQLHSTMT() const{    return hStmt;}/////////////////////////////////////////////////////////////////////////////class DBException {public:// Construction / Destruction    DBException(SQLSMALLINT HandleType, SQLHANDLE Handle);    DBException(UINT ID);    DBException(const DBException &);    virtual ~DBException();// Interface    DBException & operator = (const DBException &);    LPCTSTR getDescription() const;private:    SQLCHAR state[SQL_SQLSTATE_SIZE + 1];    SQLCHAR message[1024];    SQLINTEGER nativeErr;};/////////////////////////////////////////////////////////////////////////////inline LPCTSTR DBException::getDescription() const{    return (LPCTSTR)message;}/////////////////////////////////////////////////////////////////////////////class DBVariant {// Construction / Destructionpublic:    DBVariant();    ~DBVariant();// Interface    enum Type {        vt_null = 0,        vt_bool,        vt_uchar,        vt_short,        vt_long,        vt_single,        vt_double,        vt_date,        vt_string,        vt_binary    };    Type type;    union {        bool boolVal;        unsigned char chVal;        short iVal;        long lVal;        float fltVal;        double dblVal;        TIMESTAMP_STRUCT* pdate;        TCHAR* pstring;        BYTE* pbinary;    };    void clear();// Implementation};/////////////////////////////////////////////////////////////////////////////#endif // __ODBCUTIL_H__