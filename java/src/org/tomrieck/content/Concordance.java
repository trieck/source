package org.tomrieck.content;

import java.io.*;
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
        this.outfile = outfile;
    }

    public boolean isFull() {
        return block.isFull();
    }

    public void blockSave() throws IOException {
        if (block.getCount() == 0) {
            return;
        }

        File file = File.createTempFile("conc", "ndx");
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

        BlockMerge merger = new BlockMerge();
        String merge = merger.merge(tempfiles);

        File oldFile = new File(merge); // merge target
        File newFile = new File(outfile);

        DataOutputStream dos = new DataOutputStream(new FileOutputStream(newFile));
        FileInputStream fis = new FileInputStream(oldFile);

        // write the magic number
        dos.writeInt(MAGIC_NUMBER);
        
        // write the number of input files
        dos.writeInt(infiles.length);
        for (String infile : infiles) { // write each input file name in index order
            IOUtil.writeString(dos, infile);
        }

        byte[] bytes = new byte[BUF_SIZE];

        int nread;
        while ((nread = fis.read(bytes)) != -1) {
            dos.write(bytes, 0, nread);
        }
        
        fis.close();
        dos.close();
    }

    public void insert(String term, int docnum, int wordnum) throws IOException {

        if (isFull()) {
            blockSave();
        }

        block.insert(term, docnum, wordnum);
    }
}
