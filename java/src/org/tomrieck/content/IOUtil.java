package org.tomrieck.content;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

public class IOUtil {

    private IOUtil() {
    }

    public static void writeString(OutputStream os, String s) throws IOException {
        if (s.length() == 0) {
            warning("writing empty string");
        }
        os.write(s.getBytes());
        os.write(0);    // terminator
    }

    public static String readString(InputStream is) throws IOException {

        StringBuilder builder = new StringBuilder();

        int c;
        while ((c = is.read()) != -1) {
            if (c == '\0')
                break;

            builder.append((char) c);
        }

        if (c != -1 && builder.length() == 0) {
            warning("non-EOF, read empty string");
        }

        return builder.toString();
    }

    private static void warning(String format, Object ... args) {
        String message = String.format(format, args);
        System.err.printf("   {WARNING} : %s\n", message);
    }

}
