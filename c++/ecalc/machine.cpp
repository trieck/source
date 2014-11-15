/////////////////////////////////////////////////////////////////////////////
//
// MACHINE.CPP	a simple stack machine
//
// Copyright (c) 1999 Thomas A. Rieck
//

#include "common.h"
#include "machine.h"
#include "program.h"
#include "symbol.h"
#include "except.h"
#include <math.h>
#include <iostream>

extern Program program;

// Helper functions
static char unescape (const char c);

//
// Constructor
//
Machine::Machine ()
{
    pc = NULL;
    returning = false;
}

//
// Destructor
//
Machine::~Machine()
{
}

//
// run
//
void Machine::run(const char *input)
{
    for (const char** pp = &input; **pp; ) {
        init();
        compiler.compile(pp);
        pc = program;
        returning = false;
        execute(pc);
    }
}

//
// init
//
void Machine::init()
{
    program.init();
    machinestack.reset();
    framestack.reset();
}

//
// execute
//
void Machine::execute(const Instr * p)
{
    try {
        for (pc = p; *pc != STOP && !returning; )
            (this->*(*pc++))();
    } catch (const Warning & w) {
        cerr << w << endl;
    } catch (const Error & e) {
        cerr << e << endl;
        exit(1);
    }
}

//
// plus
//
void Machine::plus()
{
    Datum d1 = machinestack.pop();
    Datum d2 = machinestack.pop();

    Datum d3;
    d3.value = d1.value + d2.value;

    machinestack.push(d3);
}

//
// minus
//
void Machine::minus()
{
    Datum d1 = machinestack.pop();
    Datum d2 = machinestack.pop();

    Datum d3;
    d3.value = d2.value - d1.value;

    machinestack.push(d3);
}

//
// unaryminus
//
void Machine::unaryminus()
{
    Datum d = machinestack.pop();

    d.value = - d.value;

    machinestack.push(d);
}

//
// mult
//
void Machine::mult()
{
    Datum d1 = machinestack.pop();
    Datum d2 = machinestack.pop();

    Datum d3;
    d3.value = d2.value * d1.value;

    machinestack.push(d3);
}

//
// divide
//
void Machine::divide()
{
    Datum d1 = machinestack.pop();
    Datum d2 = machinestack.pop();

    if (d1.value == 0)
        throw Warning(W_DIVIDEBYZERO);

    Datum d3;
    d3.value = d2.value / d1.value;

    machinestack.push(d3);
}

//
// mod
//
void Machine::mod()
{
    Datum d1 = machinestack.pop();
    Datum d2 = machinestack.pop();

    if (d1.value == 0)
        throw Warning(W_DIVIDEBYZERO);

    Datum d3;
    d3.value = int(d2.value) % int(d1.value);

    machinestack.push(d3);
}

//
// assign
//
void Machine::assign()
{
    Datum d1 = machinestack.pop();
    Datum d2 = machinestack.pop();

    if (d2.symbol == NULL)
        throw Warning(W_LITERALASSIGN);

    if (d2.symbol->type != variable && d2.symbol->type != undefined)
        throw Warning(W_NONVARASSIGN);

    d2.symbol->value = d1.value;
    d2.symbol->type = variable;

    machinestack.push(d1);
}

//
// varpush
//
void Machine::varpush()
{
    Datum d;
    d.symbol = *(Symbol **)pc++;
    machinestack.push(d);
}

//
// constpush
//
void Machine::constpush()
{
    Datum d;
    d.value = (*(Symbol**)pc++)->value;
    machinestack.push(d);
}

//
// strpush
//
void Machine::strpush()
{
    Datum d;
    d.symbol = *(Symbol **)pc++;
    machinestack.push(d);
}

//
// eval
//
void Machine::eval()
{
    Datum d = machinestack.pop();
    if (d.symbol == NULL)
        throw Warning(W_EVALLITERAL);

    if (d.symbol->type == undefined)
        throw Warning(W_UNDEFINEDVAR);

    d.value = d.symbol->value;
    machinestack.push(d);
}

//
// printf
//
void Machine::printf()
{
    int nargs = *(int *)pc++;

    // first argument is the deepest
    Datum * dp = machinestack.stackp - nargs;
    const char * format = (dp++)->symbol->str;

    for ( ; format[0] != '\0'; *format++) {
        if (format[0] == '%') {
            switch (format[1]) {
            case 'c':
                cout << (char)(dp++)->value;
                format++;
                break;
            case 'd':
                cout << (int)(dp++)->value;
                format++;
                break;
            case 'f':
                cout << (float)(dp++)->value;
                format++;
                break;
            case 's':
                cout << (dp++)->symbol->str;
                format++;
                break;
            default:
                break;
            }
        } else if (format[0] == '\\') {
            cout << unescape(format[1]);
            format++;
        } else cout << format[0];
    }

    // pop the arguments from the stack
    for (int i = 0; i < nargs; i++)
        machinestack.pop();
}

