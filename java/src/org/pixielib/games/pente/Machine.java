package org.pixielib.games.pente;

import java.awt.*;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

public class Machine {

    /**
     * all initially feasible vectors
     */
    public static final List<Point[]> VECTORS = new ArrayList<Point[]>();

    /* generate all the intially feasible vectors */

    static {
        int b, i, m, n;
        Point[] v;

        for (b = 0; b < Board.NSQUARES; b++) {
            m = b / Board.SIZE;
            n = b % Board.SIZE;

            // if Board.VSIZE + n <= Board.SIZE,
            // we have a horizontal vector from b.
            if (Board.VSIZE + n <= Board.SIZE) {
                v = new Point[Board.VSIZE];
                for (i = 0; i < Board.VSIZE; i++) {
                    v[i] = new Point(m, n + i);
                }
                VECTORS.add(v);
            }

            // if Board.VSIZE + m <= Board.SIZE,
            // we have a vertical vector from b.
            if (Board.VSIZE + m <= Board.SIZE) {
                v = new Point[Board.VSIZE];
                for (i = 0; i < Board.VSIZE; i++) {
                    v[i] = new Point(m + i, n);
                }
                VECTORS.add(v);
            }

            // if Board.VSIZE + m <= Board.SIZE and
            // Board.VSIZE + n <= Board.SIZE,
            // we have a "diagonal down" vector from b.
            if (Board.VSIZE + m <= Board.SIZE && Board.VSIZE + n <= Board.SIZE) {
                v = new Point[Board.VSIZE];
                for (i = 0; i < Board.VSIZE; i++) {
                    v[i] = new Point(m + i, n + i);
                }
                VECTORS.add(v);
            }

            // if m >= Board.VSIZE - 1 and
            // Board.VSIZE + n <= Board.SIZE,
            // we have a "diagonal up" vector from b.
            if (m >= Board.VSIZE - 1 && Board.VSIZE + n <= Board.SIZE) {
                v = new Point[Board.VSIZE];
                for (i = 0; i < Board.VSIZE; i++) {
                    v[i] = new Point(m - i, n + i);
                }
                VECTORS.add(v);
            }
        }
    }

    private static final float MINWEIGHT = -Float.MIN_VALUE;
    private static final float MAXWEIGHT = Float.MAX_VALUE;
    private static final float PIECEWEIGHT = Board.VSIZE;
    private static final int CENTER = (Board.NSQUARES + 1) / 2 - 1;
    private static final int MEANPOINT = Board.VSIZE / 2;

    private final List<Point> block = new ArrayList<Point>(); /*
     * current "must
	 * block" list
	 */
    private final Board board = Board.getInstance();

    public Point move() {

        float nweight, maxWeight = MINWEIGHT;
        Point[] maxV = null;
        Point pt = null;

        /* generate the blocking list */
        getBlock();

        for (final Point[] v : VECTORS) {
            nweight = weight(v);
            if (nweight > maxWeight) {
                maxWeight = nweight;
                maxV = v;
            }
        }

        if (maxWeight == MINWEIGHT && block.size() == 0) { // no feasible
            // strategy found
            if ((pt = blockMove()) == null) { // try a blocking move
                pt = randomMove(); // try a random move
            }

            if (pt != null) {
                board.mark(pt.x, pt.y, Graph.VT_X);
            }

            return pt;
        }

        if (maxV != null) {
            pt = getSquare(maxV);
        }

        /* Check if we need to block */
        if (block.size() > 0 && maxWeight < MAXWEIGHT) {
            pt = block.get(0);
        }
        board.mark(pt.x, pt.y, Graph.VT_X);

        return pt;
    }

    /* Attempt to block opponent on a maximally feasible opponent vector */

    Point blockMove() {
        float weight, maxWeight = MINWEIGHT;
        Point[] maxV = null;

        for (final Point[] v : VECTORS) {
            weight = 0;
            for (final Point element : v) {
                final int type = board.markType(element.x, element.y);
                if (type == Graph.VT_O) {
                    weight += PIECEWEIGHT;
                }
                if (type == Graph.VT_X) {
                    weight = MINWEIGHT;
                    break;
                } // not feasible
            }
            if (weight > maxWeight) {
                maxWeight = weight;
                maxV = v;
            }
        }

        if (maxV != null) {
            for (final Point element : maxV) {
                final int type = board.markType(element.x, element.y);
                if (type == Graph.VT_E) {
                    return element;
                }
            }
        }

        return null;
    }

    /* Attempt to move to a random open square */

    Point randomMove() {
        final ArrayList<Point> empty = new ArrayList<Point>();
        for (int i = 0; i < Board.SIZE; i++) {
            for (int j = 0; j < Board.SIZE; j++) {
                if (board.markType(i, j) == Graph.VT_E) {
                    empty.add(new Point(i, j));
                }
            }
        }

        if (empty.size() > 0) {
            final int n = (int) Math.round(Math.random() * (empty.size() - 1));
            return empty.get(n);
        }

        return null;
    }

    /*
      * Does v contain an empty center?
      */

    private boolean center(Point[] v) {
        for (final Point aV : v) {
            final int square = aV.x * Board.SIZE + aV.y;
            if ((square == CENTER) && board.markType(aV.x, aV.y) == Graph.VT_E) {
                return true;
            }
        }
        return false;
    }

    /*
      * Find the best square for a feasible vector
      */

