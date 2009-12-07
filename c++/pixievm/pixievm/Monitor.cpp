/////////////////////////////////////////////////////////////////////////////
//
// MONITOR.CPP : Pixie Virtual Machine Monitor
//
// Copyright (c) 2006-2009, Thomas A. Rieck, All Rights Reserved
//

#include "Common.h"
#include "Monitor.h"
#include "LineReader.h"
#include "Util.h"
#include "HelpCmd.h"
#include "AssemCmd.h"
#include "DisassemCmd.h"
#include "LoadCmd.h"
#include "QuitCmd.h"
#include "RegistersCmd.h"
#include "SaveCmd.h"
#include "DumpCmd.h"
#include "StepCmd.h"

/////////////////////////////////////////////////////////////////////////////
Monitor::Monitor() : exit_mon(false), show_notice(true)
{
	commands["?"] = new HelpCmd(this);
	commands["help"] = commands["?"]->CopyRef();
	commands["a"] = new AssemCmd(this);
	commands["d"] = new DisassemCmd(this);
	commands["l"] = new LoadCmd(this);
	commands["q"] = new QuitCmd(this);
	commands["r"] = new RegistersCmd(this);
	commands["s"] = new SaveCmd(this);
	commands["u"] = new DumpCmd(this);
	commands["z"] = new StepCmd(this);
}

/////////////////////////////////////////////////////////////////////////////
Monitor::~Monitor()
{
	CommandMap::const_iterator it = commands.begin();
	for (; it != commands.end(); it++) {
		LPCOMMAND cmd = (*it).second;
		cmd->DecRef();
	}
}

/////////////////////////////////////////////////////////////////////////////
void Monitor::disassemble(word address)
{
	// this is a single line convenience method used by the stepper

	DisassemCmd *disassemble = static_cast<DisassemCmd*>(commands["d"]);
	if (disassemble != NULL) {
		disassemble->disassemble(address);
	}
}

/////////////////////////////////////////////////////////////////////////////
void Monitor::run()
{
	notice();
	runLoop(NULL);
}

/////////////////////////////////////////////////////////////////////////////
void Monitor::runLoop(void *data)
{
	LineReader reader(cin);
	string line;
	
	for (exit_mon = false; !exit_mon; ) {
		prompt();
		line = reader.readLine();
		if (line.length())
			dispatch(line);
	}
}

/////////////////////////////////////////////////////////////////////////////
void Monitor::notice() const
{
	if (show_notice) {
		cout << endl << "PixieVM version 0.0.1" << endl
			<< "Copyright (c) 2006-2009 Thomas A. Rieck" << endl
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
		CommandMap::const_iterator it = commands.find(v[0]);
		if (it == commands.end()) {
			cerr << '?' << endl;
		} else {
			v.erase(v.begin());
			LPCOMMAND command = (*it).second;
			command->exec(v);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
void Monitor::prompt() const
{
	cout << "> ";
}

////////////////////////////////////////////////////////////////////////////
void Monitor::handle()
{
	run();
}

////////////////////////////////////////////////////////////////////////////
void Monitor::trap(void *data)
{
	runLoop(data);
}

