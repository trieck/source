package org.tomrieck.content;

import java.io.DataInputStream;
import java.io.FileInputStream;
import java.io.IOException;

public class CheckIndex {

    private int nfiles; // number of files indexed
    
    public CheckIndex() {        
    }

    public void checkIndex(String file) throws IOException {

        DataInputStream dis = new DataInputStream(new FileInputStream(file));

        int magicno = dis.readInt();
        if (magicno != Concordance.MAGIC_NUMBER) {
            throw new IOException("file not in index format");
        }

        nfiles = dis.readInt();
        System.out.printf("   Checking index file: %s...\n", file);
        System.out.printf("   Indexes %d content file(s):\n", nfiles);

        String infile;
        for (int i = 0; i < nfiles; i++) {
            infile = IOUtil.readString(dis);
            System.out.printf("      %s\n", infile);
        }

        String term;
        int vsize;  // document vector size
        long[] docvec;

        while ((term = IOUtil.readString(dis)).length() > 0) {
            vsize = dis.readInt();
            if (vsize <= 0) {
                throw new IOException(
                    String.format("bad document vector size %d for term \"%s\".",
                        vsize, term));
            }

            docvec = new long[vsize];
            for (int i = 0; i < vsize; i++) {
                docvec[i] = dis.readLong();
            }

            checkDocs(docvec);
        }
    }

    private void checkDocs(long[] docvec) throws IOException {
        int docnum;
        int wordnum;

        for (int i = 0; i < docvec.length; i++) {
            docnum = (int)(docvec[i] >> 32);
            if (docnum < 0 || docnum >= nfiles) {
                throw new IOException(
                    String.format("document number (%d) out of range.", docnum)
                );
            }
            wordnum = (int)docvec[i];
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
