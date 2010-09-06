package org.tomrieck.content;

import java.io.*;
import java.nio.channels.Channel;
import java.nio.channels.Channels;
import java.nio.channels.FileChannel;

/**
 * External open-addressed hash table index
 */
public class Index {

    public static final int MAGIC_NUMBER = 0xbaadd00d;
    private static final int BUCKET_SIZE = 8;
    private static final int FILL_FACTOR = 3;

    private String filename;

    public Index(String filename) {
        this.filename = filename;
    }

    public void index(String concordance) throws IOException {
        
        RandomAccessFile infile = new RandomAccessFile(concordance, "r");
        RandomAccessFile outfile = new RandomAccessFile(filename, "rw");

        // write the magic number
        outfile.writeInt(MAGIC_NUMBER);

        int magicno = infile.readInt();
        if (magicno != Concordance.MAGIC_NUMBER) {
            throw new IOException("file not in concordance format.");
        }

        long nterms = infile.readLong();            // total number of terms
        long term_area_offset = infile.readLong();  // term area offset

        long tableSize = Prime.prime(nterms * 8 * FILL_FACTOR);
        outfile.setLength(tableSize + 4 /* MAGIC_NUMBER */);

        outfile.seek(4 /* MAGIC_NUMBER */);
        for (long i = 0; i < tableSize; i++) {
            outfile.write(0);
        }

        // seek to beginning of term list
        infile.seek(term_area_offset);

        long term_offset = term_area_offset;
        long h;
        int vsize;

        String term;
        InputStream is = Channels.newInputStream(infile.getChannel());

        while ((term = IOUtil.readString(is)).length() > 0) {
            h = bucket_hash(term, tableSize);
            
            outfile.seek(4 + h /* MAGIC_NUMBER */);

            // collisions are resolved via linear-probing
            while (outfile.readLong() != 0)
                ;

            // move back to the last empty slot
            outfile.seek(outfile.getFilePointer()-8);

            // write the term offset
            outfile.writeLong(term_offset);

            // document vector size
            vsize = infile.readInt() * 8;
            infile.skipBytes(vsize);

            // next term offset
            term_offset = infile.getFilePointer();
        }
        
        infile.close();
        outfile.close();
    }

    private static long bucket_hash(String term, long size) {
        long h = (DoubleHash64.hash(term) & 0x7FFFFFFFFFFFFFFFL) % size;

        // align offset to multiple of bucket size
        h = h + (BUCKET_SIZE-1) & ~(BUCKET_SIZE-1);

        return h;
    }
}
