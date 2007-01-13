/////////////////////////////////////////////////////////////////////////////
//
//	KEYNOTES.H
//
//	Copyright © 1999 Rieck Enterprises
//

#ifndef __KEYNOTES_H__
#define __KEYNOTES_H__

/////////////////////////////////////////////////////////////////////////////
// Modifier enumeration
typedef enum {
	NATURAL = 0,
	FLAT = -1,
	SHARP = 1
} Modifier;

/////////////////////////////////////////////////////////////////////////////
// KeyNote structure
typedef struct {
	char keyname;
	Modifier mod;
} KeyNote, *LPKEYNOTE;

// array of modifiers
const KeyNote modifiers [] = {
	'B', FLAT,
	'E', FLAT,
	'A', FLAT,
	'D', FLAT,
	'G', FLAT,
	'C', FLAT,
	'F', FLAT,
	'F', SHARP,
	'C', SHARP,
	'G', SHARP,
	'D', SHARP,
	'A', SHARP,
	'E', SHARP,
	'B', SHARP
};

// tagKeySignature struct
typedef struct {
	KeyNote name;				// keynote name
	const KeyNote * modifiers;	// pointer to start of modifier array	
	int size;					// number of modifiers 
} tagKeySignature;

// KeySignatures array
const tagKeySignature KeySignatures [] = {
	'C', NATURAL, NULL, 0,			/* C major / A minor */
	'F', NATURAL, modifiers, 1,		/* F major / D minor */
	'B', FLAT, modifiers, 2,		/* Bb major / G minor */
	'E', FLAT, modifiers, 3,		/* Eb major / C minor */
	'A', FLAT, modifiers, 4,		/* Ab major / F minor */
	'D', FLAT, modifiers, 5,		/* Db major / Bb minor */
	'G', FLAT, modifiers, 6,		/* Gb major / Eb minor */
	'C', FLAT, modifiers, 7,		/* Cb major / Ab minor */
	'G', NATURAL, modifiers + 7, 1,	/* G major / E minor */
	'D', NATURAL, modifiers + 7, 2,	/* D major / B minor */
	'A', NATURAL, modifiers + 7, 3,	/* A major / F# minor */
	'E', NATURAL, modifiers + 7, 4,	/* E major / C# minor */
	'B', NATURAL, modifiers + 7, 5,	/* B major / G# minor */
	'F', SHARP, modifiers + 7, 6,	/* F# major / D# minor */
	'C', SHARP, modifiers + 7, 7	/* C# major / A# minor */
};	

#endif // __KEYNOTES_H__

