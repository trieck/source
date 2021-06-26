#pragma once

#include <atlbase.h>
#include <atlcom.h>
#include <atltypes.h>
#include <atlapp.h>
#include <atlwin.h>
#include <atlcrack.h>
#include <atlframe.h>
#include <exception>

#define COMMAND_HANDLER2(id, code, func) \
    if ((uMsg == WM_COMMAND) && ((code) == HIWORD(wParam)) && ((id) == LOWORD(wParam))) \
    { \
        this->SetMsgHandled(TRUE); \
        func(); \
        lResult = 0; \
        if(this->IsMsgHandled()) \
            return TRUE; \
    }

#define MSG_WM_PAINT2(func) \
    if (uMsg == WM_PAINT) \
    { \
        this->SetMsgHandled(TRUE); \
        CPaintDC dc(m_hWnd); \
        func(dc); \
        lResult = 0; \
        if(this->IsMsgHandled()) \
            return TRUE; \
    }

#define WM_SETSTATUS            (WM_USER+1)
#define WM_OBJECT_CREATED       (WM_SETSTATUS+1)
