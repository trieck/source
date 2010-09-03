package org.tomrieck.apps.ecalc;

public class Compiler {

    Machine machine; // Machine instance
    Symbols symbols; // Symbol table
    Lexer lexer; // Lexical analyzer
    Program program; // Generated program
    Lexer.Token tok; // The current token
    boolean indef; // Are we in a function definition?

    public Compiler() {
        machine = Machine.getInstance();
        symbols = Symbols.getInstance();
    }

    /**
     * Compile a string into a program for a runtime machine
     *
     * @param str the input
     * @return the program
     */
    public Program compile(String str) throws CompilerException {
        lexer = new Lexer(str);
        program = new Program();
        expr(true);
        return program;
    }

    /**
     * Get the next expression
     *
     * @param get whether to get next token
     */
    private void expr(boolean get) throws CompilerException {
        compexpr(get);

        for (; ;) {
            switch (tok.type) {
                case Lexer.TT_AND:
                    if (lexer.peek() == Lexer.TT_AND) {
                        logand();
                    } else {
                        bitand();
                    }
                    break;
                case Lexer.TT_OR:
                    if (lexer.peek() == Lexer.TT_OR) {
                        logor();
                    } else {
                        bitor();
                    }
                    break;
                default:
                    return;
            }
        }
    }

    /**
     * Comparison expression
     *
     * @param get whether to get next token
     */
    private void compexpr(boolean get) throws CompilerException {
        shiftexpr(get);

        for (; ;) {
            switch (tok.type) {
                case Lexer.TT_EQUAL: // ==
                    if (lexer.peek() == Lexer.TT_EQUAL) {
                        tok = lexer.gettok();
                        equal();
                    } else {
                        prim(true);
                    }
                    break;
                case Lexer.TT_NOT: // !=
                    if (lexer.peek() == Lexer.TT_EQUAL) {
                        tok = lexer.gettok();
                        notequal();
                    } else {
                        prim(true);
                    }
                    break;
                case Lexer.TT_LT:
                    if (lexer.peek() == Lexer.TT_EQUAL) {
                        tok = lexer.gettok();
                        lessequal();
                    } else {
                        lessthan();
                    }
                    break;
                case Lexer.TT_GT:
                    if (lexer.peek() == Lexer.TT_EQUAL) {
                        tok = lexer.gettok();
                        greatequal();
                    } else {
                        greatthan();
                    }
                    break;
                default:
                    return;
            }
        }
    }

    /**
     * Shift expression
     *
     * @param get whether to get next token
     */
    private void shiftexpr(boolean get) throws CompilerException {
        addexpr(get);

        for (; ;) {
            switch (tok.type) {
                case Lexer.TT_LT:
                    if (lexer.peek() == Lexer.TT_LT) {
                        tok = lexer.gettok();
                        shiftleft();
                    } else {
                        return;
                    }
                    break;
                case Lexer.TT_GT:
                    if (lexer.peek() == Lexer.TT_GT) {
                        shiftright();
                    } else {
                        return;
                    }
                    break;
                default:
                    return;
            }
        }

    }

    /**
     * Additive expression
     *
     * @param get whether to get next token
     */
    private void addexpr(boolean get) throws CompilerException {
        multexpr(get);

        for (; ;) {
            switch (tok.type) {
                case Lexer.TT_PLUS:
                    plus();
                    break;
                case Lexer.TT_MINUS:
                    minus();
                    break;
                default:
                    return;
            }
        }
    }

    /**
     * Multiplicative expression
     *
     * @param get whether to get next token
     */
    private void multexpr(boolean get) throws CompilerException {
        prim(get);

        for (; ;) {
            switch (tok.type) {
                case Lexer.TT_MULT:
                    mult();
                    break;
                case Lexer.TT_DIV:
                    divide();
                    break;
                case Lexer.TT_MOD:
                    mod();
                    break;
                default:
                    return;
            }
        }
    }

