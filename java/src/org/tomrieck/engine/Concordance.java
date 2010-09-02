package org.tomrieck.bible;

import java.io.DataInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

public class Concordance {

	private static final String CONCORD_MASTER = "d:/bible/concord.idx";
	private final Inverter block = new Inverter();
	private final List<String> filenames = new ArrayList<String>();

	public Concordance() {
	}

	public boolean isfull() {
		return block.isfull();
	}

	public void insert(String term, int docnum) {
		block.insert(term, docnum);
	}

	public void blocksave() throws IOException {
		if (block.getCount() == 0) {
			return;
		}

		final File file = File.createTempFile("conc", "ndx");
		file.deleteOnExit();

		final FileOutputStream os = new FileOutputStream(file);
		filenames.add(file.getAbsolutePath());

		block.write(os);

		os.close();
	}

	public void merge() throws IOException {
		blocksave();

		if (filenames.size() == 0) {
			return;
		}

		final File oldFile = new File(filenames.get(0)); // first file
		final File newFile = new File(CONCORD_MASTER);

		newFile.delete();
		oldFile.renameTo(newFile);
	}

	public void commit(Connection conn) throws IOException, SQLException {
		final File concord = new File(CONCORD_MASTER);
		final DataInputStream dis = new DataInputStream(new FileInputStream(
				concord));

		PreparedStatement stmt = conn.prepareStatement("DELETE FROM [index]");
		stmt.execute();
		stmt.close();

		stmt = conn.prepareStatement("INSERT INTO [index] VALUES(?,?)");

		int length;
		byte[] bterm;
		byte[] doclist;
		String term;

		while (dis.available() > 0) {
			length = dis.readInt(); // term length
			bterm = new byte[length];
			dis.read(bterm); // read term
			term = new String(bterm);

			length = dis.readInt() * 4; // document vector length
			doclist = new byte[length];

			dis.read(doclist);

			stmt.setString(1, term);
			stmt.setBytes(2, doclist);

			stmt.execute();
		}

		stmt.close();
		conn.close();

	}
}
