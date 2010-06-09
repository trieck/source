package org.tomrieck.engine;

import java.io.DataOutputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.nio.IntBuffer;

public class Inverter {

	/** maximum amount of memory available for concordance */
	private static final int MEMORY_SIZE = 67108864;

	/** average record size */
	private static final int AVERAGE_SIZE = 50;

	/** maximum number of records */
	private static final int MAX_COUNT = MEMORY_SIZE / AVERAGE_SIZE;

	private static final int FILL_RATIO = 2;

	private final int size;
	private int count;

	private Table table;

	public Inverter() {
		size = (int) Prime.prime(FILL_RATIO * MAX_COUNT);
		count = 0;
	}

	public int getCount() {
		return count;
	}

	public boolean isfull() {
		return count >= MAX_COUNT;
	}

	private void compact() {
		table.compact();
	}

	private void sort() {
		table.sort(count);
	}

	private void clear() {
		table.clear();
	}

	public void write(OutputStream os) throws IOException {
		compact();
		sort();

		final DataOutputStream dos = new DataOutputStream(os);

		String term;
		IntBuffer doclist;

		for (int i = 0; i < count; i++) {
			term = table.getTerm(i);
			doclist = table.getDocList(i);

			dos.writeInt(term.length()); // length of term
			dos.write(term.getBytes()); // term bytes

			dos.writeInt(doclist.position()); // length of doclist
			for (int j = 0; j < doclist.position(); j++) {
				dos.writeInt(doclist.get(j)); // documents
			}
		}

		clear();
	}

	public void insert(String term, int doc) {

		if (table == null) {
			alloc();
		}

		final int i = lookup(term);

		if (table.isEmpty(i)) {
			table.put(i, term);
			count++;
		}

		table.putDoc(i, doc);
	}

	private void alloc() {
		table = Table.allocate(size);
	}

	private int lookup(String term) {

		int i = (int) (Hash32.hash(term) % size);

		while (!table.isEmpty(i) && !table.getTerm(i).equals(term)) {
			i = (i + 1) % size;
		}

		return i;
	}

}
