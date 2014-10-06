package org.pixielib.content;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class Concordance {

    private final List<String> tempfiles = new ArrayList<>(); // temporary files
    private Inverter block = new Inverter();

    public Concordance() {
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
        try (FileOutputStream os = new FileOutputStream(file)) {
            tempfiles.add(file.getAbsolutePath());

            block.write(os);
        }
    }

    public String merge() throws IOException {
        blockSave();

        if (tempfiles.size() == 1)
            return tempfiles.get(0);    // optimization

        ConcordMerge merger = new ConcordMerge();
        return merger.merge(tempfiles);
    }

    public void insert(String term, long anchor) throws IOException {

        if (isFull()) {
            blockSave();
        }

        block.insert(term, anchor);
    }
}
