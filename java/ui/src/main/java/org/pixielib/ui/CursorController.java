package org.pixielib.ui;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public final class CursorController {

    public final static Cursor busyCursor = Cursor
            .getPredefinedCursor(Cursor.WAIT_CURSOR);
    public final static Cursor defaultCursor = Cursor.getDefaultCursor();

    private CursorController() {
    }

    public static ActionListener createListener(final Component component,
                                                final ActionListener mainActionListener) {
        final ActionListener actionListener = new ActionListener() {
            public void actionPerformed(ActionEvent ae) {
                try {
                    component.setCursor(busyCursor);
                    mainActionListener.actionPerformed(ae);
                } finally {
                    component.setCursor(defaultCursor);
                }
            }
        };
        return actionListener;
    }
}
