/////////////////////////////////////////////////////////////////////////////
//
// MONITOR.CPP : Pixie Virtual Machine Monitor
//
// Copyright (c) 2006, Thomas A. Rieck, All Rights Reserved
//

#include "Common.h"
#include "Memory.h"
#include "Trap.h"
#include "Interrupt.h"
#include "CPU.h"
#include "Util.h"
#include "Modes.h"
#include "Instructions.h"
#include "Monitor.h"
#include "Machine.h"
#include "LineReader.h"
#include "SymbolTable.h"
#include "Opinfo.h"
#include "MiniAssembler.h"
#include "MiniDisassembler.h"
#include "Exception.h"
#include <sys/types.h>
#include <sys/stat.h>

/////////////////////////////////////////////////////////////////////////////
class Help : public Command {
public:
	Help(Monitor *mon) : Command(mon) {}
	void exec(const stringvec &v) {
		cout << "?   print help screen" << endl;
		cout << "a   assemble [address]" << endl;
		cout << "d   disassemble [range]" << endl;
		cout << "l   load address file" << endl;
		cout << "q   quit" << endl;
		cout << "r   print registers" << endl;
		cout << "s   save range file" << endl;
		cout << "z   step" << endl;
	}
};

/////////////////////////////////////////////////////////////////////////////
class Assemble : public Command {
private:
	MiniAssembler assembler;
public:
	Assemble(Monitor *mon) : Command(mon) {}
	void exec(const stringvec &v) {
		word address;
		if (v.size()) {
			int n = sscanf(v[0].c_str(), "%hx", &address);
			if (n != 1) {
				cerr << "? a [address]" << endl;
				return;
			}
			assembler.assemble(&address);
		} else {
			assembler.assemble(NULL);
		}
	}
};

/////////////////////////////////////////////////////////////////////////////
class Disassemble : public Command {
private:
	MiniDisassembler disassembler;
public:
	Disassemble(Monitor *mon) : Command(mon) {}
	void exec(const stringvec &v) {
		word start, end;
		if (v.size() == 0) {
			disassembler.disassemble(NULL, NULL);
		} else if (v.size() == 1) {
			int n = sscanf(v[0].c_str(), "%hx", &start);
			if (n != 1) {
				cerr << "? d [range]" << endl;
				return;
			}
			disassembler.disassemble(&start, NULL);
		} else if (v.size() > 1) {
			int n = sscanf(v[0].c_str(), "%hx", &start);
			if (n != 1) {
				cerr << "? d [range]" << endl;
				return;
			}
			n = sscanf(v[1].c_str(), "%hx", &end);
			if (n != 1) {
				cerr << "? d [range]" << endl;
				return;
			}
			disassembler.disassemble(&start, &end);
		}
	}
};

/////////////////////////////////////////////////////////////////////////////
class Load : public Command {
public:
	Load(Monitor *mon) : Command(mon) {}
	void exec(const stringvec &v) {
		word start;
		if (v.size() < 2) {
			cerr << "? l address file" << endl;
			return;
		}
		int n = sscanf(v[0].c_str(), "%hx", &start);
		if (n != 1) {
			cerr << "? l address file" << endl;
			return;
		}
		string filename = v[1];

		struct _stat buf;
		n = stat(filename.c_str(), (struct stat*)&buf);
		if (n) {
			fprintf(stderr, "unable to stat file \"%s\".\n", filename.c_str());
			return;
		}

		ifstream ifs;
		ifs.open(filename.c_str(), ifstream::in | ifstream::binary);
		if (!ifs.is_open()) {
			fprintf(stderr, "unable to open file \"%s\".\n", filename.c_str());
			return;
		}

		Memory *mem = Memory::getInstance();
		if (!mem->load(ifs, start, buf.st_size)) {
			fprintf(stderr, "unable to load file \"%s\".\n",
			        filename.c_str());
		}
	}
};

