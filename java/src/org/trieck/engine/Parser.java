package org.trieck.engine;

import java.io.FileInputStream;
import java.io.IOException;

public class Parser {

    private Lexer lexer;
    private Inverter table = new Inverter();

    public Parser(String filename) throws IOException {
        lexer = new Lexer(new FileInputStream(filename));
    }

    public void parse() throws IOException {
        String tok;
        for (int i = 0; (tok = lexer.getToken()).length() > 0; i++) {
            append(tok, i, lexer.getOffset() - tok.length() - 1);
        }
    }

    private void append(String s, int word, int offset) {
        Locality list = table.get(s);
        list = list != null ? list : new Locality();
        list.add(new Location(word, offset));
        table.put(s, list);
    }

    public Locality get(String term) {
        return table.get(term);
    }
}
