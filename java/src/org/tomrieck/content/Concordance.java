package org.tomrieck.content;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class Concordance {

    private static final int BUF_SIZE = 4096;

    private Inverter block = new Inverter();
    private final List<String> tempfiles = new ArrayList<String>(); // temporary files

    private String[] infiles;   // input files

    public Concordance(String[] infiles) throws IOException {
        this.infiles = infiles;
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

    public String merge() throws IOException {
        blockSave();

        ConcordMerge merger = new ConcordMerge();
        return merger.merge(tempfiles);
    }

    public void insert(String term, int docnum, int wordnum) throws IOException {

        if (isFull()) {
            blockSave();
        }

        block.insert(term, docnum, wordnum);
    }
}
