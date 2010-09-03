package org.tomrieck.content;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class Concordance {

    private Inverter block = new Inverter();
    private final List<String> filenames = new ArrayList<String>();

    public Concordance() {
    }

    public boolean isFull() {
        return block.isFull();
    }

    public void blockSave() throws IOException {
        if (block.getCount() == 0) {
            return;
        }

        final File file = File.createTempFile("conc", "ndx");
        file.deleteOnExit();

        final FileOutputStream os = new FileOutputStream(file);
        filenames.add(file.getAbsolutePath());

        block.write(os);

        os.close();
    }

    public void merge(String outfile) throws IOException {
        blockSave();

        if (filenames.size() == 0) {
            return;
        }

        final File oldFile = new File(filenames.get(0)); // first file
        final File newFile = new File(outfile);

        newFile.delete();
        oldFile.renameTo(newFile);
    }

    public void insert(String term, int docnum, int wordnum) throws IOException {

        if (isFull()) {
            blockSave();
        }

        block.insert(term, docnum, wordnum);
    }
}
