package org.pixielib.apps.jumble;

import java.io.IOException;
import java.io.PrintStream;

public class Jumble {

    private Concordance concordance;

    public Jumble() throws IOException {
        concordance = Concordance.getInstance();
    }
    
    public void solve(String word, PrintStream ps) throws IOException {
        int N = Arrangements.arrangements(word);
        ps.println(String.format("%d arrangements possible.", N));
    }
    
    public static void main(String[] args) {
        if (args.length == 0) {
            System.err.println("usage: Jumble word");
            System.exit(1);
        }
        
        try {
            Jumble jumble = new Jumble();
            jumble.solve(args[0], System.out);
        } catch (IOException e) {
            System.err.println(e);
            System.exit(2);
        }
    }
}
