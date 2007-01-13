package org.trieck.pixievm.assembler;

import java.io.FileReader;
import java.io.IOException;
import java.io.PushbackReader;
import java.io.Reader;

public class Lexer {

    public static final int TT_EMPTY = 0;
    public static final int TT_UNDEF = 1;
    public static final int TT_LITERAL = 2;
    public static final int TT_STR = 3;
    public static final int TT_NUM = 4;
    public static final int TT_LPAREN = '(';
    public static final int TT_RPAREN = ')';
    public static final int TT_POUND = '#';
    public static final int TT_SEMI = ';';
    public static final int TT_QUOTE = '\'';
    public static final int TT_PERIOD = '.';

    private static final char[] HEXISH = "0123456789abcdefABCDEF".toCharArray();

    private PushbackReader reader;
    private int lineno;

    public int getLineno() {
        return lineno;
    }

    public class Token {
        private int type;       /* token type */
        private String value;   /* token value */

        public Token() {
        }

        public int getType() {
            return type;
        }

        public void setType(int type) {
            this.type = type;
        }

        public String getValue() {
            return value;
        }

        public void setValue(String value) {
            this.value = value;
        }
    }

    /**
     * Public ctor
     *
     * @param filename
     * @throws IOException
     */
    public Lexer(String filename) throws IOException {
        this.reader = new PushbackReader(new FileReader(filename));
    }

    /**
     * Get next input token
     *
     * @return token
     * @throws IOException
     */
    public Token getToken() throws IOException {
        int c;
        StringBuffer output = new StringBuffer();
        Token tok = new Token();
        tok.setType(TT_EMPTY);

        while ((c = reader.read()) != -1) {
            switch (c) {
                case TT_LPAREN:
                case TT_RPAREN:
                case TT_POUND:
                case TT_SEMI:
                    tok.setType(c);
                    return tok;
                case TT_QUOTE:
                    if (output.length() > 0) {
                        tok.setValue(output.toString());
                        return tok;
                    }
                    return literal();
                case TT_PERIOD:
                    if (output.length() > 0) {
                        tok.setValue(output.toString());
                        return tok;
                    }
                    tok.setType(c);
                    tok.setValue(".");
                    return tok;
                case '\n':      /* white space */
                    lineno++;   /* fall through */
                case ' ':
                case '\t':
                case '\r':
                    if (output.length() > 0) {
                        tok.setValue(output.toString());
                        return tok;
                    }
                    break;  /* eat white space */
                default:
                    if (isXdigit(c)) {         /* hex digit */
                        do {
                            output.append((char) c);
                        } while ((c = reader.read()) != -1 && isXdigit(c));
                        reader.unread(c);
                        tok.setType(TT_NUM);
                        tok.setValue(output.toString());
                    } else if (isString(c)) {   /* string */
                        do {
                            output.append((char) c);
                        } while ((c = reader.read()) != -1 && isString(c));
                        reader.unread(c);
                        tok.setType(TT_STR);
                        tok.setValue(output.toString());
                    } else {
                        tok.setType(TT_UNDEF);
                        tok.setValue("" + (char) c);
                        return tok;
                    }
                    break;
            }
        }

        tok.setValue(output.toString());

        return tok;
    }

    /* Test character is hexadecimal digit */
    private static boolean isXdigit(int c) {
        for (char d : HEXISH)
            if (d == (char) c)
                return true;

        return false;
    }

    /* Test character is string */
    private static boolean isString(int c) {
        return Character.isLetterOrDigit(c) || c == '_';
    }

    /**
     * Get literal token in quotes
     *
     * @return literal
     * @throws IOException
     */
    private Token literal() throws IOException {
        int c;
        StringBuffer output = new StringBuffer();
        Token tok = new Token();
        tok.setType(TT_LITERAL);

        while ((c = reader.read()) != -1 && c != '"') {
            output.append((char) c);
        }

        reader.unread(c);

        tok.setValue(output.toString());
        return tok;
    }

}
