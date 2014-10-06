package org.pixielib.content;

import org.pixielib.io.Tokenizer;

import java.io.IOException;
import java.io.Reader;

public class QueryTokenizer extends Tokenizer {

    public QueryTokenizer(Reader r) {
        super(r);
    }

    /* get the next token from the reader */
    @Override
    public String getToken() throws IOException {

        clear();    // clear the token buffer

        StringBuilder token = new StringBuilder();

        int c, blen;
        while ((c = read()) != -1) {
            blen = token.length();  // length of current token

            switch (c) {
                case '[':   // field-term delimiter
                case ']':
                    if (blen > 0) {
                        unread(1);
                        return token.toString();
                    }
                    token.append((char) c);
                    return token.toString();
                case '"':   // literal
                    if (blen > 0) {
                        unread(1);
                        return token.toString();
                    }
                    while ((c = read()) != -1 && c != '"') {
                        token.append((char) c);
                    }
                    return token.toString();
                case '_':
                case '\'':
                    if (blen > 0) {
                        token.append((char) c);
                    }
                    break;
                default:
                    if (Character.isLetterOrDigit(c)) {
                        token.append(Character.toLowerCase((char) c));
                    } else if (blen > 0) {
                        return token.toString();
                    }
                    break;
            }
        }

        return token.toString();
    }
}
