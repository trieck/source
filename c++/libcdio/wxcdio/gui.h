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

#endif //__gui__
