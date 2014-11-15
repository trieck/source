/////////////////////////////////////////////////////////////////////////////
//
// CONFIGURATION.H : Configuration class
//
// This class is meant to be a replacement for GetPrivateProfileString, etc.
// which do not exist on a Unix system.  This class implements only the
// most basic functionality.
//
// Copyright (c) 2004, Thomas A. Rieck
// All Rights Reserved
//

#ifndef __CONFIGURATION_H__
#define __CONFIGURATION_H__

/////////////////////////////////////////////////////////////////////////////
class Configuration {
// Construction / Destruction
public:
    Configuration(const char *pfile);
    virtual ~Configuration();

// Interface
    string GetValue(const char *app, const char *key, const char *def = "");
    string GetValueEx(const char *app, const char *key, const char *def = "");

// Implementation
private:
    string filename;
};
/////////////////////////////////////////////////////////////////////////////

#endif // __CONFIGURATION_H__