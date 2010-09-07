package org.tomrieck.content;

import java.io.*;
import java.nio.channels.Channels;

public class CheckIndex {

    private int nfiles;

    private long nterms;            // number of terms in index
    private long conc_offset;       // offset to concordance
    private long hash_tbl_size;     // hash table size
    private long hash_tbl_offset;   // hash table offset

    private RandomAccessFile file1, file2;

    public CheckIndex() {
    }

    public void checkIndex(String file) throws IOException {
        DataInputStream dis = new DataInputStream(new FileInputStream(file));

        /* for searching */
        file1 = new RandomAccessFile(file, "r");
        file2 = new RandomAccessFile(file, "r");

        int magicno = dis.readInt();
        if (magicno != Index.MAGIC_NO) {
            throw new IOException("file not in index format.");
        }

        nterms = dis.readLong();
        System.out.printf("    Contains %d terms(s)\n", nterms);

        conc_offset = dis.readLong();
        System.out.printf("    Concordance offset: 0x%08x\n", conc_offset);

        hash_tbl_size = dis.readLong();
        System.out.printf("    Hash table size: 0x%08x\n", hash_tbl_size);

        hash_tbl_offset = dis.readLong();
        System.out.printf("    Hash table offset: 0x%08x\n", hash_tbl_offset);

        nfiles = dis.readInt();
        System.out.printf("    Indexes %d files:\n", nfiles);

        String infile;
        for (int i = 0; i < nfiles; i++) {
            infile = IOUtil.readString(dis);
            System.out.printf("       %s\n", infile);
        }

        String term;
        int vsize;  // document vector size
        long[] docvec;

        for (long i = 0; i < nterms; i++) {
            term = IOUtil.readString(dis);

            search(term);

            vsize = dis.readInt();
            if (vsize <= 0) {
                throw new IOException(
                        String.format("bad document vector size %d for term \"%s\".",
                                vsize, term));
            }

            docvec = new long[vsize];
            for (int j = 0; j < vsize; j++) {
                docvec[j] = dis.readLong();
            }

            checkDocs(docvec);
        }

        dis.close();

        file1.close();
        file2.close();
    }

    private void search(String term) throws IOException {

        long hash = Index.bucket_hash(term, hash_tbl_size);

        file1.seek(hash_tbl_offset + hash);

        String sTerm;
        InputStream is = Channels.newInputStream(file2.getChannel());

        long offset = file1.readLong();
        while (offset != 0) {
            file2.seek(offset);
            sTerm = IOUtil.readString(is);
            if (sTerm.equals(term)) {
                break;  // hit!
            }
            offset = file1.readLong();
        }

        if (offset == 0) {
            throw new IOException(String.format("search failed for term \"%s\".", term));
        }
    }

    private void checkDocs(long[] docvec) throws IOException {
        int docnum;
        int wordnum;

        for (int i = 0; i < docvec.length; i++) {
            docnum = (int) (docvec[i] >> 32);
            if (docnum < 0 || docnum >= nfiles) {
                throw new IOException(
                        String.format("document number (%d) out of range.", docnum)
                );
            }
            wordnum = (int) docvec[i];
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

        CheckIndex chkindex = new CheckIndex();

        try {
            chkindex.checkIndex(args[0]);
        } catch (IOException e) {
            System.err.println(e.getMessage());
            System.exit(1);
        }
    }
}
