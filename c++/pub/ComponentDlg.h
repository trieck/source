#pragma once

class ComponentDlg :
    public CDialogImpl<ComponentDlg>,
    public CComObjectRoot,
    public IAdviseSink
{
public:
    DECLARE_PROTECT_FINAL_CONSTRUCT()
BEGIN_COM_MAP(ComponentDlg)
            COM_INTERFACE_ENTRY(IAdviseSink)
    END_COM_MAP()

BEGIN_MSG_MAP(ComponentDlg)
        MSG_WM_INITDIALOG(OnInitDialog)
        MESSAGE_HANDLER(WM_DRAWITEM, OnDrawItem)
        MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
        MESSAGE_HANDLER(WM_HSCROLL, OnHScroll)
        COMMAND_HANDLER2(IDC_CREATE, BN_CLICKED, OnCreateObject)
        COMMAND_HANDLER2(IDC_DRAW, BN_CLICKED, OnDrawObject)
        COMMAND_HANDLER2(IDC_COPY, BN_CLICKED, OnCopyObject)
        COMMAND_HANDLER2(IDC_LOAD, BN_CLICKED, OnLoadObject)
        COMMAND_HANDLER2(IDC_SAVE, BN_CLICKED, OnSaveObject)
        COMMAND_HANDLER2(IDC_EXIT, BN_CLICKED, OnExit)
    END_MSG_MAP()

    enum { IDD = IDD_COMPONENT };

    ComponentDlg()
    {
        InternalAddRef();
    }

    void FinalRelease()
    {
        Unadvise();
    }

    // IAdviseSink members
    void __stdcall OnDataChange(FORMATETC* pFormatetc, STGMEDIUM* pStgmed) override
    {
        if (pFormatetc == nullptr || pStgmed == nullptr) {
            return;
        }

        if (!(pFormatetc->dwAspect == DVASPECT_CONTENT && pFormatetc->cfFormat == CF_ENHMETAFILE)) {
            return;
        }

        if (pStgmed->tymed != TYMED_ENHMF) {
            return;
        }

        UpdateControls();
    }

    void __stdcall OnViewChange(DWORD dwAspect, LONG lindex) override
    {
    }

    void __stdcall OnRename(IMoniker* pmk) override
    {
    }

    void __stdcall OnSave() override
    {
    }

    void __stdcall OnClose() override
    {
    }

    BOOL OnInitDialog(CWindow /*wndFocus*/, LPARAM /*lInitParam*/)
    {
        auto hInstance = ModuleHelper::GetResourceInstance();
        ATLASSERT(hInstance);

        auto hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDR_MAINFRAME));
        ATLASSERT(hIcon);

        SetClassLongPtr(*this, GCLP_HICON, reinterpret_cast<LONG_PTR>(hIcon));

        SendDlgItemMessage(IDC_COLORSLIDE, TBM_SETRANGE, TRUE, MAKELONG(0, 255));

        return TRUE;
    }

    LRESULT OnDrawItem(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& bHandled)
    {
        bHandled = FALSE;

        auto dis = reinterpret_cast<LPDRAWITEMSTRUCT>(lParam);
        ATLASSERT(dis);

        if (dis->CtlID == IDC_COLOR) {
            auto value = static_cast<int>(SendDlgItemMessage(IDC_COLORSLIDE, TBM_GETPOS, 0, 0));
            auto color = RGB(value, 0, value); // some kind of purple

            SetBkColor(dis->hDC, color);
            ExtTextOut(dis->hDC, 0, 0, ETO_OPAQUE, &dis->rcItem, nullptr, 0, nullptr);
            bHandled = TRUE;
        }

        return TRUE;
    }

    LRESULT OnHScroll(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& bHandled)
    {
        auto hWndTrack = GetDlgItem(IDC_COLORSLIDE);
        ATLASSERT(hWndTrack);

        if (reinterpret_cast<HWND>(lParam) == hWndTrack) {
            auto value = SendMessage(hWndTrack, TBM_GETPOS, 0, 0);

            auto hWndColor = GetDlgItem(IDC_COLOR);
            ATLASSERT(hWndColor);
            ::InvalidateRect(hWndColor, nullptr, TRUE);

            // Set object color and redraw it
            auto pDrawObject = _Module.GetDrawObject();
            if (pDrawObject) {
                pDrawObject->SetColor(RGB(value, 0, value));
            }
        }

        return 0;
    }

    LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
    {
        _Module.Release(); // FIXME!!!

        bHandled = TRUE;

        return 0;
    }

    void OnCreateObject()
    {
        auto parent = GetParent();

        CComPtr<IDrawObject> pDrawObject;
        auto hr = _Module.CreateObject(pDrawObject);
        if (SUCCEEDED(hr)) {
            Advise();
            auto hWndTrack = GetDlgItem(IDC_COLORSLIDE);
            ATLASSERT(hWndTrack);

            auto value = SendMessage(hWndTrack, TBM_GETPOS, 0, 0);
            pDrawObject->SetColor(RGB(value, 0, value));

            parent.SendMessage(WM_OBJECT_CREATED);
            parent.SendMessage(WM_SETSTATUS, IDS_CREATESUCCEED);
        } else {
            parent.SendMessage(WM_SETSTATUS, IDS_CREATEFAILED);
        }
    }

    void OnDrawObject()
    {
        auto parent = GetParent();
        auto pDrawObject = _Module.GetDrawObject();
        if (pDrawObject) {
            auto hr = pDrawObject->Randomize();
            if (SUCCEEDED(hr)) {
                parent.SendMessage(WM_SETSTATUS, IDS_RANDOMIZED);
            } else {
                parent.SendMessage(WM_SETSTATUS, IDS_CANTRANDOMIZE);
            }
        } else {
            parent.SendMessage(WM_SETSTATUS, IDS_NOOBJECT);
        }
    }

    void OnCopyObject()
    {
        ATLASSERT(FALSE);
    }

    void OnLoadObject()
    {
        auto parent = GetParent();
        auto pDrawObject = _Module.GetDrawObject();
        if (pDrawObject) {
            auto hr = pDrawObject->Load(CComBSTR(R"(object.dat)"));
            auto message = SUCCEEDED(hr) ? IDS_LOAD : IDS_NOLOAD;
            parent.SendMessage(WM_SETSTATUS, message);
        } else {
            parent.SendMessage(WM_SETSTATUS, IDS_NOOBJECT);
        }
    }

    void OnSaveObject()
    {
        auto parent = GetParent();
        auto pDrawObject = _Module.GetDrawObject();
        if (pDrawObject) {
            auto hr = pDrawObject->Save(CComBSTR(R"(object.dat)"));
            auto message = SUCCEEDED(hr) ? IDS_SAVE : IDS_NOSAVE;
            parent.SendMessage(WM_SETSTATUS, message);
        } else {
            parent.SendMessage(WM_SETSTATUS, IDS_NOOBJECT);
        }
    }

    void OnExit()
    {
        GetParent().PostMessage(WM_CLOSE, 0, 0);
    }

