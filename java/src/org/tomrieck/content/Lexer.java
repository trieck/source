package org.pixielib.content;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.Reader;

public class Lexer {

    private BufferedReader reader;

    public Lexer(Reader r) {
        reader = new BufferedReader(r);
    }

    public String getToken() throws IOException {

        StringBuilder builder = new StringBuilder();

        int c;
        while ((c = reader.read()) != -1) {
            if ((c == '_' || c == '\'') && builder.length() > 0) {
                builder.append((char) c);
            } else if (Character.isLetterOrDigit(c)) {
                builder.append(Character.toLowerCase((char) c));
            } else if (builder.length() > 0) {
                return builder.toString();
            }
        }

        return builder.toString();
    }
}