/////////////////////////////////////////////////////////////////////////////
class Save : public Command {
public:
	Save(Monitor *mon) : Command(mon) {}
	void exec(const stringvec &v) {
		word start, end;
		if (v.size() < 3) {
			cerr << "? s range file" << endl;
			return;
		}
		int n = sscanf(v[0].c_str(), "%hx", &start);
		if (n != 1) {
			cerr << "? s range file" << endl;
			return;
		}
		n = sscanf(v[1].c_str(), "%hx", &end);
		if (n != 1) {
			cerr << "? s range file" << endl;
			return;
		}

		string filename = v[2];
		ofstream ofs;
		ofs.open(filename.c_str(), ofstream::out | ofstream::binary);
		if (!ofs.is_open()) {
			fprintf(stderr, "unable to open file \"%s\".\n",
			        filename.c_str());
			return;
		}

		Memory *mem = Memory::getInstance();
		if (!mem->save(ofs, start, (end - start) + 1)) {
			fprintf(stderr, "unable to save to file \"%s\".\n",
			        filename.c_str());
		}
	}
};

/////////////////////////////////////////////////////////////////////////////
class Quit : public Command {
public:
	Quit(Monitor *mon) : Command(mon) {}
	void exec(const stringvec &v) {
		exit(0);
	}
};

/////////////////////////////////////////////////////////////////////////////
class Registers : public Command {
public:
	Registers(Monitor *mon) : Command(mon) {}
	void exec(const stringvec &v) {
		CPU *cpu = CPU::getInstance();

		char sr[9];
		word flags = cpu->getFL();
		sr[0] = flags & NEG_FLAG ? '1' : '0';
		sr[1] = flags & OVERFLOW_FLAG ? '1' : '0';
		sr[2] = '0'; /* unused */
		sr[3] = '0'; /* unused */
		sr[4] = flags & BRK_FLAG ? '1' : '0';
		sr[5] = flags & INT_DISABLE_FLAG ? '1' : '0';
		sr[6] = flags & ZERO_FLAG ? '1' : '0';
		sr[7] = flags & CARRY_FLAG ? '1' : '0';
		sr[8] = '\0';

		printf(" A: $%.4hX"
		       "  B: $%.4hX"
		       "  C: $%.4hX"
		       "  D: $%.4hX\n"
		       " X: $%.4hX"
		       " SP: $%.4hX"
		       " IP: $%.4hX"
		       " FL: %s\n",
		       cpu->getA(), cpu->getB(), cpu->getC(), cpu->getD(),
		       cpu->getX(), cpu->getSP(), cpu->getIP(), sr);
	}
};

/////////////////////////////////////////////////////////////////////////////
class Step : public Command {
public:
	Step(Monitor *mon) : Command(mon) {}

	void exec(const stringvec &v) {
		g_interrupt.setPending(IK_MONITOR);
		getMonitor()->setExit(true);
	}
};

/////////////////////////////////////////////////////////////////////////////
Monitor::Monitor() : exit_mon(false), show_notice(true)
{
	commands["?"] = new Help(this);
	commands["a"] = new Assemble(this);
	commands["d"] = new Disassemble(this);
	commands["l"] = new Load(this);
	commands["q"] = new Quit(this);
	commands["r"] = new Registers(this);
	commands["s"] = new Save(this);
	commands["z"] = new Step(this);
}

/////////////////////////////////////////////////////////////////////////////
Monitor::~Monitor()
{
	CommandMap::const_iterator it = commands.begin();
	for (; it != commands.end(); it++) {
		LPCOMMAND cmd = (*it).second;
		delete cmd;
	}
}

/////////////////////////////////////////////////////////////////////////////
void Monitor::run(void *data)
{
	LineReader reader(cin);
	string line;

	notice();

	for (exit_mon = false; !exit_mon; ) {
		prompt();
		line = reader.readLine();
		if (line.length())
			dispatch(line);
	}
}

/////////////////////////////////////////////////////////////////////////////
void Monitor::notice()
{
	if (show_notice) {
		cout << endl << "PixieVM version 0.0.1" << endl
			<< "Copyright(c) 2006-2009 Thomas A. Rieck" << endl
			<< "type '?' for help" << endl;
	}
}

/////////////////////////////////////////////////////////////////////////////
void Monitor::dispatch(const string & line)
{
	stringvec v = tokenize(line);
	if (v.size() == 0) {
		cerr << '?' << endl;
	} else {
		LPCOMMAND command = commands[v[0]];
		if (command == NULL) {
			cerr << '?' << endl;
		} else {
			v.erase(v.begin());
			command->exec(v);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
void Monitor::prompt()
{
	cout << "> ";
}

////////////////////////////////////////////////////////////////////////////
void Monitor::trap(void *data)
{
	run(data);
}