    /**
     * Handle primary
     *
     * @param get whether to get next token
     */
    private void prim(boolean get) throws CompilerException {
        if (get) {
            tok = lexer.gettok();
        }

        switch (tok.type) {
            case Lexer.TT_SYMBOL:
                symbol();
                break;
            case Lexer.TT_NUM:
                constant();
                tok = lexer.gettok();
                break;
            case Lexer.TT_LPAREN:
                arglist();
                tok = lexer.gettok(); // eat ')'
                break;
            case Lexer.TT_LBRACE:
                // compstmt();
                tok = lexer.gettok(); // eat '}'
                break;
            case Lexer.TT_MINUS:
                // unaryminus();
                break;
            case Lexer.TT_NOT:
                // not();
                break;
            case Lexer.TT_STR:
                // string();
                tok = lexer.gettok();
                break;
            case Lexer.TT_ARG:
                arg();
                break;
            default:
                break;
        }
    }

    /**
     * Handle symbol
     */
    private void symbol() throws CompilerException {
        final Symbol symbol = Symbols.lookup(tok.value);
        if (symbol != null && symbol.getType() == Symbol.ST_BUILTIN) {
            builtin(symbol);
        } else if (symbol != null && symbol.getType() == Symbol.ST_KEYWD) {
            keyword(symbol);
        } else if (symbol != null && symbol.getType() == Symbol.ST_FUNC
                || symbol.getType() == Symbol.ST_PROC) {
            call(symbol);
        } else {
            var(symbol);
        }
    }

    /**
     * Handle constant
     */
    private void constant() throws CompilerException {
        if (tok.type != Lexer.TT_NUM) {
            throw new CompilerException(CompilerException.CE_NAN);
        }

        try {
        } catch (final NumberFormatException e) {
            throw new CompilerException(CompilerException.CE_NAN);
        }

        program.code(null /* machine.constpush */);
        program.code(null /* symbol */);
    }

    /**
     * Handle builtin
     *
     * @param symbol the symbol
     */
    private void builtin(Symbol symbol) throws CompilerException {
        prim(true);
        program.code(symbol.getInstr());
    }

    /**
     * Handle keyword
     *
     * @param symbol the keyword
     */
    private void keyword(Symbol symbol) throws CompilerException {
        switch (symbol.getKeyword()) {
            case Symbol.KW_FUNC:
                funcdef();
                break;
            case Symbol.KW_PROC:
                procdef();
                break;
            case Symbol.KW_RETURN:
                ret();
                break;
            case Symbol.KW_WHILE:
                whilecode();
                break;
            case Symbol.KW_IF:
                // ifcode();
                break;
            case Symbol.KW_ELSE:
                expr(true);
                break;
            case Symbol.KW_PRINTF:
                // printf();
                break;
            default:
                break;
        }
    }

    /**
     * Call a function / procedure
     *
     * @param symbol the function
     */
    private void call(Symbol symbol) throws CompilerException {

        tok = lexer.gettok(); // '('
        tok = lexer.gettok(); // ')'
        program.code(null /* machine.call */);
        program.code(null /* symbol */);
        program.code(null /* nargs */);
    }

    /**
     * Handle a variable
     *
     * @param symbol the variable
     */
    private void var(Symbol symbol) throws CompilerException {

        if (symbol == null) {
            symbol = Symbols.install(tok.value, Symbol.ST_UNDEF, 0.0);
        }

        program.code(null /* machine.varpush */);
        program.code(null /* symbol */);

        tok = lexer.gettok();
        if (tok.type == Lexer.TT_EQUAL && lexer.peek() != Lexer.TT_EQUAL) {
            assign(); // assign
        } else {
            program.code(null /* machine.eval */);
        }
    }

    /**
     * Variable assignment
     */
    private void assign() throws CompilerException {
        expr(true);
        program.code(machine.assign);
        program.code(machine.pop);
    }

    /**
     * Define a function
     */
    private void funcdef() throws CompilerException {
        indef = true;
        tok = lexer.gettok(); // function name
        final String name = tok.value;

        // Insert the function into the symbol table
        // This is needed to make recursion work properly
        Symbols.install(name, Symbol.ST_FUNC, null);

        tok = lexer.gettok(); // '('
        tok = lexer.gettok(); // ')'
        expr(true); // function body

        program.code(null /* machine.procret */);
        program.define(name, Symbol.ST_FUNC);
        indef = false;
    }

    /**
     * Define a procedure
     */
    private void procdef() throws CompilerException {
        indef = true;
        tok = lexer.gettok(); // procedure name
        final String name = tok.value;

        // Insert the procdure into the symbol table
        // This is needed to make recursion work properly
        Symbols.install(name, Symbol.ST_PROC, null);

        tok = lexer.gettok(); // '('
        tok = lexer.gettok(); // ')'
        expr(true); // procedure body

        program.code(null /* machine.procret */);
        program.define(name, Symbol.ST_PROC);
        indef = false;
    }

