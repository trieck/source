#pragma once

class ComponentDlg :
    public CDialogImpl<ComponentDlg>,
    public CUpdateUI<ComponentDlg>,
    public CMessageFilter,
    public CIdleHandler,
    public AdvisableSink
{
public:
BEGIN_MSG_MAP(ComponentDlg)
        MSG_WM_INITDIALOG(OnInitDialog)
        MESSAGE_HANDLER(WM_DRAWITEM, OnDrawItem)
        MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
        MESSAGE_HANDLER(WM_HSCROLL, OnHScroll)
        COMMAND_HANDLER2(IDC_CREATE, BN_CLICKED, OnCreateObject)
        COMMAND_HANDLER2(IDC_DESTROY, BN_CLICKED, OnDestroyObject)
        COMMAND_HANDLER2(IDC_DRAW, BN_CLICKED, OnDrawObject)
        COMMAND_HANDLER2(IDC_COPY, BN_CLICKED, OnCopyObject)
        COMMAND_HANDLER2(IDC_LOAD, BN_CLICKED, OnLoadObject)
        COMMAND_HANDLER2(IDC_SAVE, BN_CLICKED, OnSaveObject)
        COMMAND_HANDLER2(IDC_EXIT, BN_CLICKED, OnExit)
        CHAIN_MSG_MAP(CUpdateUI<ComponentDlg>)
    END_MSG_MAP()

    BEGIN_UPDATE_UI_MAP(ComponentDlg)
        UPDATE_ELEMENT(IDC_CREATE, UPDUI_CHILDWINDOW)
        UPDATE_ELEMENT(IDC_DESTROY, UPDUI_CHILDWINDOW)
        UPDATE_ELEMENT(IDC_DRAW, UPDUI_CHILDWINDOW)
        UPDATE_ELEMENT(IDC_COPY, UPDUI_CHILDWINDOW)
        UPDATE_ELEMENT(IDC_LOAD, UPDUI_CHILDWINDOW)
        UPDATE_ELEMENT(IDC_SAVE, UPDUI_CHILDWINDOW)
    END_UPDATE_UI_MAP()

    enum { IDD = IDD_COMPONENT };

    BOOL PreTranslateMessage(MSG* pMsg) override
    {
        return CWindow::IsDialogMessage(pMsg);
    }

    BOOL OnIdle() override
    {
        auto pDrawObject = theApp.GetDrawObject();

        UIEnable(IDC_CREATE, pDrawObject == nullptr);
        UIEnable(IDC_DESTROY, pDrawObject != nullptr);
        UIEnable(IDC_DRAW, pDrawObject != nullptr);
        UIEnable(IDC_COPY, pDrawObject != nullptr);
        UIEnable(IDC_LOAD, pDrawObject != nullptr);
        UIEnable(IDC_SAVE, pDrawObject != nullptr);

        UIUpdateChildWindows();

        return TRUE;
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

    BOOL OnInitDialog(CWindow /*wndFocus*/, LPARAM /*lInitParam*/)
    {
        auto* pLoop = theApp.GetMessageLoop();
        pLoop->AddMessageFilter(this);
        pLoop->AddIdleHandler(this);

        auto hInstance = ModuleHelper::GetResourceInstance();
        ATLASSERT(hInstance);

        auto hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDR_MAINFRAME));
        ATLASSERT(hIcon);

        SetClassLongPtr(*this, GCLP_HICON, reinterpret_cast<LONG_PTR>(hIcon));

        SendDlgItemMessage(IDC_COLORSLIDE, TBM_SETRANGE, TRUE, MAKELONG(0, 255));

        UIAddChildWindowContainer(m_hWnd);

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
            auto pDrawObject = theApp.GetDrawObject();
            if (pDrawObject) {
                pDrawObject->SetColor(RGB(value, 0, value));
            }
        }

        return 0;
    }

    LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
    {
        auto pDrawObject = theApp.GetDrawObject();
        if (pDrawObject) {
            Unadvise(pDrawObject);
        }

        auto* pLoop = theApp.GetMessageLoop();
        pLoop->RemoveIdleHandler(this);
        pLoop->RemoveMessageFilter(this);

        bHandled = TRUE;

        return 0;
    }

    void OnCreateObject()
    {
        auto parent = GetParent();

        CComPtr<IDrawObject> pDrawObject;
        auto hr = theApp.CreateObject(pDrawObject);
        if (SUCCEEDED(hr)) {
            Advise(pDrawObject);
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

    void OnDestroyObject()
    {
        auto parent = GetParent();

        theApp.Release();

        parent.SendMessage(WM_OBJECT_DESTROYED);
        parent.SendMessage(WM_SETSTATUS, IDS_OK);
    }

    void OnDrawObject()
    {
        auto parent = GetParent();
        auto pDrawObject = theApp.GetDrawObject();
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
        auto parent = GetParent();
        auto pDrawObject = theApp.GetDrawObject();
        if (pDrawObject) {
            CComQIPtr<IDataObject> pData(pDrawObject);
            if (!pData) {
                parent.SendMessage(WM_SETSTATUS, IDS_COPYFAIL);
            } else {
                auto hr = OleSetClipboard(pData);
                if (FAILED(hr)) {
                    parent.SendMessage(WM_SETSTATUS, IDS_COPYFAIL);
                } else {
                    parent.SendMessage(WM_SETSTATUS, IDS_COPYSUCCEED);
                }
            }
        } else {
            parent.SendMessage(WM_SETSTATUS, IDS_NOOBJECT);
        }
    }

    void OnLoadObject()
    {
        auto parent = GetParent();
        auto pDrawObject = theApp.GetDrawObject();
        if (pDrawObject) {
            CComQIPtr<IPersistFile> pFile(pDrawObject);
            if (!pFile) {
                parent.SendMessage(WM_SETSTATUS, IDS_INOSUPPORT);
                return;
            }

            auto hr = pFile->Load(L"object.dat", STGM_DIRECT | STGM_READ | STGM_SHARE_EXCLUSIVE);
            auto message = SUCCEEDED(hr) ? IDS_LOAD : IDS_NOLOAD;
            parent.SendMessage(WM_SETSTATUS, message);
        } else {
            parent.SendMessage(WM_SETSTATUS, IDS_NOOBJECT);
        }
    }

    void OnSaveObject()
    {
        auto parent = GetParent();
        auto pDrawObject = theApp.GetDrawObject();
        if (pDrawObject) {
            CComQIPtr<IPersistFile> pFile(pDrawObject);
            if (!pFile) {
                parent.SendMessage(WM_SETSTATUS, IDS_INOSUPPORT);
                return;
            }

            auto hr = pFile->Save(L"object.dat", TRUE);
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
        auto pDrawObject = theApp.GetDrawObject();
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
};
