/////////////////////////////////////////////////////////////////////////////
//
//	PLAYRONE.CPP : Player One Class
//
#include "stdafx.h"
#include "playrone.h"
#include "resource.h"

IMPLEMENT_DYNAMIC(PlayerOne, Player)
/////////////////////////////////////////////////////////////////////////////
PlayerOne::PlayerOne()
{
	hPiece = (HICON)LoadImage(AfxGetResourceHandle(),
		MAKEINTRESOURCE(IDI_GREENPIECE),
		IMAGE_ICON,
		0, 0, LR_SHARED);
	ASSERT(hPiece != NULL);
}
/////////////////////////////////////////////////////////////////////////////
PlayerOne::~PlayerOne()
{
}