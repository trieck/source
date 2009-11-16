package org.trieck.games.ttt;

public class Machine {
	private static final int MAX_RANK = Integer.MAX_VALUE;
	public static final int MAX_DEPTH = 4;
	
	int color;
				
	private class Move {
		public Move() {
			this(-1,-1, 0);
		}
		
		public Move(int x, int y, int rank) {
			this.x = x;
			this.y = y;
			this.rank = rank;
		}
		
		int x, y, rank;
	}
	
	public Machine(int color) {
		this.color = color;
	}
	
	public boolean move(Board board) {
		if (board.available() == 0)
			return false;
		
		board.makeTree();
		
		Move move;
		if ((move = minimax(board, MAX_DEPTH, Board.COLOR_CROSS)) == null)
			return false;
		
		board.setPiece(move.x, move.y, color);
		
		return true;
	}
	
	private Move minimax(Board board, int depth, int color) {
		if (depth == 0 || board.available() == 0) {
			Move m = new Move();
			m.x = board.getNodeRep() / Board.BOARD_SIZE;
			m.y = board.getNodeRep() % Board.BOARD_SIZE;
			m.rank = board.rank();
			return m;
		}

		Board best = null; 
		Move m = null;
		
		int alpha = -color * Integer.MAX_VALUE;
		
		for (Board child : board) {
			m = minimax(child, depth-1, -color);
			
			if (color == Board.COLOR_CROSS) {
				if (m.rank > alpha) {
					alpha = m.rank;
					best = child;
				}
			} else {
				if (m.rank < alpha) {
					alpha = m.rank;
					best = child;
				}
			}
		}
		
			
		m = new Move();
		m.rank = alpha;
			
		if (best != null) {
			m.x = best.getNodeRep() / Board.BOARD_SIZE;
			m.y = best.getNodeRep() % Board.BOARD_SIZE;
		}
		
		return m;
	}
}

	
