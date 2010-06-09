package org.tomrieck.engine;

import java.nio.IntBuffer;
import java.util.Arrays;

public class Table {

	private static final int INITIAL_SIZE = 80;

	private class Record implements Comparable<Record> {
		String term;
		IntBuffer buffer;

		public int compareTo(Record o) {
			return term.compareTo(o.term);
		}
	}

	private Record[] records;

	private int size;

	private Table() {
	}

	public static Table allocate(int size) {
		final Table table = new Table();
		table.size = size;
		table.records = new Record[table.size = size];
		return table;
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

	public IntBuffer getDocList(int index) {
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

		records[index] = new Record();
		records[index].buffer = IntBuffer.allocate(INITIAL_SIZE);
		records[index].term = new String(term);
	}

	public void putDoc(int index, int doc) {
		if (index < 0 || index >= records.length) {
			throw new IllegalArgumentException();
		}

		assert (records[index] != null);

		IntBuffer buffer = records[index].buffer;
		if (buffer.position() > 0) {
			if (buffer.get(buffer.position() - 1) == doc) {
				return; // exists
			}
		}

		if (!buffer.hasRemaining()) { // reallocate
			reallocate(index);
			buffer = records[index].buffer;
		}

		buffer.put(doc);
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
		final IntBuffer buffer = records[index].buffer;
		assert (!buffer.hasRemaining());

		final IntBuffer newBuffer = IntBuffer.allocate(buffer.capacity() * 2);
		newBuffer.put(buffer.array());

		records[index].buffer = newBuffer;
	}
}
