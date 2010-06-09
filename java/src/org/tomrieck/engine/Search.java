package org.tomrieck.engine;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class Search {

	private final Connection conn;

	public Search() throws SQLException, ClassNotFoundException {
		final String driver = "com.microsoft.jdbc.sqlserver.SQLServerDriver";
		final String datasource = "jdbc:microsoft:sqlserver://localhost:1433;databaseName=bible";

		Class.forName(driver);
		conn = DriverManager.getConnection(datasource, "sa", "tiger929");
	}

	public static void main(String[] args) {
		if (args.length < 1) {
			System.err.println("usage: Search term(s)");
			System.exit(1);
		}

		try {
			final Search search = new Search();
			search.search(args);
		} catch (final SQLException e) {
			System.err.println(e);
			System.exit(2);
		} catch (final ClassNotFoundException e) {
			System.err.println(e);
			System.exit(3);
		}
	}

	public void search(String[] terms) throws SQLException {
		DocList docs = new DocList();

		for (int i = 0; i < terms.length; i++) {
			if (i == 0) {
				docs = search(terms[i]);
			} else {
				docs = DocList.intersection(docs, search(terms[i]));
			}
		}

		results(docs);
	}

	public DocList search(String term) throws SQLException {
		DocList results = new DocList();

		final PreparedStatement stmt = conn
				.prepareStatement("select doclist from [index] where term = ?");
		stmt.setString(1, term);

		final ResultSet rs = stmt.executeQuery();
		if (rs.next()) {
			results = new DocList(rs.getBytes(1));
		}

		rs.close();
		stmt.close();

		return results;
	}

	private void results(DocList docs) throws SQLException {
		int book, chapter, verse;

		int document;
		for (int i = 0; i < docs.length(); i++) {
			document = docs.getDoc(i);
			book = (document & 0xFF0000) >> 16;
			chapter = (document & 0xFF00) >> 8;
			verse = document & 0xFF;
			results(book, chapter, verse);
		}
	}

	private void results(int book, int chapter, int verse) throws SQLException {
		PreparedStatement stmt = conn
				.prepareStatement("select name from [Books] where booknum = ?");
		stmt.setInt(1, book);
		ResultSet rs = stmt.executeQuery();
		if (!rs.next()) {
			throw new SQLException("can't find book!");
		}

		final String bookName = rs.getString(1);
		rs.close();
		stmt.close();

		stmt = conn
				.prepareStatement("select text from [verses] where book = ? and chapter = ? and verse = ?");
		stmt.setInt(1, book);
		stmt.setInt(2, chapter);
		stmt.setInt(3, verse);

		rs = stmt.executeQuery();
		if (!rs.next()) {
			throw new SQLException("can't find document!");
		}

		final String text = rs.getString(1);

		System.out.print(bookName + "(" + chapter + ":" + verse + "): ");
		System.out.println(text);
		System.out.println();

		rs.close();
		stmt.close();

	}
}
