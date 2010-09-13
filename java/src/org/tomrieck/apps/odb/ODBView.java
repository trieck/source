package org.tomrieck.apps.odb;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ComponentAdapter;
import java.awt.event.ComponentEvent;

public class ODBView extends JScrollPane {

    /**
     *
     */
    private static final long serialVersionUID = 1L;
    private final ODBTable table = new ODBTable();

    private static class WindowResizeManager extends ComponentAdapter {
        @Override
        public void componentResized(ComponentEvent event) {
            final ODBView theView = (ODBView) event.getComponent();
            if (theView.table != null) {
                final Dimension dim = theView.getSize();
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
