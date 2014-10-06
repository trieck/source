package org.pixielib.content;

import java.io.DataInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.Set;
import java.util.TreeSet;

public class AnchorList {

    private ArrayList<Long> anchors = new ArrayList<>();

    public AnchorList() {
    }

    public static AnchorList intersection(AnchorList set1, AnchorList set2) {
        AnchorList output = new AnchorList();

        Anchor left, right;

        int i = 0, j = 0, m = set1.size(), n = set2.size();
        long leftdoc, rightdoc;

        while (i != m && j != n) {
            left = set1.getAnchor(i);
            right = set2.getAnchor(j);

            leftdoc = left.getDocID();
            rightdoc = right.getDocID();

            if (leftdoc < rightdoc) {
                i++;
            } else if (leftdoc > rightdoc) {
                j++;
            } else {    // intersection is defined by same document
                output.add(left);
                i++;
                j++;
            }
        }

        return output;
    }

    public static AnchorList adjacent(AnchorList set1, AnchorList set2) {

        AnchorList output = new AnchorList();

        Anchor left, right;

        int i = 0, j = 0, k, m = set1.size(), n = set2.size();

        while (i != m && j != n) {
            left = set1.getAnchor(i);
            right = set2.getAnchor(j);

            k = left.compareTo(right);
            if (k == -1) { // adjacent is defined only when right > left
                output.add(right);
                i++;
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

    public int size() {
        return anchors.size();
    }

    /**
     * Return the unique set of documents in the anchor list
     *
     * @return the set of unique documents
     */
    public DocList documents() {
        Set<Long> documents = new TreeSet<>();

        Anchor a;
        for (int i = 0; i < anchors.size(); i++) {
            a = getAnchor(i);
            documents.add(a.getDocID());
        }

        DocList list = new DocList();
        list.addAll(documents);

        return list;
    }

    public Anchor getAnchor(int index) {
        return new Anchor(anchors.get(index));
    }

    public void read(InputStream is) throws IOException {

        DataInputStream dis = new DataInputStream(is);

        int size = dis.readInt();   // size of anchor list
        if (size <= 0) {
            throw new IOException("bad anchor list size.");
        }

        byte[] buffer = new byte[size * 8];

        int nread = dis.read(buffer);
        if (nread != buffer.length) {
            throw new IOException("unable to read anchor list.");
        }

        anchors.clear();
        anchors.ensureCapacity(size);

        long anchor;
        for (int i = 0; i < size; i++) {    // convert byte array to long
            anchor = ((long) (buffer[i * 8] & 0xFF)) << 56
                    | ((long) (buffer[i * 8 + 1] & 0xFF)) << 48
                    | ((long) (buffer[i * 8 + 2] & 0xFF)) << 40
                    | ((long) (buffer[i * 8 + 3] & 0xFF)) << 32
                    | ((long) (buffer[i * 8 + 4] & 0xFF)) << 24
                    | ((long) (buffer[i * 8 + 5] & 0xFF)) << 16
                    | ((long) (buffer[i * 8 + 6] & 0xFF)) << 8
                    | ((long) (buffer[i * 8 + 7] & 0xFF));
            anchors.add(anchor);
        }
    }

    public void add(long l) {
        anchors.add(l);
    }

    public void add(Anchor anchor) {
        add(anchor.getAnchorID());
    }
}
