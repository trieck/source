package org.trieck.games.ttt;

public class Board implements Cloneable {

	public static final int BOARD_SIZE = 3;
	public static final int COLOR_EMPTY = 0;
	public static final int COLOR_CROSS = 1;
	public static final int COLOR_NOUGHT = -1;	
	
	private static final int MIN_ADVANTAGE = 1;
	private static final int MAX_ADVANTAGE = 3;
	
	private static final Vectors VECTORS = Vectors.instance();
	
	private int rep[][];
	
	public Board() {
		rep = new int[BOARD_SIZE][BOARD_SIZE];
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
		Board board = new Board();
				
		for (int i = 0; i < rep.length; i++) {
			System.arraycopy(rep[i], 0, board.rep[i],0, rep[i].length);
		}
		
		return board;
	}
	
	public void setPiece(int x, int y, int color) {
		x = x % BOARD_SIZE;
		y = y % BOARD_SIZE;
		rep[x][y] = color;
	}
	
	public int getPiece(int x, int y) {
		x = x % BOARD_SIZE;
		y = y % BOARD_SIZE;
		return rep[x][y];
	}	
	
	public int available() {
		int count = 0;
		
		if (winner() != COLOR_EMPTY)
			return 0;
		
		for (int i = 0; i < Board.BOARD_SIZE; i++) {
			for (int j = 0; j < Board.BOARD_SIZE; j++) {
				if (rep[i][j] == COLOR_EMPTY)
					count++;
			}
		}
		
		return count;
	}
	
	public int rank(int color) {
		int rank = 0;
		
		for (int[] v : VECTORS) {
			rank += rankV(v, color);
		}
		
		return rank;
	}
	
	private int rankV(int[] v, int color) {
		int row, col;
		int noughts = 0, crosses = 0;
		
		for (int i = 0; i < v.length; i++) {
			row = v[i] / BOARD_SIZE;
			col = v[i] % BOARD_SIZE;
			
			if (rep[row][col] == COLOR_NOUGHT)
				noughts++;
			
			if (rep[row][col] == COLOR_CROSS)
				crosses++;
		}
		
		if (noughts > 0 && crosses > 0)
			return 0;	// infeasible
		
		int advantage = MIN_ADVANTAGE;
		if (noughts == 0) {
			if (color == COLOR_CROSS)
				advantage = MAX_ADVANTAGE;	// player advantage
			return (int)Math.pow(10, crosses) * advantage;
		}
		
		if (crosses == 0) {
			if (color == COLOR_NOUGHT)
				advantage = MAX_ADVANTAGE;	// player advantage
			return -(int)Math.pow(10, noughts) * advantage;
		}
		
		return 0;
	}
	
	public int winner() {
		int winner = COLOR_EMPTY;
		
		for (int[] v : VECTORS) {
			if ((winner = winnerV(v)) != COLOR_EMPTY)
				return winner;
		}
		
		return COLOR_EMPTY;
	}
	
	private int winnerV(int[] v) {
		int row, col;
		int noughts = 0, crosses = 0;
		
		for (int i = 0; i < v.length; i++) {
			row = v[i] / BOARD_SIZE;
			col = v[i] % BOARD_SIZE;
			
			if (rep[row][col] == COLOR_NOUGHT)
				noughts++;
			
			if (rep[row][col] == COLOR_CROSS)
				crosses++;
		}
		
		if (noughts > 0 && crosses > 0)
			return 0;	// infeasible
		
		if (crosses == BOARD_SIZE)
			return COLOR_CROSS;
		
		if (noughts == BOARD_SIZE)
			return COLOR_NOUGHT;
		
		return COLOR_EMPTY;
	}
	
	@Override
	public String toString() {
		StringBuffer output = new StringBuffer();
		
		for (int i = 0; i < Board.BOARD_SIZE; i++) {
			if (i > 0) output.append("\n-----\n");
			for (int j = 0; j < Board.BOARD_SIZE; j++) {
				if (rep[i][j] == COLOR_EMPTY) {
					output.append(" ");
				} else if (rep[i][j] == COLOR_CROSS) {
					output.append("x");
				} else {
					output.append("o");
				}
				if (j < Board.BOARD_SIZE-1)
					output.append("|");
			}
		}
		
		return output.toString();
	}
	
}