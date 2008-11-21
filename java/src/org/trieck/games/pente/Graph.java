package org.trieck.games.pente;

public class Graph {
    public static final int VT_E = 0;
    public static final int VT_O = 1;
    public static final int VT_X = 2;

    private class Vertex {
        private int type;

        public Vertex() {
            type = VT_E;
        }

        public int getType() {
            return type;
        }
    }

    private Vertex[][] vertices = null;

    public Graph(int size) {
        vertices = new Vertex[size][size];
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                vertices[i][j] = new Vertex();
    }

    public void setVertexType(int m, int n, int type) {
        vertices[m][n].type = type;
    }

    public int getVertexType(int m, int n) {
        return vertices[m][n].type;
    }
}
