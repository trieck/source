package org.trieck.apps.odb;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;
import java.net.UnknownHostException;
import java.util.Iterator;
import java.util.List;
import java.util.Vector;

public class ClientThread implements Runnable {

    private static final int WAIT_TIME = 2000;

    private List<ActionListener> listeners = new Vector<ActionListener>();
    private String poolid = "";
    private ODBClient odb = new ODBClient("localhost");

    public ClientThread() {
    }

    public void addListener(ActionListener listener) {
        listeners.add(listener);
    }

    public void run() {

        try {
            poolid = odb.makePool();
        } catch (IOException ioe) {
            System.err.println(ioe);
            return;
        }

        String key = null, val = null;
        for (; ;) {

            /* always try to destroy the object first */
            try {
                if (key != null) odb.destroyObject(poolid, key);
            } catch (IOException e) {
                ;
            }

            try {
                key = odb.createString(poolid, "This is a value");

                odb.setString(poolid, key, randomString());

                val = odb.getString(poolid, key);

                notifyListeners(key, val);
                sleep(WAIT_TIME);

            } catch (UnknownHostException uhe) {
                System.err.println(uhe);
            } catch (IOException ioe) {
                System.err.println(ioe);
            }
        }
    }

    private void notifyListeners(String key, String val) {

        RowData row = new RowData(key, val, 0, 0, 0);
        ActionEvent event = new ActionEvent(row, 0, "newResponse");

        Iterator<ActionListener> it = listeners.iterator();
        while (it.hasNext()) {
            ActionListener listener = it.next();
            listener.actionPerformed(event);
        }

    }

    private boolean sleep(long millis) {
        try {
            Thread.sleep(millis);
        } catch (InterruptedException e) {
            return false;
        }

        return true;
    }

    private String randomString() {
        StringBuffer buf = new StringBuffer();

        for (int i = 0, c; i < 20; i++) {
            c = 32 + (int)(Math.random() * 94);
            buf.append((char)c);
        }

        return buf.toString();
    }
}
