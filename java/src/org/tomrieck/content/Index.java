package org.tomrieck.content;

import java.io.FileReader;
import java.io.IOException;
import java.util.Arrays;

public class Index {

    private String[] infiles;
    private String outfile;
    private int currDoc;

    private Concordance concord = new Concordance();

    public Index() {
    }

    public void index(String[] args) throws IOException {
        infiles = Arrays.copyOf(args, args.length - 1);
        outfile = args[args.length - 1];
        index();
    }

    private void index() throws IOException {
        for (String file : infiles) {
            indexFile(file);
            currDoc++;
        }

        concord.merge(outfile);
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
            System.err.println("usage: Index input-files output-file");
            System.exit(1);
        }

        Index index = new Index();

        try {
            index.index(args);
        } catch (IOException e) {
            System.err.println(e);
            System.exit(1);
        }
    }
}
