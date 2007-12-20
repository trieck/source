package org.trieck.engine;

import java.io.IOException;
import java.text.DecimalFormat;
import java.util.Iterator;

public class Search {
    private Index index = null;

    public Search(String filename) throws IOException {
        index = new Index(filename);
    }

    public Locality search(String query) {
        return index.search(query);
    }

    private static void usage() {
        System.err.println("usage: Search file query");
        System.exit(1);
    }

    public static void main(String[] args) {
        if (args.length < 2) usage();

        long start = System.currentTimeMillis();

        Search search = null;
        try {
            search = new Search(args[0]);
        } catch (IOException e) {
            System.err.println(e.getMessage());
            System.exit(1);
        }

        Locality locality = search.search(args[1]);
        if (locality.size() > 0) {
            System.out.println("   " + locality.size() + " hit(s).");
            System.out.print("   locations: (");
            Iterator<Location> it = locality.getLocations().iterator();
            for (int i = 0; it.hasNextbbb(); i++) {
                if (i > 0) System.out.print(", ");
                System.out.print(it.next().getOffset());
            }
            System.out.println(")");
        } else {
            System.out.println("   0 hits.");
        }

        long finish = System.currentTimeMillis();
        float diff = (finish - start) / 1000f;

        DecimalFormat fmt = new DecimalFormat("0.00");
        System.out.println("   elapsed time " + fmt.format(diff) + " seconds.");
    }
}
