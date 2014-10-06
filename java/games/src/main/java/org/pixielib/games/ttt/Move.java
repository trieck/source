package org.pixielib.games.ttt;

public class Move {

    public int row;
    public int col;

    public Move() {
        this(0, 0);
    }

    public Move(int row, int col) {
        this.row = this.col;
    }

    public Move(Move move) {
        row = move.row;
        col = move.col;
    }

}
