package org.trieck.games.ttt;

import java.awt.Color;
import java.awt.Cursor;
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

import javax.swing.BorderFactory;
import javax.swing.JComponent;

public class View extends JComponent implements MouseListener {

	public static final int BORDER_CX = 3;
	public static final int BORDER_CY = 3;
	public static final int CELL_CX = 513 / Board.BOARD_SIZE;
	private static final int CELL_CX_SEG = CELL_CX / 3;
	public static final int CELL_CY = 513 / Board.BOARD_SIZE;
	private static final int CELL_CY_SEG = CELL_CY / 3;
	private static final int CX_POLYGONS = Board.BOARD_SIZE;
	private static final int CY_POLYGONS = Board.BOARD_SIZE;

	private static final int[] XPOINTS = { CELL_CX_SEG, CELL_CX_SEG * 2,
			CELL_CX, CELL_CX, CELL_CX_SEG * 2, CELL_CX_SEG, 0, 0 };
	private static final int[] YPOINTS = { 0, 0, CELL_CY_SEG, CELL_CY_SEG * 2,
			CELL_CY, CELL_CY, CELL_CY_SEG * 2, CELL_CY_SEG };

	private static final Polygon HEXAGON = new Polygon(XPOINTS, YPOINTS,
			XPOINTS.length);
	private static final Color[] PALETTE = { new Color(0x00, 0x64, 0x00),
			new Color(0x8B, 0x00, 0x00) };

	private static final long serialVersionUID = 1L;

	private BufferedImage[] buff; // image buffers
	private final TicTacToe theGame = TicTacToe.getInstance();

	public View() {
		init();
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

	private void init() {
		createBuffers();
		setOpaque(true);
		setBorder(BorderFactory.createLoweredBevelBorder());
		setBackground(new Color(0xFF, 0xEF, 0xD5));
		setPreferredSize(new Dimension(CELL_CX * CX_POLYGONS + BORDER_CX * 2,
				CELL_CY * CY_POLYGONS + BORDER_CY * 2));
		addMouseListener(this);
	}

	@Override
	public void mouseClicked(MouseEvent e) {
		final Board board = theGame.getBoard();
		if (board.available() == 0) {
			return;
		}

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
			final int color = board.getPiece(px, py);
			if (color == Board.COLOR_EMPTY) {
				board.setPiece(px, py, Board.COLOR_NOUGHT);
				Rectangle rc = p.getBounds();
				paintImmediately(rc);

				setCursor(Cursor.getPredefinedCursor(Cursor.WAIT_CURSOR));
				pt = theGame.getMachineTurn();
				setCursor(Cursor.getDefaultCursor());

				if (pt != null) {
					p = polygonFromPoint(new Point(BORDER_CX + pt.x * CELL_CX,
							BORDER_CY + pt.y * CELL_CY));
					rc = p.getBounds();
					repaint(rc);
				}
			}
		}
	}

	@Override
	public void mouseEntered(MouseEvent e) {
	}

	@Override
	public void mouseExited(MouseEvent e) {
	}

	@Override
	public void mousePressed(MouseEvent e) {
	}

	@Override
	public void mouseReleased(MouseEvent e) {
	}

	private void paintBoard(Graphics2D g) {
		final Board board = theGame.getBoard();
		final Rectangle rc = getVisibleRect();

		final int bx = rc.x / CELL_CX;
		final int by = rc.y / CELL_CY;

		final int cx = (rc.x + rc.width) / CELL_CX;
		final int cy = (rc.y + rc.height) / CELL_CY;

		int color;
		for (int i = bx; i < cx; i++) {
			for (int j = by; j < cy; j++) {
				BufferedImage image = null;
				color = board.getPiece(i, j);
				switch (color) {
				case Board.COLOR_EMPTY:
					image = buff[0];
					break;
				case Board.COLOR_NOUGHT:
					image = buff[1];
					break;
				case Board.COLOR_CROSS:
					image = buff[2];
					break;
				}
				g.drawImage(image, null, BORDER_CX + i * CELL_CX, BORDER_CY + j
						* CELL_CY);
			}
		}
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

	private Polygon polygonFromPoint(Point pt) {
		final int[] xpts = { pt.x + CELL_CX_SEG, pt.x + CELL_CX_SEG * 2,
				pt.x + CELL_CX, pt.x + CELL_CX, pt.x + CELL_CX_SEG * 2,
				pt.x + CELL_CX_SEG, pt.x, pt.x };

		final int[] ypts = { pt.y, pt.y, pt.y + CELL_CY_SEG,
				pt.y + CELL_CY_SEG * 2, pt.y + CELL_CY, pt.y + CELL_CY,
				pt.y + CELL_CY_SEG * 2, pt.y + CELL_CY_SEG };

		return new Polygon(xpts, ypts, xpts.length);
	}

}
