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

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "gff.h"

#define BUFSIZE 8000
#define STACKSIZE 100

static void usage(void);
static void cleanup(void);
static void open(const char *file);
static void error(const char *fmt, ...);
static void fppush(void);
static long fppop(void);
static const char *GetFieldType(int type);
static CExoString getstr (void);
static CExoLocString getlocstr (void);
static CResRef getresref (void);
static void freestr(CExoString str);
static void freesubstr(CExoLocSubString str);
static void print_exostr(void);
static void print_exolocstr(void);
static void print_resref(void);
static void print_field(Field *field);
static void print_fields(Struct *s);
static void print_struct(Struct *s);
static void print_list(Field *field);
static void print_cfield(Field *field);
static void print_structs(void);
static void print_cstruct(Field *field);
static void output(void);

static GffHeader header;
static FILE *fp;
static long fpstack[STACKSIZE];
static int sp;	/* stack pointer */


/* push current file pointer pos */
void fppush(void)
{
	if (sp >= STACKSIZE)
		error("stack overflow.\n");

	fpstack[sp++] = ftell(fp);
}

/* pop file pointer and restore */
long fppop(void)
{
	long pos;
	if (sp <= 0)
		error("stack underflow.\n");

	pos = fpstack[--sp];

	if (fseek(fp, pos, SEEK_SET) != 0) {
		error("unable to seek in file.\n");
	}

	return pos;
}

/* app usage */
void usage(void)
{
	error("usage: gff file\n");
}

