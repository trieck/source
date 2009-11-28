#ifndef __wxcdionode__
#define __wxcdionode__

#include <wx/treectrl.h>
#include <cdio++/iso9660.hpp>

class wxcdioNode : public wxTreeItemData {

public:
	wxcdioNode(ISO9660::Stat* stat);
	~wxcdioNode();

	iso9660_stat_t *GetStat() const {
		return m_stat->p_stat;
	}
private:
	ISO9660::Stat *m_stat;
};

#endif // __wxcdionode__
