/////////////////////////////////////////////////////////////////////////////
//
//	EXCEPT.H	exception classes
//
//	Copyright (c) 1999 Thomas A. Rieck

#ifndef __EXCEPT_H__
#define __EXCEPT_H__

#define E_FRAMEUNDERRUN			1001
#define E_CALLNESTEDTOODEEP		1002
#define E_STACKUNDERRUN			1003
#define E_STACKTOODEEP			1004

#define W_DIVIDEBYZERO			5003
#define W_LITERALASSIGN			5004
#define W_NONVARASSIGN			5005
#define W_EVALLITERAL			5006
#define W_UNDEFINEDVAR			5007
#define W_PROCRETVAL			5008
#define W_FUNCRETNOVAL			5009
#define W_NOTENOUGHARGS			5010

/////////////////////////////////////////////////////////////////////////////
class Exception {
    friend ostream & operator << (ostream & os, const Exception & e);
public:
    Exception(int);
    Exception(const Exception &);
    ~Exception() {};

    Exception & operator = (const Exception &);
protected:
    int ncode;
    string desc;
};
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
class Warning : public Exception {
public:
    Warning(int);
    ~Warning() {}
};
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
class Error : public Exception {
public:
    Error(int);
    ~Error() {}
};
/////////////////////////////////////////////////////////////////////////////

#endif // __EXCEPT_H__

