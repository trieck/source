/////////////////////////////////////////////////////////////////////////////
//
// WINTHRD.CPP : Win32 application class
//

#include "common.h"

WinThread::WinThread()
		: thread(0),
		mainWnd(0)
{
	currentMessage.message = WM_NULL;
}

WinThread::~WinThread()
{
}

bool WinThread::initInstance()
{
	return TRUE;
}

bool WinThread::run()
{
	return pumpMessages();
}

int WinThread::exitInstance()
{
	return 0;
}

bool WinThread::pumpMessages()
{
	for (;;) {
		bool idle = true;

		while (idle && !::PeekMessage(&currentMessage, NULL, NULL, NULL, PM_NOREMOVE)) {
			if (!onIdle())
				idle = false;
		}

		do {
			// pump message, but quit on WM_QUIT
			if (!pumpMessage())
				return exitInstance() == 0;

		} while (::PeekMessage(&currentMessage, NULL, NULL, NULL, PM_NOREMOVE));
	}

	return false;	// not reachable
}

bool WinThread::pumpMessage()
{
	if (!::GetMessage(&currentMessage, NULL, NULL, NULL)) {
		return false;
	}

	// process this message
	::TranslateMessage(&currentMessage);
	::DispatchMessage(&currentMessage);

	return true;
}

bool WinThread::onIdle()
{
	return FALSE;
}

