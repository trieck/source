package org.pixielib.apps;

import java.io.IOException;
import java.io.PrintWriter;
import java.io.PushbackReader;
import java.io.StringReader;
import java.util.Iterator;
import java.util.Set;
import java.util.Stack;
import java.util.TreeSet;

/**
 * An example engine implementing Thompson's construction of an NFA from a
 * regular expression as well as the subset construction of a DFA from an NFA.
 * <p/> The grammar for the language is: <p/> expression := conjunction '|'
 * expression | conjunction <p/> conjunction := closure conjunction | closure
 * <p/> closure := primary '*' | primary <p/> primary := '(' expression ')' |
 * characters <p/> characters := 'A-Za-z'
 */
public class Parser {

    /**
     * end of string indicator
     */
    private static final int EOF = -1; /* end of file indicator */
    private static final char EOS = 0; /* end of string indicator */
    private static final int MAXV = 250; /* maximum # of states */
    private static final int EPSILON = -1; /* epsilon transition edge */

    /**
     * input stream
     */
    private PushbackReader in;

    /**
     * current input token
     */
    private char curr;

    public static void main(String[] args) {
        if (args.length < 1) {
            System.err.println("usage: Parser input");
            System.exit(1);
        }

        final Parser parser = new Parser();
        final Machine m = parser.parse(args[0]);
        m.dump(new PrintWriter(System.out));
    }

    /**
     * parse the input string returning a machine representation
     */
    public Machine parse(String input) {
        in = new PushbackReader(new StringReader(input));
        final Machine m = expression();
        match(EOS);
        return m;
    }

    private NFA expression() {
        NFA left = conjunction();
        for (; ;) {
            if (lookahead() == '|') {
                gettok();
                left = new UnionNFA(left, conjunction());
            } else {
                return left;
            }
        }
    }

    private NFA conjunction() {
        NFA left = closure();

        for (; ;) {
            if (Character.isLetter(lookahead())) {
                left = new ConcatNFA(left, closure());
            } else {
                return left;
            }
        }
    }

    private NFA closure() {
        NFA left = primary();

        for (; ;) {
            if (lookahead() == '*') {
                gettok();
                left = new ClosureNFA(left);
            } else {
                return left;
            }
        }
    }

    private NFA primary() {
        NFA nfa = null;

        gettok();
        if (curr == '(') {
            nfa = expression();
            gettok();
            if (curr != ')') {
                error();
            }
        } else if (Character.isLetter(curr)) {
            nfa = new SimpleNFA();
        } else {
            error();
        }

        return nfa;
    }

    /**
     * lookahead to the next input token
     */
    private char lookahead() {
        final char save = curr;
        gettok();
        final char peek = curr;
        pushback();
        curr = save;
        return peek;
    }

    /**
     * pushback current input token
     */
    private void pushback() {
        try {
            in.unread(curr);
        } catch (final IOException ioe) {
            ;
        }
    }

    /**
     * read next input character
     */
    private char next() {

        int c = EOF;
        try {
            c = in.read();
        } catch (final IOException ioe) {
            ;
        }

        return c == EOF ? EOS : (char) c;
    }

    /* get the next input token */

    private void gettok() {

        final char c = next();

        if (NFA.isInputSymbol(c)) {
            curr = c;
        } else {
            switch (c) {
                case '(':
                case ')':
                case '|':
                case '*':
                    curr = c;
                    break;
                case EOS:
                    curr = EOS;
                    break;
                default:
                    error();
            }
        }
    }

    private void match(char c) {
        if (lookahead() != c) {
            error();
        }
    }

    /**
     * syntax error
     */
    private void error() {
        System.err.println("syntax error.");
        System.exit(1);
    }

    private interface Machine {
        public void dump(PrintWriter writer);
    }

    /**
     * Non-deterministic Finite Automata
     */
    private static abstract class NFA implements Machine {

        /**
         * the input symbol alphabet
         */
        private static final Set<Character> SIGMA;

        static {
            final char[] A = {'a', 'b'};
            SIGMA = new TreeSet<Character>();
            for (final char element : A) {
                SIGMA.add(new Character(element));
            }
        }

        protected int a[][]; /* adjacency matrix */
        private TreeSet<Integer> accept; /* set of accepting states */
        protected int state; /* current state during construction */

        public static Iterator<Character> getAlphabet() {
            return SIGMA.iterator();
        }

