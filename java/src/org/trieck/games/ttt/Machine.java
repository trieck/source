package org.trieck.games.ttt;

import java.awt.Point;

public class Machine {
	private static final int MAX_RANK = Integer.MAX_VALUE;
	public static final int MAX_DEPTH = 4;
	
	int color;
					
	public Machine(int color) {
		this.color = color;
	}
	
	public boolean move(Board board) {
		if (board.available() == 0)
			return false;
		
		board.makeTree(color);
		
		Point pt = new Point();
		minimax(board, MAX_DEPTH, color, pt);
		
		board.setPiece(pt.x, pt.y, color);
		
		return true;
	}
	
	private int minimax(Board board, int depth, int color, Point pt) {
		if (depth == 0 || board.available() == 0) {
			pt.x = board.getNodeRep() / Board.BOARD_SIZE;
			pt.y = board.getNodeRep() % Board.BOARD_SIZE;
			return board.rank();
		}

		Board best = null; 
				
		int alpha = -color * MAX_RANK;
		
		int a;
		for (Board child : board) {
			a = minimax(child, depth-1, -color, pt);
			if (color == Board.COLOR_CROSS) {
				if (a > alpha) {
					alpha = a;
					best = child;
				}
			} else {
				if (a < alpha) {
					alpha = a;
					best = child;
				}
			}
		}
					
		if (best != null) {
			pt.x = best.getNodeRep() / Board.BOARD_SIZE;
			pt.y = best.getNodeRep() % Board.BOARD_SIZE;
		}
		
		return alpha;
	}
}

	
