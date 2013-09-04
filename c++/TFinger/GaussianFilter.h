#pragma once

class GaussianFilter {
public:
	GaussianFilter();
	~GaussianFilter();

	void Filter(CImage &image);
private:
	float m_kernel[5][5];
};
