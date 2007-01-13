package org.trieck.jdbc;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.sql.ResultSet;

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
        } catch (SQLException e) {
            System.err.println(e);
            return false;
        }

        return true;
    }

    public void close() {
        if (conn != null) {
            try { conn.close(); }
            catch (SQLException e) {
                ;
            }
            conn = null;
        }
    }

    public PreparedStmt prepare(String sql, int type, int concurr) {
        try {
            return new PreparedStmt(conn, sql, type, concurr);
        } catch (SQLException e) {
            System.err.println(e);
        }
        return null;
    }

    public PreparedStmt prepare(String sql) {
        return prepare(sql, ResultSet.TYPE_SCROLL_INSENSITIVE, ResultSet.CONCUR_READ_ONLY);
    }
}
