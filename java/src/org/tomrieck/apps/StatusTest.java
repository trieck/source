package org.tomrieck.apps;

public class StatusTest {

	/**
	 * Private ctor
	 */
	private StatusTest() {
	}

	/**
	 * Run the applications
	 * 
	 * @param args;
	 *            application arguments
	 */
	private void run(String[] args) {
		final StatusFrame theFrame = new StatusFrame();
		theFrame.setVisible(true);
	}

	/**
	 * Application main entry point
	 * 
	 * @param args;
	 *            applications arguments
	 */
	public static void main(String[] args) {
		final StatusTest test = new StatusTest();
		test.run(args);
	}
}
