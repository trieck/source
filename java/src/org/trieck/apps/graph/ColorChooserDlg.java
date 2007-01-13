package org.trieck.apps.graph;

import javax.swing.*;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
import java.awt.*;

public class ColorChooserDlg extends JDialog
        implements ChangeListener {

    private JColorChooser tcc;

    public ColorChooserDlg(Frame owner) {
        super(owner, "Color Chooser", true);

        JPanel content = new JPanel(new BorderLayout());
        content.setOpaque(true);
        setContentPane(content);
        pack();

           /*
        tcc = new JColorChooser();
        tcc.getSelectionModel().addChangeListener(this);
        tcc.setBorder(BorderFactory.createTitledBorder("Choose Color"));
        add(tcc, BorderLayout.PAGE_END);

        this.
        */
    }

    public void stateChanged(ChangeEvent e) {
        Color newColor = tcc.getColor();
    }

    public void showModal() {
        setLocationRelativeTo(getParent());
        setVisible(true);

        /*
        // Make sure we have nice window decorations.
        JFrame.setDefaultLookAndFeelDecorated(true);

        JDialog dlg = new JDialog

        //Create and set up the window.
        JFrame frame = new JFrame("ColorChooserDemo");
        frame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);

        //Create and set up the content pane.
        JComponent newContentPane = new ColorChooserDlg();
        newContentPane.setOpaque(true); //content panes must be opaque
        frame.setContentPane(newContentPane);

        //Display the window.
        frame.pack();
        frame.setVisible(true);
*/
    }

}

