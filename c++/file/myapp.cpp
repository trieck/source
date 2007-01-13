/////////////////////////////////////////////////////////////////////////////
//
// MYAPP.CPP
//

#include "common.h"
#include "myapp.h"
#include "framewnd.h"

MyApp::MyApp()
{
}

MyApp::~MyApp()
{
}

bool MyApp::initInstance()
{
	mainWnd = new FrameWindow();

	mainWnd->create(_T(""), _T(""), WS_OVERLAPPEDWINDOW);

	mainWnd->updateWindow();
	mainWnd->showWindow(SW_SHOW);

	return TRUE;
}

bool MyApp::run()
{
	return Application::run();
}

int MyApp::exitInstance()
{
	return Application::exitInstance();
}


