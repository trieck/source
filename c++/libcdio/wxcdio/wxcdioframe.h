#ifndef __wxcdioframe__
#define __wxcdioframe__

#include "main.h"
#include <wx/docview.h>

class wxcdioFrame : public wxDocParentFrame {

public:
	wxcdioFrame(wxDocManager *manager,
	            wxFrame *frame = NULL,
	            wxWindowID id = wxID_ANY,
	            const wxString& title =  WXCDIO_APP_NAME,
	            const wxPoint& pos = wxDefaultPosition,
	            const wxSize& size = wxSize(CX_FRAME, CY_FRAME),
	            long style = wxCLOSE_BOX|wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL,
	            const wxString& name = wxFrameNameStr);

	~wxcdioFrame();
private:
	wxMenuBar* m_menuBar;
	wxMenu* m_menuFile;
	wxMenu* m_menuHelp;
	wxStatusBar* m_statusBar;
	wxToolBar* m_toolBar;

	enum { CX_FRAME = 600 };
	enum { CY_FRAME = 400 };

	enum { CX_TB_BMP_SIZE = 22 };
	enum { CY_TB_BMP_SIZE = 22 };

	DECLARE_EVENT_TABLE()

	void OnCloseFrame(wxCloseEvent& event);
	void OnExitClick(wxCommandEvent& event);

	void OnAbout(wxCommandEvent& event);
};

#endif // __wxcdioframe__
