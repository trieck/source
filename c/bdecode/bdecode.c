
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

static void usage(void);
static void bdecode(const char *filename);
static void error(const char *fmt, ...);
static void output(const char *fmt, ...);
static void cleanup(void);
static void parse(void);
static void parsetok(int t);
static int lex(void);
static void dict(void);
static void integer(void);
static void list(void);
static void string(void);

static FILE *fp;

int main(int argc, char *argv[])
{
    if (argc < 2) usage();

    atexit(cleanup);

    bdecode(argv[1]);

    return 0;
}

void cleanup(void)
{
    if (fp != NULL) fclose(fp);
}

void usage(void)
{
    error("usage: bdecode file\n");
}

void bdecode(const char *filename)
{
    fp = fopen(filename, "rb");
    if (fp == NULL)
        error("unable to open \"%s\".\n", filename);

    parse();
}

void parse(void)
{
    int t;
    while ((t = lex()) != EOF) {
        parsetok(t);
    }
}

void parsetok(int t)
{
    switch (t) {
    case 'd':
        dict();
        break;
    case 'i':
        integer();
        break;
    case 'l':
        list();
        break;
    default:
        if (isdigit(t)) {
            ungetc(t, fp);
            string();
        } else error("unexpected token 0x%.2x.\n", t);
        break;
    }
}

int lex(void)
{
    return fgetc(fp);
}

void error(const char *fmt, ...)
{
    va_list arglist;
    va_start(arglist, fmt);

    vfprintf(stderr, fmt, arglist);
    va_end (arglist);

    exit(1);
}

void output(const char *fmt, ...)
{
    va_list arglist;
    va_start(arglist, fmt);

    vfprintf(stdout, fmt, arglist);
    va_end (arglist);
}


void dict(void)
{
    int t;
    output("*BEGIN DICTIONARY*\n");

    while ((t = lex()) != 'e' && t != EOF) {
        parsetok(t);
    }

    output("*END DICTIONARY*\n");
}

void integer(void)
{
    int t;
    while ((t = lex()) != 'e' && t != EOF) {
        fputc(t, stdout);
    }

    fputc('\n', stdout);
    fflush(stdout);
}

void list(void)
{
    int t;
    output("*BEGIN LIST*\n");

    while ((t = lex()) != 'e' && t != EOF) {
        parsetok(t);
    }

    output("*END LIST*\n");
}

void string(void)
{
    int n, c, len;

    fscanf(fp, "%d:", &len);
    for (n = 0; n < len; n++) {
        c = lex();
        if (isprint(c)) fputc(c, stdout);
        else output("%.2x", c);
    }

    fputc('\n', stdout);
    fflush(stdout);
}