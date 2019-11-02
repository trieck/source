/////////////////////////////////////////////////////////////////////////////
//
// MYAPP.H
//

#ifndef __MYAPP_H__
#define __MYAPP_H__

#include "app.h"

/////////////////////////////////////////////////////////////////////////////
class MyApp : public Application
{
public:
// Construction / Destruction
    MyApp();
    ~MyApp();

// Interface
    bool initInstance();
    bool run();
    int exitInstance();

// Implementation
protected:
private:
};
/////////////////////////////////////////////////////////////////////////////

#endif // __MYAPP_H__

