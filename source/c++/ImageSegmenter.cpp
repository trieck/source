// ImageSegmenter.cpp : implementation file
//

#include "stdafx.h"
#include "ImageSegmenter.h"

// ImageSegmenter

#define BLOCK_SIZE			(16)
#define VARIANCE_THRESHOLD	(80)

ImageSegmenter::ImageSegmenter()
{
}

ImageSegmenter::~ImageSegmenter()
{
}

// In a fingerprint image, the background regions generally exhibit a very low
// grey-scale variance value, whereas the foreground regions have a very high
// variance. Hence, a method based on variance thresholding can be used to perform
// the segmentation. (Mehtre, 1993)
//
// Firstly, the image is divided into blocks and the grey-scale variance is
// calculated for each block in the image. If the variance is less than the global
// threshold, then the block is assigned to be a background region; otherwise, it is
// assigned to be part of the foreground. 
//
// The grey-level variance for a block of size W x W is defined as:
//
// V(k) = (1/W^2) * SIGMA(i=0, W-1, SIGMA(j=0, W-1,(I(i,j)-M(k))^2)
//
// Where V(k) is the variance for block k, I(i,j) is the grey-level value at pixel
// (i, j) and M(k) is the mean grey-level value for block k.
//
void ImageSegmenter::Segment(CImage &image)
{
	int rows = image.GetHeight();
	int cols = image.GetWidth();
	int pitch = image.GetPitch();
	
	LPBYTE pbits = reinterpret_cast<LPBYTE>(image.GetBits());	

	for (int y = 0; y < rows; y += BLOCK_SIZE) {
		for (int x = 0; x < cols; x += BLOCK_SIZE) {
			VarianceThreshold(image, x, y);
		} 
	} 
}

void ImageSegmenter::VarianceThreshold(CImage &image, int x, int y)
{
	int rows = image.GetHeight();
	int cols = image.GetWidth();
	int pitch = image.GetPitch();

	ULONG v = VarianceBlock(image, x, y);
	
	LPBYTE pbits = reinterpret_cast<LPBYTE>(image.GetBits());	

	for (int j = y; j < y + BLOCK_SIZE && j < rows; j++) {
		for (int i = x; i < x + BLOCK_SIZE && i < cols; i++) {
			BYTE &p = pbits[j*pitch+i];
			if (v <= VARIANCE_THRESHOLD)
				p = 0xFF;	// white
		}
	}
}

ULONG ImageSegmenter::VarianceBlock(CImage &image, int x, int y)
{
	ULONG variance = 0;
	
	ULONG mean = MeanBlock(image, x, y);

	int diff;
	int rows = image.GetHeight();
	int cols = image.GetWidth();
	int pitch = image.GetPitch();

	LPBYTE pbits = reinterpret_cast<LPBYTE>(image.GetBits());	

	for (int j = y; j < y + BLOCK_SIZE && j < rows; j++) {
		for (int i = x; i < x + BLOCK_SIZE && i < cols; i++) {
			diff = pbits[j*pitch+i] - mean;
			variance += (diff * diff);
		}
	}
	
	variance /= (BLOCK_SIZE * BLOCK_SIZE);

	return variance;
}

ULONG ImageSegmenter::MeanBlock(CImage &image, int x, int y)
{
	ULONG mean = 0;

	int rows = image.GetHeight();
	int cols = image.GetWidth();
	int pitch = image.GetPitch();

	LPBYTE pbits = reinterpret_cast<LPBYTE>(image.GetBits());	

	for (int j = y; j < y + BLOCK_SIZE && j < rows; j++) {
		for (int i = x; i < x + BLOCK_SIZE && i < cols; i++) {
			mean += pbits[j*pitch+i];
		}
	}
	
	mean /= (BLOCK_SIZE * BLOCK_SIZE);

	return mean;
}
