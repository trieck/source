/*********************************************************************
 * Name:      	main.cpp
 * Purpose:   	Implements simple wxWidgets application with GUI
 * 				created using wxFormBuilder.
 * Author:
 * Created:
 * Copyright:
 * License:   	wxWidgets license (www.wxwidgets.org)
 *
 * Notes:		Note that all GUI creation code is implemented in
 * 				gui.cpp source file which is generated by wxFormBuilder.
 *********************************************************************/

#include "common.h"
#include "main.h"
#include "wxcdiodoc.h"
#include "wxcdioview.h"
#include "wxcdioframe.h"

// initialize the application
IMPLEMENT_APP(MainApp);

BEGIN_EVENT_TABLE(MainApp, wxApp)
    EVT_UPDATE_UI(ID_VOL_INFO, MainApp::OnUpdateVolInfo)
END_EVENT_TABLE()

////////////////////////////////////////////////////////////////////////////////
// application class implementation
////////////////////////////////////////////////////////////////////////////////

MainApp::MainApp() : m_docManager(NULL)
{
}

bool MainApp::OnInit()
{
    m_docManager = new wxDocManager;
    m_docManager->SetMaxDocsOpen(1);

    // create a template relating drawing documents to their views
    (void)new wxDocTemplate(m_docManager, _T("ISO image"), _T("*.iso"),
                            _T(""),
                            _T("iso"),
                            _T("wxcdioDoc"),
                            _T("wxcdioView"),
                            CLASSINFO(wxcdioDoc),
                            CLASSINFO(wxcdioView));

    wxFrame *pFrame = new wxcdioFrame(m_docManager);
    pFrame->Centre(wxBOTH);

    SetTopWindow(pFrame);

    pFrame->Show();

    // true = enter the main loop
    return true;
}

wxFrame *MainApp::GetFrame() const
{
    return (wxFrame*)GetTopWindow();
}

int MainApp::OnExit(void)
{
    delete m_docManager;
    return 0;
}

void MainApp::OnUpdateVolInfo(wxUpdateUIEvent &event)
{
    bool bEnable =
        ((m_docManager != NULL) &&
         (m_docManager->GetCurrentDocument() != NULL));

    event.Enable(bEnable);
}
