/////////////////////////////////////////////////////////////////////////////
//
// APP.CPP : Win32 application class
//

#include "common.h"
#include "resource.h"

namespace
{
Application* currentApp = NULL;
}

static tstring getFileName();

Application::Application()
{
    // one time initialization only
    ASSERT(currentApp == NULL);

    instance = GetModuleHandle(NULL);
    currentApp = this;

    // get application name
    string appname;
    if (!loadString(IDS_APP_NAME, appname))
        name = _tcsdup(getFileName().c_str());
    else name = _tcsdup(appname.c_str());
}

Application::~Application()
{
    free(name);
}

Application *getApp()
{
    return currentApp;
}

bool Application::initInstance()
{
    return TRUE;
}

bool Application::run()
{
    if (mainWnd == NULL) {
        return false;
    }

    return WinThread::run();
}

int Application::exitInstance()
{
    return currentMessage.wParam;
}

/////////////////////////////////////////////////////////////////////////////
string getFileName()
{
    TCHAR path[_MAX_PATH + _MAX_FNAME + 1];
    GetModuleFileName(getInstance(), path, _MAX_PATH + _MAX_FNAME);

    TCHAR *ppath = _tcsrchr(path, '\\');
    ASSERT(ppath);
    if (ppath) {
        ppath++;
        TCHAR *pext = _tcschr(path, '.');
        ASSERT(pext);
        *pext = _T('\0');
    }

    return ppath;
}