package org.tomrieck.apps.odb;

import java.awt.Dimension;
import java.awt.Font;
import java.awt.Insets;
import java.awt.Rectangle;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JTable;

public class ODBTable extends JTable implements ActionListener {

    /**
     *
     */
    private static final long serialVersionUID = 1L;
    private static final int CX = 600, CY = 300;
    private static final Dimension TABLE_DIMS = new Dimension(CX, CY);
    private static final int TRUNCATION_POINT = 50;

    private final Font font = new Font("Courier New", Font.PLAIN, 11);

    private final ODBTableModel model = new ODBTableModel();

    public ODBTable() {
        setPreferredSize(TABLE_DIMS);
        setPreferredScrollableViewportSize(TABLE_DIMS);
        setFont(font);
        setModel(model);
    }

    public void actionPerformed(ActionEvent e) {
        synchronized (this) {
            if (getRowCount() >= TRUNCATION_POINT) {
                deleteAll();
            }

            model.actionPerformed(e);

            // scroll to newly inserted row
            makeRowVisible(getRowCount() - 1);
        }
    }

    public void makeRowVisible(int row) {
        final int height = getRowHeight() * getRowCount();
        final Dimension dim = getPreferredScrollableViewportSize();
        if (height > dim.height) {
            dim.height += height - dim.height;
            setPreferredScrollableViewportSize(dim);
            setPreferredSize(dim);
        } else if (height < dim.height) {
            dim.height -= dim.height - height;
            setPreferredScrollableViewportSize(dim);
            setPreferredSize(dim);
        }

        scrollRectToVisible(getRowBounds(row));
        clearSelection();
        setRowSelectionInterval(row, row);
        model.fireTableDataChanged();
    }

    private Rectangle getRowBounds(int row) {
        final Rectangle result = getCellRect(row, -1, true);
        final Insets i = getInsets();
        result.x = i.left;
        result.width = getWidth() - i.left - i.right;
        return result;
    }

    public void deleteAll() {
        model.deleteAllRows();
    }
}
