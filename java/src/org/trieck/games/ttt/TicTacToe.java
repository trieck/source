package org.trieck.games.ttt;

import java.awt.Point;
import javax.swing.JOptionPane;

public class TicTacToe {
	
	private Board theBoard = null;
	private Frame theFrame = null;	
	private Machine theMachine = null;
	
	private static TicTacToe theGame = null;
	
	public static synchronized TicTacToe getInstance() {
		if (theGame == null) new TicTacToe();		
		return theGame;
	}
	
	private TicTacToe() {
		theGame = this;
		theMachine = new Machine(Board.COLOR_CROSS);
		theBoard = new Board();	
		theFrame = new Frame();
        theFrame.setVisible(false);
	}
	
	public void play() {	
		theFrame.setVisible(true);		
	}
	
	public void newGame() {
		theBoard.clear();
        theFrame.repaint();
    }
	
	public Board getBoard() {
		return theBoard;
	}
	
	public Point getMachineTurn() {
		if (checkWinner())
			return null;
		
        Point pt;
        if ((pt = theMachine.move(theBoard)) == null) {
        	stalemate();
        }
        
        checkWinner();
        
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
	 
	 boolean checkWinner() {
		 int color;
		 if ((color = theBoard.winner()) != Board.COLOR_EMPTY) {
			 Object[] options = {"Yes", "No"};
             int n = JOptionPane.showOptionDialog(theFrame,
                 (color == Board.COLOR_NOUGHT ? "You" : "I") + " Win!\r\n"
                 + "Play again?",
                 "Winner",
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
             return true;
		 } 
		 
		 return false;
	 }
	 
	public static void main(String[] args) {
		TicTacToe game = TicTacToe.getInstance();
		game.play();
	}

}
