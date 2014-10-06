package org.pixielib.apps.odb;

import java.net.URL;

public class ODBManager {
    private static final String RES_PATH = "/img";
    private static ODBManager instance = null;
    private ODBFrame theFrame = null;
    private ClientThread clientThread = null;

    /**
     * Private ctor
     */
    private ODBManager() {
        instance = this;
        theFrame = new ODBFrame();
        theFrame.setVisible(false);
        clientThread = new ClientThread();
        clientThread.addListener(getTable());
    }

    public static ODBManager getInstance() {
        if (instance == null) {
            new ODBManager();
        }
        return instance;
    }

    public static void main(String[] args) {
        final ODBManager theApp = ODBManager.getInstance();
        theApp.run(args);
    }

    public String getResourcePath() {
        return getClass().getResource(RES_PATH).getPath();
    }

    public URL getResource(String r) {
        return getClass().getResource(RES_PATH + '/' + r);
    }

    public ODBTable getTable() {
        return theFrame.getTable();
    }

    /**
     * Run the applications
     *
     * @param args; application arguments
     */
    private void run(String[] args) {
        new Thread(clientThread).start();
        theFrame.setVisible(true);
    }

    public void exit(int status) {
        System.exit(status);
    }
}
