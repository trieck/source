package org.trieck.games.ttt;

import java.awt.Point;

public class Machine {
	public static final int MAX_DEPTH = 4;
	private static final int MAX_RANK = Integer.MAX_VALUE;

	int color;

	public Machine(int color) {
		this.color = color;
	}

	private int alphabeta(Board board, int depth, int color, int alpha,
			int beta, Point pt) {
		if (depth == 0 || board.available() == 0) {
			pt.x = board.getNodeRep() / Board.BOARD_SIZE;
			pt.y = board.getNodeRep() % Board.BOARD_SIZE;
			return board.rank();
		}

		Board best = board;

		int ab;
		for (final Board child : board) {
			ab = alphabeta(child, depth - 1, -color, -beta, -alpha, pt);
			if (color == Board.COLOR_CROSS) {
				if (ab > alpha) {
					alpha = ab;
					best = child;
				}

				if (alpha >= beta) {
					break; // alpha-beta cutoff
				}
			} else {
				if (ab < beta) {
					beta = ab;
					best = child;
				}

				if (beta <= alpha) {
					break; // alpha-beta cutoff
				}
			}
		}

		pt.x = best.getNodeRep() / Board.BOARD_SIZE;
		pt.y = best.getNodeRep() % Board.BOARD_SIZE;

		return (color == Board.COLOR_CROSS) ? alpha : beta;
	}

	public Point move(Board board) {
		if (board.available() == 0) {
			return null;
		}

		board.makeTree(color);

		final Point pt = new Point();
		alphabeta(board, MAX_DEPTH, color, -MAX_RANK, MAX_RANK, pt);

		board.setPiece(pt.x, pt.y, color);

		return pt;
	}
}