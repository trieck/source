#pragma once

class ComponentDlg : public CDialogImpl<ComponentDlg>
{
BEGIN_MSG_MAP(ComponentDlg)
        MSG_WM_INITDIALOG(OnInitDialog)
        MESSAGE_HANDLER(WM_DRAWITEM, OnDrawItem)
        MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
        MESSAGE_HANDLER(WM_HSCROLL, OnHScroll)
        COMMAND_HANDLER2(IDC_CREATE, BN_CLICKED, OnCreate)
        COMMAND_HANDLER2(IDC_DRAW, BN_CLICKED, OnDraw)
        COMMAND_HANDLER2(IDC_LOAD, BN_CLICKED, OnLoad)
        COMMAND_HANDLER2(IDC_EXIT, BN_CLICKED, OnExit)
    END_MSG_MAP()

    enum { IDD = IDD_COMPONENT };

    BOOL OnInitDialog(CWindow /*wndFocus*/, LPARAM /*lInitParam*/)
    {
        auto hWndTrack = GetDlgItem(IDC_COLORSLIDE);
        ATLASSERT(hWndTrack);

        auto hInstance = ModuleHelper::GetResourceInstance();
        ATLASSERT(hInstance);

        auto hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDR_MAINFRAME));
        ATLASSERT(hIcon);

        SetClassLong(*this, GCL_HICON, reinterpret_cast<LONG>(hIcon));

        SendMessage(hWndTrack, TBM_SETRANGE, TRUE, MAKELONG(0, 255));

        return TRUE;
    }

    LRESULT OnDrawItem(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& bHandled)
    {
        bHandled = FALSE;

        auto dis = reinterpret_cast<LPDRAWITEMSTRUCT>(lParam);
        ATLASSERT(dis);

        if (dis->CtlID == IDC_COLOR) {
            auto hWndTrack = GetDlgItem(IDC_COLORSLIDE);
            ATLASSERT(hWndTrack);

            auto value = static_cast<int>(SendMessage(hWndTrack, TBM_GETPOS, 0, 0));
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

    void OnCreate()
    {
        CComPtr<IDrawObject> pDrawObject;
        auto hr = _Module.CreateObject(pDrawObject);
        if (SUCCEEDED(hr)) {
            CRect rc;
            GetParent().GetClientRect(rc);
            pDrawObject->SetBounds(rc);

            GetParent().SendMessage(WM_SETSTATUS, IDS_CREATESUCCEED);
        } else {
            GetParent().SendMessage(WM_SETSTATUS, IDS_CREATEFAILED);
        }
    }

    void OnDraw()
    {
        auto pDrawObject = _Module.GetDrawObject();
        if (pDrawObject) {
            pDrawObject->Randomize();
            GetParent().SendMessage(WM_REDRAWCLIENT, 0, 0);
        } else {
            GetParent().SendMessage(WM_SETSTATUS, IDS_NOOBJECT);
        }
    }

    void OnLoad()
    {
        auto pDrawObject = _Module.GetDrawObject();
        if (pDrawObject) {
            auto hr = pDrawObject->Load(CComBSTR(R"(object.dat)"));
            auto message = SUCCEEDED(hr) ? IDS_LOAD : IDS_NOLOAD;
            GetParent().SendMessage(WM_SETSTATUS, message);
        } else {
            GetParent().SendMessage(WM_SETSTATUS, IDS_NOOBJECT);
        }
    }

    void OnExit()
    {
        GetParent().PostMessage(WM_CLOSE, 0, 0);
    }
};
