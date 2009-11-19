package org.trieck.pixievm.assembler;

import java.util.HashMap;
import java.util.Map;

public class SymbolTable {

    private Map<String, Symbol> table = new HashMap<String, Symbol>();

    public SymbolTable() {
    }

    public Symbol get(String k) {
        return table.get(k);
    }

    public void put(String k, Symbol s) {
        table.put(k, s);
    }

}
