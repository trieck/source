package org.tomrieck.content;

import org.tomrieck.util.DoubleHash64;
import org.tomrieck.util.Timer;

import java.io.*;
import java.nio.channels.Channels;
import java.util.Arrays;

public class Index {

    public static final int MAGIC_NO = 0xc001d00d;  // file magic number
    private static final int BUF_SIZE = 4096;       // buffer size

    private String[] infiles;       // array of files to index
    private String outfile;         // name of output file
    private int currDoc;            // current document # while indexing
    private Concordance concord;    // term concordance

    public Index() {
    }

    public void index(String[] args) throws IOException {
        infiles = Arrays.copyOf(args, args.length - 1);
        outfile = args[args.length - 1];
        concord = new Concordance();
        index();
    }

    private void index() throws IOException {
        for (String file : infiles) {
            indexFile(file);
            currDoc++;
        }

        finalPass();
    }

    /* combine concordance and hash table into final index */
    private void finalPass() throws IOException {

        // merge concordance blocks
        String concordFile = concord.merge();

        RandomAccessFile ofile = new RandomAccessFile(outfile, "rw");
        DataInputStream dis = new DataInputStream(new FileInputStream(concordFile));

        // write file magic number
        ofile.writeInt(MAGIC_NO);

        // write the total number of terms
        long term_count_offset = ofile.getFilePointer();
        ofile.writeLong(0); // not yet known

        // write the offset to the concordance
        long concordance_offset = ofile.getFilePointer();
        ofile.writeLong(0); // not yet known

        // write the size of the hash table
        long hash_table_size_offset = ofile.getFilePointer();
        ofile.writeLong(0); // not yet known

        // write the offset to the hash table
        long hash_table_offset = ofile.getFilePointer();
        ofile.writeLong(0); // not yet known

        // write the number of input files
        ofile.writeInt(infiles.length);

        // write each input file in index order
        OutputStream os = Channels.newOutputStream(ofile.getChannel());
        for (String infile : infiles) {
            IOUtil.writeString(os, makeCanonical(infile));
        }

        // write the real offset to the concordance
        long concordance = ofile.getFilePointer();
        ofile.seek(concordance_offset);
        ofile.writeLong(concordance);
        ofile.seek(concordance);  // jump back

        // write terms/anchors

        long nterms;
        String term;
        int n, m, read;
        byte[] buf = new byte[BUF_SIZE];

        for (nterms = 0; (term = IOUtil.readString(dis)).length() > 0; nterms++) {
            n = dis.readInt();  // anchor list size

            IOUtil.writeString(os, term);
            ofile.writeInt(n);

            for (n = n * 8 /* size in bytes */; n > 0;) {
                m = Math.min(BUF_SIZE, n);
                if ((read = dis.read(buf, 0, m)) <= 0)
                    break;

                os.write(buf, 0, read);
                n -= read;
            }
        }

        dis.close();

        // generate the hash table

        // hash table location
        long hash_table_area = ofile.getFilePointer();

        // write the total term count
        ofile.seek(term_count_offset);
        ofile.writeLong(nterms);

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
        Arrays.fill(buf, (byte) 0);

        long remaining = tableSize * 8;
        while (remaining > 0) {
            m = (int) Math.min(BUF_SIZE, remaining);
            ofile.write(buf, 0, m);
            remaining -= m;
        }

        // we need two file pointers to the output file
        // in order to generate the hash table
        RandomAccessFile infile = new RandomAccessFile(outfile, "r");

        // seek to the concordance
        infile.seek(concordance);

        InputStream is = Channels.newInputStream(infile.getChannel());

        long h, offset, term_offset = concordance;
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

    private void indexFile(String file) throws IOException {
        Lexer lexer = new Lexer(new FileReader(file));

        String term;
        for (int i = 0; ((term = lexer.getToken()).length()) != 0; i++) {
            concord.insert(term, currDoc, i);
        }
    }

    private static String makeCanonical(String filename) throws IOException {
        File file = new File(filename);
        return file.getCanonicalPath();
    }

    public static void main(String[] args) {

        if (args.length < 2) {
            System.err.println("usage: Index input-files output-file");
            System.exit(1);
        }

        Timer t = new Timer();

        Index index = new Index();

        try {
            index.index(args);
        } catch (IOException e) {
            System.err.println(e);
            System.exit(1);
        }

        System.out.printf("    elapsed time %s\n", t);
    }

    public static long hash(String term, long size) {
        long h = (DoubleHash64.hash(term) & 0x7FFFFFFFFFFFFFFFL) % size;

        return h;
    }
}
