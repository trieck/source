package org.trieck.apps;

public class StatusTest {

	/**
	 * Private ctor
	 */
	private StatusTest() {
	}

	/**
	 * Run the applications
	 * @param args; application arguments
	 */
	private void run(String[] args) {
		StatusFrame theFrame = new StatusFrame();
		theFrame.setVisible(true);
	}

	/**
	 * Application main entry point
	 * @param args; applications arguments
	 */
	public static void main(String[] args) {
		StatusTest test = new StatusTest();
		test.run(args);
	}
}
