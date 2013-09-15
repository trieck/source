package org.pixielib.content;

import java.io.*;
import java.util.ArrayList;
import java.util.List;

public class ConcordMerge {

	private static final int NWAY = 100;                    // number of ways to merge
	private static final String TERM_EOF = "\uFFFF";        // EOF indictator

	private DataOutputStream out;                           // output stream for merge
	private ConcordRecord[] records;                        // concordance records for least
	private int pass;                                       // countdown of pass number

	public ConcordMerge() {
		records = new ConcordRecord[NWAY + 1];
	}

	public String merge(List<String> files) throws IOException {
		pass = countPasses(files.size());
		return mergeMany(files, 0, files.size());
	}

	private static int countPasses(int argc) {
		int i = 0;

		if (argc <= NWAY)
			return 1;

		while (argc > 0) {
			i++;
			argc -= Math.min(argc, NWAY);
		}

		return i + countPasses(i);
	}

	private String mergeMany(List<String> files, int offset, int argc) throws IOException {
		if (argc <= NWAY) {
			return mergeOnce(files, offset, argc);
		}

		List<String> outfiles = new ArrayList<>();

		int i, n;
		for (i = 0; argc > 0; offset += n, argc -= n, i++) {
			n = Math.min(argc, NWAY);
			outfiles.add(mergeOnce(files, offset, n));
		}

		return mergeMany(outfiles, 0, i);
	}

	private String mergeOnce(List<String> files, int offset, int argc) throws IOException {

		pass--;

		File file = File.createTempFile("conc", "dat");
		file.deleteOnExit();

		out = new DataOutputStream(new FileOutputStream(file));

		final int save = offset;    // remember the offset

		ConcordRecord[] recs = new ConcordRecord[argc + 1];

		int i, j;
		for (i = 0; i < argc; i++, offset++) {
			recs[i] = new ConcordRecord();
			recs[i].stream = new DataInputStream(new FileInputStream(files.get(offset)));
		}

		recs[argc] = null;

		ConcordRecord[] list = recs;

		while (read(list)) {
			list = least(recs);
			write(list);
		}

		File infile;
		for (i = 0, j = save; i < argc; i++, j++) {
			recs[i].stream.close();
			recs[i].stream = null;
			infile = new File(files.get(j));
			infile.delete();
		}

		out.close();
		out = null;

		return file.getAbsolutePath();
	}

	private boolean read(ConcordRecord[] recs) throws IOException {

		for (int i = 0; recs[i] != null; i++) {
			if (recs[i].term.equals(TERM_EOF))
				return false;

			// read term
			recs[i].term = IOUtil.readString(recs[i].stream);
			if (recs[i].term.length() == 0) {   // EOF
				recs[i].term = TERM_EOF;
				recs[i].size = 0;
				continue;
			}

			// read size of anchor list
			recs[i].size = recs[i].stream.readInt();
		}

		return true;
	}

	private ConcordRecord[] least(ConcordRecord[] recs) {

		int j = 0, k = 0;
		int c;

		for (int i = 0; recs[i] != null; i++) {
			c = recs[i].term.compareTo(recs[k].term);
			if (c < 0) {    // less than
				k = i;
				j = 0;
				records[j++] = recs[i];
			} else if (c == 0) {    // equal to
				records[j++] = recs[i];
			}
		}

		records[j] = null;

		return records;
	}

	private void write(ConcordRecord[] recs) throws IOException {
		if (recs[0].term.equals(TERM_EOF))
			return;

		IOUtil.writeString(out, recs[0].term);

		int i, size = 0;
		for (i = 0; recs[i] != null; i++) {
			size += recs[i].size;
		}

		// write anchor list size
		out.writeInt(size);

		for (i = 0; recs[i] != null; i++) {
			IOUtil.transfer(recs[i].stream, out, recs[i].size * 8);
		}
	}
}
