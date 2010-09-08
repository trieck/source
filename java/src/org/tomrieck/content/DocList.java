package org.tomrieck.content;

import java.io.DataInputStream;
import java.io.InputStream;
import java.io.IOException;
import java.util.ArrayList;

public class DocList {

    private ArrayList<Long> documents = new ArrayList<Long>();

    public DocList() {
    }

    public int size() {
        return documents.size();
    }

    public Document getDoc(int index) {
        return new Document(documents.get(index));
    }

    public void read(InputStream is) throws IOException {

        DataInputStream dis = new DataInputStream(is);

        int size = dis.readInt();   // size of document vector

        byte[] buffer = new byte[size * 8];

        int nread = dis.read(buffer);
        if (nread != buffer.length) {
            throw new IOException("unable to read document vector.");
        }

        documents.clear();
        documents.ensureCapacity(size);
        
        long doc;
        for (int i = 0; i < size; i++) {    // convert byte array to long
            doc = buffer[i*8+0] << 56
                | buffer[i*8+1] << 48
                | buffer[i*8+2] << 40
                | buffer[i*8+3] << 32
                | buffer[i*8+4] << 24
                | buffer[i*8+5] << 16
                | buffer[i*8+6] << 8
                | buffer[i*8+7];
            documents.add(doc);
        }        
    }

    public void add(long l) {
        documents.add(l);
    }

    public void add(Document doc) {
        add(doc.getDocID());
    }

    public static DocList adjacent(DocList set1, DocList set2) {

        DocList output = new DocList();

        Document left, right;
        
        int i = 0, j = 0, k, m = set1.size(), n = set2.size();

        while (i != m && j != n) {
            left = set1.getDoc(i);
            right = set2.getDoc(j);

            k = left.compareTo(right);
            if (k == -1) {
                output.add(right);
                i++;
                j++;
            } else if (k == 1) {
                output.add(left);
                i++;
                j++;
            } else if (k < 0) {
                i++;
            } else if (k > 0) {
                j++;
            } else {
                i++;
                j++;
            }
            
        }

        return output;
    }
}