        /**
         * Determine if character is in the input symbol alphabet
         *
         * @param c the input character
         * @return true if character is in alphabet otherwise false
         */
        private static boolean isInputSymbol(char c) {
            final Iterator<?> it = getAlphabet();
            while (it.hasNext()) {
                final Character C = (Character) it.next();
                if (C.charValue() == c) {
                    return true;
                }
            }

            return false;
        }

        public int states() {
            return state + 1;
        }

        protected void setEdge(int x, int y, int c) {
            a[x][y] = c;
        }

        protected boolean isEdge(int x, int y, int c) {
            return a[x][y] == c;
        }

        protected void addAcceptingState(int s) {
            accept.add(new Integer(s));
        }

        protected boolean isAcceptingState(int s) {
            return accept.contains(new Integer(s));
        }

        /**
         * public ctor
         */
        public NFA() {
            a = new int[MAXV][MAXV];
            accept = new TreeSet<Integer>();
            initmatrix();
        }

        /**
         * initialize the matrix A path can have no edges
         */
        private void initmatrix() {
            for (int i = 0, j = 0; i < MAXV; i++, j++) {
                a[i][j] = EPSILON; /* a path can have no edges */
            }
        }

        /**
         * append an NFA
         */
        @SuppressWarnings("unchecked")
        protected void append(NFA rhs) {
            if (accept.size() > 0) {
                int N, Q, R;
                final TreeSet<Integer> tmp = (TreeSet<Integer>) accept.clone();
                accept.clear();

                final Iterator<Integer> it = tmp.iterator();
                while (it.hasNext()) {
                    Q = (it.next()).intValue();
                    for (R = 0; R <= rhs.state; R++) {
                        if (R > 0 && Q == (tmp.first()).intValue()) {
                            N = ++state;
                        } else {
                            N = Q;
                        }

                        if (rhs.isAcceptingState(R)) {
                            addAcceptingState(N);
                        }

                        for (int i = 0; i <= rhs.state; i++) {
                            if (rhs.a[R][i] != 0) {
                                if (i == 0) {
                                    a[N][Q] = rhs.a[R][i];
                                } else if (N == Q) {
                                    a[N][state + i - R] = rhs.a[R][i];
                                } else {
                                    a[N][N + i - R] = rhs.a[R][i];
                                }
                            }
                        }
                    }
                }

            } else { /* no accepting states is an empty NFA */
                System.arraycopy(rhs.a, 0, a, 0, rhs.a.length);
                accept = (TreeSet<Integer>) rhs.accept.clone();
                state = rhs.state;
            }
        }

        /**
         * print a human readable rep of the machine
         */
        public void dump(PrintWriter writer) {
            int i, j;
            for (i = 0; i <= state; i++) {
                writer.print("\t\t");
                writer.print(i);
            }

            writer.println();

            for (i = 0; i <= state; i++) {
                writer.print(i);
                for (j = 0; j <= state; j++) {
                    writer.print("\t\t");
                    writer.print(a[i][j]);
                }
                writer.println();
            }
            writer.flush();
        }
    }

    /**
     * build a simple NFA from the current input token
     */
    private class SimpleNFA extends NFA {
        public SimpleNFA() {
            super();
            setEdge(state, state + 1, curr);
            addAcceptingState(state + 1);
            state++;
        }
    }

    /**
     * construct the closure NFA
     */
    private class ClosureNFA extends NFA {
        public ClosureNFA(NFA left) {
            super();
            int i, j;
            final TreeSet<Integer> A = new TreeSet<Integer>();

            a[0][++state] = EPSILON;

            for (i = 0; i <= left.state; i++) {
                if (i > 0) {
                    state++;
                }

                if (left.isAcceptingState(i)) {
                    A.add(new Integer(state));
                    a[state][1] = EPSILON;
                }

                for (j = 0; j <= left.state; j++) {
                    if (left.a[i][j] != 0) {
                        a[state][state + j - i] = left.a[i][j];
                    }
                }
            }

            addAcceptingState(++state);

            final Iterator<Integer> it = A.iterator();
            while (it.hasNext()) {
                final int astate = (it.next()).intValue();
                a[astate][state] = EPSILON;
            }

            a[0][state] = EPSILON;
        }
    }

