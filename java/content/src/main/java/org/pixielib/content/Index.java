package org.pixielib.content;

import org.pixielib.util.DoubleHash64;

import java.io.*;
import java.nio.channels.Channels;
import java.util.Iterator;

public class Index {

	public static final int MAGIC_NO = 0xc001d00d;  // file magic number
	private Repository repos;                       // content repository
	private Concordance concord;                    // term concordance

	public Index() throws IOException {
		concord = new Concordance();
		repos = Repository.getInstance();
	}

	/* combine concordance and hash table into final index */
	@SuppressWarnings("ConvertToTryWithResources")
	public void write(String db, IndexFields fields) throws IOException {

		// merge concordance blocks
		String concordFile = concord.merge();

		File outfile = repos.getIndexPath(db);

		outfile.delete();
		
		RandomAccessFile ofile = new RandomAccessFile(outfile, "rw");
		DataInputStream dis = new DataInputStream(new FileInputStream(concordFile));

		// write file magic number
		ofile.writeInt(MAGIC_NO);

		// write the number of index fields
		ofile.writeInt(fields.size());

		// write index fields
		Iterator<String> it = fields.iterator();
		while (it.hasNext()) {
			ofile.writeUTF(it.next());
		}

		// write the total number of terms
		long term_count_offset = ofile.getFilePointer();
		ofile.writeInt(0); // not yet known

		// write the size of the hash table
		long hash_table_size_offset = ofile.getFilePointer();
		ofile.writeLong(0); // not yet known

		// write the offset to the hash table
		long hash_table_offset = ofile.getFilePointer();
		ofile.writeLong(0); // not yet known

		// concordance offset
		long concord_offset = ofile.getFilePointer();
		
		// write terms & anchors
		int n, nterms;
		String term;

		OutputStream os = Channels.newOutputStream(ofile.getChannel());
		for (nterms = 0; dis.available() > 0; nterms++) {
			term = dis.readUTF();

			// read the anchor list size
			n = dis.readInt();

			// write the term
			ofile.writeUTF(term);

			// write the anchor list size
			ofile.writeInt(n);

			// transfer the anchor list
			IOUtil.transfer(dis, os, n * 8);
		}

		dis.close();

		// generate the hash table

		// hash table location
		long hash_table_area = ofile.getFilePointer();

		// write the total term count
		ofile.seek(term_count_offset);
		ofile.writeInt(nterms);

		// compute the size of the hash table and store it
		long tableSize = Prime.prime(nterms);
		ofile.seek(hash_table_size_offset);
		ofile.writeLong(tableSize);

		// write the offset to the hash table
		ofile.seek(hash_table_offset);
		ofile.writeLong(hash_table_area);
		ofile.seek(hash_table_area); // jump back

		// expand file to make space for hash table
		long newLength = ofile.length() + (tableSize * 8);
		ofile.setLength(newLength);

		// need to ensure the hash table is empty
		IOUtil.fill(os, tableSize * 8, (byte) 0);

		// we need two file pointers to the output file
		// in order to generate the hash table
		RandomAccessFile infile = new RandomAccessFile(outfile, "r");

		// seek to the concordance
		infile.seek(concord_offset);

		long h, offset, term_offset = concord_offset;
		int vsize;
		for (long i = 0; i < nterms; i++) {
			term = infile.readUTF();

			h = hash(term, tableSize);

			// collisions are resolved via linear-probing
			for (;;) {
				offset = hash_table_area + (h * 8);

				ofile.seek(offset);
				if (ofile.readLong() == 0) {
					break;
				}

				h = (h + 1) % tableSize;
			}

			ofile.seek(offset);
			ofile.writeLong(term_offset);

			// anchor list size
			vsize = infile.readInt() * 8;
			infile.skipBytes(vsize);

			// next term offset
			term_offset = infile.getFilePointer();
		}
		infile.close();
		ofile.close();
	}

	public void insert(String term, long anchor)
					throws IOException {
		concord.insert(term, anchor);
	}

	public static long hash(String term, long size) {
		return (DoubleHash64.hash(term) & 0x7FFFFFFFFFFFFFFFL) % size;
	}
}
