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
#include "StepUntilCmd.h"
#include "Interrupt.h"
#include "CPU.h"
#include <signal.h>

MonitorPtr Monitor::instance(Monitor::getInstance());

/////////////////////////////////////////////////////////////////////////////
Monitor::Monitor() : m_exit_mon(false), m_show_notice(true)
{
	m_commands["?"] = new HelpCmd(this);
	m_commands["help"] = m_commands["?"]->CopyRef();
	m_commands["a"] = new AssemCmd(this);
	m_commands["d"] = new DisassemCmd(this);
	m_commands["l"] = new LoadCmd(this);
	m_commands["m"] = new DumpCmd(this);
	m_commands["q"] = new QuitCmd(this);
	m_commands["r"] = new RegistersCmd(this);
	m_commands["s"] = new SaveCmd(this);
	m_commands["t"] = new StepCmd(this);
	m_commands["u"] = new StepUntilCmd(this);
}

/////////////////////////////////////////////////////////////////////////////
Monitor::~Monitor()
{
	CommandMap::const_iterator it = m_commands.begin();
	for (; it != m_commands.end(); it++) {
		LPCOMMAND cmd = (*it).second;
		cmd->DecRef();
	}
}

/////////////////////////////////////////////////////////////////////////////
Monitor *Monitor::getInstance()
{
	if (instance.get() == NULL) {
		instance = MonitorPtr(new Monitor);
	}
	return instance.get();
}

/////////////////////////////////////////////////////////////////////////////
void Monitor::disassemble(word address)
{
	// this is a single line convenience method used by the stepper

	DisassemCmd *disassemble = static_cast<DisassemCmd*>(m_commands["d"]);
	if (disassemble != NULL) {
		disassemble->disassemble(address);
	}
}

/////////////////////////////////////////////////////////////////////////////
void Monitor::run()
{
	notice();
	signal(SIGBREAK, &Monitor::sighandler);
	runLoop(NULL);
}

/////////////////////////////////////////////////////////////////////////////
void Monitor::runLoop(void *data)
{
	LineReader reader(cin);
	string line;

	for (m_exit_mon = false; !m_exit_mon; ) {
		prompt();
		line = reader.readLine();
		if (line.length())
			dispatch(line);
	}
}

/////////////////////////////////////////////////////////////////////////////
void Monitor::notice() const
{
	if (m_show_notice) {
		cout << "PixieVM Monitor version 0.0.1" << endl
		     << "Copyright (c) 2006-2009 Thomas A. Rieck" << endl
		     << "use CTRL+BREAK to break execution." << endl
		     << "type '?' for help." << endl;
	}
}

/////////////////////////////////////////////////////////////////////////////
void Monitor::dispatch(const string & line)
{
	stringvec v = tokenize(line);
	if (v.size() == 0) {
		cerr << '?' << endl;
	} else {
		CommandMap::const_iterator it = m_commands.find(v[0]);
		if (it == m_commands.end()) {
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

////////////////////////////////////////////////////////////////////////////
void Monitor::sighandler(int signum)
{
	Monitor *This = Monitor::getInstance();
	CPU *cpu = CPU::getInstance();

	switch (signum) {
	case SIGBREAK:
		if (!This->isRunning()) {	// executing code, not in monitor
			This->setExit(false);	// set back to running to break
		} else {
			cpu->setShutdown(true);	// shut down CPU
			This->setExit(true);	// exit monitor
		}
	default:
		break;
	};
}