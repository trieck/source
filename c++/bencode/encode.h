/////////////////////////////////////////////////////////////////////////////
//
// ENCODE.H : Encode Bencoded Object
//
// Copyright(c) 2006 Thomas A. Rieck, All Rights Reserved
//

#ifndef __ENCODE_H__
#define __ENCODE_H__

/////////////////////////////////////////////////////////////////////////////
class BEEncoder {
// Construction / Destruction
private:
    BEEncoder(ISequentialStream *pStream);
public:
    virtual ~BEEncoder();

// Interface
    static BOOL encode(LPBEOBJECT pObject, ISequentialStream *pStream);

// Implementation
private:
    BOOL EncodeObject(LPBEOBJECT pObject);
    BOOL EncodeDict(LPDICTIONARY d);
    BOOL EncodeList(LPLIST l);
    BOOL EncodeInt(LPINTEGER i);
    BOOL EncodeString(LPSTRING s);
    BOOL BeginDictionary();
    BOOL BeginList();
    BOOL BeginInteger();
    BOOL EndObject();
    BOOL Write(void *pv, INT nlen);
    BOOL WriteRawString(LPSTRING s);
    BOOL WriteRawInt(INT64 i);
    BOOL WriteChar(char c);

    ISequentialStream *m_pStream;
};
/////////////////////////////////////////////////////////////////////////////

typedef auto_ptr<BEEncoder> BEEncoderPtr;

#endif // __ENCODE_H__