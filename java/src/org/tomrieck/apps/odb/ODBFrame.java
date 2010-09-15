package org.pixielib.apps.odb;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ComponentAdapter;
import java.awt.event.ComponentEvent;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

public class ODBFrame extends JFrame {

    /**
     *
     */
    private static final long serialVersionUID = 1L;
    private static final ODBManager theApp = ODBManager.getInstance();
    private static final String TITLE = "Object Database Manager";

    private ODBView theView = null;

    /** static initialization */
    static {
        JFrame.setDefaultLookAndFeelDecorated(true);
    }

    private static class WindowCloseManager extends WindowAdapter {
        @Override
        public void windowClosing(WindowEvent e) {
            theApp.exit(0);
        }
    }

    private static class WindowResizeManager extends ComponentAdapter {
        @Override
        public void componentResized(ComponentEvent event) {
            final ODBFrame theFrame = (ODBFrame) event.getComponent();
            if (theFrame.theView != null) {
                final Dimension dim = theFrame.getSize();
                theFrame.theView.setPreferredSize(dim);
            }
        }
    }

    /**
     * Public ctor
     */
    public ODBFrame() {
        super(TITLE);
        setIconImage(new ImageIcon(theApp.getResource("app.gif")).getImage());
        setResizable(true);
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        addWindowListener(new WindowCloseManager());
        addComponentListener(new WindowResizeManager());
        initComponents();
        setLocationRelativeTo(null);
    }

    private void initComponents() {
        final JPanel content = new JPanel(new GridLayout(1, 0));
        content.setOpaque(true);

        theView = new ODBView();
        content.add(theView);

        setContentPane(content);
        pack();
    }

    public ODBTable getTable() {
        return theView.getTable();
    }
}
