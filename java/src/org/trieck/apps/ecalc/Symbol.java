package org.trieck.apps.ecalc;

public class Symbol {

    public static final int KW_UNKNOWN = 0; // unknown
    public static final int KW_PROC = 1;    // procedure
    public static final int KW_FUNC = 2;    // function
    public static final int KW_RETURN = 3;  // return statement
    public static final int KW_IF = 4;      // if statement
    public static final int KW_ELSE = 5;    // else statement
    public static final int KW_WHILE = 6;   // while statement
    public static final int KW_PRINTF = 7;  // printf builtin

    public static final int ST_UNDEF = 0;   // undefined symbol
    public static final int ST_NUM = 1;     // numeric symbol
    public static final int ST_VAR = 2;     // variable symbol
    public static final int ST_KEYWD = 3;   // keyword symbol
    public static final int ST_BUILTIN = 4; // builtin symbol
    public static final int ST_FUNC = 5;    // function symbol
    public static final int ST_PROC = 6;    // procedure symbol
    public static final int ST_STR = 7;     // string symbol

    private int type;           // symbol type
    private double value;       // float value
    private int keyword;        // keyword
    private Instruction instr;  // instruction
    private Instruction defn;   // function / procedure
    private String str;         // string value

    public Symbol() {
        type = ST_UNDEF;
        keyword = KW_UNKNOWN;
        instr = defn = null;
        str = "";
    }

    public int getType() {
        return type;
    }

    public void setType(int t) {
        type = t;
    }

    public Instruction getInstr() {
        return instr;
    }

    public void setInstr(Instruction i) {
        instr = i;
    }

    public Instruction getDefn() {
        return defn;
    }

    public void setDefn(Instruction i) {
        defn = i;
    }

    public int getKeyword() {
        return keyword;
    }

    public void setKeyword(int k) {
        keyword = k;
    }

    public void setValue(double val) {
        value = val;
    }

    public double getValue() {
        return value;
    }

}
