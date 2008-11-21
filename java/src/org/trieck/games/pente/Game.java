package org.trieck.games.pente;

import javax.swing.*;
import java.awt.*;
import java.util.Iterator;

public class Game {
    private static Game instance = null;

    private Machine machine = null;
    private Frame theFrame = null;
    private Board board = Board.getInstance();

    private Game() {
        instance = this;
        machine = new Machine();
        theFrame = new Frame();
        theFrame.setVisible(false);
    }

    public static Game getInstance() {
        if (instance == null) new Game();
        return instance;
    }

    public void newGame() {
        Board board = Board.getInstance();
        board.clear();
        theFrame.repaint();
    }

    public Point getMachineTurn() {
        check();
        Point pt = machine.move();
        if (pt == null) stalemate();
        check();
        return pt;
    }

    public void stalemate() {
        Object[] options = {"Yes", "No"};
        int n = JOptionPane.showOptionDialog(theFrame,
            "Stalemate!\r\n"
            + "Play again?",
            "Stalemate",
            JOptionPane.YES_NO_OPTION,
            JOptionPane.QUESTION_MESSAGE,
            null,
            options,
            options[1]);
        if (n == 0) {
            newGame();
        } else {
            System.exit(0);
        }
    }

    void check() {
        Iterator<Point[]> it = Machine.VECTORS.iterator();
        while (it.hasNext()) {
            int ocount = 0, xcount = 0;
            Point[] v = it.next();
            for (int i = 0; i < v.length; i++) {
                int type = board.markType(v[i].x, v[i].y);
                if (type == Graph.VT_O) { ocount++; }
                if (type == Graph.VT_X) { xcount++; }
            }

            if (ocount == Board.VSIZE || xcount == Board.VSIZE) { // winner
                Object[] options = {"Yes", "No"};
                int n = JOptionPane.showOptionDialog(theFrame,
                    (ocount == Board.VSIZE ? "You" : "I") + " Win!\r\n"
                    + "Play again?",
                    "Winner",
                    JOptionPane.YES_NO_OPTION,
                    JOptionPane.QUESTION_MESSAGE,
                    null,
                    options,
                    options[1]);
                if (n == 0) {
                    newGame();
                    break;
                } else {
                    System.exit(0);
                }
            }
        }
    }

    private void play(String[] args) {
        theFrame.setVisible(true);
    }

    public static void main(String[] args) {
        Game theGame = Game.getInstance();
        theGame.play(args);
    }
}
