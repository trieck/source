package org.tomrieck.content;

import org.tomrieck.util.Timer;

import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.Arrays;

public class Indexer {

    private String[] infiles;
    private String outfile;
    private int currDoc;

    private Concordance concord;

    public Indexer() {
    }

    public void index(String[] args) throws IOException {

        infiles = Arrays.copyOf(args, args.length - 1);
        outfile = args[args.length - 1];
        concord = new Concordance(infiles, outfile);
        index();
    }

    private void index() throws IOException {
        for (String file : infiles) {
            indexFile(file);
            currDoc++;
        }

        concord.merge();

        Index index = new Index(outfile);
        index.index(concord.getFilename());
    }

    private void indexFile(String file) throws IOException {
        Lexer lexer = new Lexer(new FileReader(file));

        String term;
        for (int i = 0; ((term = lexer.getToken()).length()) != 0; i++) {
            concord.insert(term, currDoc, i);
        }
    }

    public static void main(String[] args) {

        if (args.length < 2) {
            System.err.println("usage: Indexer input-files output-file");
            System.exit(1);
        }

        Timer t = new Timer();

        Indexer index = new Indexer();

        try {
            index.index(args);
        } catch (IOException e) {
            System.err.println(e);
            System.exit(1);
        }

        System.out.printf("    elapsed time %s\n", t);
    }
}
