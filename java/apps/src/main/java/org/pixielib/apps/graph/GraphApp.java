package org.pixielib.apps.graph;

public class GraphApp {

    private static GraphApp instance = null;
    private GraphFrame theFrame = null;

    /**
     * Private ctor
     */
    private GraphApp() {
        theFrame = new GraphFrame();
        theFrame.setVisible(false);
    }

    public static GraphApp getInstance() {
        if (instance == null) {
            instance = new GraphApp();
        }
        return instance;
    }

    /**
     * Application main entry point
     *
     * @param args; applications arguments
     */
    public static void main(String[] args) {
        final GraphApp theApp = GraphApp.getInstance();
        theApp.run(args);
    }

    public GraphFrame getMainFrame() {
        return theFrame;
    }

    /**
     * Run the applications
     *
     * @param args; application arguments
     */
    private void run(String[] args) {
        theFrame.setVisible(true);
    }
}
