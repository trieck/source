package org.pixielib.games.jumble;

import java.io.IOException;
import java.io.PushbackReader;
import java.io.Reader;

public class ConcordanceReader {

    PushbackReader reader;
    
    public ConcordanceReader(Reader reader) {
        this.reader = new PushbackReader(reader);
    }

    public String getWord() throws IOException {

        StringBuilder builder = new StringBuilder();

        int c;
        while ((c = reader.read()) != -1) {
            if ((c == '\'') && builder.length() > 0) {
                builder.append((char) c);
            } else if (Character.isLetterOrDigit(c)) {
                builder.append(Character.toLowerCase((char) c));
            } else if (builder.length() > 0) {
                reader.unread(c);
                return builder.toString();
            }
        }

        return builder.toString();
    }
}
