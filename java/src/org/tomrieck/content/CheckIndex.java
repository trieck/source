package org.tomrieck.content;

import org.tomrieck.util.Timer;

import java.io.*;
import java.nio.channels.Channels;
import java.text.DecimalFormat;

public class CheckIndex {

    private int nfiles;
    private Query query;

    public CheckIndex() {
    }

    public void checkIndex(String filename) throws IOException {
        RandomAccessFile file = new RandomAccessFile(filename, "r");

        // for searching
        query = new Query(filename);

        int magicno = file.readInt();
        if (magicno != Index.MAGIC_NO) {
            throw new IOException("file not in index format.");
        }

        long nterms = file.readLong();
        System.out.printf("    Contains %d terms(s)\n", nterms);

        long conc_offset = file.readLong();
        System.out.printf("    Concordance offset: 0x%08x\n", conc_offset);

        long hash_tbl_size = file.readLong();
        System.out.printf("    Hash table size: 0x%08x\n", hash_tbl_size);

        long hash_tbl_offset = file.readLong();
        System.out.printf("    Hash table offset: 0x%08x\n", hash_tbl_offset);

        nfiles = file.readInt();
        System.out.printf("    Indexes %d file(s):\n", nfiles);

        String infile;
        InputStream is = Channels.newInputStream(file.getChannel());
        for (int i = 0; i < nfiles; i++) {
            infile = IOUtil.readString(is);
            System.out.printf("        %s\n", infile);
        }

        // check the terms and anchor lists
        
        String term;
        int vsize;  // anchor list size
        long[] anchorlist;

        for (long i = 0; i < nterms; i++) {
            term = IOUtil.readString(is);

            search(term);

            vsize = file.readInt();
            if (vsize <= 0) {
                throw new IOException(
                        String.format("bad anchor list size %d for term \"%s\".",
                                vsize, term));
            }

            anchorlist = new long[vsize];
            for (int j = 0; j < vsize; j++) {
                anchorlist[j] = file.readLong();
            }

            checkAnchors(anchorlist);
        }

        // check the hash table
        file.seek(hash_tbl_offset);

        long nfilled = 0;
        for (long i = 0; i < hash_tbl_size; i++) {
            if (file.readLong() != 0)
                nfilled++;
        }

        DecimalFormat df = new DecimalFormat("#0.00");

        System.out.printf("    Hash table fill factor: %s%%\n", df.format(100 * (nfilled / (double)hash_tbl_size)));
        
        is.close();
        file.close();
        query.close();
    }

    private void search(String term) throws IOException {

        AnchorList list = query.lookup(term);

        if (list.size() == 0) {
            throw new IOException(String.format("search failed for term \"%s\".", term));
        }
    }

    private void checkAnchors(long[] anchorlist) throws IOException {
        int docnum;
        int wordnum;

        for (int i = 0; i < anchorlist.length; i++) {
            docnum = (int) (anchorlist[i] >> 32);
            if (docnum < 0 || docnum >= nfiles) {
                throw new IOException(
                        String.format("document number (%d) out of range.", docnum)
                );
            }
            wordnum = (int) anchorlist[i];
            if (wordnum < 0) {
                throw new IOException(
                        String.format("word number (%d) out of range.", wordnum)
                );
            }
        }
    }

    public static void main(String[] args) {
        if (args.length != 1) {
            System.err.println("usage: CheckIndex index-file");
            System.exit(1);
        }

        Timer t = new Timer();

        CheckIndex chkindex = new CheckIndex();

        try {
            chkindex.checkIndex(args[0]);
        } catch (IOException e) {
            System.err.println(e.getMessage());
            System.exit(1);
        }

        System.out.printf("    elapsed time %s\n", t);
    }
}
