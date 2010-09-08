package org.tomrieck.content;

import java.io.IOException;
import java.io.InputStream;
import java.io.RandomAccessFile;
import java.nio.channels.Channels;

public class Search {

    public Search() {
    }

    public void search(String index_file, String phrase) throws IOException {

        Query query = new Query(index_file);

        DocList doclist = query.query(phrase);

        query.close();

        System.out.printf("    %d hits.\n", doclist.size());        
    }

    public static void main(String[] args) {
        if (args.length < 2) {
            System.err.println("usage: Search index-file \"phrase\"");
            System.exit(1);
        }

        Search search = new Search();

        try {
            search.search(args[0], args[1]);

        } catch (IOException e) {
            System.err.println(e);
            System.exit(1);
        }
    }
}
