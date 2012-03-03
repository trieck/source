package org.pixielib.games.jumble;

import org.pixielib.util.Config;

import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.HashSet;

public class Concordance {

    private static Concordance theInstance;
    private HashSet<String> table;
    private Config config;

    private Concordance() throws IOException {
        config = Config.getInstance();
        table = new HashSet<String>();
        load();
    }

    public static synchronized Concordance getInstance() throws IOException {
        if (theInstance == null) {
            theInstance = new Concordance();
        }

        return theInstance;
    }
    
    public boolean lookup(String word) {
        return table.contains(word.toLowerCase());
    }

    private void load() throws IOException {
        String filename = config.getProperty("concordance-file");
        if (filename.length() == 0)
            throw new IOException(String.format("concordance-file not set."));

        File file = new File(filename).getCanonicalFile();
        if (!file.canRead()) {
            throw new IOException(String.format("Unable to read \"%s\".", file.getCanonicalPath()));
        }

        ConcordanceReader reader = new ConcordanceReader(new FileReader(file));

        String word;
        while ((word = reader.getWord()).length() > 0) {
            table.add(word);
        }
    }
}
