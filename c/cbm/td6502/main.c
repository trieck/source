/*
 * MAIN.C
 *
 * a very teeny-tiny 6502 disassembler
 *
 */
#include "common.h"
#include "opcodes.h"
#include "code.h"
static void cleanup(void);
static void usage(void);
static void disassemble(const char *filename);
static void printpc(void);
extern word pc;						/* program counter */
FILE *fp = NULL;					/* input file */
const char *log_file_name = NULL;	/* stderr */
/*
 * main entry point
 */
int main(int argc, char *argv[])
{
    if (argc < 2)
        usage();
    atexit(cleanup);

    argc--;
    argv++;
    disassemble(argv[0]);
    return 0;
}
/*
 * disassemble the file
 */
void disassemble(const char *filename)
{
    int N;
    const Instr *p;
    fp = fopen(filename, "rb");
    if (NULL == fp)
        error("unable to open file '%s'.\n", filename);
    /* first two bytes are the load address */
    if (!fread(&pc, sizeof(word), 1, fp))
        error("unable to retrieve load address.\n");

    while ((N = getc(fp)) != EOF) {
        printpc();
        p = instructions[N];
        printf("%.2x", N);
        instruction(p);
        printf("\n");
    }
    fclose(fp);
    fp = NULL;
}
/*
 * display program counter
 */
void printpc(void)
{
    printf("0x%.4x\t", pc);
}
/*
 * clean up routine
 */
void cleanup(void)
{
    if (NULL != fp) {
        fclose(fp);
        fp = NULL;
    }
}
/*
 * print usage
 */
void usage(void)
{
    fprintf(stderr, "usage: td6502 file\n");
    exit(1);
}
