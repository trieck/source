/////////////////////////////////////////////////////////////////////////////
//
// DUMPCMD.CPP : Monitor dump command
//
// Copyright (c) 2006-2009, Thomas A. Rieck, All Rights Reserved
//

#include "common.h"
#include <stdlib.h>
#include "DumpCmd.h"
#include "Memory.h"
#include "CPU.h"

#define CEILING(x, y) ((x+(y-1))/y)
#define MAX(a,b)  (((a) > (b)) ? (a) : (b))

/////////////////////////////////////////////////////////////////////////////
DumpCmd::DumpCmd(Monitor *mon) : Command(mon), init(false), ip(0)
{
}

/////////////////////////////////////////////////////////////////////////////
DumpCmd::~DumpCmd()
{
}

/////////////////////////////////////////////////////////////////////////////
void DumpCmd::exec(const stringvec &v)
{
	word start, end;
	if (v.size() == 0) {
		if (!init) {
			start = CPU::getInstance()->getIP();
		} else {
			start = ip + 1;
		}
		end = start + (LINESIZE * DEFLINES) - 1;
	} else if (v.size() == 1) {
		int n = sscanf(v[0].c_str(), "%hx", &start);
		if (n != 1) {
			cerr << "? u [range]" << endl;
			return;
		}
		end = start + (LINESIZE * DEFLINES) - 1;
	} else if (v.size() > 1) {
		int n = sscanf(v[0].c_str(), "%hx", &start);
		if (n != 1) {
			cerr << "? u [range]" << endl;
			return;
		}
		n = sscanf(v[1].c_str(), "%hx", &end);
		if (n != 1) {
			cerr << "? u [range]" << endl;
			return;
		}
	}

	Memory *mem = Memory::getInstance();
	ip = start;

	word ndiff = (end+1)-start;
	word nlines = MAX(1, CEILING(ndiff, LINESIZE));

	for (word i = 0; i < nlines; i++) {
		printf("$%.4x\t", ip);

		word j;
		for (j = 0; j < LINESIZE; j++) {
			if (j > 0) putchar(' ');
			byte b = mem->fetch(ip+j);
			printf("%.2x", b);
			if (ip+j == end) break;
		}

		do {
			putchar (' ');
			putchar (' ');
			putchar (' ');
		} while (++j < LINESIZE);

		for (j = 0; j < LINESIZE; j++) {
			byte b = mem->fetch(ip+j);
			if (isprint(b))
				putchar(b);
			else putchar('.');
			if (ip+j == end) break;
		}

		putchar('\n');
		ip += j;
	}

	init = true;
};
