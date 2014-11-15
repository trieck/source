#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#include "bencode.h"
#include "btdict.h"
#include "lex.h"
#include "torrent.h"

#define SHA1_LEN (20)

static void usage(void);
static void load_torrent(const char *filename);
static void display(void);
static void cleanup(void);
static void enum_trackers(bt_list *trackers);
static void display_info(bt_dict *info);
static void display_files(bt_list *files);
static void display_path(bt_list *path);
static void display_pieces(bt_string *pieces);

static FILE *fp;
static bt_element torrent;

int main(int argc, char *argv[])
{
    if (argc < 2) usage();
    atexit(cleanup);
    load_torrent(argv[1]);
    display();
    return 0;
}

void load_torrent(const char *filename)
{
    fp = fopen(filename, "rb");
    if (fp == NULL)
        error("unable to open \"%s\".\n", filename);

    torrent = getelement(fp);
    if (torrent.type != ET_DICT)
        error("bad torrent file \"%s\".", filename);

    fclose(fp);
    fp = NULL;
}

void display(void)
{
    const char *announce = bt_dict_cstring(torrent.dval, "announce");
    const char *by = bt_dict_cstring(torrent.dval, "created by");
    struct tm *ptime = bt_dict_date(torrent.dval, "creation date");
    const char *comment = bt_dict_cstring(torrent.dval, "comment");
    bt_list *trackers = bt_dict_list(torrent.dval, "announce-list");
    bt_dict *info = bt_dict_dict(torrent.dval, "info");

    if (announce) output("announce:\t%s\n", announce);
    if (ptime) {
        char buf[128];
        strftime(buf, sizeof(buf), "%m/%d/%Y %I:%M:%S %p", ptime);
        output("creation date:\t%s\n", buf);
    }
    if (by) output("created by:\t%s\n", by);
    if (comment) output("comment:\t%s\n", comment);
    if (trackers) {
        output("announce-list:\n");
        enum_trackers(trackers);
    }
    if (info) display_info(info);
}

void enum_trackers(bt_list *trackers)
{
    while (trackers) {
        switch (trackers->e.type) {
        case ET_STRING:
            if (trackers->e.sval->data)
                output("\t\t%s\n", trackers->e.sval->data);
            break;
        case ET_LIST:
            output("\t\t=============\n");
            enum_trackers(trackers->e.lval);
            output("\t\t=============\n");
            break;
        }
        trackers = trackers->next;
    }
}

void display_info(bt_dict *info)
{
    const char *name = bt_dict_cstring(info, "name");
    __int64 length = bt_dict_int(info, "length");
    const char *md5sum = bt_dict_cstring(info, "md5sum");
    bt_list *files = bt_dict_list(info, "files");
    __int64 priv = bt_dict_int(info, "private");
    __int64 piecelen = bt_dict_int(info, "piece length");
    bt_string *pieces = bt_dict_string(info, "pieces");

    output("info:\n");
    if (name) output("\t\tname:\t\t%s\n", name);
    if (length) output("\t\tlength:\t\t%I64d bytes\n", length);
    if (md5sum) output("\t\tmd5sum:\t\t%s\n", md5sum);
    output("\t\tprivate:\t%I64d\n", priv);
    if (files) display_files(files);
    output("\t\tpiece length:\t%I64d bytes\n", piecelen);
    if (pieces) display_pieces(pieces);
}

void display_files(bt_list *files)
{
    output("\t\tfiles...\n");

    while (files) {
        if (files->e.type == ET_DICT) {
            bt_list *path  = bt_dict_list(files->e.dval, "path");
            __int64 length = bt_dict_int(files->e.dval, "length");
            const char *md5sum = bt_dict_cstring(files->e.dval, "md5sum");
            if (path) display_path(path);
            output(" (%I64d bytes)\n", length);
            if (md5sum) output("\t\tmd5sum:\t\t%s\n", md5sum);
        }
        files = files->next;
    }
    output("\n");
}

void display_path(bt_list *path)
{
    int i;
    output("\t\t");

    for (i = 0; path; i++) {
        if (i > 0) output("/");
        output(path->e.sval->data);
        path = path->next;
    }
}

void display_pieces(bt_string *pieces)
{
    int i, j, npieces;
    char *ppieces = pieces->data;

    if (pieces->nlen % SHA1_LEN)
        error("pieces not a multiple of sha1 length.");
    npieces = pieces->nlen / SHA1_LEN;

    output("pieces (%d):\n", npieces);
    for (i = 0; i < npieces; i++) {
        output("\t\t(0x%.4X)  0x", i+1);
        for (j = 0; j < SHA1_LEN; j++) {
            output("%.2X", (unsigned char)*ppieces++);
        }
        output("\n");
    }
}

void cleanup(void)
{
    if (fp != NULL) {
        fclose(fp);
        fp = NULL;
    }
    free_element(torrent);
}

void usage(void)
{
    error("usage: torrent file\n");
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

