package org.pixielib.apps.ecalc;

public class Program {

    public Program() {
    }

    /**
     * Generate instruction code
     *
     * @param instr the instruction
     */
    public void code(Instruction instr) {
    }

    /**
     * Store program data from symbol table
     *
     * @param symbol
     *            the symbol
     */
    // public void code(Symbol symbol) {
    // }

    /**
     * Define a function / procedure
     *
     * @param name the procedure name
     * @param type the symbol type
     */
    public void define(String name, int type) {
        Symbols.install(name, type, /* base */null);
        // pbase = pmem
    }

}
