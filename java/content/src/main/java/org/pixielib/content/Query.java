package org.pixielib.content;

import java.io.*;
import java.nio.channels.Channels;

/**
 * This class maps a search expression into an anchor list.
 * <p/>
 * The grammar uses juxtaposition for the "and" operator.
 * Each production rule has a corresponding method in the class.
 * Search "phrases" are surrounded by double-quotes.
 * <p/>
 * conjunction := primary primary
 * | primary
 * <p/>
 * primary     := field[ term-list ]
 * <p/>
 * term-list   := term term
 * | term
 */

public class Query {

    private RandomAccessFile f1, f2;
    private long hash_tbl_size, hash_tbl_offset;
    private QueryTokenizer lexer;

    protected Query() {
    }

    public Query(String db) throws IOException {
        Repository repos = Repository.getInstance();
        File index_file = repos.getIndexPath(db);
        f1 = new RandomAccessFile(index_file, "r");
        f2 = new RandomAccessFile(index_file, "r");
        readHeader();
    }

    public void close() throws IOException {
        if (f1 != null) {
            f1.close();
            f1 = null;
        }

        if (f2 != null) {
            f2.close();
            f2 = null;
        }
    }

    public AnchorList query(String phrase) throws IOException {
        lexer = new QueryTokenizer(new StringReader(phrase));
        return conjunction();
    }

    private AnchorList conjunction() throws IOException {
        AnchorList left = primary();

        for (; ; ) {
            if (lookahead().length() == 0)
                return left;

            AnchorList right = primary();

            left = intersection(left, right);
        }
    }

    private AnchorList primary() throws IOException {
        AnchorList anchorlist = new AnchorList();

        String left = getTok();

        if (left.length() == 0)
            return anchorlist; // error condition

        if (lookahead().equals("[")) {  // field restriction
            getTok();   // '['
            anchorlist = termList(left);
            getTok();   // ']'
        }

        return anchorlist;  // error condition
    }

    private String getTok() throws IOException {
        return lexer.getToken();
    }

    private String lookahead() throws IOException {
        return lexer.lookahead();
    }

    private AnchorList adjacent(AnchorList left, AnchorList right) {
        return AnchorList.adjacent(left, right);
    }

    private AnchorList intersection(AnchorList left, AnchorList right) {
        return AnchorList.intersection(left, right);
    }

    private AnchorList termList(String field) throws IOException {

        String term = getTok();

        AnchorList list = lookup(field, term);

        for (; ; ) {
            if (lookahead().equals(""))
                return list;

            if (lookahead().equals("]"))
                return list;

            term = getTok();

            list = intersection(list, lookup(field, term));
        }
    }

    protected AnchorList lookup(String field, String term) throws IOException {
        AnchorList list = new AnchorList();

        Lexer reader = new Lexer(new StringReader(term));

        String token, restriction;
        for (int i = 0; (token = reader.getToken()).length() > 0; i++) {
            restriction = String.format("%s:%s", field, token);

            if (i > 0) {
                list = adjacent(list, lookup(restriction));
            } else {
                list = lookup(restriction);
            }
        }

        return list;
    }

    protected AnchorList lookup(String term) throws IOException {
        AnchorList list = new AnchorList();

        // hash the term
        long h = Index.hash(term, hash_tbl_size);

        // seek to bucket in hash table
        f1.seek(hash_tbl_offset + (h * 8));

        // read the concordance offset
        long offset;
        if ((offset = f1.readLong()) == 0)
            return list; // no hit

        String sTerm;
        InputStream is = Channels.newInputStream(f2.getChannel());
        while (offset != 0) {   // linear-probing

            // seek into concordance
            f2.seek(offset);

            // read term in concordance
            sTerm = DataInputStream.readUTF(f2);
            if (sTerm.equals(term)) {   // match
                list.read(is);
                break;
            }

            // move to next bucket
            h = (h + 1) % hash_tbl_size;

            f1.seek(hash_tbl_offset + (h * 8));

            offset = f1.readLong();
        }

        return list;
    }

    private void readHeader() throws IOException {
        f1.seek(0);

        int magicno = f1.readInt();
        if (magicno != Index.MAGIC_NO)
            throw new IOException("index bad file format.");

        int nfields = f1.readInt();         // number of fields
        while (nfields-- > 0) {
            f1.readUTF();                   // index field
        }

        f1.readInt();                       // number of terms

        hash_tbl_size = f1.readLong();      // size of hash table
        hash_tbl_offset = f1.readLong();    // offset to the hash table
    }
}
