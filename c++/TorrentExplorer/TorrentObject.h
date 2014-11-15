#if !defined(AFX_TORRENTOBJECT_H__8E5E75D7_EF4D_432F_9E30_F83914017052__INCLUDED_)
#define AFX_TORRENTOBJECT_H__8E5E75D7_EF4D_432F_9E30_F83914017052__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TorrentObject.h : header file
//

// element types
#define ET_UNDEF	0
#define ET_INTEGER	1
#define ET_STRING	2
#define ET_LIST		3
#define ET_DICT		4

/////////////////////////////////////////////////////////////////////////////
// TorrentObject command target

class TorrentObject : public CObject {
public:
    TorrentObject();
    virtual ~TorrentObject();

// Attributes
public:
    virtual int GetElementType() const = 0;

// Operations
public:

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(TorrentObject)
public:
    //}}AFX_VIRTUAL
    //}}AFX_VIRTUAL

// Implementation
private:
};

typedef TorrentObject *LPTORRENTOBJECT;

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TORRENTOBJECT_H__8E5E75D7_EF4D_432F_9E30_F83914017052__INCLUDED_)
