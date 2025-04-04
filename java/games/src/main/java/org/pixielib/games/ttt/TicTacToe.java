package org.pixielib.games.ttt;

import javax.swing.*;

public class TicTacToe {

    private static TicTacToe theGame = null;
    private Board theBoard = null;
    private Frame theFrame = null;
    private Machine theMachine = null;

    private TicTacToe() {
        theGame = this;
        theMachine = new Machine(Board.COLOR_CROSS);
        theBoard = new Board();
        theFrame = new Frame();
        theFrame.setVisible(false);
    }

    public static synchronized TicTacToe getInstance() {
        if (theGame == null) {
            new TicTacToe();
        }
        return theGame;
    }

    public static void main(String[] args) {
        final TicTacToe game = TicTacToe.getInstance();
        game.play();
    }

    private boolean checkGameOver() {
        if (checkWinner()) {
            return true;
        }

        return checkDraw();
    }

    private boolean checkWinner() {
        int color;
        if ((color = theBoard.winner()) != Board.COLOR_EMPTY) {
            final Object[] options = {"Yes", "No"};
            final int n = JOptionPane.showOptionDialog(theFrame,
                    (color == Board.COLOR_NOUGHT ? "You" : "I") + " Win!\r\n"
                            + "Play again?", "Winner",
                    JOptionPane.YES_NO_OPTION, JOptionPane.QUESTION_MESSAGE,
                    null, options, options[1]);
            if (n == 0) {
                newGame();
            } else {
                System.exit(0);
            }
            return true;
        }

        return false;
    }

    public Board getBoard() {
        return theBoard;
    }

    public Move getMachineTurn() {
        if (checkGameOver()) {
            return null;
        }

        final Move move = theMachine.move(theBoard);

        if (checkGameOver()) {
            return null;
        }

        return move;
    }

    public void newGame() {
        theBoard.clear();
        theFrame.repaint();
    }

    public void play() {
        theFrame.setVisible(true);
    }

    public int getDepth() {
        return theMachine.getDepth();
    }

    public void setDepth(int depth) {
        theMachine.setDepth(depth);
    }

    public boolean checkDraw() {
        if (theBoard.isDraw()) {
            final Object[] options = {"Yes", "No"};
            final int n = JOptionPane.showOptionDialog(theFrame, "Draw!\r\n"
                            + "Play again?", "Draw", JOptionPane.YES_NO_OPTION,
                    JOptionPane.QUESTION_MESSAGE, null, options, options[1]);
            if (n == 0) {
                newGame();
            } else {
                System.exit(0);
            }

            return true;
        }

        return false;
    }

}
