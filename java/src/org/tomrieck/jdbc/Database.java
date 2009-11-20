package org.tomrieck.jdbc;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;

public abstract class Database {

	private Connection conn = null;

	public Database() {
	}

	protected abstract String getUID();

	protected abstract String getPWD();

	protected abstract String getURL();

	public boolean open() {
		close();
		try {
			conn = DriverManager.getConnection(getURL(), getUID(), getPWD());
		} catch (final SQLException e) {
			System.err.println(e);
			return false;
		}

		return true;
	}

	public void close() {
		if (conn != null) {
			try {
				conn.close();
			} catch (final SQLException e) {
				;
			}
			conn = null;
		}
	}

	public PreparedStmt prepare(String sql, int type, int concurr) {
		try {
			return new PreparedStmt(conn, sql, type, concurr);
		} catch (final SQLException e) {
			System.err.println(e);
		}
		return null;
	}

	public PreparedStmt prepare(String sql) {
		return prepare(sql, ResultSet.TYPE_SCROLL_INSENSITIVE,
				ResultSet.CONCUR_READ_ONLY);
	}
}