//
// pow
//
void Machine::pow()
{
    Datum d1 = machinestack.pop();
    Datum d2 = machinestack.pop();

    Datum d3;
    d3.value = ::pow(d2.value, d1.value);

    machinestack.push(d3);
}

//
// log
//
void Machine::log()
{
    Datum d1 = machinestack.pop();

    Datum d2;
    d2.value = ::log(d1.value);

    machinestack.push(d2);
}

//
// log10
//
void Machine::log10()
{
    Datum d1 = machinestack.pop();

    Datum d2;
    d2.value = ::log10(d1.value);

    machinestack.push(d2);
}

//
// fmod
//
void Machine::fmod()
{
    Datum d1 = machinestack.pop();
    Datum d2 = machinestack.pop();

    Datum d3;
    d3.value = ::fmod(d2.value, d1.value);

    machinestack.push(d3);
}

//
// sin
//
void Machine::sin()
{
    Datum d1 = machinestack.pop();

    Datum d2;
    d2.value = ::sin(d1.value);

    machinestack.push(d2);
}

//
// asin
//
void Machine::asin()
{
    Datum d1 = machinestack.pop();

    Datum d2;
    d2.value = ::asin(d1.value);

    machinestack.push(d2);
}

//
// sinh
//
void Machine::sinh()
{
    Datum d1 = machinestack.pop();

    Datum d2;
    d2.value = ::sinh(d1.value);

    machinestack.push(d2);
}


//
// cos
//
void Machine::cos()
{
    Datum d1 = machinestack.pop();

    Datum d2;
    d2.value = ::cos(d1.value);

    machinestack.push(d2);
}

//
// acos
//
void Machine::acos()
{
    Datum d1 = machinestack.pop();

    Datum d2;
    d2.value = ::acos(d1.value);

    machinestack.push(d2);
}

//
// cosh
//
void Machine::cosh()
{
    Datum d1 = machinestack.pop();

    Datum d2;
    d2.value = ::cosh(d1.value);

    machinestack.push(d2);
}

//
// tan
//
void Machine::tan()
{
    Datum d1 = machinestack.pop();

    Datum d2;
    d2.value = ::tan(d1.value);

    machinestack.push(d2);
}

//
// atan
//
void Machine::atan()
{
    Datum d1 = machinestack.pop();

    Datum d2;
    d2.value = ::atan(d1.value);

    machinestack.push(d2);
}

//
// tanh
//
void Machine::tanh()
{
    Datum d1 = machinestack.pop();

    Datum d2;
    d2.value = ::tanh(d1.value);

    machinestack.push(d2);
}

//
// sqrt
//
void Machine::sqrt()
{
    Datum d1 = machinestack.pop();

    Datum d2;
    d2.value = ::sqrt(d1.value);

    machinestack.push(d2);
}

//
// iint
//
void Machine::iint ()
{
    Datum d1 = machinestack.pop();

    Datum d2;
    d2.value = int(d1.value);

    machinestack.push(d2);
}

//
// exp
//
void Machine::exp()
{
    Datum d1 = machinestack.pop();

    Datum d2;
    d2.value = ::exp(d1.value);

    machinestack.push(d2);
}

//
// ceil
//
void Machine::ceil()
{
    Datum d1 = machinestack.pop();

    Datum d2;
    d2.value = ::ceil(d1.value);

    machinestack.push(d2);
}

//
// floor
//
void Machine::floor()
{
    Datum d1 = machinestack.pop();

    Datum d2;
    d2.value = ::floor(d1.value);

    machinestack.push(d2);
}

//
// abs
//
void Machine::abs()
{
    Datum d1 = machinestack.pop();

    Datum d2;
    d2.value = ::fabs(d1.value);

    machinestack.push(d2);
}

//
// shiftleft
//
void Machine::shiftleft()
{
    Datum d1 = machinestack.pop();
    Datum d2 = machinestack.pop();

    Datum d3;
    d3.value = int(d2.value) << int(d1.value);

    machinestack.push(d3);
}

//
// shiftright
//
void Machine::shiftright()
{
    Datum d1 = machinestack.pop();
    Datum d2 = machinestack.pop();

    Datum d3;
    d3.value = int(d2.value) >> int(d1.value);

    machinestack.push(d3);
}

//
// whilecode
//
void Machine::whilecode()
{
    const Instr *savepc = pc;			// loop body

    execute(savepc + 2);                // condition

    Datum d = machinestack.pop();
    while (d.value) {
        execute(*(Instr **)(savepc));	// loop body
        if (returning)
            break;

        execute(savepc + 2);			// condition
        d = machinestack.pop();
    }

    if (!returning)
        pc = *((Instr **)(savepc + 1));	// next statement
}

