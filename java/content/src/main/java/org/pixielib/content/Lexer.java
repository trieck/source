package org.pixielib.content;

import org.pixielib.io.Tokenizer;

import java.io.IOException;
import java.io.Reader;

public class Lexer extends Tokenizer {

    public Lexer(Reader r) {
        super(r);
    }

    /* get next token from reader */
    @Override
    public String getToken() throws IOException {

        clear();    // clear the token buffer

        StringBuilder builder = new StringBuilder();

        int c;
        while ((c = read()) != -1) {
            if ((c == '_' || c == '\'') && builder.length() > 0) {
                builder.append((char) c);
            } else if (Character.isLetterOrDigit(c)) {
                builder.append(Character.toLowerCase((char) c));
            } else if (builder.length() > 0) {
                unread(1);
                return builder.toString();
            }
        }

        return builder.toString();
    }
}
