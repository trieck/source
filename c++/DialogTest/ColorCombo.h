// COLORCOMBO.H

#include <afxwin.h>

// CComboBox derived class
class CColorCombo : public CComboBox {
protected:
	// Overridden ancestor methods
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
public:
	void AddColorToList(COLORREF cr);
	void FillList();
};