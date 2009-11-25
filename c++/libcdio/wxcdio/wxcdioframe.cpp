
#include <wx/wx.h>
#include "wxcdioframe.h"

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
	
	m_menuBar = new wxMenuBar( 0 );
	m_menuFile = new wxMenu();
	wxMenuItem* menuFileNew;
	menuFileNew = new wxMenuItem( m_menuFile, wxID_NEW, wxString( _("&New") ) + wxT('\t') + wxT("Alt+N"), _("Create a new ISO image"), wxITEM_NORMAL );
	m_menuFile->Append( menuFileNew );
	
	wxMenuItem* menuFileExit;
	menuFileExit = new wxMenuItem( m_menuFile, wxID_EXIT, wxString( _("E&xit") ) + wxT('\t') + wxT("Alt+X"), wxEmptyString, wxITEM_NORMAL );
	m_menuFile->Append( menuFileExit );
	
	m_menuBar->Append( m_menuFile, _("&File") );
	
	m_menuHelp = new wxMenu();
	wxMenuItem* m_menuAbout;
	m_menuAbout = new wxMenuItem( m_menuHelp, wxID_ANY, wxString( _("About") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuHelp->Append( m_menuAbout );
	
	m_menuBar->Append( m_menuHelp, _("Help") );
	
	SetMenuBar( m_menuBar );
	
	m_statusBar = CreateStatusBar( 1, wxST_SIZEGRIP, wxID_ANY );
	
	m_toolBar = CreateToolBar( wxTB_FLAT|wxTB_HORIZONTAL, wxID_ANY );
	m_toolBar->SetToolBitmapSize( wxSize( 22,22 ) );
	m_toolBar->AddSeparator();
	m_toolBar->AddTool( wxID_NEW, _("&New"), wxBitmap( wxT("resources/new.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString );
	m_toolBar->AddTool( wxID_OPEN, _("&Open"), wxBitmap( wxT("resources/open.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString );
	m_toolBar->AddTool( wxID_SAVE, _("&Save"), wxBitmap( wxT("resources/save.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString );
	m_toolBar->AddSeparator();
	m_toolBar->AddTool( wxID_ANY, _("&Delete"), wxBitmap( wxT("resources/delete.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString );
	m_toolBar->AddSeparator();
	m_toolBar->AddTool( wxID_ABOUT, _("About"), wxBitmap( wxT("resources/help.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString );
	m_toolBar->Realize();
		
	Layout();
	Centre(wxBOTH);
	
	// Connect Events
	Connect(wxEVT_CLOSE_WINDOW, wxCloseEventHandler(wxcdioFrame::OnCloseFrame));
	Connect(menuFileExit->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(wxcdioFrame::OnExitClick));
}

void wxcdioFrame::OnCloseFrame(wxCloseEvent& event)
{
	Destroy();
}

void wxcdioFrame::OnExitClick(wxCommandEvent& event)
{
	Destroy();
}

wxcdioFrame::~wxcdioFrame()
{
	// Disconnect Events
	Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( wxcdioFrame::OnCloseFrame ) );
	Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( wxcdioFrame::OnExitClick ) );
}

