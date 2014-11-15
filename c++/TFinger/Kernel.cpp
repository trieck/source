#include "StdAfx.h"
#include "Kernel.h"

/////////////////////////////////////////////////////////////////////////////
Kernel::Kernel(int bsize, const BYTE *data)
    : m_blocksize(bsize)
{
    m_data = new BYTE[bsize*bsize];
    memcpy(m_data, data, bsize*bsize);
}

/////////////////////////////////////////////////////////////////////////////
Kernel::~Kernel(void)
{
    delete [] m_data;
}

/////////////////////////////////////////////////////////////////////////////
BYTE Kernel::GetPixel(int x, int y) const
{
    if (x < 0 || y < 0)
        return 0;

    if (x >= m_blocksize || y >= m_blocksize)
        return 0;

    return m_data[y*m_blocksize+x];
}

/////////////////////////////////////////////////////////////////////////////
Kernel* Kernel::MakeKernel(int bsize, const BYTE *data)
{
    return new Kernel(bsize, data);
}

