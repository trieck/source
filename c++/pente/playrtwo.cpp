/////////////////////////////////////////////////////////////////////////////
//
//	PLAYRTWO.CPP : Player Two Class
//
#include "stdafx.h"
#include "playrtwo.h"
#include "resource.h"

IMPLEMENT_DYNAMIC(PlayerTwo, Player)
/////////////////////////////////////////////////////////////////////////////
PlayerTwo::PlayerTwo()
{
	hPiece = (HICON)LoadImage(AfxGetResourceHandle(),
		MAKEINTRESOURCE(IDI_REDPIECE),
		IMAGE_ICON,
		0, 0, LR_SHARED);
	ASSERT(hPiece != NULL);
}
/////////////////////////////////////////////////////////////////////////////
PlayerTwo::~PlayerTwo()
{
}