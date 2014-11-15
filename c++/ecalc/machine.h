/////////////////////////////////////////////////////////////////////////////
//
//	MACHINE.H		a simple stack machine
//
//	Copyright (c) 1999 Thomas A. Rieck
//

#ifndef __MACHINE_H__
#define __MACHINE_H__

#include "stack.h"
#include "frame.h"
#include "compile.h"

// Forward declarations
class SymbolTable;

/////////////////////////////////////////////////////////////////////////////
class Machine {
    friend class Compile;
    friend class SymbolTable;

public:
// Construction / Destruction
    Machine ();
    ~Machine();

// Interface
    void run(const char *);
// Implementation
protected:
    // built in functions
    void plus();
    void minus();
    void unaryminus();
    void mult();
    void divide();
    void mod();
    void assign();
    void varpush();
    void constpush();
    void strpush();
    void eval();
    void printf();
    void pow();
    void log();
    void log10();
    void fmod();
    void sin();
    void asin();
    void sinh();
    void cos();
    void acos();
    void cosh();
    void tan();
    void atan();
    void tanh();
    void sqrt();
    void iint();
    void exp();
    void ceil();
    void floor();
    void abs();
    void shiftleft();
    void shiftright();
    void whilecode();
    void ifcode();
    void lt();
    void gt();
    void le();
    void ge();
    void eq();
    void ne();
    void not();
    void pop();
    void bitand();
    void bitor();
    void logand();
    void logor();
    void arg();
    void argassign();
    void call();
    void funcret();
    void procret();
    void ret();

    void execute(const Instr *);
    void init();

    double *getarg();
private:
    const Instr * pc;		// program counter during execution
    Stack machinestack;		// machine stack
    FrameStack framestack;	// procedure / function call frame stack
    Compile compiler;		// compiler
    bool returning;			// returning from a function / procedure
};
/////////////////////////////////////////////////////////////////////////////

#endif // __MACHINE_H__