    private Point getSquare(Point[] v) {

        // first try center
        if (center(v)) {
            return new Point(CENTER / Board.SIZE, CENTER % Board.SIZE);
        }

        float weight, maxWeight = MINWEIGHT;
        Point maxP = null;

        /* try to find an adjacent piece */
        for (int i = 0; i < v.length; i++) {
            if (board.markType(v[i].x, v[i].y) == Graph.VT_X) {
                if (i > 0
                        && board.markType(v[i - 1].x, v[i - 1].y) == Graph.VT_E) {
                    weight = weight(v[i - 1]);
                    if (weight > maxWeight) {
                        maxWeight = weight;
                        maxP = v[i - 1];
                    }
                }

                if (i < v.length - 1
                        && board.markType(v[i + 1].x, v[i + 1].y) == Graph.VT_E) {
                    weight = weight(v[i + 1]);
                    if (weight > maxWeight) {
                        maxWeight = weight;
                        maxP = v[i + 1];
                    }
                }
            }
        }

        if (maxP != null) {
            return maxP;
        }

        /* try to find an empty piece */
        for (final Point aV : v) {
            if (board.markType(aV.x, aV.y) == Graph.VT_E) {
                weight = weight(aV);
                if (weight > maxWeight) {
                    maxWeight = weight;
                    maxP = aV;
                }
            }
        }

        return maxP;
    }

    /*
      * Determine weight of a square By the number of maximally feasible vectors
      * it is contained in.
      */

    private float weight(Point p) {
        int i;
        float weight = 0, vweight;

        if (board.markType(p.x, p.y) != Graph.VT_E) {
            return MINWEIGHT; // not available
        }

        final Iterator<Point[]> it = VECTORS.iterator();
        while (it.hasNext()) {
            final Point[] v = it.next();
            for (i = 0; i < v.length; i++) {
                if (v[i] == p) {
                    break; // contained
                }
            }

            if (i < v.length) {
                vweight = weight(v);
                if (vweight > MINWEIGHT) {
                    weight += vweight;
                }
            }
        }

        return weight;
    }

    /*
      * Determine weight of a vector
      */

    private float weight(Point[] v) {
        float weight = 0;

        for (final Point aV : v) {
            final int type = board.markType(aV.x, aV.y);
            switch (type) {
                case Graph.VT_O:
                    return MINWEIGHT; // vector must contain no O's
                case Graph.VT_X:
                    weight += PIECEWEIGHT;
                    break;
            }
        }

        if (weight == (Board.VSIZE - 1) * PIECEWEIGHT) {
            return MAXWEIGHT; // winner
        }

        // vector must contain a blocking strategy if we need to block
        if (block.size() > 0) {
            int bcount = 0;
            for (final Point element : v) {
                if (block.contains(element)) {
                    bcount++;
                }
            }
            if (bcount == 0) {
                return MINWEIGHT; // no blocking strategy
            }
        }

        // add the individual piece weights
        for (final Point aV : v) {
            final int type = board.markType(aV.x, aV.y);
            if (type == Graph.VT_X) {
                weight += weight(aV);
            }
        }

        // add weighted distance from center
        final int m = v[MEANPOINT].x, n = v[MEANPOINT].y;
        final int x = CENTER / Board.SIZE, y = CENTER % Board.SIZE;
        final float d = Math.abs(x - m) + Math.abs(y - n) + 1;
        weight += 1 / d;

        // add weighted contiguity
        weight += contiguity(v);

        return weight;
    }

    private int contiguity(Point[] v) {
        int cont = 0, maxCont = 0;
        for (final Point element : v) {
            final int type = board.markType(element.x, element.y);
            switch (type) {
                case Graph.VT_X:
                    cont++;
                    break;
                case Graph.VT_E:
                    if (cont > maxCont) {
                        maxCont = cont;
                    }
                    cont = 0;
                    break;
            }
        }

        if (cont > maxCont) {
            maxCont = cont;
        }

        return maxCont;
    }

    /*
      * Determine squares where we must block where the vector contains
      * Board.SIZE - 1 O's and one empty
      */

    private void getBlock() {
        int ocount, ecount;
        Point b = null, maxP = null;
        float weight, maxWeight = MINWEIGHT;
        block.clear();

        final Iterator<Point[]> it = VECTORS.iterator();
        while (it.hasNext()) {
            ocount = ecount = 0;
            final Point[] v = it.next();
            for (final Point element : v) {
                final int type = board.markType(element.x, element.y);
                if (type == Graph.VT_O) {
                    ocount++;
                }
                if (type == Graph.VT_E) {
                    ecount++;
                    b = element;
                }
            }

            if (ocount == Board.VSIZE - 1 && ecount == 1) { // must block, b
                // contains the
                // square to block
                weight = weight(b);
                if (weight > maxWeight) {
                    maxP = b;
                    maxWeight = weight;
                }
            }

            // block contiguous with open ends
            if (ocount == Board.VSIZE - 2 && ecount == 2) {
                if (board.markType(v[0].x, v[0].y) == Graph.VT_E
                        && board.markType(v[v.length - 1].x, v[v.length - 1].y) == Graph.VT_E) {
                    weight = weight(b);
                    if (weight > maxWeight) {
                        maxP = b;
                        maxWeight = weight;
                    }
                }
            }
        }

        if (maxP != null) {
            block.add(maxP);
        }
    }
}
