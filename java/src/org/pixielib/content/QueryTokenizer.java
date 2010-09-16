package org.pixielib.content;

import java.io.IOException;
import java.io.PushbackReader;
import java.io.Reader;

public class QueryTokenizer {

    private static final int BUFFER_SIZE = 8192;    // push-back reader buffer size

    private PushbackReader reader;  // underlying push-back reader
    private StringBuilder buffer;   // token buffer

    public QueryTokenizer(Reader r) {
        reader = new PushbackReader(r, BUFFER_SIZE);
        buffer = new StringBuilder(BUFFER_SIZE);
    }

    /**
     * Lookahead to the next token
     *
     * @return the peeked token
     * @throws IOException, if an i/o error occurs
     */
    public String lookahead() throws IOException {
        String tok = getToken();
        unread();   // unread the token buffer
        return tok;
    }

    /**
     * Unread the entire token buffer
     *
     * @throws IOException, if an i/o error occurs
     */
    private void unread() throws IOException {
        unread(buffer.length());
    }

    /**
     * Unread characters from the token buffer
     *
     * @param n, the number of characters to unread
     * @return the number of characters unread
     * @throws IOException, if an i/o error occurs
     */
    private int unread(int n) throws IOException {

        int m = Math.min(buffer.length(), n);

        int c;
        for (int i = buffer.length() - 1, j = 0; i >= 0 && j < m; i--, j++) {
            c = buffer.charAt(i);
            reader.unread(c);
            buffer.deleteCharAt(i);
        }

        return m;
    }

    /* clear the token buffer */

    private void clear() {
        buffer.setLength(0);
    }

    /* read next character from reader into token buffer */

    private int read() throws IOException {
        int c = reader.read();
        buffer.append((char) c);
        return c;
    }


    /* get the next token from the reader */

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
