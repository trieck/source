package org.trieck.engine;

import java.io.IOException;
import java.io.InputStream;

public class Lexer {

    private InputStream is;
    private int offset;

    public Lexer(InputStream is) {
        this.is = is;
    }

    /* Get next token from input */
    public String getToken() throws IOException {
        StringBuffer buff = new StringBuffer();

        for (int c; (c = is.read()) != -1; offset++) {
            if (Character.isLetterOrDigit((char) c)) {
                buff.append(Character.toLowerCase((char) c));
            } else if (buff.length() > 0) {
                offset++;
                break;
            }
        }

        return buff.toString();
    }

    public int getOffset() {
        return offset;
    }
}
