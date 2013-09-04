/*
 * GFF.C
 *
 * The Generic File Format (GFF) is an all-purpose generic format used to
 * store data in BioWare games. It is designed to make it easy to add or
 * remove fields and data structures while still maintaining backward and
 * forward compatibility in reading old or new versions of a file format.
 *
 * The following file types within a module are all in GFF:
 *
 *	Module info file (ifo)
 *	Area-related files: area file (are), game object instances and dynamic
 *		area properties (git), game instance comments (gic)
 *	Object Blueprints: creature (utc), door (utd), encounter (ute),
 *		item (uti), placeable (utp), sound (uts), store (utm),
 *		trigger (utt), waypoint (utw)
 *	Conversation files (dlg)
 *	Journal file (jrl)
 *	Faction file (fac)
 *	Palette file (itp)
 *	Plot Wizard files: plot instance/plot manager file (ptm),
 *		plot wizard blueprint (ptt)
 *
 * The following files created by the game are also GFF:
 *	Character/Creature File (bic)
 */

#ifndef __GFF_H__
#define __GFF_H__

#define GFF_TOPLEVEL_STRUCTID 0xFFFFFFFF
#define GFF_VERSION "V3.2"
#define GFF_CRESREFMAX 16

typedef unsigned long long T_DWORD64;
typedef long long T_INT64;

/* GFF header */
typedef struct tagGffHeader {
	char FileType[4];				/* "DLG ", "ITP", etc. */
	char FileVersion[4];			/* "V3.2" */
	unsigned StructOffset;			/* Offset of Struct array as bytes */
	unsigned StructCount;			/* Number of elements in the Struct array */
	unsigned FieldOffset;			/* Offset of Field array as bytes */
	unsigned FieldCount;			/* Number of elements in the Field array */
	unsigned LabelOffset;			/* Offset of Label array as bytes */
	unsigned LabelCount;			/* Number of elements in the Label array */
	unsigned FieldDataOffset;		/* Offset of Field Data as bytes */
	unsigned FieldDataCount;		/* Number of bytes in Field Data block */
	unsigned FieldIndicesOffset;	/* Offset of Field Indices array as bytes */
	unsigned FieldIndicesCount;		/* Number of bytes in Field Indices array */
	unsigned ListIndicesOffset;		/* Offset of List Indices array as bytes */
	unsigned ListIndicesCount;		/* Number of bytes in ListIndicesArray */
} GffHeader;

/* Struct type */
typedef struct tagStruct {
	unsigned Type;					/* Programmer defined id */
	unsigned DataOrDataOffset;		/* If FieldCount = 1, this is an index
										into the Field Array.
									 	If FieldCount > 1, this is a byte
									 	offset into the Field Indices
										array, where there is an array of
										DWORDs having a number of elements
										equal to FieldCount. Each one of these DWORDs
										is an index into the Field Array.
									*/
	unsigned FieldCount;			/* Number of fields in this struct */
} Struct;

/* Field type */
typedef struct tagField {
	unsigned FieldType;				/* Field data type */
	unsigned LabelIndex;			/* Index into the Label array */
	unsigned DataOrDataOffset;		/* If FieldType is a simple data type
										then this is the value actual of
										the field.  If FieldType is a complex
										data type , then this is
										a byte offset into the Field Data block.
									*/

} Field;

enum FTYPE {
    BYTE = 0,
    CHAR = 1,
    WORD = 2,
    SHORT = 3,
    DWORD = 4,
    INT = 5,
    DWORD64 = 6,
    INT64 = 7,
    FLOAT = 8,
    DOUBLE = 9,
    CEXOSTRING = 10,
    CRESREF = 11,
    CEXOLOCSTRING = 12,
    VOID = 13,
    STRUCT = 14,
    LIST = 15
};

/* simple character string type */
typedef struct tagCExoString {
	unsigned Size;
	char *Str;
} CExoString;

/* localized substring */
typedef struct tagCExoLocSubString {
	int StringID;
	int StrLength;
	char *Str;
} CExoLocSubString;

/* localized string */
typedef struct tagCExoLocString {
	unsigned Size;
	unsigned StrRef;	/* index into user's dialog.tlk file,
							which contains a list of almost all
							the localized text in the game and toolset.
							if StrRef = 0xFFFFFFFF, then LocString
							does not reference dialog.tlk at all.
						*/
	unsigned StrCount;
	CExoLocSubString *SubStrs;
} CExoLocString;

/* used to store filename */
typedef struct tagCResRef {
	unsigned char Size;
	char Str[GFF_CRESREFMAX];
} CResRef;

/* VOID data */
typedef struct tagVoid {
	unsigned Size;
	unsigned char *Ptr;
} Void;

#endif /* __GFF_H__ */

