package org.tomrieck.content;

import org.tomrieck.util.DoubleHash64;

import java.io.*;
import java.nio.channels.Channels;

public class Index {

    public static final int MAGIC_NO = 0xc001d00d;  // file magic number
    private static final int CONC_OFFSET = 28;      // offset to concordance

    private Repository repos;                       // content repository
    private Concordance concord;                    // term concordance

    public Index() throws IOException {
        concord = new Concordance();
        repos = Repository.getInstance();
    }

    /* combine concordance and hash table into final index */
    public void write(String db, int nfiles) throws IOException {

        // merge concordance blocks
        String concordFile = concord.merge();

        File outfile = repos.getIndexPath(db);

        RandomAccessFile ofile = new RandomAccessFile(outfile, "rw");
        DataInputStream dis = new DataInputStream(new FileInputStream(concordFile));

        // write file magic number
        ofile.writeInt(MAGIC_NO);

        // write the number of documents indexed
        ofile.writeInt(nfiles);

        // write the total number of terms
        long term_count_offset = ofile.getFilePointer();
        ofile.writeInt(0); // not yet known

        // write the size of the hash table
        long hash_table_size_offset = ofile.getFilePointer();
        ofile.writeLong(0); // not yet known

        // write the offset to the hash table
        long hash_table_offset = ofile.getFilePointer();
        ofile.writeLong(0); // not yet known

        // write terms/anchors

        int n, nterms;
        String term;

        OutputStream os = Channels.newOutputStream(ofile.getChannel());
        for (nterms = 0; (term = IOUtil.readString(dis)).length() > 0; nterms++) {
            // read the anchor list size
            n = dis.readInt();

            // write the term
            IOUtil.writeString(os, term);

            // write the anchor list size
            ofile.writeInt(n);

            // transfer the anchor list
            IOUtil.transfer(dis, os, n * 8);
        }

        dis.close();

        // generate the hash table

        // hash table location
        long hash_table_area = ofile.getFilePointer();

        // write the total term count
        ofile.seek(term_count_offset);
        ofile.writeInt(nterms);

        // compute the size of the hash table and store it
        long tableSize = Prime.prime(nterms);
        ofile.seek(hash_table_size_offset);
        ofile.writeLong(tableSize);

        // write the offset to the hash table
        ofile.seek(hash_table_offset);
        ofile.writeLong(hash_table_area);
        ofile.seek(hash_table_area); // jump back

        // expand file to make space for hash table
        long newLength = ofile.length() + (tableSize * 8);
        ofile.setLength(newLength);

        // need to ensure the hash table is empty
        IOUtil.fill(os, tableSize * 8, (byte) 0);

        // we need two file pointers to the output file
        // in order to generate the hash table
        RandomAccessFile infile = new RandomAccessFile(outfile, "r");

        // seek to the concordance
        infile.seek(CONC_OFFSET);

        InputStream is = Channels.newInputStream(infile.getChannel());

        long h, offset, term_offset = CONC_OFFSET;
        int vsize;
        for (long i = 0; i < nterms; i++) {
            term = IOUtil.readString(is);

            h = hash(term, tableSize);

            // collisions are resolved via linear-probing
            for (; ;) {
                offset = hash_table_area + (h * 8);

                ofile.seek(offset);
                if (ofile.readLong() == 0)
                    break;

                h = (h + 1) % tableSize;
            }

            ofile.seek(offset);
            ofile.writeLong(term_offset);

            // anchor list size
            vsize = infile.readInt() * 8;
            infile.skipBytes(vsize);

            // next term offset
            term_offset = infile.getFilePointer();
        }

        is.close();
        infile.close();
        ofile.close();
    }

    public void insert(String term, int docnum, int wordnum)
            throws IOException {
        concord.insert(term, docnum, wordnum);
    }

    public static long hash(String term, long size) {
        return (DoubleHash64.hash(term) & 0x7FFFFFFFFFFFFFFFL) % size;
    }
}
