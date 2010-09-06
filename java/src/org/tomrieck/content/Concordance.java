package org.tomrieck.content;

import java.io.*;
import java.nio.channels.Channels;
import java.util.ArrayList;
import java.util.List;

public class Concordance {

    public static final int MAGIC_NUMBER = 0xc001d00d;
    private static final int BUF_SIZE = 4096;
    
    private Inverter block = new Inverter();
    private final List<String> tempfiles = new ArrayList<String>(); // temporary files

    private String[] infiles;   // input files
    private String outfile;     // output file

    public Concordance(String[] infiles, String outfile) {
        this.infiles = infiles;
        this.outfile = IOUtil.baseFilename(outfile) + ".dat";
    }

    public String getFilename() {
        return outfile;
    }
    
    public boolean isFull() {
        return block.isFull();
    }

    public void blockSave() throws IOException {
        if (block.getCount() == 0) {
            return;
        }

        File file = File.createTempFile("conc", "dat");
        file.deleteOnExit();

        FileOutputStream os = new FileOutputStream(file);
        tempfiles.add(file.getAbsolutePath());

        block.write(os);

        os.close();
    }

    public void merge() throws IOException {
        blockSave();

        if (tempfiles.size() == 0) {
            return;
        }

        ConcordMerge merger = new ConcordMerge();
        String merge = merger.merge(tempfiles);

        RandomAccessFile ofile = new RandomAccessFile(outfile, "rw");
        DataInputStream dis = new DataInputStream(new FileInputStream(merge));

        // write the magic number
        ofile.writeInt(MAGIC_NUMBER);

        // write the total number of terms
        long term_count_offset = ofile.getFilePointer();
        ofile.writeLong(0); // not yet known

        // write the offset to the term area
        long term_area_offset = ofile.getFilePointer();
        ofile.writeLong(0); // not yet known

        // write the number of input files
        ofile.writeInt(infiles.length);

        // write each input file in index order
        OutputStream os = Channels.newOutputStream(ofile.getChannel());
        for (String infile : infiles) {
            IOUtil.writeString(os, infile);
        }

        // write the real offset to the term area
        long term_area = ofile.getFilePointer();
        ofile.seek(term_area_offset);
        ofile.writeLong(term_area);
        ofile.seek(term_area);  // jump back
        
        // write terms/docvectors

        long nterms;
        String term;
        int n, m, read;
        byte[] buf = new byte[BUF_SIZE];

        for (nterms = 0; (term = IOUtil.readString(dis)).length() > 0; nterms++) {
            n = dis.readInt();  // docvec size

            IOUtil.writeString(os, term);
            ofile.writeInt(n);

            for (n = n * 8 /* size in bytes */; n > 0; ) {
                m = Math.min(BUF_SIZE, n);
                if ((read = dis.read(buf, 0, m)) <= 0)
                    break;

                os.write(buf, 0, read);
                n -= read;
            }
        }

        ofile.seek(term_count_offset);  // term count offset
        ofile.writeLong(nterms);
        
        dis.close();
        os.close();
        ofile.close();
    }

    public void insert(String term, int docnum, int wordnum) throws IOException {

        if (isFull()) {
            blockSave();
        }

        block.insert(term, docnum, wordnum);
    }
}
