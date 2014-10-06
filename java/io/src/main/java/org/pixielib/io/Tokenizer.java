package org.pixielib.io;

import java.io.IOException;
import java.io.PushbackReader;
import java.io.Reader;

/**
 * Lookahead tokenizer
 */
public abstract class Tokenizer {
    private static final int BUFFER_SIZE = 8192;    // push-back reader buffer size

    private PushbackReader reader;  // underlying push-back reader
    private StringBuilder buffer;   // token buffer

    public Tokenizer(Reader r) {
        reader = new PushbackReader(r, BUFFER_SIZE);
        buffer = new StringBuilder(BUFFER_SIZE);
    }

    /**
     * Lookahead to the next token
     *
     * @return the peeked token
     * @throws java.io.IOException, if an i/o error occurs
     */
    public final String lookahead() throws IOException {
        String tok = getToken();
        unread();   // unread the token buffer
        return tok;
    }

    /**
     * Unread the entire token buffer
     *
     * @throws IOException, if an i/o error occurs
     */
    protected final void unread() throws IOException {
        unread(buffer.length());
    }

    /**
     * Unread characters from the token buffer
     *
     * @param n, the number of characters to unread
     * @return the number of characters unread
     * @throws IOException, if an i/o error occurs
     */
    protected final int unread(int n) throws IOException {

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

    protected final void clear() {
        buffer.setLength(0);
    }

    /* read next character from reader into token buffer */

    protected final int read() throws IOException {
        int c = reader.read();
        if (c != -1) {
            buffer.append((char) c);
        }

        return c;
    }

    /* get the next token from the reader */

    public abstract String getToken() throws IOException;
}
