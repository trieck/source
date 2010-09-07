package org.tomrieck.apps.graph;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Insets;
import java.awt.Point;
import java.awt.Polygon;
import java.awt.Rectangle;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.image.BufferedImage;
import java.util.HashSet;
import java.util.Iterator;

import javax.swing.BorderFactory;
import javax.swing.JComponent;

public class GraphView extends JComponent implements MouseListener {

    /**
     *
     */
    private static final long serialVersionUID = 1L;
    private static final int CX_POLYGONS = 19;
    private static final int CY_POLYGONS = 19;
    public static final int BORDER_CX = 3;
    public static final int BORDER_CY = 3;
    public static final int CELL_CX = 24;
    public static final int CELL_CY = 24;
    private static final int CELL_CX_SEG = CELL_CX / 3;
    private static final int CELL_CY_SEG = CELL_CY / 3;
    private static final int[] XPOINTS = {CELL_CX_SEG, CELL_CX_SEG * 2,
            CELL_CX, CELL_CX, CELL_CX_SEG * 2, CELL_CX_SEG, 0, 0};

    private static final int[] YPOINTS = {0, 0, CELL_CY_SEG, CELL_CY_SEG * 2,
            CELL_CY, CELL_CY, CELL_CY_SEG * 2, CELL_CY_SEG};

    private static final Polygon HEXAGON = new Polygon(XPOINTS, YPOINTS,
            XPOINTS.length);
    private static final Color[] PALETTE = {new Color(0xFF, 0xDE, 0xAD),
            new Color(0xBC, 0x8F, 0x8F)};

    private static class Fill {
        private final Point pt; // polygon index
        private final int color; // palette index

        public Fill(Point p, int c) {
            pt = (Point) p.clone();
            color = c;
        }

        @Override
        public boolean equals(Object o) {
            if (this == o) {
                return true;
            }
            if (!(o instanceof Fill)) {
                return false;
            }

            final Fill fill = (Fill) o;

            if (color != fill.color) {
                return false;
            }
            if (pt != null ? !pt.equals(fill.pt) : fill.pt != null) {
                return false;
            }

            return true;
        }

        @Override
        public int hashCode() {
            int result;
            result = (pt != null ? pt.hashCode() : 0);
            result = 29 * result + color;
            return result;
        }
    }

    private final java.util.Set<Fill> filled; // set of filled polygons
    private BufferedImage[] buff; // image buffers
    private int current; // current color

    public GraphView() {
        filled = new HashSet<Fill>();
        init();
    }

    private void init() {
        createBuffers();
        setOpaque(true);
        setBorder(BorderFactory.createLoweredBevelBorder());
        setBackground(new Color(0xF4, 0xA4, 0x60));
        setPreferredSize(new Dimension(CELL_CX * CX_POLYGONS + BORDER_CX * 2,
                CELL_CY * CY_POLYGONS + BORDER_CY * 2));
        addMouseListener(this);
    }

    private void createBuffers() {
        buff = new BufferedImage[3];

        // non-filled image
        buff[0] = new BufferedImage(CELL_CX + 1, CELL_CY + 1,
                BufferedImage.TYPE_INT_ARGB);
        Graphics2D gbi = buff[0].createGraphics();
        gbi.setColor(Color.WHITE);
        gbi.drawPolygon(HEXAGON);

        // filled image color 1
        buff[1] = new BufferedImage(CELL_CX + 1, CELL_CY + 1,
                BufferedImage.TYPE_INT_ARGB);
        gbi = buff[1].createGraphics();
        gbi.setColor(PALETTE[0]);
        gbi.fillPolygon(HEXAGON);
        gbi.setColor(Color.WHITE);
        gbi.drawPolygon(HEXAGON);

        // filled image color 2
        buff[2] = new BufferedImage(CELL_CX + 1, CELL_CY + 1,
                BufferedImage.TYPE_INT_ARGB);
        gbi = buff[2].createGraphics();
        gbi.setColor(PALETTE[1]);
        gbi.fillPolygon(HEXAGON);
        gbi.setColor(Color.WHITE);
        gbi.drawPolygon(HEXAGON);
    }

