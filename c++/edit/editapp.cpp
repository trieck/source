/////////////////////////////////////////////////////////////////////////////
//
// EDITAPP.CPP : application class
//
// Copyright (c) 1999 Rieck Enterprises
//

#include "common.h"
#include "editapp.h"
#include "editfram.h"

static EditApp theApp;

EditApp::EditApp()
{
}

EditApp::~EditApp()
{
}

BOOL EditApp::InitInstance()
{
	Window *pWnd = new EditFrame("Toast");

	pWnd->Show();
	pWnd->Update();

	return TRUE;
}

