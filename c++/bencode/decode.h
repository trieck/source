/////////////////////////////////////////////////////////////////////////////
//
// DECODE.H : Decode Bencoded stream
//
// Copyright(c) 2006 Thomas A. Rieck, All Rights Reserved
//

#ifndef __DECODE_H__
#define __DECODE_H__

/////////////////////////////////////////////////////////////////////////////
class BEDecoder
{
// Construction / Destruction
private:
    BEDecoder(IPeekableStream *pStream);
public:
    virtual ~BEDecoder();

// Interface
    static LPBEOBJECT decode(IPeekableStream *pStream);

// Implementation
private:
    LPBEOBJECT LoadObject();
    LPINTEGER LoadInteger();
    LPSTRING LoadString();
    LPLIST LoadList();
    LPDICTIONARY LoadDictionary();

    int Gettok();
    int Getc();
    int Peek();

    IPeekableStream *m_pStream;
};
/////////////////////////////////////////////////////////////////////////////

typedef auto_ptr<BEDecoder> BEDecoderPtr;

#endif // __DECODE_H__