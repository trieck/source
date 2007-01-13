/////////////////////////////////////////////////////////////////////////////
//
// WINTHRD.H : Win32 Thread class
//

#ifndef __WINTHRD_H__
#define __WINTHRD_H__

#include "window.h"

/////////////////////////////////////////////////////////////////////////////
class WinThread
{
public:
// Construction / Destruction
	WinThread();
	virtual ~WinThread();

// Interface 
	virtual bool initInstance();
	virtual bool run();
	virtual int exitInstance();

	Window *getMainWnd() const;

// Implementation
protected:
	bool pumpMessages();
	bool pumpMessage();
	bool onIdle();

	Window *mainWnd;
	MSG currentMessage;
private:
	HANDLE thread;
};
/////////////////////////////////////////////////////////////////////////////

inline Window *WinThread::getMainWnd() const {
	return mainWnd;
}

#endif // __WINTHRD_H__

