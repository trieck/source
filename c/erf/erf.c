/*
 * ERF.C
 *
 * The Encapsulated Resource File (ERF) format is one of BioWare's methods
 * of packing multiple files into a single file so that they may be treated
 * as a single unit. In this regard, it is similar to .zip, .tar, or .rar.
 *
 * BioWare Aurora Engine/Toolset files that use the ERF format include the
 * following: .erf, .hak, .mod, and .nwm.
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "erf.h"

#define BUFSIZE 8000

static void usage(void);
static void print_header(void);
static StringElement nextstr(void);
static void freestr(StringElement e);
static void print_strings(void);
static const char *restype(short type);
static void print_keylist(void);
static void print_reslist(void);
static void open(const char *file);
static void output(void);
static void cleanup(void);
static void extract(int id);
static void error(const char *fmt, ...);

static ErfHeader header;
static FILE *fp;

/* app usage */
void usage(void)
{
	error("usage: erf file [resid]\n");
}

/* print ERF header */
void print_header(void)
{
	printf("ERF HEADER\n__________\n\n"
	       "File Type: %.4s\nVersion: %.4s\nNumber of Strings: %d\nSize of String Table: %d\n"
	       "# of Files Packed: %d\nOffset to String List: %d\nOffset to Key List: %d\n"
	       "Offset to Resource List: %d\nBuild Year: %d\nBuild Day: %d\n\n"
	       ,
	       header.FileType,
	       header.Version,
	       header.LanguageCount,
	       header.LocalizedStringSize,
	       header.EntryCount,
	       header.OffsetToLocalizedString,
	       header.OffsetToKeyList,
	       header.OffsetToResourceList,
	       1900+header.BuildYear,
	       header.BuildDay);
}

/* extract the next string */
StringElement nextstr(void)
{
	StringElement e;

	if (!fread(&e, sizeof(e.LanguageID)+sizeof(e.StringSize), 1, fp)) {
		error("unable to read string element.\n");
	}

	e.Str = (char*)malloc(e.StringSize);
	if (!fread(e.Str, e.StringSize, 1, fp)) {
		error("unable to read string data.\n");
	}

	return e;
}

/* free storage allocated for string element */
void freestr(StringElement e)
{
	free(e.Str);
}

/* print string list */
void print_strings(void)
{
	int n = 0, c = 0;
	StringElement e;

	printf("\n\nSTRING LIST\n___________\n\n");

	if (fseek(fp, header.OffsetToLocalizedString, SEEK_SET) != 0) {
		error("unable to seek to string list.\n");
	}

	while (n < header.LocalizedStringSize) {
		e = nextstr();
		for (c = 0; c < e.StringSize; c++) {
			putchar(e.Str[c]);
		}
		putchar('\n');
		n += STRING_SIZE(e);
		freestr(e);
	}
}

/* human readable resource type */
const char *restype(short type)
{
	switch (type) {
	case RESTYPE_BMP:
		return "bmp";
	case RESTYPE_TGA:
		return "tga";
	case RESTYPE_WAV:
		return "wav";
	case RESTYPE_PLT:
		return "plt";
	case RESTYPE_INI:
		return "ini";
	case RESTYPE_TXT:
		return "txt";
	case RESTYPE_MDL:
		return "mdl";
	case RESTYPE_NSS:
		return "nss";
	case RESTYPE_NCS:
		return "ncs";
	case RESTYPE_ARE:
		return "are";
	case RESTYPE_SET:
		return "set";
	case RESTYPE_IFO:
		return "ifo";
	case RESTYPE_BIC:
		return "bic";
	case RESTYPE_WOK:
		return "wok";
	case RESTYPE_2DA:
		return "2da";
	case RESTYPE_TXI:
		return "txi";
	case RESTYPE_GIT:
		return "git";
	case RESTYPE_UTI:
		return "uti";
	case RESTYPE_UTC:
		return "utc";
	case RESTYPE_DLG:
		return "dlg";
	case RESTYPE_ITP:
		return "itp";
	case RESTYPE_UTT:
		return "utt";
	case RESTYPE_DDS:
		return "dds";
	case RESTYPE_UTS:
		return "uts";
	case RESTYPE_LTR:
		return "ltr";
	case RESTYPE_GFF:
		return "gff";
	case RESTYPE_FAC:
		return "fac";
	case RESTYPE_UTE:
		return "ute";
	case RESTYPE_UTD:
		return "utd";
	case RESTYPE_UTP:
		return "utp";
	case RESTYPE_DFT:
		return "dft";
	case RESTYPE_GIC:
		return "gic";
	case RESTYPE_GUI:
		return "gui";
	case RESTYPE_UTM:
		return "utm";
	case RESTYPE_DWK:
		return "dwk";
	case RESTYPE_PWK:
		return "pwk";
	case RESTYPE_JRL:
		return "jrl";
	case RESTYPE_UTW:
		return "utw";
	case RESTYPE_SSF:
		return "ssf";
	case RESTYPE_NDB:
		return "ndb";
	case RESTYPE_PTM:
		return "ptm";
	case RESTYPE_PTT:
		return "ptt";
	case 0xFFFF:
		return "N/A";
	default:
		return "unknown";
	}
}