    /**
     * construct the union of two NFAs
     */
    private class UnionNFA extends NFA {
        public UnionNFA(NFA left, NFA right) {
            super();
            int i, j;
            final TreeSet<Integer> A = new TreeSet<Integer>();

            a[0][++state] = EPSILON;

            for (i = 0; i <= left.state; i++) {
                if (i > 0) {
                    state++;
                }

                if (left.isAcceptingState(i)) {
                    A.add(new Integer(state));
                }

                for (j = 0; j <= left.state; j++) {
                    if (left.a[i][j] != 0) {
                        a[state][state + j - i] = left.a[i][j];
                    }
                }
            }

            a[0][++state] = EPSILON;

            for (i = 0; i <= right.state; i++) {
                if (i > 0) {
                    state++;
                }

                if (right.isAcceptingState(i)) {
                    A.add(new Integer(state));
                }

                for (j = 0; j <= right.state; j++) {
                    if (right.a[i][j] != 0) {
                        a[state][state + j - i] = right.a[i][j];
                    }
                }
            }

            addAcceptingState(++state);

            final Iterator<Integer> it = A.iterator();
            while (it.hasNext()) {
                final int astate = (it.next()).intValue();
                a[astate][state] = EPSILON;
            }
        }
    }

    /**
     * construct the concatenation of two NFAs
     */
    private class ConcatNFA extends NFA {
        public ConcatNFA(NFA left, NFA right) {
            super();
            append(left);
            append(right);
        }
    }

    /**
     * Deterministic Finite Automata
     */
    public class DFA implements Machine {

        private final NFA nfa;

        public class DFAState {
            private boolean marked;
            private final Set<Integer> states; /* subset of NFA states */

            private DFAState() {
                marked = false;
                states = new TreeSet<Integer>();
            }

            @Override
            public int hashCode() {
                return 17 * (states.hashCode() + (marked ? 1 : 0));
            }

            @Override
            public boolean equals(Object o) {
                if (this == o) {
                    return true;
                }

                final DFAState rhs = (DFAState) o;

                return (marked == rhs.marked && states.equals(rhs.states));
            }
        }

        private final Set<DFAState> Dstates;

        public DFA(NFA nfa) { /* subset construction */
            this.nfa = nfa;
            Dstates = new TreeSet<DFAState>();
            construct();
        }

        /**
         * Subset construction of a DFA from an NFA
         */
        private void construct() {
            /*
                * Initially, closure(s0) is the only state in Dstates and it is
                * unmarked
                */
            DFAState T = closure(0);
            Dstates.add(T);

            for (; T != null; T = getUnmarkedState()) {
                T.marked = true; /* mark the state */
                final Iterator<?> it = NFA.getAlphabet();
                while (it.hasNext()) {
                    final char a = ((Character) it.next()).charValue();
                    final DFAState U = closure(move(T, a));
                    if (!Dstates.contains(U)) {
                        Dstates.add(U);
                    }

                    // DTran[T, a] := U
                }
            }
        }

        /**
         * Return the first unmarked DFA state
         *
         * @return unmarked state or null if none
         */
        private DFAState getUnmarkedState() {
            final Iterator<DFAState> it = Dstates.iterator();
            while (it.hasNext()) {
                final DFAState T = it.next();
                if (!T.marked) {
                    return T;
                }
            }

            return null;
        }

        /**
         * Set of NFA states reachable from NFA state s on epsilon transitions
         * alone
         */
        private DFAState closure(int s) {
            final DFAState input = new DFAState();
            input.states.add(new Integer(s));
            return closure(input);
        }

        /**
         * Set of NFA states reachable from some NFA states s in T on epsilon
         * transitions alone
         */
        private DFAState closure(DFAState T) {
            final DFAState ds = new DFAState();
            final Stack<Integer> st = new Stack<Integer>();

            st.addAll(T.states);

            while (!st.isEmpty()) {
                final int t = (st.pop()).intValue();
                for (int u = 0; u < nfa.states(); u++) {
                    if (nfa.isEdge(t, u, EPSILON)) {
                        final Integer U = new Integer(u);
                        if (!ds.states.contains(U)) {
                            ds.states.add(U);
                            st.push(U);
                        }
                    }
                }
            }

            return ds;
        }

        /**
         * Set of NFA states to which there is a transition on input symbol a
         * from some NFA state s in T
         */
        private DFAState move(DFAState T, char a) {
            final DFAState ds = new DFAState();

            final Iterator<?> it = T.states.iterator();
            while (it.hasNext()) {
                final int s = ((Integer) it.next()).intValue();
                for (int i = 0; i < nfa.states(); i++) {
                    if (nfa.isEdge(s, i, a)) {
                        final Integer t = new Integer(i);
                        if (!ds.states.contains(t)) {
                            ds.states.add(t);
                        }
                    }
                }
            }

            return ds;
        }

        /**
         * print a human readable rep of the machine
         */
        public void dump(PrintWriter writer) {
        }
    }
}
