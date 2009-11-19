package org.trieck.apps.odb;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.List;
import java.util.Vector;

import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
import javax.swing.table.AbstractTableModel;

public class ODBTableModel extends AbstractTableModel implements
		ChangeListener, ActionListener {
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;

	private static final String[] HEADERS = new String[] { "ID", "Value",
			"Type", "Create Date", "Last Accessed" };

	private static final int ID_COL = 0;
	private static final int VAL_COL = 1;
	private static final int TYPE_COL = 2;
	private static final int CREATE_DT_COL = 3;
	private static final int LAST_ACCESSED_COL = 4;

	public static final String NEW_RESPONSE = "newResponse";

	private final List<RowData> data = new Vector<RowData>(); // row data

	public ODBTableModel() {
	}

	public int getColumnCount() {
		return HEADERS.length;
	}

	public int getRowCount() {
		return data.size();
	}

	@Override
	public String getColumnName(int column) {
		return HEADERS[column];
	}

	@Override
	public boolean isCellEditable(int row, int col) {
		return false;
	}

	public Object getValueAt(int row, int col) {
		if (row >= data.size()) {
			return null;
		}

		final RowData r = data.get(row);

		switch (col) {
		case ID_COL:
			return r.getId();
		case VAL_COL:
			return r.getVal();
		case TYPE_COL:
			return "000";
		case CREATE_DT_COL:
			return "--";
		case LAST_ACCESSED_COL:
			return "--";
		}

		return null;
	}

	@Override
	public void setValueAt(Object value, int row, int col) {
	}

	public void stateChanged(ChangeEvent event) {
		fireTableDataChanged();
	}

	public void actionPerformed(ActionEvent e) {
		final String command = e.getActionCommand();
		if (command.equals(NEW_RESPONSE)) {
			data.add((RowData) e.getSource());
			fireTableRowsInserted(data.size() - 1, data.size() - 1);
		}
	}

	public void deleteAllRows() {
		final int size = data.size();
		if (size > 0) {
			data.clear();
			fireTableRowsDeleted(0, size - 1);
		}
	}

}
