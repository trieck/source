package org.trieck.games.ttt;

public class TicTacToe {
	
	private Board board;
	
	public TicTacToe() {
		board = new Board();		
	}
	
	public void play() {	
		Machine playerOne = new Machine(Board.COLOR_CROSS);
		Machine playerTwo = new Machine(Board.COLOR_NOUGHT);
				
		while (board.available() > 0) {
			if (!playerOne.move(board)) {
				return;
			}
			
			System.out.println(board);
			System.out.println();
			
			if (!playerTwo.move(board)) {
				return;
			}
			
			System.out.println(board);
			System.out.println();
		}
	}
	
	public static void main(String[] args) {
		TicTacToe game = new TicTacToe();
		game.play();
	}

}
