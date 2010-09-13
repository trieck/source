package org.tomrieck.apps;

import org.tomrieck.ui.StatusPanel;

import javax.swing.*;
import java.awt.*;

public class StatusFrame extends JFrame {

    /**
     *
     */
    private static final long serialVersionUID = 1L;
    private static final String title = "Test App";
    private static final Dimension dimensions = new Dimension(400, 200);

    /** static initialization */
    static {
        JFrame.setDefaultLookAndFeelDecorated(true);
    }

    /**
     * Public ctor
     */
    public StatusFrame() {
        super(title);
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        initComponents();
        setLocationRelativeTo(null);
    }

    /**
     * Initialize components
     */
    private void initComponents() {
        final JPanel content = new JPanel(new BorderLayout());
        content.setPreferredSize(dimensions);
        setContentPane(content);

        final JPanel innerPane = new JPanel();
        innerPane.setBorder(BorderFactory.createLoweredBevelBorder());
        content.add(innerPane, BorderLayout.CENTER);

        final StatusPanel status = new StatusPanel();
        content.add(status, BorderLayout.SOUTH);
        pack();
    }
}
