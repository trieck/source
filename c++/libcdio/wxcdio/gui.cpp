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

PropertiesDlg::PropertiesDlg( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
    this->SetSizeHints( wxDefaultSize, wxDefaultSize );

    wxBoxSizer* bSizer;
    bSizer = new wxBoxSizer( wxVERTICAL );

    wxFlexGridSizer* fgSizer;
    fgSizer = new wxFlexGridSizer( 5, 2, 0, 0 );
    fgSizer->SetFlexibleDirection( wxBOTH );
    fgSizer->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

    m_staticText5 = new wxStaticText( this, wxID_ANY, _("Created:"), wxDefaultPosition, wxDefaultSize, 0 );
    m_staticText5->Wrap( -1 );
    fgSizer->Add( m_staticText5, 0, wxALL, 5 );

    m_stCreated = new wxStaticText( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 175,-1 ), 0 );
    m_stCreated->Wrap( -1 );
    fgSizer->Add( m_stCreated, 0, wxALL, 5 );

    m_staticText7 = new wxStaticText( this, wxID_ANY, _("Starting sector:"), wxDefaultPosition, wxDefaultSize, 0 );
    m_staticText7->Wrap( -1 );
    fgSizer->Add( m_staticText7, 0, wxALL, 5 );

    m_stLSN = new wxStaticText( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 175,-1 ), 0 );
    m_stLSN->Wrap( -1 );
    fgSizer->Add( m_stLSN, 0, wxALL, 5 );

    m_staticText9 = new wxStaticText( this, wxID_ANY, _("Size in bytes:"), wxDefaultPosition, wxDefaultSize, 0 );
    m_staticText9->Wrap( -1 );
    fgSizer->Add( m_staticText9, 0, wxALL, 5 );

    m_stSize = new wxStaticText( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 175,-1 ), 0 );
    m_stSize->Wrap( -1 );
    fgSizer->Add( m_stSize, 0, wxALL, 5 );

    m_staticText11 = new wxStaticText( this, wxID_ANY, _("Number of sectors:"), wxDefaultPosition, wxDefaultSize, 0 );
    m_staticText11->Wrap( -1 );
    fgSizer->Add( m_staticText11, 0, wxALL, 5 );

    m_stSectors = new wxStaticText( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 175,-1 ), 0 );
    m_stSectors->Wrap( -1 );
    fgSizer->Add( m_stSectors, 0, wxALL, 5 );

    m_staticText15 = new wxStaticText( this, wxID_ANY, _("Type:"), wxDefaultPosition, wxDefaultSize, 0 );
    m_staticText15->Wrap( -1 );
    fgSizer->Add( m_staticText15, 0, wxALL, 5 );

    wxGridSizer* gSizer;
    gSizer = new wxGridSizer( 1, 2, 0, 0 );

    m_rbDirectory = new wxRadioButton( this, wxID_ANY, _("Directory"), wxDefaultPosition, wxDefaultSize, 0 );
    gSizer->Add( m_rbDirectory, 0, wxALL, 5 );

    m_rbFile = new wxRadioButton( this, wxID_ANY, _("File"), wxDefaultPosition, wxDefaultSize, 0 );
    gSizer->Add( m_rbFile, 0, wxALL, 5 );

    fgSizer->Add( gSizer, 1, wxEXPAND, 5 );

    bSizer->Add( fgSizer, 1, wxEXPAND, 5 );

    wxGridSizer* gSizer2;
    gSizer2 = new wxGridSizer( 1, 1, 0, 0 );

    m_OK = new wxButton( this, wxID_OK, _("&OK"), wxDefaultPosition, wxDefaultSize, 0 );
    m_OK->SetDefault();
    gSizer2->Add( m_OK, 0, wxALL|wxALIGN_BOTTOM|wxALIGN_CENTER_HORIZONTAL, 5 );

    bSizer->Add( gSizer2, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );

    this->SetSizer( bSizer );
    this->Layout();
}

PropertiesDlg::~PropertiesDlg()
{
}
