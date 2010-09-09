package org.tomrieck.content;

import org.tomrieck.util.Hash32;

import java.io.DataOutputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.nio.LongBuffer;

public class Inverter {

    private static final int MAX_COUNT = 100000;    // max. number of index records
    private static final int FILL_RATIO = 2;

    private InverterRecs records;   // hash table of records
    private int count;              // number of records in table
    private int size;               // size of hash table, should be prime

    public Inverter() {
        size = (int) Prime.prime(FILL_RATIO * MAX_COUNT);
        count = 0;
    }

    public int getCount() {
        return count;
    }

    public boolean isFull() {
        return count >= MAX_COUNT;
    }

    private void compact() {
        records.compact();
    }

    private void sort() {
        records.sort(count);
    }

    private void clear() {
        records.clear();
        count = 0;
    }

    public void write(OutputStream os) throws IOException {
        compact();
        sort();

        final DataOutputStream dos = new DataOutputStream(os);

        String term;
        LongBuffer anchors;

        for (int i = 0; i < count; i++) {
            term = records.getTerm(i);
            anchors = records.getAnchors(i);

            IOUtil.writeString(dos, term);
            dos.writeInt(anchors.position()); // size of anchor list

            for (int j = 0; j < anchors.position(); j++) {
                dos.writeLong(anchors.get(j)); // anchor
            }
        }

        clear();
    }

    public void insert(String term, int docnum, int wordnum) {

        if (records == null) {
            alloc();
        }

        int i = lookup(term);

        if (records.isEmpty(i)) {
            records.put(i, term);
            count++;
        }

        records.insert(i, docnum, wordnum);
    }

    private void alloc() {
        records = InverterRecs.allocate(size);
    }

    private int lookup(String term) {

        int i = (int) (Hash32.hash(term) % size);

        while (!records.isEmpty(i) && !records.getTerm(i).equals(term)) {
            i = (i + 1) % size;
        }

        return i;
    }
}
