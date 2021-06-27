/*--------------------------------------------
    Module  :   PUB.CPP
    Purpose :   Public Component Client
    Date    :   07/19/1997
---------------------------------------------*/
#include "pch.h"
#include "PubApp.h"

PubApp theApp;

int WINAPI _tWinMain(HINSTANCE /*hInstance*/, HINSTANCE /*hPrevInstance*/, LPTSTR /*lpstrCmdLine*/, int /*nCmdShow*/)
{
    int result{};

    try {
        if (!theApp.Init()) {
            return 1;
        }

        result = theApp.Run();
    } catch (std::exception& e) {
        ATLTRACE2("%s\n", e.what());
        return 1;
    }

    return result;

}

