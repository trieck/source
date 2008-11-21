package org.trieck.apps;


public class Binomial {
    
    private int N;	/** degree of binomial */
    
    /** 
     * private ctor
     * @param n degree of binomial
     */
    private Binomial(int n) {
        N = n;
    }
    
    /**
     * # of combinations of n, k at a time without regard to order
     * @param n # of things
     * @param k # at a time
     * @return # of combinations of n choose k
     */
    private static int choose(int n, int k) {
        return factorial(n) / (factorial(k) * factorial(n - k));
    }
    
    /**
     * # of permutations of n things
     * @param n # of things
     * @return n!
     */
    private static int factorial (int n) {
        if (n <= 0)
            return 1;
        
        return n * factorial(n - 1);
    }
    
    /**
     * String representation
     */
    public String toString() {
        StringBuffer output = new StringBuffer();
        output.append("(x + a)^" + N + " = ");
        for (int k = 0; k <= N; k++) {
            if (k > 0) output.append(" + ");
            int c = choose(N, k);
            if (c > 1)
                output.append(c);
            if (k > 0) {
                output.append("x");
                if (k > 1)
                    output.append("^" + k);
            }
            if (N - k > 0) {
                output.append("a");
                if (N - k > 1)
                    output.append("^" + (N - k));
            }
        }
        return output.toString();
    }
    
    /** print usage and quit */
    private static void usage() {
        System.err.println("usage: Binomial degree(1..10)");
        System.exit(-1);
    }

    /** 
     * Application main entry point
     * @param args application arguments
     */
    public static void main(String[] args) {
        if (args.length == 0) {
            usage();
        }
        
        int n = 0;
        try { 
            n = Integer.parseInt(args[0]);
            if (n < 1 || n > 10)
                throw new NumberFormatException();
        } catch (NumberFormatException e) {
            usage();
        }
        
        Binomial b = new Binomial(n);
        System.out.println(b);
    }
}
