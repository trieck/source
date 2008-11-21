package org.trieck.apps;

import java.io.IOException;
import java.io.PrintWriter;
import java.io.PushbackReader;
import java.io.StringReader;
import java.util.Iterator;
import java.util.Set;
import java.util.Stack;
import java.util.TreeSet;

/**
 * An example engine implementing Thompson's construction
 * of an NFA from a regular expression as well as the subset
 * construction of a DFA from an NFA.
 * <p/>
 * The grammar for the language is:
 * <p/>
 * expression  :=	conjunction '|' expression
 * | 	conjunction
 * <p/>
 * conjunction := 	closure conjunction
 * | 	closure
 * <p/>
 * closure		:=	primary '*'
 * |	primary
 * <p/>
 * primary     := 	'(' expression ')'
 * |	characters
 * <p/>
 * characters	:=	'A-Za-z'
 */
public class Parser {

    /**
     * end of string indicator
     */
    private static final int EOF = -1;        /* end of file indicator */
    private static final char EOS = 0;      /* end of string indicator */
    private static final int MAXV = 250;    /* maximum # of states */
    private static final int EPSILON = -1;    /* epsilon transition edge */

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

        Parser parser = new Parser();
        Machine m = parser.parse(args[0]);
        m.dump(new PrintWriter(System.out));
    }

    /**
     * parse the input string returning a machine representation
     */
    public Machine parse(String input) {
        in = new PushbackReader(new StringReader(input));
        Machine m = expression();
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
            if (curr != ')') error();
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
        char save = curr;
        gettok();
        char peek = curr;
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
        } catch (IOException ioe) {
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
        } catch (IOException ioe) {
            ;
        }

        return c == EOF ? EOS : (char) c;
    }

    /* get the next input token */
    private void gettok() {

        char c = next();

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
        private static final Set SIGMA;

        static {
            final char[] A = {'a', 'b'};
            SIGMA = new TreeSet();
            for (int i = 0; i < A.length; i++)
                SIGMA.add(new Character(A[i]));
        }

        protected int a[][];        /* adjacency matrix */
        private TreeSet accept;        /* set of accepting states */
        protected int state;        /* current state during construction */

        public static Iterator getAlphabet() {
            return SIGMA.iterator();
        }

        /**
         * Determine if character is in the input symbol alphabet
         *
         * @param c the input character
         * @return true if character is in alphabet otherwise false
         */
        private static boolean isInputSymbol(char c) {
            Iterator it = getAlphabet();
            while (it.hasNext()) {
                Character C = (Character) it.next();
                if (C.charValue() == c)
                    return true;
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
            accept = new TreeSet();
            initmatrix();
        }

        /**
         * initialize the matrix
         * A path can have no edges
         */
        private void initmatrix() {
            for (int i = 0, j = 0; i < MAXV; i++, j++) {
                a[i][j] = EPSILON;    /* a path can have no edges */
            }
        }

        /**
         * append an NFA
         */
        protected void append(NFA rhs) {
            if (accept.size() > 0) {
                int N, Q, R;
                TreeSet tmp = (TreeSet) accept.clone();
                accept.clear();

                Iterator it = tmp.iterator();
                while (it.hasNext()) {
                    Q = ((Integer) it.next()).intValue();
                    for (R = 0; R <= rhs.state; R++) {
                        if (R > 0 && Q == ((Integer) tmp.first()).intValue()) {
                            N = ++state;
                        } else N = Q;

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

            } else {    /* no accepting states is an empty NFA */
                System.arraycopy(rhs.a, 0, a, 0, rhs.a.length);
                accept = (TreeSet) rhs.accept.clone();
                state = rhs.state;
            }
        }

        /**
         * print a human readable rep of the machine
         */
        public void dump(PrintWriter writer) {
            int i, j;
            for (i = 0; i <= this.state; i++) {
                writer.print("\t\t");
                writer.print(i);
            }

            writer.println();

            for (i = 0; i <= this.state; i++) {
                writer.print(i);
                for (j = 0; j <= this.state; j++) {
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
            TreeSet A = new TreeSet();

            a[0][++state] = EPSILON;

            for (i = 0; i <= left.state; i++) {
                if (i > 0) state++;

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

            Iterator it = A.iterator();
            while (it.hasNext()) {
                int astate = ((Integer) it.next()).intValue();
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
            TreeSet A = new TreeSet();

            a[0][++state] = EPSILON;

            for (i = 0; i <= left.state; i++) {
                if (i > 0) state++;

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
                if (i > 0) state++;

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

            Iterator it = A.iterator();
            while (it.hasNext()) {
                int astate = ((Integer) it.next()).intValue();
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
    private class DFA implements Machine {

        private NFA nfa;

        private class DFAState {
            private boolean marked;
            private Set states; /* subset of NFA states */

            private DFAState() {
                marked = false;
                states = new TreeSet();
            }

            public int hashCode() {
                return 17 * (states.hashCode() + (marked ? 1 : 0));
            }

            public boolean equals(Object o) {
                if (this == o)
                    return true;

                DFAState rhs = (DFAState) o;

                return (this.marked == rhs.marked &&
                        this.states.equals(rhs.states));
            }
        }

        private Set Dstates;

        public DFA(NFA nfa) {    /* subset construction */
            this.nfa = nfa;
            Dstates = new TreeSet();
            construct();
        }

        /**
         * Subset construction of a DFA from an NFA
         */
        private void construct() {
            /*
                * Initially, closure(s0) is the only state in Dstates
                * and it is unmarked
                */
            DFAState T = closure(0);
            Dstates.add(T);

            for (; T != null; T = getUnmarkedState()) {
                T.marked = true;    /* mark the state */
                Iterator it = NFA.getAlphabet();
                while (it.hasNext()) {
                    char a = ((Character) it.next()).charValue();
                    DFAState U = closure(move(T, a));
                    if (!Dstates.contains(U))
                        Dstates.add(U);

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
            Iterator it = Dstates.iterator();
            while (it.hasNext()) {
                DFAState T = (DFAState) it.next();
                if (!T.marked)
                    return T;
            }

            return null;
        }

        /**
         * Set of NFA states reachable from NFA state s on epsilon
         * transitions alone
         */
        private DFAState closure(int s) {
            DFAState input = new DFAState();
            input.states.add(new Integer(s));
            return closure(input);
        }

        /**
         * Set of NFA states reachable from some NFA states s in T
         * on epsilon transitions alone
         */
        private DFAState closure(DFAState T) {
            DFAState ds = new DFAState();
            Stack st = new Stack();

            st.addAll(T.states);

            while (!st.isEmpty()) {
                int t = ((Integer) st.pop()).intValue();
                for (int u = 0; u < nfa.states(); u++) {
                    if (nfa.isEdge(t, u, EPSILON)) {
                        Integer U = new Integer(u);
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
         * Set of NFA states to which there is a transition
         * on input symbol a from some NFA state s in T
         */
        private DFAState move(DFAState T, char a) {
            DFAState ds = new DFAState();

            Iterator it = T.states.iterator();
            while (it.hasNext()) {
                int s = ((Integer) it.next()).intValue();
                for (int i = 0; i < nfa.states(); i++) {
                    if (nfa.isEdge(s, i, a)) {
                        Integer t = new Integer(i);
                        if (!ds.states.contains(t))
                            ds.states.add(t);
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
