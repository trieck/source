package org.tomrieck.content;

import java.io.*;
import java.nio.channels.Channels;

public class Query {

    private RandomAccessFile f1, f2;
    private long hash_tbl_size, hash_tbl_offset;
    private QueryTokenizer lexer;

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

        for (; ;) {
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

        return lookup(left);
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

    public AnchorList lookup(String term) throws IOException {
        AnchorList list = new AnchorList();

        Lexer lexer = new Lexer(new StringReader(term));

        String token;
        for (int i = 0; (token = lexer.getToken()).length() > 0; i++) {
            if (i > 0) {
                list = adjacent(list, indexLookup(token));
            } else {
                list = indexLookup(token);
            }
        }

        return list;
    }

    private AnchorList indexLookup(String term) throws IOException {
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
            sTerm = IOUtil.readString(is);
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

        f1.readInt();  // number of terms

        hash_tbl_size = f1.readLong();     // size of hash table
        hash_tbl_offset = f1.readLong();   // offset to the hash table
    }
}
