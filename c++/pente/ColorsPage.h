#pragma once

#include "ColorButton.h"

// CColorsPage dialog

class CColorsPage : public CPropertyPage {
	DECLARE_DYNAMIC(CColorsPage)

public:
	CColorsPage();
	virtual ~CColorsPage();

// Dialog Data
	enum { IDD = IDD_COLORS_PAGE };

	ColorButton	m_TableColor;
	ColorButton	m_BoardColor;
	ColorButton	m_GridColor;
	ColorButton m_PlayerOneColor;
	ColorButton m_PlayerTwoColor;
	CButton m_Default;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

	afx_msg void OnBoardColor();
	afx_msg void OnGridColor();
	afx_msg void OnTableColor();
	afx_msg void OnPlayerOneColor();
	afx_msg void OnPlayerTwoColor();
	afx_msg void OnBnClickedDefault();

private:
	enum {
		TABLE_COLOR = 1 << 0,
		BOARD_COLOR = 1 << 1,
		GRID_COLOR = 1 << 2,
		PLAYER_ONE_COLOR = 1 << 3,
		PLAYER_TWO_COLOR = 1 << 4
	};
	DWORD m_ModFlags;

public:
	virtual BOOL OnApply();
};
