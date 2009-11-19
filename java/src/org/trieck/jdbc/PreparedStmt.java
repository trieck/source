package org.trieck.jdbc;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class PreparedStmt {

	private final PreparedStatement stmt;

	public PreparedStmt(Connection conn, String sql) throws SQLException {
		stmt = conn.prepareStatement(sql);
	}

	public PreparedStmt(Connection conn, String sql, int type, int concurr)
			throws SQLException {
		stmt = conn.prepareStatement(sql, type, concurr);
	}

	public void close() {
		try {
			if (stmt != null) {
				stmt.close();
			}
		} catch (final SQLException e) {
			System.err.println(e);
		}
	}

	void prepare(int index, Recordset.Param param) {
		try {
			switch (param.type) {
			case java.sql.Types.INTEGER:
				stmt.setInt(index, (Integer) param.data);
				break;
			case java.sql.Types.VARCHAR:
				stmt.setString(index, (String) param.data);
				break;
			case java.sql.Types.JAVA_OBJECT:
				stmt.setObject(index, param.data);
			default:
				throw new IllegalArgumentException(
						"unsupported java.sql.Types type");
			}
		} catch (final SQLException e) {
			System.err.println(e);
		}
	}

	public ResultSet execute() {
		try {
			return stmt.executeQuery();
		} catch (final SQLException e) {
			System.err.println(e);
		}

		return null;
	}
}
