package org.tomrieck.content;

import java.io.DataOutputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.nio.LongBuffer;

public class Inverter {

    /**
     * maximum amount of memory available for concordance
     */
    private static final int MEMORY_SIZE = 67108864;

    /**
     * average record size
     */
    private static final int AVERAGE_SIZE = 50;

    /**
     * maximum number of records
     */
    private static final int MAX_COUNT = MEMORY_SIZE / AVERAGE_SIZE;

    private static final int FILL_RATIO = 2;

    private IndexRecs records;
    private int count;
    private int size;

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
    }

    public void write(OutputStream os) throws IOException {
        compact();
        sort();

        final DataOutputStream dos = new DataOutputStream(os);

        String term;
        LongBuffer locations;

        for (int i = 0; i < count; i++) {
            term = records.getTerm(i);
            locations = records.getLocations(i);

            dos.writeInt(term.length()); // length of term
            dos.write(term.getBytes()); // term bytes

            dos.writeInt(locations.position()); // length of doclist
            for (int j = 0; j < locations.position(); j++) {
                dos.writeLong(locations.get(j)); // documents
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
        records = IndexRecs.allocate(size);
    }

    private int lookup(String term) {

        int i = (int) (Hash32.hash(term) % size);

        while (!records.isEmpty(i) && !records.getTerm(i).equals(term)) {
            i = (i + 1) % size;
        }

        return i;
	}
}
