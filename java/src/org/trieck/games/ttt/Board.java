package org.trieck.games.ttt;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.Random;

public class Board implements Cloneable, Iterable<Board> {

	public static final int BOARD_SIZE = 3;
	public static final int COLOR_CROSS = 1;
	public static final int COLOR_EMPTY = 0;
	public static final int COLOR_NOUGHT = -1;

	private static final Vectors VECTORS = Vectors.instance();

	private static void addNode(Board parent, int depth, int color) {
		if (depth > Machine.MAX_DEPTH) {
			return;
		}

		final Random random = new Random();
		final int rowStart = random.nextInt(BOARD_SIZE);
		final int colStart = random.nextInt(BOARD_SIZE);

		int row, col;
		for (int i = 0; i < BOARD_SIZE; i++) {
			for (int j = 0; j < BOARD_SIZE; j++) {
				row = (rowStart + i) % BOARD_SIZE;
				col = (colStart + j) % BOARD_SIZE;

				if (parent.rep[row][col] != COLOR_EMPTY) {
					continue;
				}

				final Board next = (Board) parent.clone();
				next.children = new ArrayList<Board>();
				next.rep[row][col] = color;
				next.node_rep = row * BOARD_SIZE + col;
				parent.children.add(next);

				if (next.winner() != COLOR_EMPTY) {
					continue; // winner
				}

				addNode(next, depth + 1, -color);
			}
		}
	}

	private List<Board> children; // child nodes
	private int node_rep; // representation of node in game tree

	private final int rep[][]; // board representation

	public Board() {
		node_rep = -1;
		rep = new int[BOARD_SIZE][BOARD_SIZE];
		children = new ArrayList<Board>();
	}

	public int available() {
		int count = 0;

		if (winner() != COLOR_EMPTY) {
			return 0;
		}

		for (int i = 0; i < Board.BOARD_SIZE; i++) {
			for (int j = 0; j < Board.BOARD_SIZE; j++) {
				if (rep[i][j] == COLOR_EMPTY) {
					count++;
				}
			}
		}

		return count;
	}

	public void clear() {
		for (int i = 0; i < Board.BOARD_SIZE; i++) {
			for (int j = 0; j < Board.BOARD_SIZE; j++) {
				rep[i][j] = COLOR_EMPTY;
			}
		}
	}

	@Override
	public Object clone() {
		final Board board = new Board();

		board.node_rep = node_rep;

		for (int i = 0; i < rep.length; i++) {
			System.arraycopy(rep[i], 0, board.rep[i], 0, rep[i].length);
		}

		board.children = new ArrayList<Board>(children);

		return board;
	}

	public int getNodeRep() {
		return node_rep;
	}

	public int getPiece(int x, int y) {
		x = x % BOARD_SIZE;
		y = y % BOARD_SIZE;
		return rep[x][y];
	}

	public Iterator<Board> iterator() {
		return children.iterator();
	}

	public void makeTree(int color) {
		children.clear();
		Board.addNode(this, 1, color);
	}

	public int rank() {
		int rank = 0;

		for (final Integer[] v : VECTORS) {
			rank += rankV(v);
		}

		return rank;
	}

	private int rankV(Integer[] v) {
		int row, col;
		int crosses = 0, noughts = 0;

		for (final Integer element : v) {
			row = element / BOARD_SIZE;
			col = element % BOARD_SIZE;

			if (rep[row][col] == COLOR_NOUGHT) {
				noughts++;
			}

			if (rep[row][col] == COLOR_CROSS) {
				crosses++;
			}
		}

		if (noughts == 0) {
			return (int) Math.pow(10, crosses);
		} else if (crosses == 0) {
			return -(int) Math.pow(10, noughts);
		}

		return 0;
	}

	public void setPiece(int x, int y, int color) {
		x = x % BOARD_SIZE;
		y = y % BOARD_SIZE;
		rep[x][y] = color;
	}

	@Override
	public String toString() {
		final StringBuffer output = new StringBuffer();

		final StringBuffer line = new StringBuffer();
		for (int i = 0; i < Board.BOARD_SIZE * 2 - 1; i++) {
			line.append('-');
		}

		for (int i = 0; i < Board.BOARD_SIZE; i++) {
			if (i > 0) {
				output.append('\n');
				output.append(line);
				output.append('\n');
			}
			for (int j = 0; j < Board.BOARD_SIZE; j++) {
				if (rep[i][j] == COLOR_EMPTY) {
					output.append(" ");
				} else if (rep[i][j] == COLOR_CROSS) {
					output.append("x");
				} else {
					output.append("o");
				}
				if (j < Board.BOARD_SIZE - 1) {
					output.append("|");
				}
			}
		}

		return output.toString();
	}

	public int winner() {
		int winner = COLOR_EMPTY;

		for (final Integer[] v : VECTORS) {
			if ((winner = winnerV(v)) != COLOR_EMPTY) {
				return winner;
			}
		}

		return COLOR_EMPTY;
	}

	private int winnerV(Integer[] v) {
		int row, col;
		int noughts = 0, crosses = 0;

		for (final Integer element : v) {
			row = element / BOARD_SIZE;
			col = element % BOARD_SIZE;

			if (rep[row][col] == COLOR_NOUGHT) {
				noughts++;
			}

			if (rep[row][col] == COLOR_CROSS) {
				crosses++;
			}
		}

		if (noughts > 0 && crosses > 0) {
			return 0; // infeasible
		}

		if (crosses == BOARD_SIZE) {
			return COLOR_CROSS;
		}

		if (noughts == BOARD_SIZE) {
			return COLOR_NOUGHT;
		}

		return COLOR_EMPTY;
	}
}