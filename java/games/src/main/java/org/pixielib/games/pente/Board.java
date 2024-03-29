package org.pixielib.games.pente;

public class Board {
    public static final int SIZE = 19; // must be odd
    public static final int NSQUARES = SIZE * SIZE;
    private final Graph graph = new Graph(SIZE);
    public static final int VSIZE = 5; // vector size
    private static Board instance = null;

    private Board() {
    }

    public static Board getInstance() {
        if (instance == null) {
            instance = new Board();
        }
        return instance;
    }

    public void mark(int i, int j, int type) {
        graph.setVertexType(i, j, type);
    }

    public int markType(int i, int j) {
        return graph.getVertexType(i, j);
    }

    public void clear() {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                graph.setVertexType(i, j, Graph.VT_E);
            }
        }
    }
}
