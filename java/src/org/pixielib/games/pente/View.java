package org.pixielib.games.pente;

import javax.swing.*;
import java.awt.*;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.image.BufferedImage;

public class View extends JComponent implements MouseListener {

	/**
	 *
	 */
	private static final long serialVersionUID = 1L;
	private static final int CX_POLYGONS = Board.SIZE;
	private static final int CY_POLYGONS = Board.SIZE;
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
	private static final Color[] PALETTE = {new Color(0x00, 0x64, 0x00),
			new Color(0x8B, 0x00, 0x00)};

	private final Board board = Board.getInstance();
	private final Game game = Game.getInstance();
	private BufferedImage[] buff; // image buffers

	public View() {
		init();
	}

	private void init() {
		createBuffers();
		setOpaque(true);
		setBorder(BorderFactory.createLoweredBevelBorder());
		setBackground(new Color(0xFF, 0xEF, 0xD5));
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
		gbi.setColor(Color.BLACK);
		gbi.drawPolygon(HEXAGON);

		// filled image color 1
		buff[1] = new BufferedImage(CELL_CX + 1, CELL_CY + 1,
				BufferedImage.TYPE_INT_ARGB);
		gbi = buff[1].createGraphics();
		gbi.setColor(PALETTE[0]);
		gbi.fillPolygon(HEXAGON);
		gbi.setColor(Color.BLACK);
		gbi.drawPolygon(HEXAGON);

		// filled image color 2
		buff[2] = new BufferedImage(CELL_CX + 1, CELL_CY + 1,
				BufferedImage.TYPE_INT_ARGB);
		gbi = buff[2].createGraphics();
		gbi.setColor(PALETTE[1]);
		gbi.fillPolygon(HEXAGON);
		gbi.setColor(Color.BLACK);
		gbi.drawPolygon(HEXAGON);
	}

	@Override
	protected void paintComponent(Graphics g) {
		final Graphics2D g2d = (Graphics2D) g.create();
		if (isOpaque()) { // paint background
			g2d.setColor(getBackground());
			g2d.fillRect(0, 0, getWidth(), getHeight());
		}

		paintBoard(g2d);
		g2d.dispose();
	}

	private void paintBoard(Graphics2D g) {
		final Rectangle rc = getVisibleRect();

		final int bx = rc.x / CELL_CX;
		final int by = rc.y / CELL_CY;

		final int cx = (rc.x + rc.width) / CELL_CX;
		final int cy = (rc.y + rc.height) / CELL_CY;

		for (int i = bx; i < cx; i++) {
			for (int j = by; j < cy; j++) {
				BufferedImage image = null;
				final int type = board.markType(i, j);
				switch (type) {
					case Graph.VT_E:
						image = buff[0];
						break;
					case Graph.VT_O:
						image = buff[1];
						break;
					case Graph.VT_X:
						image = buff[2];
						break;
				}
				g.drawImage(image, null, BORDER_CX + i * CELL_CX, BORDER_CY + j
						* CELL_CY);
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

	public void mousePressed(MouseEvent e) {
		Point pt = e.getPoint();
		final Insets insets = getInsets();
		final int width = getWidth() - insets.left - insets.right;
		final int height = getHeight() - insets.top - insets.bottom;

		final int cx = width / CELL_CX;
		final int cy = height / CELL_CY;

		final int px = (pt.x - BORDER_CX) / CELL_CX;
		final int py = (pt.y - BORDER_CY) / CELL_CY;

		Polygon p = polygonFromPoint(new Point(BORDER_CX + px * CELL_CX,
				BORDER_CY + py * CELL_CY));
		if (p.contains(pt) && px < cx && py < cy) {
			final int type = board.markType(px, py);
			if (type == Graph.VT_E) {
				board.mark(px, py, Graph.VT_O);
				Rectangle rc = p.getBounds();
				repaint(rc);
				pt = game.getMachineTurn();
				if (pt != null) {
					p = polygonFromPoint(new Point(BORDER_CX + pt.x * CELL_CX,
							BORDER_CY + pt.y * CELL_CY));
					rc = p.getBounds();
					repaint(rc);
				}
			}
		}
	}

	public void mouseClicked(MouseEvent e) {
	}

	public void mouseReleased(MouseEvent e) {
	}

	public void mouseEntered(MouseEvent e) {
	}

	public void mouseExited(MouseEvent e) {
	}
}
