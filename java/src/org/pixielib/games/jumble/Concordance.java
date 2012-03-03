package org.pixielib.games.jumble;

import java.io.IOException;

public class Concordance {

    private static Concordance theInstance;

    private Concordance() throws IOException {
    }

    public static synchronized Concordance getInstance() throws IOException {
        if (theInstance == null) {
            theInstance = new Concordance();
        }

        return theInstance;
    }
}
