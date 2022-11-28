package org.pixielib.webapps.jumble;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

public class Jumble {

    private final Concordance concordance;

    public Jumble() throws IOException {
        concordance = Concordance.getInstance();
    }

    public static void main(String[] args) {
        if (args.length == 0) {
            System.err.println("usage: Jumble word");
            System.exit(1);
        }

        Iterator<String> it;

        try {
            Jumble jumble = new Jumble();
            it = jumble.solve(args[0]).iterator();
            while (it.hasNext()) {
                System.out.println(it.next());
            }
        } catch (IOException e) {
            System.err.println(e.toString());
            System.exit(1);
        }
    }

    public List<String> solve(String word) {

        List<String> solutions = new ArrayList<String>();

        var values = concordance.lookup(word);
        if (values != null) {
            solutions.addAll(values);
        }

        return solutions;
    }
}
