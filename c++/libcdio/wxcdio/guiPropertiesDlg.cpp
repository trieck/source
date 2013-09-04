#include "common.h"
#include "guiPropertiesDlg.h"
#include "util.h"

guiPropertiesDlg::guiPropertiesDlg(wxWindow* parent, iso9660_stat_t *stat)
	: PropertiesDlg(parent), m_stat(stat)
{
	m_rbDirectory->Enable(false);
	m_rbFile->Enable(false);

	wxDateTime date(m_stat->tm);
	wxString strDate = date.Format(_T("%m/%d/%Y %I:%M:%S %p"));

	m_stCreated->SetLabel(strDate);
	m_stLSN->SetLabel(Comma(m_stat->lsn));
	m_stSize->SetLabel(Comma(m_stat->size));
	m_stSectors->SetLabel(Comma(m_stat->secsize));

	if (iso9660_stat_s::_STAT_DIR == m_stat->type) {
		m_rbDirectory->SetValue(true);
	} else {
		m_rbFile->SetValue(true);
	}
}
