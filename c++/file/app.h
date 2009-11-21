/////////////////////////////////////////////////////////////////////////////
//
// APP.H : Win32 application class
//

#ifndef __APP_H__
#define __APP_H__

#include "winthrd.h"

/////////////////////////////////////////////////////////////////////////////
class Application : public WinThread {
public:
// Construction / Destruction
	Application();
	virtual ~Application();

// Interface
	virtual bool initInstance();
	virtual bool run();
	virtual int exitInstance();

	HMODULE getInstance() const;
	const LPCTSTR getName() const;

// Implementation
protected:
private:
	LPTSTR name;
	HMODULE instance;
};
/////////////////////////////////////////////////////////////////////////////

inline const LPCTSTR Application::getName() const
{
	return name;
}
inline HMODULE Application::getInstance() const
{
	return instance;
}
Application *getApp();

#endif // __APP_H__

