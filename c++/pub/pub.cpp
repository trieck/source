/*--------------------------------------------
    Module  :   PUB.CPP
    Purpose :   Public Component Client
    Date    :   07/19/1997
---------------------------------------------*/
#include "pch.h"
#include "PubApp.h"

PubApp _Module;

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPTSTR /*lpstrCmdLine*/, int /*nCmdShow*/)
{
    int result;

    try {
        if (!_Module.Init()) {
            return 1;
        }

        result = _Module.Run();
    } catch (std::exception& e) {
        ATLTRACE2("%s\n", e.what());
        return 1;
    }

    return result;

}

