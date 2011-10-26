/////////////////////////////////////////////////////////////////////////////
//
//	DBLEBUFF.CPP : double buffer
//
//	This class implements a double buffer scheme
//	for streaming MIDI data
//
//	Copyright(c) 1999-2011 Thomas A. Rieck, All Rights Reserved
//

#include "stdafx.h"
#include "baseinc.h"

#define CHUNKSIZE   1024
#define REALLOCSIZE 2

//
// Constructor
//
DoubleBuffer::DoubleBuffer()
{
	memset(&m_Buffers, 0, sizeof(m_Buffers));
	AllocBuffers();
}

//
// Destructor
//
DoubleBuffer::~DoubleBuffer()
{
	FreeBuffers();
}

//
// AllocBuffers
//
void DoubleBuffer::AllocBuffers()
{
	FreeBuffers();

	for (int i = 0; i < BUFFERS; i++) {
		m_Buffers[i].lpData = new CHAR[CHUNKSIZE];
		m_Buffers[i].dwBufferLength = m_Buffers[i].dwBytesRecorded = CHUNKSIZE;
	}
}

//
// FreeBuffers
//
void DoubleBuffer::FreeBuffers()
{
	for (int i = 0; i < BUFFERS; i++) {
		if (m_Buffers[i].lpData != NULL)
			delete [] m_Buffers[i].lpData;
		memset(&m_Buffers[i], 0, sizeof(MIDIHDR));
	}
}

//
// ReallocBuffer
//
BOOL DoubleBuffer::ReallocBuffer(MIDIHDR * pBuffer) const
{
	ASSERT(pBuffer != NULL);
	ASSERT(pBuffer->lpData != NULL);

	DWORD bytes = pBuffer->dwBufferLength * REALLOCSIZE;

	// Reallocate the buffer
	PSTR pdata = (PSTR)realloc(pBuffer->lpData, bytes);
	if (pdata == NULL)
		return FALSE;

	pBuffer->lpData = pdata;
	pBuffer->dwBufferLength = pBuffer->dwBytesRecorded = bytes;

	return TRUE;
}

//
// SetFront
//
BOOL DoubleBuffer::SetFront(MIDIHDR * pdata)
{
	ASSERT(pdata != NULL);

	return Set(&m_Buffers[0], pdata);
}

//
// SetBack
//
BOOL DoubleBuffer::SetBack(MIDIHDR * pdata)
{
	ASSERT(pdata != NULL);

	return Set(&m_Buffers[1], pdata);
}

//
// Set
//
BOOL DoubleBuffer::Set(MIDIHDR * pDest, MIDIHDR * pSrc) const
{
	ASSERT(pDest != NULL);
	ASSERT(pSrc != NULL);

	// Do we need to reallocate the buffer
	while (pSrc->dwBufferLength > max(pDest->dwBufferLength, CHUNKSIZE)) {
		if (!ReallocBuffer(pDest))
			return FALSE;
	}

	memcpy(pDest->lpData, pSrc->lpData, pSrc->dwBufferLength);
	pDest->dwBufferLength = pDest->dwBytesRecorded = pSrc->dwBufferLength;

	return TRUE;
}

