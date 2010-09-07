package org.tomrieck.content;

import java.nio.LongBuffer;
import java.util.Arrays;

/**
 * Open addressed hash table of inverter records
 */
public class InverterRecs {

    /**
     * default buffer size
     */
    private static final int DEF_BUF_SIZE = 80;

    private InverterRecord[] records;
    private int size;   // size of table, should be prime

    private InverterRecs() {
    }

    public static InverterRecs allocate(int size) {
        InverterRecs recs = new InverterRecs();
        recs.size = size;
        recs.records = new InverterRecord[size];
        return recs;
    }

    public boolean isEmpty(int index) {
        if (index < 0 || index >= records.length) {
            throw new IllegalArgumentException();
        }

        return records[index] == null;
    }

    public String getTerm(int index) {
        if (index < 0 || index >= records.length) {
            throw new IllegalArgumentException();
        }

        return records[index].term;
    }

    public LongBuffer getLocations(int index) {
        if (index < 0 || index >= records.length) {
            throw new IllegalArgumentException();
        }

        return records[index].buffer;
    }

    public void put(int index, String term) {
        if (index < 0 || index >= records.length) {
            throw new IllegalArgumentException();
        }

        assert (records[index] == null);

        records[index] = new InverterRecord();
        records[index].buffer = LongBuffer.allocate(DEF_BUF_SIZE);
        records[index].term = new String(term);
    }

    public void insert(int index, int docnum, int wordnum) {
        if (index < 0 || index >= records.length) {
            throw new IllegalArgumentException();
        }

        assert (records[index] != null);

        long location = (docnum << 32) | wordnum;

        LongBuffer buffer = records[index].buffer;
        if (buffer.position() > 0) {
            if (buffer.get(buffer.position() - 1) == location) {
                return; // exists
            }
        }

        if (!buffer.hasRemaining()) { // reallocate
            reallocate(index);
            buffer = records[index].buffer;
        }

        buffer.put(location);
    }

    public void compact() {
        for (int i = 0, j = 0; i < records.length; i++) {
            if (records[i] != null) {
                continue;
            }

            for (; j < records.length; j++) {
                if (j > i && records[j] != null) {
                    break;
                }
            }

            if (j >= records.length) {
                break;
            }

            records[i] = records[j];
            records[j] = null;
        }
    }

    /* must be compacted first */

    public void sort(int count) {
        Arrays.sort(records, 0, count);
    }

    public void clear() {
        for (int i = 0; i < size; i++) {
            records[i] = null;
        }
    }

    private void reallocate(int index) {
        LongBuffer buffer = records[index].buffer;
        assert (!buffer.hasRemaining());

        LongBuffer newBuffer = LongBuffer.allocate(buffer.capacity() * 2);
        newBuffer.put(buffer.array());

        records[index].buffer = newBuffer;
    }
}