/* print key list */
void print_keylist(void)
{
	int n = 0;
	Key key;

	printf("\n\nKEY LIST\n________\n\n");

	if (fseek(fp, header.OffsetToKeyList, SEEK_SET) != 0) {
		error("unable to seek to key list.\n");
	}

	for (n = 0; n < header.EntryCount; n++) {
		if (!fread(&key, sizeof(Key), 1, fp)) {
			error("unable to read key data.\n");
		}

		if (n > 0) printf("\n");

		printf("Filename: %.16s\nResource ID: %d\nFile Type: %s\n",
		       key.ResRef, key.ResID, restype(key.ResType));
	}

}

/* print resource list */
void print_reslist(void)
{
	int n = 0;
	Resource res;

	printf("\n\nRESOURCE LIST\n_____________\n\n");

	if (fseek(fp, header.OffsetToResourceList, SEEK_SET) != 0) {
		error("unable to seek to resource list.\n");
	}

	for (n = 0; n < header.EntryCount; n++) {
		if (!fread(&res, sizeof(Resource), 1, fp)) {
			error("unable to read resource data.\n");
		}

		if (n > 0) printf("\n");

		printf("Offset to Resource: %d\nResource Size: %d\n",
		       res.OffsetToResource, res.ResourceSize);
	}
}

/* open ERF file */
void open(const char *file)
{
	fp = fopen(file, "rb");
	if (fp == NULL) {
		error("unable to open file \"%s\".\n", file);
	}

	if (!fread(&header, sizeof(ErfHeader), 1, fp)) {
		error("unable to read header.\n");
	}
}

/* output ERF file */
void output(void)
{
	print_header();
	print_strings();
	print_keylist();
	print_reslist();
}

/* cleanup */
void cleanup(void)
{
	if (fp != NULL) {
		fclose(fp);
		fp = NULL;
	}
}

/* extract resource to file */
void extract(int id)
{
	FILE *fpout;
	Key key;
	Resource res;
	int offset, c, i;
	char file[BUFSIZE];

	if (id < 0 || id >= header.EntryCount) {
		error("resource id %d out of range.\n", id);
	}

	/* seek to key */
	offset = header.OffsetToKeyList + id * sizeof(Key);
	if (fseek(fp, offset, SEEK_SET) != 0) {
		error("unable to seek to key.\n");
	}

	/* read key */
	if (!fread(&key, sizeof(Key), 1, fp)) {
		error("unable to read key data.\n");
	}

	/* seek to resource */
	offset = header.OffsetToResourceList + id * sizeof(Resource);
	if (fseek(fp, offset, SEEK_SET) != 0) {
		error("unable to seek to resource list data.\n");
	}

	/* read resource list data */
	if (!fread(&res, sizeof(Resource), 1, fp)) {
		error("unable to read resource list data.\n");
	}

	/* seek to resource data */
	if (fseek(fp, res.OffsetToResource, SEEK_SET) != 0) {
		error("unable to seek to resource data.\n");
	}

	sprintf(file, "%.16s.%s", key.ResRef, restype(key.ResType));
	fpout = fopen(file, "wb");
	if (fpout == NULL) {
		error("unable to open file \"%s\".\n", file);
	}

	for (i = 0; i < res.ResourceSize; i++) {
		if ((c = fgetc(fp)) == EOF) {
			fclose(fpout);
			error("unexpected EOF encountered.");
		}
		fputc(c, fpout);
	}

	fflush(fpout);
	fclose(fpout);
}

/* fatal error */
void error(const char *fmt, ...)
{
	char buf[BUFSIZE];

	va_list arglist;
	va_start(arglist, fmt);

	vsprintf(buf, fmt, arglist);

	va_end (arglist);

	fprintf(stderr, buf);
	exit(1);
}

/* main entry point */
int main(int argc, char *argv[])
{
	if (argc < 2) {
		usage();
	}

	atexit(cleanup);
	open(argv[1]);

	if (argc > 2) {	/* extract resource */
		extract(atoi(argv[2]));
	} else {	/* display erf */
		output();
	}

	return 0;
}
