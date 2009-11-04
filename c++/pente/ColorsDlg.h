#pragma once

#include "ColorButton.h"

// CColorsDlg dialog

class CColorsDlg : public CDialog
{
	DECLARE_DYNAMIC(CColorsDlg)

public:
	CColorsDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CColorsDlg();

// Dialog Data
	enum { IDD = IDD_COLORS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	ColorButton	m_TableColor;		
	ColorButton	m_BoardColor;
	ColorButton	m_GridColor;
private:
	enum {
		TABLE_COLOR = 1 << 0,
		BOARD_COLOR = 1 << 1,
		GRID_COLOR = 1 << 2
	};
	DWORD m_ModFlags;

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBoardColor();
	afx_msg void OnGridColor();
	afx_msg void OnTableColor();
	afx_msg void OnBnClickedOk();
};
