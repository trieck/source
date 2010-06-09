package org.tomrieck.engine;

import java.io.FileReader;
import java.io.IOException;
import java.io.Reader;
import java.math.BigInteger;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class Index {

	private static NoiseList noise;
	private final byte[] rep = new byte[3];
	private final Concordance concord = new Concordance();
	private final Connection conn;

	static {
		try {
			noise = NoiseList.instance();
		} catch (final IOException e) {
			System.err.println(e);
			System.exit(-1);
		}
	}

	public Index() throws SQLException, ClassNotFoundException {
		final String driver = "com.microsoft.jdbc.sqlserver.SQLServerDriver";
		final String datasource = "jdbc:microsoft:sqlserver://localhost:1433;databaseName=bible";

		Class.forName(driver);
		conn = DriverManager.getConnection(datasource, "sa", "tiger929");
	}

	public static void main(String[] args) {
		if (args.length != 1) {
			System.err.println("usage: Index input-file");
			System.exit(1);
		}

		try {
			final Index index = new Index();
			index.index(args[0]);
			index.commit();
		} catch (final IOException e) {
			System.err.println(e);
			System.exit(2);
		} catch (final SQLException e) {
			System.err.println(e);
			System.exit(3);
		} catch (final ClassNotFoundException e) {
			System.err.println(e);
			System.exit(4);
		}
	}

	private void index(String inputFile) throws SQLException, IOException {

		PreparedStatement stmt = conn.prepareStatement("delete from [Verses]");
		stmt.execute();
		stmt.close();

		stmt = conn.prepareStatement("delete from [Books]");
		stmt.execute();
		stmt.close();

		index(new FileReader(inputFile));
	}

	private void index(Reader r) throws SQLException, IOException {

		final Lexer lexer = new Lexer(r);

		final StringBuffer verseText = new StringBuffer();

		String chapterVerse;
		int book = 0, chapter = 0, verse = 0;

		Token token;
		while ((token = lexer.getToken()).getTokenType() != Token.TT_NONE) {

			if (concord.isfull()) {
				concord.blocksave();
			}

			if (token.getTokenType() == Token.TT_BOOK) { // new book
				if (verseText.length() != 0) {
					insertVerse(book, chapter, verse, verseText.toString());
					verseText.setLength(0);
				}

				book = Integer.parseInt(token.getTokenWord(1));
				insertBook(book, token.getTokenWords(2, token
						.getTokenWordCount() - 2));

			} else if (token.getTokenType() == Token.TT_VERSE) { // new verse
				if (verseText.length() != 0) {
					insertVerse(book, chapter, verse, verseText.toString());
				}

				verseText.setLength(0);
				verseText.append(token.getTokenText().substring(8));

				chapterVerse = token.getTokenWord(0);
				chapter = Integer.parseInt(chapterVerse.substring(0, 3));
				verse = Integer.parseInt(chapterVerse.substring(3, 6));
				index(book, chapter, verse, token.getTokenWords(1, token
						.getTokenWordCount() - 1));
			} else {
				verseText.append(' ');
				verseText.append(token.getTokenText().trim());

				index(book, chapter, verse, token.getTokenWords(0, token
						.getTokenWordCount()));
			}
		}

		if (verseText.length() != 0) {
			insertVerse(book, chapter, verse, verseText.toString());
		}

		concord.merge();
	}

	private void insertBook(int booknum, String[] words) throws SQLException {

		final StringBuffer name = new StringBuffer();

		for (int i = 0; i < words.length; i++) {
			if (i > 0) {
				name.append(' ');
			}
			name.append(words[i]);
		}

		final PreparedStatement stmt = conn
				.prepareStatement("INSERT INTO [Books] VALUES(?,?)");

		stmt.setInt(1, booknum);
		stmt.setString(2, name.toString());

		stmt.execute();
	}

	private void insertVerse(int book, int chapter, int verse, String text)
			throws SQLException {

		final PreparedStatement stmt = conn
				.prepareStatement("INSERT INTO [Verses] VALUES(?,?,?,?)");

		stmt.setInt(1, book);
		stmt.setInt(2, chapter);
		stmt.setInt(3, verse);
		stmt.setString(4, text.toString());

		try {
			stmt.execute();
		} catch (final SQLException e) {
			System.err.println("cannot insert verse: " + book + "," + chapter
					+ "," + verse);
			throw e;
		}

		stmt.close();
	}

	private void index(int book, int chapter, int verse, String[] words) {

		for (final String element : words) {
			if (noise.isNoise(element)) {
				continue;
			}

			rep[0] = (byte) book;
			rep[1] = (byte) chapter;
			rep[2] = (byte) verse;

			final BigInteger bi = new BigInteger(rep);

			concord.insert(element, bi.intValue());
		}
	}

	private void commit() throws IOException, SQLException {
		concord.commit(conn);
	}

}
