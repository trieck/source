/////////////////////////////////////////////////////////////////////////////
//
// WINAPP.CPP : application class
//
// Copyright (c) 1999 Rieck Enterprises
//

#include "common.h"

// singleton instance
WinApp *pApp = NULL;

WinApp::WinApp()
{
	pApp = this;
	m_nExitCode = 0;
}

WinApp::~WinApp()
{
}

int WinApp::Run()
{
	MSG msg;

	while (GetMessage(&msg, (HWND) NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	m_nExitCode = msg.wParam;

	return ExitInstance();
}

int WinApp::ExitInstance()
{
	// Return the exit code to the system.
	return m_nExitCode;
}

// main entry point
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR command, int nCmdShow)
{
	ASSERT(pApp != NULL);

	pApp->m_hInstance = hInstance;
	pApp->m_command = command;
	pApp->m_nCmdShow = nCmdShow;

	if (!pApp->InitInstance())
		return 0;

	if (!pApp->Run())
		return 0;

	return pApp->ExitInstance();
}
