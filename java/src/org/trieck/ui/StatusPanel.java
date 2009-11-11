package org.trieck.ui;

import javax.swing.*;
import java.awt.*;

public class StatusPanel extends JPanel {

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;

	private static final Font STATUS_FONT = new Font("Arial", Font.TRUETYPE_FONT, 18);

	private static final int GRIPPER_OFFSET_X = 4;
	private static final int GRIPPER_OFFSET_Y = 3;
	private static final int GRIPPER_WIDTH = 3;
	private static final int GRIPPER_SEP_WIDTH = 3;

    private boolean gripper;    // draw the gripper?
    private JLabel label = null;

	/**
	 * Public ctor
	 */
	public StatusPanel() {
        init();
	}

    public boolean hasGripper() { return gripper; }
    public void setGripper(boolean b) {
        gripper = b;
        invalidate();
    }

	/**
	 * Initialize component
	 */
	private void init() {
        label = new JLabel();
        label.setVisible(false);
        label.setBorder(BorderFactory.createEtchedBorder());
        setLayout(new BorderLayout());
        add(label, BorderLayout.EAST);

		setFont(STATUS_FONT);
		FontMetrics fm = getFontMetrics(STATUS_FONT);
		setBorder(BorderFactory.createEtchedBorder());
		Insets insets = getInsets();
		setPreferredSize(new Dimension(0, fm.getHeight() + insets.top + insets.bottom));
		setOpaque(true);
	}

	/**
	 * Paint component
	 * @param g graphics context
	 */
	@Override
	protected void paintComponent(Graphics g) {
        Graphics2D g2d = (Graphics2D)g;
        super.paintComponent(g2d);
        if (gripper) {
		    drawGripper(g2d);
        }
	}

	/**
	 * Draw gripper bar
	 * @param g graphics context
	 */
	private void drawGripper(Graphics2D g) {
        Rectangle rect = getBounds();

		int x = GRIPPER_OFFSET_X;
		int y = GRIPPER_OFFSET_Y;
		int cy = rect.height - (GRIPPER_OFFSET_Y * 2);

		g.setColor(Color.LIGHT_GRAY);
		g.fill3DRect(x, y, GRIPPER_WIDTH, cy, true);
		g.fill3DRect(x + GRIPPER_SEP_WIDTH, y, GRIPPER_WIDTH, cy, true);
	}

    public void setText(String str) {
        label.setText(str);
        label.setVisible(str.length()>0);
    }
}
