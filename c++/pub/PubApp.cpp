#include "pch.h"
#include "PubApp.h"
#include "MainFrame.h"
#include "AdviseSink.h"
#include "DrawObject_i.h"
#include "ComCreator.h"

bool PubApp::Init()
{
    auto hr = CAppModule::Init(nullptr, ModuleHelper::GetModuleInstance());
    if (FAILED(hr)) {
        return false;
    }

    hr = ComCreator::Create<AdviseSink>(m_pAdviseSink);
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

    Release();

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

    // Create an advistory connection
    hr = Advise();
    if (FAILED(hr)) {
        m_pDraw.Release();
        return hr;
    }

    pDrawObject = m_pDraw;

    return hr;
}

CComPtr<IDrawObject> PubApp::GetDrawObject() const
{
    return m_pDraw;
}

HRESULT PubApp::Advise()
{
    if (!(m_pAdviseSink && m_pDraw)) {
        return E_POINTER;
    }

    Unadvise();

    FORMATETC fe{};
    fe.cfFormat = CF_ENHMETAFILE;
    fe.dwAspect = DVASPECT_CONTENT;
    fe.ptd = nullptr;
    fe.tymed = TYMED_ENHMF;
    fe.lindex = -1;

    CComQIPtr<IDataObject> pDataObject(m_pDraw);
    if (pDataObject == nullptr) {
        return E_NOINTERFACE;
    }

    auto hr = pDataObject->DAdvise(&fe, ADVF_NODATA, m_pAdviseSink, &m_dwConn);

    return hr;
}

HRESULT PubApp::Unadvise()
{
    if (!m_pDraw) {
        return E_POINTER;
    }

    CComQIPtr<IDataObject> pDataObject(m_pDraw);
    if (pDataObject == nullptr) {
        return E_NOINTERFACE;
    }

    auto hr = pDataObject->DUnadvise(m_dwConn);

    m_dwConn = 0;

    return hr;
}

void PubApp::Release()
{
    Unadvise();
    m_pAdviseSink.Release();
    m_pDraw.Release();
}
