package org.trieck.games.ttt;

import java.util.*;

public class Machine {
	private static final int MAX_RANK = Integer.MAX_VALUE;
	private static final int MAX_DEPTH = 4;
	
	int color;
	
	private class Move {
		public Move() {
			this(0, 0);
		}
		
		public Move(int x, int y) {
			this.x = x; this.y = y;
			rank = 0;
		}
		
		int x, y;
		int rank;
	}
			
	public Machine(int color) {
		this.color = color;
	}
	
	public boolean move(Board board) {
		if (board.available() == 0)
			return false;
		
		Move move = getMove(board, color, 1, -MAX_RANK, MAX_RANK);
		board.setPiece(move.x, move.y, color);
		
		System.out.println(board);
		System.out.println();
		
		return true;
	}
	
	private Move getMove(Board board, int color, int depth, int alpha, int beta) {
		Move move = new Move(-1,-1), bestMove = new Move(-1, -1);
		
		if (depth == MAX_DEPTH || board.available() == 0) {
			move.rank = board.rank(color);
			return move;			
		}

		Random random = new Random();
		int rowStart = random.nextInt(Board.BOARD_SIZE);
		int colStart = random.nextInt(Board.BOARD_SIZE);
		int row, col;
		
		// check all valid moves
		for (int i = 0; i < Board.BOARD_SIZE; i++) {
			for (int j = 0; j < Board.BOARD_SIZE; j++) {
				row = (rowStart + i) % 8;
				col = (colStart + j) % 8;
				
				if (board.getPiece(row, col) != Board.COLOR_EMPTY)
					continue;
			
				move.x = row; move.y = col;
				Board nextBoard = (Board)board.clone();
				nextBoard.setPiece(move.x, move.y, color);
				
				Move nextMove = getMove(nextBoard, -color, depth + 1, alpha, beta);
				
				if (color == Board.COLOR_CROSS) {
					if (alpha < nextMove.rank) {
						bestMove.x = move.x; bestMove.y = move.y;
						bestMove.rank = alpha = nextMove.rank;
						if (alpha >= beta) {
							break;
						}
                  }
				} else {
					if (beta > nextMove.rank) {
						bestMove.x = move.x; bestMove.y = move.y;
						bestMove.rank = beta = nextMove.rank;
						if (alpha >= beta) {
							break;							
	                    }
					}
				}				
			
			}
		}
		
		return bestMove;
	}	
	
}