    @Override
    protected void paintComponent(Graphics g) {
        final Graphics2D g2d = (Graphics2D) g.create();
        if (isOpaque()) { // paint background
            g2d.setColor(getBackground());
            g2d.fillRect(0, 0, getWidth(), getHeight());
        }

        paintGraph(g2d);
        g2d.dispose();
    }

    private void paintGraph(Graphics2D g) {
        final Rectangle rc = g.getClipBounds();

        final int bx = rc.x / CELL_CX;
        final int by = rc.y / CELL_CY;

        final int cx = (rc.x + rc.width) / CELL_CX;
        final int cy = (rc.y + rc.height) / CELL_CY;

        for (int i = by; i <= cy; i++) {
            for (int j = bx; j <= cx; j++) {
                final Point pt = new Point(j, i);
                final Fill f = getFill(pt);
                if (f != null) {
                    if (f.color == 0) {
                        g.drawImage(buff[1], null, BORDER_CX + j * CELL_CX,
                                BORDER_CY + i * CELL_CY);
                    } else {
                        g.drawImage(buff[2], null, BORDER_CX + j * CELL_CX,
                                BORDER_CY + i * CELL_CY);
                    }
                } else {
                    g.drawImage(buff[0], null, BORDER_CX + j * CELL_CX,
                            BORDER_CY + i * CELL_CY);
                }
            }
        }
    }

    private Polygon polygonFromPoint(Point pt) {
        final int[] xpts = {pt.x + CELL_CX_SEG, pt.x + CELL_CX_SEG * 2,
                pt.x + CELL_CX, pt.x + CELL_CX, pt.x + CELL_CX_SEG * 2,
                pt.x + CELL_CX_SEG, pt.x, pt.x};

        final int[] ypts = {pt.y, pt.y, pt.y + CELL_CY_SEG,
                pt.y + CELL_CY_SEG * 2, pt.y + CELL_CY, pt.y + CELL_CY,
                pt.y + CELL_CY_SEG * 2, pt.y + CELL_CY_SEG};

        return new Polygon(xpts, ypts, xpts.length);
    }

    public void mouseClicked(MouseEvent e) {
        final Point pt = e.getPoint();
        final Insets insets = getInsets();
        final int width = getWidth() - insets.left - insets.right;
        final int height = getHeight() - insets.top - insets.bottom;

        final int cx = width / CELL_CX;
        final int cy = height / CELL_CY;

        final int px = (pt.x - BORDER_CX) / CELL_CX;
        final int py = (pt.y - BORDER_CY) / CELL_CY;

        final Polygon p = polygonFromPoint(new Point(BORDER_CX + px * CELL_CX,
                BORDER_CY + py * CELL_CY));

        String str = "";
        if (p.contains(pt) && px < cx && py < cy) {
            str = py + ", " + px;
            final Point ptf = new Point(px, py);
            Fill f = getFill(ptf);
            if (f != null) {
                filled.remove(f);
            } else {
                f = new Fill(ptf, current);
                filled.add(f);
                current = ++current % PALETTE.length;
            }

            final Rectangle rc = p.getBounds();
            repaint(rc);
        }

        final GraphApp app = GraphApp.getInstance();
        final GraphFrame frame = app.getMainFrame();
        frame.setStatusText(str);
    }

    /**
     * Determine whether current polygon is filled
     *
     * @param pt polygon index
     * @return fill instance if filled otherwise null
     */
    Fill getFill(Point pt) {
        final Iterator<Fill> it = filled.iterator();
        while (it.hasNext()) {
            final Fill f = it.next();
            if (f.pt.equals(pt)) {
                return f;
            }
        }

        return null;
    }

    public void mousePressed(MouseEvent e) {
    }

    public void mouseReleased(MouseEvent e) {
    }

    public void mouseEntered(MouseEvent e) {
    }

    public void mouseExited(MouseEvent e) {
    }
}
