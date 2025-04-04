///////////////////////////////////////////////////////////////////////
//
//	MIDICOMMON.H
//
//	Copyright � 1999 Rieck Enterprises
//

#ifndef __MIDICOMMON_H__
#define __MIDICOMMON_H__

#pragma warning(disable:4201)	// nameless struct / union warning

#include <mmsystem.h>

#define FREEMIDIDATA(p)             \
    if (p != NULL) {                \
        if (p->lpData != NULL) {    \
            delete [] p->lpData;    \
            p->lpData = NULL;       \
        }                           \
        delete p;                   \
        p = NULL;                   \
    }

///////////////////////////////////////////////////////////////////////
// shortEvent structure
//
// This is a simplification of the
// MIDIEVENT structure
//
typedef struct {
    DWORD delta;    // time in MIDI ticks between previous and current event
    DWORD id;       // reserved; must be 0
    DWORD event;    // event code, parameters, length
} shortEvent, *PSHORTEVENT;

#define NOTEOFF(n)			0x80 | n
#define NOTEON(n)			0x90 | n
#define PROGRAM_CHANGE(c)	0xC0 | c
#define TEMPO_CHANGE(t)		((DWORD)MEVT_TEMPO << 24) | t
#define DEFAULT_PPQN		96

#endif // __MIDICOMMON_H__

