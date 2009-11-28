
#include "wxcdionode.h"

wxcdioNode::wxcdioNode(ISO9660::Stat *stat) : m_stat(stat)
{
}

wxcdioNode::~wxcdioNode()
{
	// node owns stat
	if (m_stat != NULL) {
		delete m_stat;
	}
}

