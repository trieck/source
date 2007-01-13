// ColorButton.cpp : implementation file
//

#include "stdafx.h"
#include "torrentexplorer.h"
#include "ColorButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define CX_BOX		(12)
#define CX_OFFSET	(4)
#define CY_BOX		(12)

/////////////////////////////////////////////////////////////////////////////
// ColorButton

ColorButton::ColorButton()
{
	m_Hilight = GetSysColor(COLOR_3DHILIGHT);
	m_GrayText = GetSysColor(COLOR_GRAYTEXT);
	m_Text = GetSysColor(COLOR_WINDOWTEXT);
	m_Set = FALSE;
	m_BkgndBrush.CreateSolidBrush(GetSysColor(COLOR_BTNFACE));
}

ColorButton::~ColorButton()
{
}


BEGIN_MESSAGE_MAP(ColorButton, CButton)
	//{{AFX_MSG_MAP(ColorButton)
	ON_WM_SYSCOLORCHANGE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ColorButton message handlers


void ColorButton::DrawItem(LPDRAWITEMSTRUCT dis) 
{
	CDC *pDC = CDC::FromHandle(dis->hDC);

	UINT uStyle = DFCS_BUTTONPUSH;

	if (dis->itemState & ODS_SELECTED)
		uStyle |= DFCS_PUSHED;
  
	CString text;
	GetWindowText(text);
	CSize size = pDC->GetTextExtent(text);
	CRect rc(dis->rcItem);

	int x;
	if (dis->itemState & ODS_DISABLED) {
		x = (rc.Width() - size.cx) / 2;
	} else {
		x = (rc.Width() - size.cx + CX_BOX + CX_OFFSET) / 2;
	}
	
	int y = (rc.Height() - size.cy) / 2;

	pDC->DrawFrameControl(rc, DFC_BUTTON, uStyle);
	pDC->SetBkMode(TRANSPARENT);

	COLORREF clrOld;
	if (dis->itemState & ODS_DISABLED) {
		clrOld = pDC->SetTextColor(m_Hilight);
		pDC->TextOut(x + 1, y + 1, text);
		pDC->SetTextColor(m_GrayText);	
	} else {
		int cx = x - CX_BOX - CX_OFFSET;
		int cy = (rc.Height() - CY_BOX) / 2; 
		CBrush *pOldBrush = pDC->SelectObject(&m_BkgndBrush);
		pDC->Rectangle(
			cx, 
			cy, 
			cx + CX_BOX, 
			cy + CY_BOX
		);
		if (m_Set) {
			pDC->FillSolidRect(
				cx + 1, 
				cy + 1,
				CX_BOX - 2,
				CY_BOX - 2,
				m_Fill
			);
		}
		pDC->SelectObject(pOldBrush);
		clrOld = pDC->SetTextColor(m_Text);
	}

	pDC->TextOut(x, y, text);
	pDC->SetTextColor(clrOld);
}

void ColorButton::OnSysColorChange() 
{
	CButton::OnSysColorChange();

	m_Hilight = GetSysColor(COLOR_3DHILIGHT);
	m_GrayText = GetSysColor(COLOR_GRAYTEXT);
	m_Text = GetSysColor(COLOR_WINDOWTEXT);	
	m_BkgndBrush.DeleteObject();
	m_BkgndBrush.CreateSolidBrush(GetSysColor(COLOR_BTNFACE));
}

void ColorButton::SetFillColor(COLORREF clr)
{
	m_Fill = clr;
	m_Set = TRUE;
	Invalidate();
}

COLORREF ColorButton::GetFillColor() const
{
	return m_Fill;
}
