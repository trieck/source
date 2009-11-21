// List.cpp: implementation of the List class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TorrentExplorer.h"
#include "List.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

List::List()
{

}

List::~List()
{
	LPTORRENTOBJECT t;

	POSITION pos = list.GetHeadPosition();
	while (pos != NULL) {
		t = list.GetNext(pos);
		delete t;
	}
}

//////////////////////////////////////////////////////////////////////
void List::append(LPTORRENTOBJECT t)
{
	list.AddTail(t);
}

//////////////////////////////////////////////////////////////////////
UINT List::size() const
{
	return list.GetCount();
}

//////////////////////////////////////////////////////////////////////
LPTORRENTOBJECT List::GetAt(UINT n) const
{
	POSITION pos = list.FindIndex(n);
	if (pos == NULL)
		return NULL;

	return list.GetAt(pos);
}