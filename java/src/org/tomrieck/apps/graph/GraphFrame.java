package org.tomrieck.apps.graph;

import org.tomrieck.ui.StatusPanel;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;

public class GraphFrame extends JFrame {

    /**
     *
     */
    private static final long serialVersionUID = 1L;
    private static final String title = "Graph";
    private static final String MENU_FILE = "File";
    private static final String MENU_OPTIONS = "Options";
    private static final String ITEM_EXIT = "Exit";
    private static final String ITEM_COLORS = "Colors";

    private StatusPanel status = null;

    /** static initialization */
    static {
        JFrame.setDefaultLookAndFeelDecorated(true);
        JDialog.setDefaultLookAndFeelDecorated(true);
    }

    private final ActionListener ITEM_EXIT_LISTENER = new ActionListener() {
        public void actionPerformed(ActionEvent e) {
            System.exit(0);
        }
    };

    private final ActionListener ITEM_COLORS_LISTENER = new ActionListener() {
        public void actionPerformed(ActionEvent e) {
            ColorChooserDlg dlg = new ColorChooserDlg(GraphFrame.this);
            dlg.showModal();
        }
    };

    /**
     * Public ctor
     */
    public GraphFrame() {
        super(title);
        init();
    }

    private void init() {
        setResizable(false);
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        initComponents();
        setLocationRelativeTo(null);
    }

    /**
     * Initialize components
     */
    private void initComponents() {

        initMenu();

        final JPanel content = new JPanel(new BorderLayout());
        content.setOpaque(true);
        setContentPane(content);

        final GraphView view = new GraphView();
        content.add(view, BorderLayout.CENTER);

        status = new StatusPanel();
        status.setGripper(true);
        content.add(status, BorderLayout.SOUTH);

        pack();
    }

    private void initMenu() {
        final JMenuBar bar = new JMenuBar();

        JMenu menu = new JMenu(MENU_FILE);
        menu.setMnemonic(KeyEvent.VK_F);
        bar.add(menu);

        JMenuItem item = new JMenuItem(ITEM_EXIT, KeyEvent.VK_X);
        item.addActionListener(ITEM_EXIT_LISTENER);
        menu.add(item);

        menu = new JMenu(MENU_OPTIONS);
        menu.setMnemonic(KeyEvent.VK_O);
        bar.add(menu);

        item = new JMenuItem(ITEM_COLORS, KeyEvent.VK_C);
        item.addActionListener(ITEM_COLORS_LISTENER);
        menu.add(item);

        setJMenuBar(bar);
    }

    public void setStatusText(String text) {
        status.setText(text);
    }

}