    /**
     * Handle return statement
     */
    private void ret() throws CompilerException {
        if (lexer.lookahead().type != Lexer.TT_EOS) {
            expr(true);
            program.code(null /* machine.funcret */);
        } else {
            program.code(null /* machine.procret */);
        }
    }

    /**
     * Handle while statement
     */
    private void whilecode() {
        program.code(null /* machine.whilecode */);

        // Reserve spots for pointers to loop body and next statement

    }

    /**
     * Handle argument
     */
    private void arg() throws CompilerException {

        int arg;

        try {
            arg = Integer.parseInt(tok.value);
        } catch (final NumberFormatException e) {
            throw new CompilerException(CompilerException.CE_NAN);
        }

        tok = lexer.gettok();
        if (tok.type == Lexer.TT_EQUAL && lexer.peek() != Lexer.TT_EQUAL) {
            argassign(arg);
        } else {
            program.code(null /* machine.arg */);
            program.code(null /* arg */);
        }
    }

    /**
     * Handle argument assignment
     *
     * @param narg the argument
     */
    private void argassign(int narg) throws CompilerException {
        expr(true);
        program.code(null /* machine.argassign */);
        program.code(null /* narg */);
        program.code(machine.pop);
    }

    /**
     * Handle argument list to function / proc
     *
     * @return the number of arguments processed
     */
    private int arglist() throws CompilerException {
        int nargs = 0;

        while (tok.type != Lexer.TT_EOS) {
            expr(true);
            if (tok.type == Lexer.TT_RPAREN) {
                break;
            }
            nargs++;
        }

        return nargs;
    }

    /**
     * Bitwise AND operation
     */
    private void bitand() throws CompilerException {

        compexpr(true);
        program.code(null /* machine.bitand */);

    }

    /**
     * Logical AND operation
     */
    private void logand() throws CompilerException {
        compexpr(true);
        program.code(null /* machine.logand */);
    }

    /**
     * Bitwise OR operation
     */
    private void bitor() throws CompilerException {
        compexpr(true);
        program.code(null /* machine.bitor */);
    }

    /**
     * Logical OR operation
     */
    private void logor() throws CompilerException {
        compexpr(true);
        program.code(null /* machine.logor */);
    }

    /**
     * Less than
     */
    private void lessthan() throws CompilerException {
        shiftexpr(true);
        program.code(null /* machine.lessthan */);
    }

    /**
     * Greater than
     */
    private void greatthan() throws CompilerException {
        shiftexpr(true);
        program.code(null /* machine.greatthan */);
    }

    /**
     * Less than or equal
     */
    private void lessequal() throws CompilerException {
        shiftexpr(true);
        program.code(null /* machine.lessequal */);
    }

    /**
     * Greater than or equal
     */
    private void greatequal() throws CompilerException {
        shiftexpr(true);
        program.code(null /* machine.greatequal */);
    }

    /**
     * Equal
     */
    private void equal() throws CompilerException {
        shiftexpr(true);
        program.code(null /* machine.equal */);
    }

    /**
     * Not equal
     */
    private void notequal() throws CompilerException {
        shiftexpr(true);
        program.code(null /* machine.notequal */);
    }

    /**
     * Shift left
     */
    private void shiftleft() throws CompilerException {
        addexpr(true);
        program.code(null /* machine.shiftleft */);
    }

    /**
     * Shift right
     */
    private void shiftright() throws CompilerException {
        addexpr(true);
        program.code(null /* machine.shiftright */);
    }

    /**
     * Plus
     */
    private void plus() throws CompilerException {
        multexpr(true);
        program.code(machine.plus);
    }

    /**
     * Minus
     */
    private void minus() throws CompilerException {
        multexpr(true);
        program.code(machine.minus);
    }

    /**
     * Multiply
     */
    private void mult() throws CompilerException {
        prim(true);
        program.code(machine.mult);
    }

    /**
     * Divide
     */
    private void divide() throws CompilerException {
        prim(true);
		program.code(machine.divide);
	}

	/**
	 * Modulo
	 */
	private void mod() throws CompilerException {
		prim(true);
		program.code(machine.mod);
	}
}
