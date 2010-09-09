package org.tomrieck.content;

import org.tomrieck.util.Timer;

import java.io.*;

public class CheckIndex {

    private int nfiles;
    private Query query;

    public CheckIndex() {
    }

    public void checkIndex(String file) throws IOException {
        DataInputStream dis = new DataInputStream(new FileInputStream(file));

        /* for searching */
        query = new Query(file);

        int magicno = dis.readInt();
        if (magicno != Index.MAGIC_NO) {
            throw new IOException("file not in index format.");
        }

        long nterms = dis.readLong();
        System.out.printf("    Contains %d terms(s)\n", nterms);

        long conc_offset = dis.readLong();
        System.out.printf("    Concordance offset: 0x%08x\n", conc_offset);

        long hash_tbl_size = dis.readLong();
        System.out.printf("    Hash table size: 0x%08x\n", hash_tbl_size);

        long hash_tbl_offset = dis.readLong();
        System.out.printf("    Hash table offset: 0x%08x\n", hash_tbl_offset);

        nfiles = dis.readInt();
        System.out.printf("    Indexes %d files:\n", nfiles);

        String infile;
        for (int i = 0; i < nfiles; i++) {
            infile = IOUtil.readString(dis);
            System.out.printf("       %s\n", infile);
        }

        String term;
        int vsize;  // anchor list size
        long[] anchorlist;

        for (long i = 0; i < nterms; i++) {
            term = IOUtil.readString(dis);

            search(term);

            vsize = dis.readInt();
            if (vsize <= 0) {
                throw new IOException(
                        String.format("bad anchor list size %d for term \"%s\".",
                                vsize, term));
            }

            anchorlist = new long[vsize];
            for (int j = 0; j < vsize; j++) {
                anchorlist[j] = dis.readLong();
            }

            checkAnchors(anchorlist);
        }

        dis.close();
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