/* open GFF file */
void open(const char *file)
{
	fp = fopen(file, "rb");
	if (fp == NULL) {
		error("unable to open file \"%s\".\n", file);
	}

	if (!fread(&header, sizeof(GffHeader), 1, fp)) {
		error("unable to read header.\n");
	}

	/* validate version */
	if (strncmp(header.FileVersion, GFF_VERSION, sizeof(header.FileVersion)) != 0)
		error("expected version %.4s not found.", GFF_VERSION);
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

/* cleanup */
void cleanup(void)
{
	if (fp != NULL) {
		fclose(fp);
		fp = NULL;
	}
}

/* get field type description */
const char *GetFieldType(int type)
{
	switch (type) {
	case BYTE:
		return "BYTE";
	case CHAR:
		return "CHAR";
	case WORD:
		return "WORD";
	case SHORT:
		return "SHORT";
	case DWORD:
		return "DWORD";
	case INT:
		return "INT";
	case DWORD64:
		return "DWORD64";
	case INT64:
		return "INT64";
	case FLOAT:
		return "FLOAT";
	case DOUBLE:
		return "DOUBLE";
	case CEXOSTRING:
		return "CExoString";
	case CRESREF:
		return "CResRef";
	case CEXOLOCSTRING:
		return "CExoLocString";
	case VOID:
		return "VOID";
	case STRUCT:
		return "Struct";
	case LIST:
		return "List";
	default:
		return "Unknown";
	}
}


/* read and return a CExoString */
CExoString getstr (void)
{
	CExoString str;
	if (!fread(&str.Size, sizeof(unsigned int), 1, fp)) {
		error("unable to read CExoString size.\n");
	}

	str.Str = (char*)malloc(str.Size);
	if (str.Str == NULL) {
		error("unable to allocate memory for string data.\n");
	}

	if (str.Size && !fread(str.Str, str.Size, 1, fp)) {
		error("unable to read CExoString data.\n");
	}

	return str;
}

/* read and return a CExoLocString */
CExoLocString getlocstr (void)
{
	unsigned i;
	CExoLocString str;
	if (!fread(&str.Size, sizeof(unsigned int), 1, fp)) {
		error("unable to read CExoLocString size.\n");
	}

	if (!fread(&str.StrRef, sizeof(unsigned int), 1, fp)) {
		error("unable to read CExoLocString String Ref.\n");
	}

	if (!fread(&str.StrCount, sizeof(unsigned int), 1, fp)) {
		error("unable to read CExoLocString String Count.\n");
	}

	str.SubStrs = (CExoLocSubString *)malloc(str.StrCount *
	              sizeof(CExoLocSubString));

	/* read substrings */
	for (i = 0; i < str.StrCount; i++) {
		if (!fread(&str.SubStrs[i].StringID, sizeof(unsigned int), 1, fp)) {
			error("unable to read CExoLocSubString String ID.\n");
		}

		if (!fread(&str.SubStrs[i].StrLength, sizeof(unsigned int), 1, fp)) {
			error("unable to read CExoLocSubString String Length.\n");
		}

		str.SubStrs[i].Str = (char*)malloc(str.SubStrs[i].StrLength);
		if (str.SubStrs[i].Str == NULL) {
			error("unable to allocate memory for string data.\n");
		}

		if (str.SubStrs[i].StrLength &&
		        !fread(str.SubStrs[i].Str, str.SubStrs[i].StrLength, 1, fp)) {
			error("unable to read CExoLocSubString data.\n");
		}
	}

	return str;
}

/* read and return a CResRef */
CResRef getresref (void)
{
	CResRef ref;
	if (!fread(&ref, sizeof(CResRef), 1, fp)) {
		error("unable to read CResRef.\n");
	}

	return ref;
}

/* free string data */
void freestr(CExoString str)
{
	free(str.Str);
}

/* free substring data */
void freesubstr(CExoLocSubString str)
{
	free(str.Str);
}

/* print a CExoString field */
void print_exostr(void)
{
	unsigned i;
	CExoString str = getstr();

	for (i = 0; i < str.Size; i++) {
		putchar(str.Str[i]);
	}

	freestr(str);
	putchar('\n');
}

/* print a CExoLocString field */
void print_exolocstr(void)
{
	unsigned i;
	int j;

	CExoLocString str = getlocstr();

	if (str.StrCount == 0) {
		putchar('\n');
	} else {
		for (i = 0; i < str.StrCount; i++) {
			for (j = 0; j < str.SubStrs[i].StrLength; j++) {
				putchar(str.SubStrs[i].Str[j]);
			}

			freesubstr(str.SubStrs[i]);
			putchar('\n');
		}
	}
}

/* print a CResRef field */
void print_resref(void)
{
	unsigned char i;
	CResRef ref = getresref();

	for (i = 0; i < ref.Size; i++) {
		putchar(ref.Str[i]);
	}

	putchar('\n');
}


/* print field */
void print_field(Field *field)
{
	printf("Field data: ");

	switch (field->FieldType) {
	case BYTE:
		printf("0x%.2x\n", field->DataOrDataOffset);
		break;
	case CHAR:
		printf("%c\n", field->DataOrDataOffset);
		break;
	case WORD:
		printf("%hd\n", field->DataOrDataOffset);
		break;
	case SHORT:
		printf("%hu\n", field->DataOrDataOffset);
		break;
	case DWORD:
		printf("%ud\n", field->DataOrDataOffset);
		break;
	case INT:
		printf("%d\n", field->DataOrDataOffset);
		break;
	case FLOAT:
		printf("%f\n", (float)field->DataOrDataOffset);
		break;
	case DWORD64:
	case INT64:
	case DOUBLE:
	case CEXOSTRING:
	case CRESREF:
	case CEXOLOCSTRING:
	case VOID:
	case STRUCT:
	case LIST:
		print_cfield(field);	/* complex data */
		break;
	default:
		printf("???\n");
		break;
	}
}

/* print fields */
void print_fields(Struct *s)
{
	printf("\nFIELDS\n______\n\n");

	if (s->FieldCount == 1) {	/* index into field array */
		;	/* FIXME */
	} else if (s->FieldCount > 1) { /* offset into field indices array */
		int offset = header.FieldIndicesOffset + s->DataOrDataOffset;
		unsigned i;

		/* seek into field indices array */
		if (fseek(fp, offset, SEEK_SET) != 0) {
			error("unable to seek into field indices array.\n");
		}

		for (i = 0; i < s->FieldCount; i++) {
			unsigned index, offset;
			Field field;

			/* read next field index */
			if (!fread(&index, sizeof(unsigned int), 1, fp)) {
				error("unable to read field index.\n");
			}

			fppush();

			/* seek into field array */
			offset = header.FieldOffset + sizeof(Field) * index;
			if (fseek(fp, offset, SEEK_SET) != 0) {
				error("unable to seek into field array.\n");
			}

			/* read next field */
			if (!fread(&field, sizeof(Field), 1, fp)) {
				error("unable to read field.\n");
			}

			if (i > 0) printf("\n");

			printf("Field #%d\nType: %s\nLabel Index: %d\nDataOrDataOffset: %d\n",
			       i+1, GetFieldType(field.FieldType),
			       field.LabelIndex, field.DataOrDataOffset);

			print_field(&field);

			fppop();
		}
	}
}

/* print a struct */
void print_struct(Struct *s)
{
	fppush();
	printf("Type: %d\nDataOrDataOffset: %d\nField Count: %d\n",
	       s->Type, s->DataOrDataOffset, s->FieldCount);
	print_fields(s);
	fppop();
}

/* print a List */
void print_list(Field *field)
{
	unsigned i, size, index;
	int offset;
	Struct s;

	/* a List is a list of Structs whose members are indices into
	 * the Struct array. Unlike most of the complex Field data types,
	 * a List Field's data is located not in the Field Data Block,
	 * but in the List Indices Array.  The starting address of a List
	 * is specified in its Field's DataOrDataOffset value as a byte offset
	 * element.
	 */
	offset = header.ListIndicesOffset + field->DataOrDataOffset;
	if (fseek(fp, offset, SEEK_SET) != 0) {
		error("unable to seek into list data.\n");
	}

	if (!fread(&size, sizeof(unsigned int), 1, fp)) {
		error("unable to read list size.\n");
	}

	printf("\nSTRUCTS\n_______\n\n");

	for (i = 0; i < size; i++) {
		if (!fread(&index, sizeof(unsigned int), 1, fp)) {
			error("unable to read list index.\n");
		}

		fppush();

		offset = header.StructOffset + index * sizeof(Struct);
		if (fseek(fp, offset, SEEK_SET) != 0) {
			error("unable to seek into Struct array.\n");
		}

		if (!fread(&s, sizeof(Struct), 1, fp)) {
			error("unable to read struct.\n");
		}

		printf("\nStruct #%d\n", i+1);
		print_struct(&s);

		fppop();
	}
}

/* print complex field struct */
void print_cstruct(Field *field)
{
	int offset;
	Struct s;

	/* Unlike most of the complex Field data types, a Struct Field's data
	 * is located not in the Field Data Block, but in the Struct Array.
	 * Normally, a Field's DataOrDataOffset value would be a byte offset
	 * into the Field Data Block, but for a Struct, it is an index into
	 * the Struct Array
	 */
	offset = header.StructOffset + field->DataOrDataOffset * sizeof(Struct);
	if (fseek(fp, offset, SEEK_SET) != 0) {
		error("unable to seek into struct array.\n");
	}

	if (!fread(&s, sizeof(Struct), 1, fp)) {
		error("unable to read struct.\n");
	}

	print_struct(&s);
}

/* print complex field */
void print_cfield(Field *field)
{
	T_DWORD64 t;
	double d;

	if (field->FieldType != LIST && field->FieldType != STRUCT) {
		int offset = header.FieldDataOffset + field->DataOrDataOffset;
		if (fseek(fp, offset, SEEK_SET) != 0) {
			error("unable to seek into field data.\n");
		}
	}

	switch (field->FieldType) {
	case DWORD64:
		if (!fread(&t, sizeof(T_DWORD64), 1, fp)) {
			error("unable to read field data.\n");
		}
		printf("%llu", t);
		break;
	case INT64:
		if (!fread(&t, sizeof(T_INT64), 1, fp)) {
			error("unable to read field data.\n");
		}
		printf("%lld", (T_INT64)t);
		break;
	case DOUBLE:
		if (!fread(&d, sizeof(double), 1, fp)) {
			error("unable to read field data.\n");
		}
		printf("%.8f", d);
		break;
	case CEXOSTRING:
		print_exostr();
		break;
	case CRESREF:
		print_resref();
		break;
	case CEXOLOCSTRING:
		print_exolocstr();
		break;
	case VOID:
		printf("not implemented.\n");
		break;
	case STRUCT:
		print_cstruct(field);
		break;
	case LIST:
		print_list(field);
		break;
	default:
		printf("???\n");
		break;
	}
}

/* print structs */
void print_structs(void)
{
	Struct s;
	unsigned i;

	if (header.StructCount == 0)
		error("gff must contain a top-level struct.\n");

	/* seek to struct offset */
	if (fseek(fp, header.StructOffset, SEEK_SET) != 0) {
		error("unable to seek to struct array.\n");
	}

	/* read top-level struct */
	if (!fread(&s, sizeof(Struct), 1, fp)) {
		error("unable to read top-level struct.\n");
	}

	/* ensure valid top-level struct */
	if (s.Type != GFF_TOPLEVEL_STRUCTID) {
		error("top level struct expected type 0x%.8x.\n",
		      GFF_TOPLEVEL_STRUCTID);
	}

	printf("\nSTRUCTS\n_______\n\n");
	printf("Struct #1\n");
	print_struct(&s);

	/* print structs */
	for (i = 1; i < header.StructCount; i++) {
		if (!fread(&s, sizeof(Struct), 1, fp)) {
			error("unable to read struct.\n");
		}
		printf("\n");
		printf("\nStruct #%d\n", i+1);
		print_struct(&s);
	}
}

/* output GFF file */
void output(void)
{
	print_structs();
}

/* main entry point */
int main(int argc, char *argv[])
{
	if (argc < 2) {
		usage();
	}

	atexit(cleanup);
	open(argv[1]);
	output();

	return 0;
}
