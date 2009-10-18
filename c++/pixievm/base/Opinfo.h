#ifndef __OPINFO_H__
#define __OPINFO_H__

/* opcode info structure */
typedef struct Opinfo {
	const char **mnemonic;	/* pointer to mnemonic */
	byte mode;			/* addressing mode */
} *LPOPINFO;

extern LPOPINFO opinfo[256];

#endif /* __OPINFO_H__ */
