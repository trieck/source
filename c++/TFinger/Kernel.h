#pragma once

/////////////////////////////////////////////////////////////////////////////
class Kernel {
private:
	Kernel(int bsize, const BYTE *data);
public:
	~Kernel(void);

	BYTE GetPixel(int x, int y) const;
	int GetBlockSize() const;

	static Kernel* MakeKernel(int bsize, const BYTE *data);

private:
	int m_blocksize;
	LPBYTE m_data;
};

/////////////////////////////////////////////////////////////////////////////
inline int Kernel::GetBlockSize() const
{
	return m_blocksize;
}
