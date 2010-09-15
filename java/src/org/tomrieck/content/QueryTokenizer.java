package org.pixielib.content;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.Reader;

public class QueryTokenizer {

    private static final int READ_AHEAD_LIMIT = 8192;

    private BufferedReader reader;

    public QueryTokenizer(Reader r) {
        reader = new BufferedReader(r);
    }

    public String lookahead() throws IOException {
        reader.mark(READ_AHEAD_LIMIT);

        String tok = getToken();

        reader.reset();

        return tok;
    }

    public String getToken() throws IOException {

        StringBuilder builder = new StringBuilder();

        int c;
        while ((c = reader.read()) != -1) {
            if (c == ':') { // field/term delimiter
              if (builder.length() > 0) {
                    return builder.toString();
              }
              builder.append((char)c);
              return builder.toString();
            } else if (c == '"') { // literal
                if (builder.length() > 0) {
                    return builder.toString();
                }
                
                while ((c = reader.read()) != -1 && c != '"') {
                    builder.append((char) c);
                }
                return builder.toString();
            } else if ((c == '_' || c == '\'') && builder.length() > 0) {
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
