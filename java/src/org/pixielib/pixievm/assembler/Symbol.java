package org.pixielib.pixievm.assembler;

public class Symbol {

    public static final int ST_OPCODE = 0;

    public int getType() {
        return type;
    }

    private int type;

    public Symbol() {

    }
}
