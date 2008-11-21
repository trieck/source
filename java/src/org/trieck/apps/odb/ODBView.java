package org.trieck.apps.odb;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ComponentAdapter;
import java.awt.event.ComponentEvent;

public class ODBView extends JScrollPane {

    private ODBTable table = new ODBTable();

    private static class WindowResizeManager extends ComponentAdapter {
        public void componentResized(ComponentEvent event) {
            ODBView theView = (ODBView) event.getComponent();
            if (theView.table != null) {
                Dimension dim = theView.getSize();
                theView.table.setPreferredSize(dim);
            }
        }
    }

    public ODBView() {
        addComponentListener(new WindowResizeManager());
        setOpaque(true);
        setViewportView(table);
    }

    public ODBTable getTable() {
        return table;
    }

}
