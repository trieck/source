///////////////////////////////////////////////////////////////////////////////// MAPS.H : global handle maps//#ifndef __MAPS_H__#define __MAPS_H__#include "types.h"#include "odbcutil.h"#define MAXENTRIES 1000/////////////////////////////////////////////////////////////////////////////template <class T> class handleMap {// Construction / Destructionpublic:    handleMap();    virtual ~handleMap();// Interface    HANDLE insert(T);    BOOL remove(HANDLE);    T lookup(HANDLE);    void cleanup();// Implementationprotected:private:    T entries[MAXENTRIES];};//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////template <class T> handleMap<T>::handleMap(){    memset(entries, 0, sizeof(entries));}/////////////////////////////////////////////////////////////////////////////template <class T> handleMap<T>::~handleMap(){    cleanup();}/////////////////////////////////////////////////////////////////////////////template <class T> HANDLE handleMap<T>::insert(T object){    T *pentry = entries;    for ( ; pentry < entries + MAXENTRIES; pentry++) {        if (*pentry == NULL) {            *pentry = object;            return (HANDLE)(++pentry - entries);        }    }    return NULL; // map is full}/////////////////////////////////////////////////////////////////////////////template <class T> BOOL handleMap<T>::remove(HANDLE handle){    T *pentry = entries;    for ( ; pentry < entries + MAXENTRIES; pentry++) {        if ((HANDLE)(pentry + 1 - entries) == handle) {            if (*pentry) delete *pentry;            *pentry = NULL;            return TRUE;        }    }    return FALSE;	// bogus handle}/////////////////////////////////////////////////////////////////////////////template <class T> T handleMap<T>::lookup(HANDLE handle){    T *pentry = entries;    for ( ; pentry < entries + MAXENTRIES; pentry++) {        if ((HANDLE)(pentry + 1 - entries) == handle) {            return *pentry;        }    }    return (T)NULL;}/////////////////////////////////////////////////////////////////////////////template <class T> void handleMap<T>::cleanup(){    T* p = entries;    for ( ; p < entries + MAXENTRIES; p++) {        if (*p) delete *p;    }    memset(entries, 0, sizeof(entries));}typedef handleMap<Connection *> ConnectionMap;typedef handleMap<Recordset *> RecordsetMap;/////////////////////////////////////////////////////////////////////////////extern ConnectionMap dbmap;extern RecordsetMap rsmap;/////////////////////////////////////////////////////////////////////////////#endif // __TYPES_H__