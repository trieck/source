///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Apr 16 2008)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __gui__
#define __gui__

#include <wx/intl.h>

#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/statbmp.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/dialog.h>
#include <wx/radiobut.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class AboutDlg
///////////////////////////////////////////////////////////////////////////////
class AboutDlg : public wxDialog 
{
	private:
	
	protected:
		wxStaticBitmap* m_bmCD;
		wxStaticText* m_label;
		wxButton* m_ok;
	
	public:
		AboutDlg( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("About wxCDIO"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 278,197 ), long style = wxDEFAULT_DIALOG_STYLE );
		~AboutDlg();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class PropertiesDlg
///////////////////////////////////////////////////////////////////////////////
class PropertiesDlg : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText5;
		wxStaticText* m_stCreated;
		wxStaticText* m_staticText7;
		wxStaticText* m_stLSN;
		wxStaticText* m_staticText9;
		wxStaticText* m_stSize;
		wxStaticText* m_staticText11;
		wxStaticText* m_stSectors;
		wxStaticText* m_staticText15;
		wxRadioButton* m_rbDirectory;
		wxRadioButton* m_rbFile;
		wxButton* m_OK;
		wxButton* m_Cancel;
	
	public:
		PropertiesDlg( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Properties"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 299,267 ), long style = wxDEFAULT_DIALOG_STYLE );
		~PropertiesDlg();
	
};

#endif //__gui__
