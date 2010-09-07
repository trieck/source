package org.tomrieck.pixievm.assembler;

import java.io.IOException;
import java.text.MessageFormat;

public class Parser {

    private final Lexer lexer;
    private final SymbolTable table = new SymbolTable();

    public Parser(String filename) throws IOException {
        lexer = new Lexer(filename);
    }

    /**
     * Parse input
     *
     * @throws ParserException
     * @throws IOException
     */
    public void parse() throws ParserException, IOException {
        Lexer.Token tok;
        Symbol sym;

        while ((tok = lexer.getToken()).getType() != Lexer.TT_EMPTY) {
            switch (tok.getType()) {
                case Lexer.TT_UNDEF:
                    error("undefined token \"{0}\"", tok.getValue());
                case Lexer.TT_NUM:
                case Lexer.TT_STR:
                    sym = table.get(tok.getValue());
                    if (sym != null && sym.getType() == Symbol.ST_OPCODE) {
                        opcode(sym);
                    } else {
                        error("unexpected token \"{0}\"", tok.getValue());
                    }
                    break;
                case Lexer.TT_PERIOD:
                    pseudo();
                    break;
                case Lexer.TT_SEMI: /* comment */
                    break;
                default:
                    break;
            }
        }
    }

    /**
     * Pseudo op
     */
    private void pseudo() {
    }

    /**
     * Opcode code generation
     *
     * @param sym
     */
    private void opcode(Symbol sym) {
    }

    /**
     * Parser error
     *
     * @param pattern
     * @param arguments
     * @throws ParserException
     */
    public void error(String pattern, Object... arguments)
            throws ParserException {
        String message = MessageFormat.format(pattern, arguments);
        message = message + " @ line #" + lexer.getLineno() + ".";
        throw new ParserException(message);
    }
}
