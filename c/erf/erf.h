/*
 * ERF.H
 *
 * The Encapsulated Resource File (ERF) format is one of BioWare's methods 
 * of packing multiple files into a single file so that they may be treated
 * as a single unit. In this regard, it is similar to .zip, .tar, or .rar.
 *
 * BioWare Aurora Engine/Toolset files that use the ERF format include the 
 * following: .erf, .hak, .mod, and .nwm.
 *
 */

#ifndef __ERF_H__
#define __ERF_H__

/* ERF header */
typedef struct tagErfHeader {
	char FileType[4];				/* "ERF ", "MOD ", "SAV ", "HAK " as appropriate */
	char Version[4];				/* "V1.0" */
	int LanguageCount;				/* Number of strings in the Localized String Table */
	int LocalizedStringSize;		/* Total size (bytes) of Localized String Table */
	int EntryCount;					/* Number of files packed into the ERF */
	int OffsetToLocalizedString;	/* From beginning of file */
	int OffsetToKeyList;			/* From beginning of file */
	int OffsetToResourceList;		/* From beginning of file */
	int BuildYear;					/* Since 1900 */
	int BuildDay;					/* Since January 1st */
	int DescriptionStrRef;			/* strref for file description */
	unsigned char Reserved[116];	/* NULL padding */
} ErfHeader;

/* Element in a String List */
typedef struct tagStringElement {
	int LanguageID;
	int StringSize;
	char *Str;
} StringElement;

/* Key structure */
typedef struct tagKey {
	char ResRef[16];	/* Filename */
	int ResID;			/* Resource ID */
	short ResType;		/* File Type */
	short Unused;		/* NULLs */
} Key;

/* Resource structure */
typedef struct tagResource {
	int OffsetToResource;	
	int ResourceSize;
} Resource;

#define STRING_SIZE(x) \
	(sizeof(x.LanguageID)+sizeof(x.StringSize)+x.StringSize)

/* Resource types */
#define RESTYPE_BMP 1
#define RESTYPE_TGA 3
#define RESTYPE_WAV 4
#define RESTYPE_PLT 6
#define RESTYPE_INI 7
#define RESTYPE_TXT 10
#define RESTYPE_MDL 2002
#define RESTYPE_NSS 2009
#define RESTYPE_NCS 2010
#define RESTYPE_ARE 2012
#define RESTYPE_SET 2013
#define RESTYPE_IFO 2014
#define RESTYPE_BIC 2015
#define RESTYPE_WOK 2016
#define RESTYPE_2DA 2017
#define RESTYPE_TXI 2022
#define RESTYPE_GIT 2023
#define RESTYPE_UTI 2025
#define RESTYPE_UTC 2027
#define RESTYPE_DLG 2029
#define RESTYPE_ITP 2030
#define RESTYPE_UTT 2032
#define RESTYPE_DDS 2033
#define RESTYPE_UTS 2035
#define RESTYPE_LTR 2036
#define RESTYPE_GFF 2037
#define RESTYPE_FAC 2038
#define RESTYPE_UTE 2040
#define RESTYPE_UTD 2042
#define RESTYPE_UTP 2044
#define RESTYPE_DFT 2045
#define RESTYPE_GIC 2046
#define RESTYPE_GUI 2047
#define RESTYPE_UTM 2051
#define RESTYPE_DWK 2052
#define RESTYPE_PWK 2053
#define RESTYPE_JRL 2056
#define RESTYPE_UTW 2058
#define RESTYPE_SSF 2060
#define RESTYPE_NDB 2064
#define RESTYPE_PTM 2065
#define RESTYPE_PTT 2066

#endif /* __ERF_H__ */
