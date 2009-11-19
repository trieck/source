package org.trieck.jdbc;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;
import java.util.Iterator;

public abstract class Recordset {
    private Database db;
    private PreparedStmt stmt;
    private ResultSet rs;

    public class Param {
        int type;
        Object data;
        Param(int type, Object data) {
            this.type = type; this.data = data;
        }
    }

    private List<Param> params = new ArrayList<Param>();

    public Recordset(Database db) {
        this.db = db;
        db.open();
    }

    public abstract boolean open();

    public void addParam(int type) {
        params.add(new Param(type, null));
    }

    public void addParam(int type, Object param) {
        params.add(new Param(type, param));
    }

    public void setParam(int index, Object param) {
        if (params.size() < index - 1) throw new IndexOutOfBoundsException();
        Param p = params.get(--index);
        p.data = param;
    }

    protected boolean open(String sql) {
        return open(sql, ResultSet.TYPE_SCROLL_INSENSITIVE, ResultSet.CONCUR_READ_ONLY);
    }

    protected boolean open(String sql, int type, int concurr) {
        close();
        PreparedStmt stmt = db.prepare(sql, type, concurr);
        if (stmt == null) return false;
        prepare(stmt);
        rs = stmt.execute();
        return rs != null;
    }

    public boolean next() {
        try {
            return rs.next();
        } catch (SQLException e) {
            System.err.println(e);
        }

        return false;
    }

    public String getString(int index) {
        try {
            return rs.getString(index);
        } catch (SQLException e) {
            System.err.println(e);
        }

        return "";
    }

    public String getString(String column) {
        try {
            return rs.getString(column);
        } catch (SQLException e) {
            System.err.println(e);
        }

        return "";
    }

    public int getInt(int index) {
        try {
            return rs.getInt(index);
        } catch (SQLException e) {
            System.err.println(e);
        }

        return 0;
    }

    public int getInt(String column) {
        try {
            return rs.getInt(column);
        } catch (SQLException e) {
            System.err.println(e);
        }
        return 0;
    }

    public Object getObject(int index) {
        try {
            return rs.getObject(index);
        } catch (SQLException e) {
            System.err.println(e);
        }

        return 0;
    }

    public Object getObject(String column) {
        try {
            return rs.getObject(column);
        } catch (SQLException e) {
            System.err.println(e);
        }

        return 0;
    }

    public void updateObject(int index, Object data) {
        try {
            rs.updateObject(index, data);
        } catch (SQLException e) {
            System.err.println(e);
        }
    }

    public void updateRow() {
        try {
            rs.updateRow();
        } catch (SQLException e) {
            System.err.println(e);
        }
    }

    private void prepare(PreparedStmt stmt) {
        Iterator<Param> it = params.iterator();
        for (int i = 1; it.hasNext(); i++) {
            Param param = it.next();
            stmt.prepare(i, param);
        }
    }

    public void close() {
        try {
            if (rs != null) rs.close();
            if (stmt != null) stmt.close();
        } catch (SQLException e) { ; }
        rs = null;
        stmt = null;
    }
}
