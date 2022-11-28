package org.pixielib.apps.odb;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;
import java.net.UnknownHostException;
import java.util.Iterator;
import java.util.List;
import java.util.Vector;

public class ClientThread implements Runnable {

    private static final int WAIT_TIME = 2000;

    private final List<ActionListener> listeners = new Vector<ActionListener>();
    private final ODBClient odb = new ODBClient("localhost");
    private String poolid = "";

    public ClientThread() {
    }

    public void addListener(ActionListener listener) {
        listeners.add(listener);
    }

    public void run() {

        try {
            poolid = odb.makePool();
        } catch (final IOException ioe) {
            System.err.println(ioe);
            return;
        }

        String key = null, val = null;
        for (; ; ) {

            /* always try to destroy the object first */
            try {
                if (key != null) {
                    odb.destroyObject(poolid, key);
                }
            } catch (final IOException e) {
            }

            try {
                key = odb.createString(poolid, "This is a value");

                odb.setString(poolid, key, randomString());

                val = odb.getString(poolid, key);

                notifyListeners(key, val);
                sleep(WAIT_TIME);

            } catch (final UnknownHostException uhe) {
                System.err.println(uhe);
            } catch (final IOException ioe) {
                System.err.println(ioe);
            }
        }
    }

    private void notifyListeners(String key, String val) {

        final RowData row = new RowData(key, val, 0, 0, 0);
        final ActionEvent event = new ActionEvent(row, 0, "newResponse");

        final Iterator<ActionListener> it = listeners.iterator();
        while (it.hasNext()) {
            final ActionListener listener = it.next();
            listener.actionPerformed(event);
        }

    }

    private boolean sleep(long millis) {
        try {
            Thread.sleep(millis);
        } catch (final InterruptedException e) {
            return false;
        }

        return true;
    }

    private String randomString() {
        final StringBuffer buf = new StringBuffer();

        for (int i = 0, c; i < 20; i++) {
            c = 32 + (int) (Math.random() * 94);
            buf.append((char) c);
        }

        return buf.toString();
    }
}
