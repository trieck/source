package org.trieck.games.pente;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class Frame extends JFrame {
    /**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private static final String TITLE = "Pente";
    private static final String MENU_FILE = "File";
    private static final String ITEM_NEW = "New Game";
    private static final String ITEM_EXIT = "Exit";

    private View theView = null;

    /** static initialization */
    static {
        JFrame.setDefaultLookAndFeelDecorated(true);
    }

    private static class WindowCloseManager extends WindowAdapter {
        @Override
		public void windowClosing(WindowEvent e) {
            System.exit(0);
        }
    }

    private static class WindowResizeManager extends ComponentAdapter {
        @Override
		public void componentResized(ComponentEvent event) {
            Frame theFrame = (Frame) event.getComponent();
            if (theFrame.theView != null) {
                Dimension dim = theFrame.getSize();
                theFrame.theView.setPreferredSize(dim);
            }
        }
    }

    private final ActionListener ITEM_NEW_LISTENER = new ActionListener() {
        public void actionPerformed(ActionEvent e) {
            Game game = Game.getInstance();
            game.newGame();
        }
    };

    private final ActionListener ITEM_EXIT_LISTENER = new ActionListener() {
        public void actionPerformed(ActionEvent e) {
            System.exit(0);
        }
    };

    /**
     * Public ctor
     */
    public Frame() {
        super(TITLE);
        setResizable(false);
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        addWindowListener(new WindowCloseManager());
        addComponentListener(new WindowResizeManager());
        initComponents();
        setLocationRelativeTo(null);
    }

    private void initComponents() {
        initMenu();
        JPanel content = new JPanel(new GridLayout(1, 0));
        content.setOpaque(true);

        theView = new View();
        content.add(theView);

        setContentPane(content);
        pack();
    }


     private void initMenu() {
        JMenuBar bar = new JMenuBar();

        JMenu menu = new JMenu(MENU_FILE);
        menu.setMnemonic(KeyEvent.VK_F);
        bar.add(menu);

        JMenuItem item = new JMenuItem(ITEM_NEW, KeyEvent.VK_N);
        item.addActionListener(ITEM_NEW_LISTENER);
        menu.add(item);

        item = new JMenuItem(ITEM_EXIT, KeyEvent.VK_X);
        item.addActionListener(ITEM_EXIT_LISTENER);
        menu.add(item);

        setJMenuBar(bar);
    }
}
