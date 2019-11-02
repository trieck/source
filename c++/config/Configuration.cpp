/////////////////////////////////////////////////////////////////////////////
//
// CONFIGURATION.CPP : Configuration class
//
// This class is meant to be a replacement for GetPrivateProfileString, etc.
// which do not exist on a Unix system.  This class implements only the
// most basic functionality.
//
// Copyright (c) 2004, Thomas A. Rieck
// All Rights Reserved
//
#include "common.h"
#include "Exception.h"
#include "Configuration.h"

namespace
{
string GetValue(FILE *fp);
bool FindApp(const char *app, FILE *fp);
bool FindKey(const char *key, FILE *fp);
string trim(const string &str);
string trim_left(const string &str);
string trim_right(const string &str);
}

/////////////////////////////////////////////////////////////////////////////
Configuration::Configuration(const char *pfile)
    : filename(pfile)
{
    // check read permission
    if (_access(pfile, 04) == -1)
        throw Exception("file is not readable.");
}

/////////////////////////////////////////////////////////////////////////////
Configuration::~Configuration()
{
}

/////////////////////////////////////////////////////////////////////////////
string Configuration::GetValue(const char *app, const char *key,
                               const char *def)
{
    string output;

    FILE *fp = fopen(filename.c_str(), "r");
    if (fp == NULL)
        throw Exception("cannot open file.");

    if (!FindApp(app, fp)) {
        fclose(fp);
        return def;
    }

    if (!FindKey(key, fp)) {
        fclose(fp);
        return def;
    }

    output = ::GetValue(fp);

    fclose(fp);

    return output;
}

/////////////////////////////////////////////////////////////////////////////
// for Regression testing
string Configuration::GetValueEx(const char *app, const char *key,
                                 const char *def)
{
    char buf[256] = { 0 };
    GetPrivateProfileString(app, key, def, buf, sizeof(buf), filename.c_str());
    return buf;
}

namespace  	// anonymous
{

/////////////////////////////////////////////////////////////////////////////
bool FindApp(const char *app, FILE *fp)
{
    int c;
    string capp;

    while ((c = getc(fp)) != -1) {
        switch (c) {
        case '\n':
        case '[':
            capp = "";
            break;
        case ']':
            if (stricmp(trim(capp).c_str(), app) == 0)
                return true;
            break;
        default:
            capp += (char)c;
            break;
        }
    }

    return false;
}

/////////////////////////////////////////////////////////////////////////////
bool FindKey(const char *key, FILE *fp)
{
    int c, bdone = 0;
    string ckey;

    while ((c = getc(fp)) != -1) {
        switch (c) {
        case '\n':
            ckey = "";
            bdone = 0;
            break;
        case '[':
            return false;	// new section
        case '=':
            if (stricmp(trim(ckey).c_str(), key) == 0)
                return true;
            bdone = 1;
            break;
        default:
            if (!bdone)
                ckey += (char)c;
            break;
        }
    }

    return false;
}

/////////////////////////////////////////////////////////////////////////////
string GetValue(FILE *fp)
{
    string output;

    int c;
    while ((c = fgetc(fp)) != -1) {
        switch (c) {
        case '\n':
            return output;
        case '"':
            //TODO: handle quotes intelligently.
            break;
        default:
            output += (char)c;
            break;
        }
    }

    return output;
}

/////////////////////////////////////////////////////////////////////////////
string trim(const string &str)
{
    return trim_left(trim_right(str));
}

/////////////////////////////////////////////////////////////////////////////
string trim_left(const string &str)
{
    string::size_type i = 0;
    for ( ; i < str.length() && isspace(str[i]); i++)
        ;

    return str.substr(i);
}

/////////////////////////////////////////////////////////////////////////////
string trim_right(const string &str)
{
    string::size_type i = str.length() - 1;
    for ( ; i != -1 && isspace(str[i]); i--)
        ;

    return str.substr(0, i + 1);
}

}	// anonymous