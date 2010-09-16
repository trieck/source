package org.pixielib.content;

import org.pixielib.util.Timer;
import org.pixielib.xml.QParser;

import java.io.*;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class XMLIndexer extends QParser {

    private Repository repos;       // repository instance
    private Index index;            // index instance
    private String field;           // current tag while parsing
    private short filenum;          // current file number while indexing
    private int offset;             // offset into current file
    
    public XMLIndexer() throws IOException {
        repos = Repository.getInstance();
    }

    /**
     * Process an element while parsing
     *
     * @param name the name of the tag
     * @param tag  the tag value
     */
    @Override
    public void element(String name, String tag) {
        field = name;
        if (field.equals("record")) {
            offset = (int)Math.max(0, getPosition() - tag.length());
            assert(offset < ((long)1 << Anchor.OFFSET_BITS-1));
        }
    }

    /**
     * Process a value while parsing
     *
     * @param text the text encountered
     */
    @Override
    public void value(String text) {
        Lexer lexer = new Lexer(new StringReader(text));

        long anchor;

        try {
            String term, tok;
            for (short i = 0; ((tok = lexer.getToken()).length()) != 0; i++) {
                term = String.format("%s:%s", field, tok);
                anchor = Anchor.makeAnchorID(filenum, offset, i);
                index.insert(term, anchor);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void load(String db) throws IOException {

        File dir = repos.mapPath(db);

        List<File> files = expand(dir);
        if (files.size() == 0)
            throw new IOException(
                    String.format("no content files found in \"%s\".",
                            dir.getCanonicalPath())
            );

        index = new Index();
        loadfiles(files);
        index.write(db);
    }

    private void loadfiles(List<File> files)
            throws IOException {
        for (File f : files) {
            setPosition(0);
            loadfile(f);            
            filenum++;
        }
    }

    private void loadfile(File file)
            throws IOException {
        setPosition(0);
        parse(new FileReader(file));
    }

    private List<File> expand(File dir) {
        List<File> result = new ArrayList<File>();

        // list xml files
        File[] files = dir.listFiles(new FilenameFilter() {
            public boolean accept(File dir, String name) {
                return name.endsWith(".xml");
            }
        }
        );

        result.addAll(Arrays.asList(files));

        return result;
    }

    public static void main(String[] args) {

        if (args.length != 1) {
            System.err.println("usage: XMLIndexer database");
            System.exit(1);
        }

        Timer t = new Timer();

        try {
            XMLIndexer indexer = new XMLIndexer();
            indexer.load(args[0]);
        } catch (IOException e) {
            System.err.println(e);
            System.exit(1);
        }

        System.out.printf("    elapsed time %s\n", t);
    }
}
