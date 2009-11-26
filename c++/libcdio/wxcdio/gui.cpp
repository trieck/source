///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Apr 16 2008)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "gui.h"

///////////////////////////////////////////////////////////////////////////

AboutDlg::AboutDlg( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer;
	bSizer = new wxBoxSizer( wxVERTICAL );
	
	m_bmCD = new wxStaticBitmap( this, wxID_ANY, wxBitmap( wxT("resources/cd-player.png"), wxBITMAP_TYPE_ANY ), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer->Add( m_bmCD, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_label = new wxStaticText( this, wxID_ANY, _("wxCDIO\nVersion 0.0.1\nCopyright (c) 2009 Thomas A. Rieck\nAll Rights Reserved"), wxDefaultPosition, wxDefaultSize, 0 );
	m_label->Wrap( -1 );
	bSizer->Add( m_label, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_ok = new wxButton( this, wxID_OK, _("&OK"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer->Add( m_ok, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	this->SetSizer( bSizer );
	this->Layout();
}

AboutDlg::~AboutDlg()
{
}
