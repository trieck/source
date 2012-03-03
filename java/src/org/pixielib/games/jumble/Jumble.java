package org.pixielib.games.jumble;

import java.io.IOException;
import java.io.PrintStream;

public class Jumble {

    private Concordance concordance;

    public Jumble() throws IOException {
        concordance = Concordance.getInstance();
    }

    public void solve(String word, PrintStream ps) throws IOException {
                
        WordPerms wp = new WordPerms(word);
        
        ps.println(String.format("%d possible arrangements.", wp.getSize()));

        String perm = wp.getFirstPerm();

        int n = 1;

        do {
            ps.println(String.format("%d\t%s", n++, perm));
            
        } while ((perm = wp.getNextPerm(perm)) != null);
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
            System.exit(1);
        }
    }
}
