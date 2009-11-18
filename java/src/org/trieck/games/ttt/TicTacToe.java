package org.trieck.games.ttt;

import javax.swing.JOptionPane;

public class TicTacToe {

	private static TicTacToe theGame = null;

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

	boolean checkWinner() {
		int color;
		if ((color = theBoard.winner()) != Board.COLOR_EMPTY) {
			final Object[] options = { "Yes", "No" };
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
		if (checkWinner()) {
			return null;
		}

		Move move;
		if ((move = theMachine.move(theBoard)) == null) {
			stalemate();
		}

		checkWinner();

		return move;
	}

	public void newGame() {
		theBoard.clear();
		theFrame.repaint();
	}

	public void play() {
		theFrame.setVisible(true);
	}

	public void stalemate() {
		final Object[] options = { "Yes", "No" };
		final int n = JOptionPane.showOptionDialog(theFrame, "Stalemate!\r\n"
				+ "Play again?", "Stalemate", JOptionPane.YES_NO_OPTION,
				JOptionPane.QUESTION_MESSAGE, null, options, options[1]);
		if (n == 0) {
			newGame();
		} else {
			System.exit(0);
		}
	}

}