//
// ifcode
//
void Machine::ifcode()
{
    const Instr *savepc = pc;			// then part

    execute(savepc + 3);				// condition

    Datum d = machinestack.pop();
    if (d.value)
        execute(*((Instr **)(savepc)));
    else if (*((Instr **)(savepc + 1)))	// else part
        execute(*((Instr **)(savepc + 1)));

    if (!returning)
        pc = *((Instr **)(savepc + 2));	// next statement
}

//
// lt
//
void Machine::lt()
{
    Datum d1 = machinestack.pop();
    Datum d2 = machinestack.pop();

    Datum d3;
    d3.value = double(d2.value < d1.value);

    machinestack.push(d3);
}

//
// gt
//
void Machine::gt()
{
    Datum d1 = machinestack.pop();
    Datum d2 = machinestack.pop();

    Datum d3;
    d3.value = double(d2.value > d1.value);

    machinestack.push(d3);
}

//
// le
//
void Machine::le()
{
    Datum d1 = machinestack.pop();
    Datum d2 = machinestack.pop();

    Datum d3;
    d3.value = double(d2.value <= d1.value);

    machinestack.push(d3);
}

//
// ge
//
void Machine::ge()
{
    Datum d1 = machinestack.pop();
    Datum d2 = machinestack.pop();

    Datum d3;
    d3.value = double(d2.value >= d1.value);

    machinestack.push(d3);
}

//
// eq
//
void Machine::eq()
{
    Datum d1 = machinestack.pop();
    Datum d2 = machinestack.pop();

    Datum d3;
    d3.value = double(d2.value == d1.value);

    machinestack.push(d3);
}

//
// ne
//
void Machine::ne()
{
    Datum d1 = machinestack.pop();
    Datum d2 = machinestack.pop();

    Datum d3;
    d3.value = double(d2.value != d1.value);

    machinestack.push(d3);
}

//
// not
//
void Machine::not()
{
    Datum d1 = machinestack.pop();

    Datum d2;
    d2.value = double(!d1.value);

    machinestack.push(d2);
}

//
// pop
//
void Machine::pop()
{
    machinestack.pop();
}

//
// bitand
//
void Machine::bitand()
{
    Datum d1 = machinestack.pop();
    Datum d2 = machinestack.pop();

    Datum d3;
    d3.value = int(d2.value) & int(d1.value);

    machinestack.push(d3);
}

//
// logand
//
void Machine::logand()
{
    Datum d1 = machinestack.pop();
    Datum d2 = machinestack.pop();

    Datum d3;
    d3.value = d2.value && d1.value;

    machinestack.push(d3);
}

//
// bitor
//
void Machine::bitor()
{
    Datum d1 = machinestack.pop();
    Datum d2 = machinestack.pop();

    Datum d3;
    d3.value = int(d2.value) | int(d1.value);

    machinestack.push(d3);
}

//
// logor
//
void Machine::logor()
{
    Datum d1 = machinestack.pop();
    Datum d2 = machinestack.pop();

    Datum d3;
    d3.value = d2.value || d1.value;

    machinestack.push(d3);
}

//
// call
//
void Machine::call()	// call a function
{
    const Symbol * sp = *(Symbol **)pc;

    Frame frame;
    frame.sp = sp;
    frame.nargs = *(int *)(pc + 1);
    frame.retpc = pc + 2;
    frame.argn = machinestack.stackp - 1;

    framestack.push(frame);

    execute(sp->defn);

    returning = false;
}

//
// funcret
//
void Machine::funcret()
{
    if (framestack.framep->sp->type == procedure)
        throw Warning(W_PROCRETVAL);

    Datum d = machinestack.pop();
    ret();
    machinestack.push(d);
}

//
// procret
//
void Machine::procret()
{
    if (framestack.framep->sp->type == function)
        throw Warning(W_FUNCRETNOVAL);

    ret();
}

//
// ret
//
void Machine::ret()	// return from a function / procedure
{
    for (int i = 0; i < framestack.framep->nargs; i++) {
        machinestack.pop();
    }

    pc = framestack.framep->retpc;
    framestack.framep--;

    returning = true;
}

//
// arg
//
void Machine::arg()
{
    Datum d;
    d.value = *getarg();
    machinestack.push(d);
}

//
// argassign
//
void Machine::argassign()
{
    Datum d = machinestack.pop();
    machinestack.push(d);
    *getarg() = d.value;
}

//
// getarg
//
double * Machine::getarg()
{
    int nargs = *(int *)pc++;
    if (nargs > framestack.framep->nargs)
        throw Warning(W_NOTENOUGHARGS);

    return &framestack.framep->argn[nargs - framestack.framep->nargs].value;
}

// Helper functions

char unescape (const char c)
{
    static const char transtab[] = "b\bf\fn\nr\rt\t";

    if (strchr(transtab, c)) {
        return strchr(transtab, c)[1];
    }

    return c;
}
