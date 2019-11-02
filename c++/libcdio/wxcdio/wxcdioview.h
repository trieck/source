#ifndef __wxcdioview__
#define __wxcdioview__

#include "wxcdiocanvas.h"

class wxcdioView : public wxView
{
    DECLARE_DYNAMIC_CLASS(wxcdioView)
public:
    wxcdioView();
    ~wxcdioView();

    void OnDraw(wxDC*);
    bool OnCreate(wxDocument* doc, long flags);
    void OnClosingDocument();
    bool OnClose(bool deleteWindow);
    void OnUpdate(wxView *sender, wxObject *hint);

private:
    wxcdioCanvas *m_canvas;
    int m_canvasID;
};

#endif // __wxcdioview__
