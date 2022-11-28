package org.pixielib.webapps.jumble;

import java.io.IOException;
import java.io.InputStreamReader;
import java.util.*;

public class Concordance {

    private static Concordance theInstance;
    private final HashMap<String, List<String>> table;

    private Concordance() throws IOException {
        table = new HashMap<>();
        load();
    }

    public static synchronized Concordance getInstance() throws IOException {
        if (theInstance == null) {
            theInstance = new Concordance();
        }

        return theInstance;
    }

    public List<String> lookup(String word) {

        word = sortWord(word);

        return table.get(word);
    }

    private String sortWord(String word)
    {
        var chars = word.toCharArray();

        Arrays.sort(chars);

        return Arrays.toString(chars);
    }

    private void load() throws IOException {

        try (var stream = getClass().getResourceAsStream("/jumble.concordance")) {
            if (stream == null) {
                throw new IOException("Cannot find \"jumble.concordance\".");
            }

            var reader = new ConcordanceReader(new InputStreamReader(stream));

            String word;
            while ((word = reader.getWord()).length() > 0) {
                var key = sortWord(word);

                var words = table.get(key);
                if (words == null) {
                    words = new ArrayList<>();
                    words.add(word);
                    table.put(key, words);
                } else {
                    words.add(word);
                }
            }
        }
    }
}
