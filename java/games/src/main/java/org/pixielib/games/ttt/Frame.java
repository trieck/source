package org.pixielib.games.ttt;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class Frame extends JFrame {

    private static final String MENU_FILE = "File";
    private static final String ITEM_FILE_EXIT = "Exit";
    private static final String ITEM_FILE_NEW = "New Game";
    private static final String MENU_TOOLS = "Tools";
    private static final String ITEM_TOOLS_OPTIONS = "Options";
    private static final long serialVersionUID = 1L;
    private static final String TITLE = "Tic Tac Toe";
    /** static initialization */
    static {
        JFrame.setDefaultLookAndFeelDecorated(true);
    }
    private final ActionListener ITEM_FILE_EXIT_LISTENER = new ActionListener() {
        public void actionPerformed(ActionEvent e) {
            System.exit(0);
        }
    };
    private final ActionListener ITEM_FILE_NEW_LISTENER = new ActionListener() {
        public void actionPerformed(ActionEvent e) {
            TicTacToe game = TicTacToe.getInstance();
            game.newGame();
        }
    };
    private final ActionListener ITEM_TOOLS_OPTIONS_LISTENER = new ActionListener() {
        public void actionPerformed(ActionEvent e) {
            TicTacToe game = TicTacToe.getInstance();
            int ndepth = game.getDepth();
            String[] depths = {"1", "2", "4", "9"};

            String depth = (String) JOptionPane.showInputDialog(Frame.this,
                    "Game Tree Depth:", "Options",
                    JOptionPane.QUESTION_MESSAGE, null, depths, String
                            .valueOf(ndepth));

            if (depth != null) {
                try {
                    ndepth = Integer.parseInt(depth);
                    game.setDepth(ndepth);
                } catch (NumberFormatException ex) {
                    ex.printStackTrace(System.err);
                }
            }
        }
    };
    private View theView = null;

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
        final JPanel content = new JPanel(new GridLayout(1, 0));
        content.setOpaque(true);

        theView = new View();
        content.add(theView);

        setContentPane(content);
        pack();
    }

    private void initMenu() {
        final JMenuBar bar = new JMenuBar();

        JMenu menu = new JMenu(MENU_FILE);
        menu.setMnemonic(KeyEvent.VK_F);
        bar.add(menu);

        JMenuItem item = new JMenuItem(ITEM_FILE_NEW, KeyEvent.VK_N);
        item.addActionListener(ITEM_FILE_NEW_LISTENER);
        menu.add(item);

        item = new JMenuItem(ITEM_FILE_EXIT, KeyEvent.VK_X);
        item.addActionListener(ITEM_FILE_EXIT_LISTENER);
        menu.add(item);

        menu = new JMenu(MENU_TOOLS);
        menu.setMnemonic(KeyEvent.VK_T);
        bar.add(menu);

        item = new JMenuItem(ITEM_TOOLS_OPTIONS, KeyEvent.VK_O);
        item.addActionListener(ITEM_TOOLS_OPTIONS_LISTENER);
        menu.add(item);

        setJMenuBar(bar);
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
            final Frame theFrame = (Frame) event.getComponent();
            if (theFrame.theView != null) {
                final Dimension dim = theFrame.getSize();
                theFrame.theView.setPreferredSize(dim);
            }
        }
    }

}
