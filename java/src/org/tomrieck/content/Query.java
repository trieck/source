package org.tomrieck.content;

import java.io.*;
import java.nio.channels.Channels;

public class Query {

    private RandomAccessFile f1, f2;
    private long hash_tbl_size, hash_tbl_offset;
    private Lexer lexer;

    public Query(String index_file) throws IOException {
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

    public DocList query(String phrase) throws IOException {
        lexer = new Lexer(new StringReader(phrase));
        return conjunction();
    }

    private DocList conjunction() throws IOException {
        DocList left = primary();

        for (;;) {
            if (lookahead().length() == 0)
                return left;

            DocList right = primary();
            
            left = adjacent(left, right);
        }
    }

    private DocList primary() throws IOException {
        DocList doclist = new DocList();

        String left = getTok();

        if (left.length() == 0)
            return doclist; // error condition

        return lookup(left);
    }

    private String getTok() throws IOException {
        return lexer.getToken();
    }

    private String lookahead() throws IOException {
        return lexer.lookahead();
    }

    private DocList adjacent(DocList left, DocList right) {
        return DocList.adjacent(left, right);
    }
    
    private DocList lookup(String term) throws IOException {
        DocList doclist = new DocList();

        // hash the term
        long bucket = Index.bucket_hash(term, hash_tbl_size);

        // seek to bucket in hash table
        f1.seek(hash_tbl_offset + bucket);

        // read the concordance offset
        long conc_offset;
        if ((conc_offset = f1.readLong()) == 0)
            return doclist; // no hit
        
        String sTerm;
        InputStream is = Channels.newInputStream(f2.getChannel());
        while (conc_offset != 0) {   // linear-probing

            // seek into concordance
            f2.seek(conc_offset);

            // read term in concordance
            sTerm = IOUtil.readString(is);
            if (sTerm.equals(term)) {   // match
                doclist.read(is);
                break;
            }

            // move to next bucket
            conc_offset = f1.readLong();
        }

        return doclist;
    }

    private void readHeader() throws IOException {
        f1.seek(0);

        int magicno = f1.readInt();
        if (magicno != Index.MAGIC_NO)
            throw new IOException("index bad file format.");

        f1.readLong();  // number of terms
        f1.readLong();  // concordance offset

        hash_tbl_size = f1.readLong();     // size of hash table
        hash_tbl_offset = f1.readLong();   // offset to the hash table
    }
}
