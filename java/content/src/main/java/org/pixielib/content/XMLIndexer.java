package org.pixielib.content;

import org.pixielib.util.Timer;
import org.pixielib.xml.QParser;

import java.io.*;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Stack;

public class XMLIndexer extends QParser {

    private Repository repos;       // repository instance
    private Index index;            // index instance
    private int filenum;            // current file number while indexing
    private int rec_offset;         // record offset into current file
    private int field_num;          // current top-level field number
    private Stack<Field> elements;  // stack of fields while indexing
    private IndexFields fields;     // set of top-level fields for indexing

    public XMLIndexer() throws IOException {
        repos = Repository.getInstance();
        elements = new Stack<>();
    }

    public static void main(String[] args) {

        if (args.length < 2) {
            System.err.println("usage: XMLIndexer database fields");
            System.exit(1);
        }

        Timer t = new Timer();

        try {
            XMLIndexer indexer = new XMLIndexer();
            indexer.load(args[0], Arrays.copyOfRange(args, 1, args.length));
        } catch (IOException e) {
            System.err.println(e);
            System.exit(1);
        }

        System.out.printf("    elapsed time %s\n", t);
    }

    /**
     * Process an element while parsing
     *
     * @param name the name of the tag
     * @param tag  the tag value
     */
    @Override
    public void startElement(String name, String tag) {
        elements.push(new Field(name));

        if (name.equals("record")) {
            rec_offset = (int) Math.max(0, getPosition() - tag.length());
            field_num = -1;
            assert (rec_offset < ((long) 1 << (Anchor.OFFSET_BITS)));
        } else if (rec_offset > 0) {
            if (isTopLevel()) {
                field_num++;
                assert (field_num < (1 << (Anchor.FIELDNUM_BITS)));
            }
        }
    }

    @Override
    public void endElement() {
        Field field = elements.peek();
        if (field.getName().equals("record")) {
            rec_offset = 0;
            field_num = -1;
        }

        elements.pop();
    }

    /**
     * Process a value while parsing
     *
     * @param text the text encountered
     */
    @Override
    public void value(String text) {

        if (field_num == -1 || !isTopLevel())
            return; // no top-level field

        if ((text = text.trim()).length() == 0)
            return; // whitespace

        Field field = elements.peek();
        int word_num = field.getWordCount();

        Lexer lexer = new Lexer(new StringReader(text));
        long anchor;

        try {
            String term, tok;
            while ((tok = lexer.getToken()).length() != 0) {
                term = String.format("%s:%s", field.getName(), tok);
                anchor = Anchor.makeAnchorID(filenum, rec_offset, field_num, word_num++);
                index.insert(term, anchor);
            }
        } catch (IOException ignored) {
        }

        field.setWordCount(word_num);
    }

    public void load(String db, String[] aFields) throws IOException {

        fields = new IndexFields(aFields);    // top-level index fields

        File dir = repos.mapPath(db);
        List<File> files = expand(dir);
        if (files.isEmpty())
            throw new IOException(
                    String.format("no content files found in \"%s\".",
                            dir.getCanonicalPath())
            );

        index = new Index();
        loadfiles(files);
        index.write(db, fields);
    }

    private void loadfiles(List<File> files)
            throws IOException {
        for (File f : files) {
            setPosition(0);
            loadfile(f);
            filenum++;
            assert (filenum < (1 << (Anchor.FILENUM_BITS)));
        }
    }

    private void loadfile(File file)
            throws IOException {
        setPosition(0);
        parse(new FileReader(file));
    }

    private List<File> expand(File dir) {
        List<File> result = new ArrayList<>();

        // list xml files
        File[] files = dir.listFiles(new FilenameFilter() {
            @Override
            public boolean accept(File dir, String name) {
                return name.endsWith(".xml");
            }
        });

        result.addAll(Arrays.asList(files));

        return result;
    }

    private boolean isTopLevel() {
        if (elements.size() == 0)
            return false;

        Field field = elements.peek();

        return fields.isTopLevel(field.getName());
    }
}
