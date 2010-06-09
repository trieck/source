package org.tomrieck.games.ttt;

public class Machine {
	public static final int DEFAULT_DEPTH = 4;
	private static final int MAX_RANK = Integer.MAX_VALUE;
	private final int color;
	private int theDepth;

	public Machine(int color) {
		theDepth = DEFAULT_DEPTH;
		this.color = color;
	}

	public int getDepth() {
		return theDepth;
	}

	public void setDepth(int depth) {
		theDepth = depth;
	}

	private int alphabeta(Board board, int depth, int color, int alpha,
			int beta, Move move) {
		if (depth == 0 || board.available() == 0) {
			move.row = board.getNodeRep() / Board.BOARD_SIZE;
			move.col = board.getNodeRep() % Board.BOARD_SIZE;
			return board.rank();
		}

		Board best = board;

		int ab;
		for (final Board child : board) {
			ab = alphabeta(child, depth - 1, -color, -beta, -alpha, move);
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

		move.row = best.getNodeRep() / Board.BOARD_SIZE;
		move.col = best.getNodeRep() % Board.BOARD_SIZE;

		return (color == Board.COLOR_CROSS) ? alpha : beta;
	}

	public Move move(Board board) {
		if (board.available() == 0) {
			return null;
		}

		board.makeTree(theDepth, color);

		final Move move = new Move();
		alphabeta(board, theDepth, color, -MAX_RANK, MAX_RANK, move);

		board.setPiece(move.row, move.col, color);

		return move;
	}
}
