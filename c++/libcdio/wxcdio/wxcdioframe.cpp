
#include "common.h"
#include "wxcdioframe.h"
#include "gui.h"

BEGIN_EVENT_TABLE(wxcdioFrame, wxDocParentFrame)
    EVT_MENU(wxID_EXIT, wxcdioFrame::OnExitClick)
    EVT_MENU(wxID_ABOUT, wxcdioFrame::OnAbout)
    EVT_MENU(ID_VOL_INFO, wxcdioFrame::OnVolInfo)
    EVT_CLOSE(wxcdioFrame::OnCloseFrame)
END_EVENT_TABLE()

wxcdioFrame::wxcdioFrame(wxDocManager *manager, wxFrame *frame,
                         wxWindowID id, const wxString& title, const wxPoint& pos,
                         const wxSize& size, long style, const wxString& name)
    : wxDocParentFrame(manager, frame, id, title, pos, size, style, name)
{
    wxImage::AddHandler(new wxPNGHandler());

    SetSizeHints(wxDefaultSize, wxDefaultSize);

#ifdef __WXMSW__
    SetIcon(wxIcon(wxT("WXICON_AAA")));
#endif

    m_menuBar = new wxMenuBar();
    m_menuFile = new wxMenu();

    wxMenuItem* menuFileNew;
    menuFileNew = new wxMenuItem( m_menuFile, wxID_NEW, wxString( _("&New") ) + wxT('\t') + wxT("Alt+N"), _T("Create a new ISO image"), wxITEM_NORMAL );
    m_menuFile->Append( menuFileNew );

    wxMenuItem* menuFileOpen;
    menuFileOpen = new wxMenuItem(m_menuFile, wxID_OPEN, wxString( _("&Open") ) + wxT('\t') + wxT("Alt+O"), _T("Open an existing ISO image"), wxITEM_NORMAL );
    m_menuFile->Append( menuFileOpen );

    wxMenuItem* menuFileClose;
    menuFileClose = new wxMenuItem(m_menuFile, wxID_CLOSE, wxString( _("&Close") ) + wxT('\t') + wxT("Alt+C"), _T("Close image"), wxITEM_NORMAL );
    m_menuFile->Append( menuFileClose );

    wxMenuItem* menuFileSave;
    menuFileSave = new wxMenuItem(m_menuFile, wxID_SAVE, wxString( _("&Save") ) + wxT('\t') + wxT("Alt+S"), _T("Save image"), wxITEM_NORMAL );
    m_menuFile->Append( menuFileSave );

    m_menuFile->AppendSeparator();

    wxMenuItem* menuFileInfo;
    menuFileInfo = new wxMenuItem(m_menuFile, ID_VOL_INFO, wxString( _("&Volume information") ) + wxT('\t') + wxT("Alt+V"), _T(
                                      "Volume Information"), wxITEM_NORMAL );
    m_menuFile->Append( menuFileInfo );

    m_menuFile->AppendSeparator();

    wxMenuItem* menuFileExit;
    menuFileExit = new wxMenuItem( m_menuFile, wxID_EXIT, wxString( _("E&xit") ) + wxT('\t') + wxT("Alt+X"), _T("Exit application"), wxITEM_NORMAL );
    m_menuFile->Append( menuFileExit );

    manager->FileHistoryUseMenu(m_menuFile);

    m_menuBar->Append( m_menuFile, _("&File") );

    m_menuHelp = new wxMenu();
    wxMenuItem* m_menuAbout;
    m_menuAbout = new wxMenuItem( m_menuHelp, wxID_ABOUT, wxString( _("About") ) , _T("About wxCDIO"), wxITEM_NORMAL );
    m_menuHelp->Append( m_menuAbout );

    m_menuBar->Append( m_menuHelp, _("Help") );

    SetMenuBar( m_menuBar );

    m_statusBar = CreateStatusBar();

    m_toolBar = CreateToolBar(wxTB_FLAT | wxTB_HORIZONTAL, wxID_ANY );
    m_toolBar->SetToolBitmapSize(wxSize(CX_TB_BMP_SIZE, CY_TB_BMP_SIZE));
    m_toolBar->AddSeparator();
    m_toolBar->AddTool( wxID_NEW, _("&New"), wxBitmap( wxT("resources/new.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, _T("New image"), _T("Create a new ISO image"));
    m_toolBar->AddTool( wxID_OPEN, _("&Open"), wxBitmap( wxT("resources/open.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL,_T("Open image"), _T("Open an existing ISO image"));
    m_toolBar->AddTool( wxID_CLOSE, _("&Close"), wxBitmap( wxT("resources/close.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, _T("Close image"), _T("Close ISO image"));
    m_toolBar->AddTool( wxID_SAVE, _("&Save"), wxBitmap( wxT("resources/save.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, _T("Save image"), _T("Save image to disc"));
    m_toolBar->AddSeparator();
    m_toolBar->AddTool(ID_VOL_INFO, _("Volume"), wxBitmap( wxT("resources/info.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, _T("Volume information"), _T("Volume information"));
    m_toolBar->AddSeparator();
    m_toolBar->AddTool( wxID_ABOUT, _("About"), wxBitmap( wxT("resources/help.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, _T("About wxCDIO"), _T("About wxCDIO"));
    m_toolBar->Realize();

    Layout();
    Centre(wxBOTH);
}

void wxcdioFrame::OnCloseFrame(wxCloseEvent& event)
{
    Destroy();
}

void wxcdioFrame::OnExitClick(wxCommandEvent& event)
{
    Destroy();
}

void wxcdioFrame::OnAbout(wxCommandEvent& event)
{
    AboutDlg dlg(this);
    dlg.ShowModal();
}

void wxcdioFrame::OnVolInfo(wxCommandEvent& event)
{
}

wxcdioFrame::~wxcdioFrame()
{
}

