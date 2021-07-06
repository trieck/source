#pragma once

enum class ObjectType
{
    NONE,
    APPID,
    CLSID,
    IID,
    TYPELIB
};

/////////////////////////////////////////////////////////////////////////////
struct ObjectData
{
    ObjectData();
    ObjectData(ObjectType t, const GUID& uuid, WORD maj = 0, WORD min = 0);
    ObjectData(ObjectType t, LPCTSTR pGUID, WORD maj = 0, WORD min = 0);
    ~ObjectData() = default;

    // no copy or move possible
    ObjectData(const ObjectData&) = delete;
    ObjectData(ObjectData&&) = delete;
    ObjectData& operator =(const ObjectData&) = delete;
    ObjectData& operator =(ObjectData&&) = delete;

    ObjectType type; // type of object
    GUID guid; // UUID of object or GUID_NULL for none
    WORD wMaj; // major version of typelib
    WORD wMin; // minor version of typelib
};

using LPOBJECTDATA = ObjectData*;
