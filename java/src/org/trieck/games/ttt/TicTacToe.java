package org.trieck.games.ttt;

import java.awt.Point;

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
		if (theBoard.available() == 0)
			return null;
		
		return theMachine.move(theBoard);		
	}
	
	public static void main(String[] args) {
		TicTacToe game = TicTacToe.getInstance();
		game.play();
	}

}
