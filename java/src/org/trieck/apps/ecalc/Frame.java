package org.trieck.apps.ecalc;

public class Frame {

    private Symbol symbol;      // symbol table entry
    private Instruction retpc;  // where to resume after return
    private Datum argn;         // nth argument on the stack
    private int nargs;          // number of arguments

}
