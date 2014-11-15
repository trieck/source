/////////////////////////////////////////////////////////////////////////////
//
// DICTIONARY.H : Bencoded dictionary class
//
// Copyright(c) 2006 Thomas A. Rieck, All Rights Reserved
//

#ifndef __DICTIONARY_H__
#define __DICTIONARY_H__

#include "BEObject.h"
#include "BEString.h"

/////////////////////////////////////////////////////////////////////////////
struct StringLess : std::binary_function <LPSTRING, LPSTRING, bool> {
    bool operator()(LPSTRING left, LPSTRING right) const {
        int n = min(left->GetLength(), right->GetLength());
        return memcmp(left->GetData(), right->GetData(), n) < 0;
    }
};

class DictIterator;

/////////////////////////////////////////////////////////////////////////////
class Dictionary : public BEObject {
private:
    // Construction / Destruction
    Dictionary();
public:
    Dictionary(const Dictionary &d);
    ~Dictionary();

// Interface
    Dictionary &operator =(const Dictionary &rhs);

    virtual ObjectType GetType() const {
        return BET_DICT;
    }
    virtual LPBEOBJECT Copy() const;

    void Set(LPSTRING k, LPBEOBJECT v);
    void Set(LPCSTR k, LPBEOBJECT v);
    void Set(LPCSTR k, LPCSTR v);
    void Set(LPCSTR k, const string &v);
    void Set(LPCSTR k, INT64 v);
    LPBEOBJECT Get(LPSTRING k);
    LPBEOBJECT Get(LPCSTR k);
    DictIterator GetIterator() const;

    typedef map<LPSTRING, LPBEOBJECT, StringLess> ObjectMap;
    typedef ObjectMap::const_iterator CIterator;
    typedef const std::pair<LPSTRING, LPBEOBJECT> ObjectEntry;

// Implementation
private:
    ObjectMap m;
    friend Dictionary *MakeDictionary();
};
/////////////////////////////////////////////////////////////////////////////

typedef Dictionary *LPDICTIONARY;

/////////////////////////////////////////////////////////////////////////////
class DictIterator {
public:
    DictIterator(Dictionary::CIterator s, Dictionary::CIterator e) {
        start = it = s;
        end = e;
    }
    DictIterator(const DictIterator &rhs) {
        *this = rhs;
    }
    DictIterator &operator = (const DictIterator &rhs) {
        if (this != &rhs) {
            start = it = rhs.start;
            end = rhs.end;
        }
        return *this;
    }
    Dictionary::ObjectEntry GetNext() {
        return *it++;
    }
    bool HasNext() const {
        return it != end;
    }
    void Reset() {
        it = start;
    }
private:
    Dictionary::CIterator start, end, it;
};

/////////////////////////////////////////////////////////////////////////////
// Global helpers
LPDICTIONARY MakeDictionary();

#endif // __DICTIONARY_H__