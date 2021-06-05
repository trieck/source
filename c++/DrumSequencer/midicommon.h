/////////////////////////////////////////////////////////////////////////////
//
//  MIDICOMMON.H : Common MIDI header
//
//  Copyright(c) 2011, Thomas A. Rieck, All Rights Reserved
//

#ifndef __MIDICOMMON_H__
#define __MIDICOMMON_H__

typedef struct MIDISHORTEVENT
{
    DWORD delta; // time in MIDI ticks between previous and current event
    DWORD id; // reserved; must be 0
    DWORD event; // event code, parameters, length
}* PMIDISHORTEVENT;

#define NOTEOFF(n)          (0x89 | (n))
#define NOTEON(n)           (0x99 | (n))
#define PROGRAM_CHANGE(c)   (0xC9 | (c))
#define TEMPO_CHANGE(t)     (((DWORD)MEVT_TEMPO << 24) | (t))

constexpr auto DEFAULT_PPQN = 96;

#endif // __MIDICOMMON_H__
