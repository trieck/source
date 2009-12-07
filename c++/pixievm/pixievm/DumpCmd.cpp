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
DumpCmd::DumpCmd(Monitor *mon) : Command(mon)
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
		start = CPU::getInstance()->getIP();
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
	word pc = start;
	uint32_t nlines = CEILING((end+1)-start, LINESIZE);

	for (uint32_t i = 0; i < nlines; i++) {
		printf("$%.4x\t", pc);

		uint32_t j;
		for (j = 0; j < LINESIZE; j++) {
			if (j > 0) putchar(' ');
			byte b = mem->fetch(pc+j);
			printf("%.2x", b);
			if (pc+j == end) break;
		}

		do {
			putchar (' ');
			putchar (' ');
			putchar (' ');
		} while (++j < LINESIZE);

		for (j = 0; j < LINESIZE; j++) {
			byte b = mem->fetch(pc+j);
			if (isprint(b))
				putchar(b);
			else putchar('.');
			if (pc+j == end) break;
		}

		putchar('\n');
		pc += j;
	} 
};