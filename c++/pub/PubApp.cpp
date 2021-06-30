#include "pch.h"
#include "PubApp.h"
#include "MainFrame.h"

bool PubApp::Init()
{
    auto hr = OleInitialize(nullptr);
    if (FAILED(hr)) {
        return FALSE;
    }

    hr = CAppModule::Init(nullptr, ModuleHelper::GetModuleInstance());
    if (FAILED(hr)) {
        return false;
    }

    return true;
}

int PubApp::Run()
{
    CMessageLoop theLoop;
    AddMessageLoop(&theLoop);

    MainFrame wndMain;
    if (!wndMain.CreateEx()) {
        throw std::exception("main window creation failed.");
    }

    STARTUPINFO info;
    GetStartupInfo(&info);
    const auto nCmdShow = info.dwFlags & STARTF_USESHOWWINDOW
                              ? info.wShowWindow
                              : SW_SHOWDEFAULT;

    wndMain.ShowWindow(nCmdShow);

    auto result = theLoop.Run();

    RemoveMessageLoop();

    OleFlushClipboard();
    Release();
    OleUninitialize();

    Term();

    return result;
}

HRESULT PubApp::CreateObject(CComPtr<IDrawObject>& pDrawObject)
{
    m_pDraw.Release();

    auto hr = m_pDraw.CoCreateInstance(__uuidof(DrawObject));
    if (FAILED(hr)) {
        return hr;
    }

    pDrawObject = m_pDraw;

    return hr;
}

CComPtr<IDrawObject> PubApp::GetDrawObject() const
{
    return m_pDraw;
}

void PubApp::Release()
{
    m_pDraw.Release();
}
