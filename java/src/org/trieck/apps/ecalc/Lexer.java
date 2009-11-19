package org.trieck.apps.ecalc;

public class Lexer {

    // token types
    public static final char TT_UNDEF = '\u0000';       // undefined token
    public static final char TT_STR = '\u0001';         // string literal
    public static final char TT_NUM = '\u0002';         // number
    public static final char TT_SYMBOL = '\u0003';      // variable / builtin
    public static final char TT_ARG = '$';              // argument
    public static final char TT_PLUS = '+';             // addition
    public static final char TT_MINUS = '-';            // subtraction
    public static final char TT_MULT = '*';             // multiplication
    public static final char TT_DIV = '/';              // division
    public static final char TT_MOD = '%';              // modulo
    public static final char TT_LT = '<';               // less than
    public static final char TT_GT = '>';               // greater than
    public static final char TT_EQUAL = '=';            // equal
    public static final char TT_NOT = '!';              // not
    public static final char TT_AND = '&';              // and
    public static final char TT_OR = '|';               // or
    public static final char TT_LPAREN = '(';           // left paren
    public static final char TT_RPAREN = ')';           // right paren
    public static final char TT_LBRACE = '{';           // left brace
    public static final char TT_RBRACE = '}';           // right brace
    public static final char TT_COMMA = ',';            // comma
    public static final char TT_EOS = ';';              // end of statement

    static class Token {
        int type;       // type of token
        String value;   // value of token

        private Token() {
            type = TT_UNDEF;
            value = "";
        }
    }

    public Lexer(String input) {
    }


    public Token gettok() {
        return new Token();
    }

    public char peek() {
        return TT_UNDEF;
    }

    public Token lookahead() {
        return new Token();
    }

}
