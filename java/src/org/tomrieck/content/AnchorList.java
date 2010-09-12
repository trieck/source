package org.tomrieck.content;

import java.io.DataInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.util.*;

public class AnchorList {

    private ArrayList<Long> anchors = new ArrayList<Long>();

    public AnchorList() {
    }

    public int size() {
        return anchors.size();
    }

    public AnchorList slice(int start, int count) {
        start = Math.min(start, anchors.size() - 1);
        start = Math.max(0, start);

        count = Math.min(count, anchors.size() - start);
        count = Math.max(0, count);

        AnchorList slice = new AnchorList();
        slice.anchors.addAll(anchors.subList(start, start+count));
        
        return slice;
    }

    /**
     * Return the unique set of documents in the anchor list
     * @return the set of unique documents
     */
    public DocList documents() {
        Set<Integer> documents = new TreeSet<Integer>();

        Anchor a;
        for (int i = 0; i < anchors.size(); i++) {
            a = getAnchor(i);
            documents.add(a.getDocNum());
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
        if (size <=0) {
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
            anchor = ((long)(buffer[i * 8] & 0xFF)) << 56
                    | ((long)(buffer[i * 8 + 1] & 0xFF)) << 48
                    | ((long)(buffer[i * 8 + 2] & 0xFF)) << 40
                    | ((long)(buffer[i * 8 + 3] & 0xFF)) << 32
                    | (buffer[i * 8 + 4] & 0xFF) << 24
                    | (buffer[i * 8 + 5] & 0xFF) << 16
                    | (buffer[i * 8 + 6] & 0xFF) << 8
                    | (buffer[i * 8 + 7] & 0xFF);
            anchors.add(anchor);
        }
    }

    public void add(long l) {
        anchors.add(l);
    }

    public void add(Anchor anchor) {
        add(anchor.getAnchorID());
    }

    public static AnchorList intersection(AnchorList set1, AnchorList set2) {
        AnchorList output = new AnchorList();

        Anchor left, right;

        int i = 0, j = 0, k, m = set1.size(), n = set2.size();
        int leftdoc, rightdoc;

        while (i != m && j != n) {
            left = set1.getAnchor(i);
            right = set2.getAnchor(j);

            leftdoc = left.getDocNum();
            rightdoc = right.getDocNum();

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
}