private:
    void UpdateControls()
    {
        auto pDrawObject = _Module.GetDrawObject();
        if (pDrawObject) {
            COLORREF lColor;
            auto hr = pDrawObject->GetColor(&lColor);
            if (SUCCEEDED(hr)) {
                auto rValue = GetRValue(lColor);
                SendDlgItemMessage(IDC_COLORSLIDE, TBM_SETPOS, TRUE, rValue);

                auto hWndColor = GetDlgItem(IDC_COLOR);
                ATLASSERT(hWndColor);
                ::InvalidateRect(hWndColor, nullptr, TRUE);
            }
        }
    }

    HRESULT Advise()
    {
        Unadvise();

        auto pDrawObject = _Module.GetDrawObject();
        if (!pDrawObject) {
            return E_POINTER;
        }

        FORMATETC fe;
        fe.cfFormat = CF_ENHMETAFILE;
        fe.dwAspect = DVASPECT_CONTENT;
        fe.ptd = nullptr;
        fe.tymed = TYMED_ENHMF;
        fe.lindex = -1;

        CComQIPtr<IDataObject> pDataObject(pDrawObject);
        if (pDataObject == nullptr) {
            return E_NOINTERFACE;
        }

        auto hr = pDataObject->DAdvise(&fe, 0, this, &m_dwConn);

        return hr;
    }

    HRESULT Unadvise()
    {
        auto pDrawObject = _Module.GetDrawObject();
        if (!pDrawObject) {
            return E_POINTER;
        }

        CComQIPtr<IDataObject> pDataObject(pDrawObject);
        if (pDataObject == nullptr) {
            return E_NOINTERFACE;
        }

        auto hr = pDataObject->DUnadvise(m_dwConn);

        m_dwConn = 0;

        return hr;
    }

    DWORD m_dwConn = 0;
};
