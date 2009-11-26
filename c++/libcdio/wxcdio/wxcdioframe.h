#ifndef __wxcdioframe__
#define __wxcdioframe__

#include <wx/docview.h>

class wxcdioFrame : public wxDocParentFrame {

public:
	wxcdioFrame(wxDocManager *manager,
		wxFrame *frame = NULL,
        wxWindowID id = wxID_ANY,
        const wxString& title =  _("wxCDIO"),
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
        long style = wxCLOSE_BOX|wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL,
        const wxString& name = wxFrameNameStr);
	
	~wxcdioFrame();
private:
	wxMenuBar* m_menuBar;
	wxMenu* m_menuFile;
	wxMenu* m_menuHelp;
	wxStatusBar* m_statusBar;
	wxToolBar* m_toolBar;
	
	enum { CX_TB_BMP_SIZE = 22 };
	enum { CY_TB_BMP_SIZE = 22 };
		
protected:
	virtual void OnCloseFrame(wxCloseEvent& event); 	
	virtual void OnExitClick( wxCommandEvent& event );	
};

#endif // __wxcdioframe__
