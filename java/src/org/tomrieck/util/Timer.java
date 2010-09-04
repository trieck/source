package org.tomrieck.util;

import java.text.DecimalFormat;
import java.text.MessageFormat;

public class Timer {

	private long start;
	private DecimalFormat df = new DecimalFormat("#00");

	public Timer() {
		start = System.currentTimeMillis();
	}

	public String toString() {
		StringBuffer output = new StringBuffer();

		long end = System.currentTimeMillis();
		long diff = end - start;

		long hours = (diff / 1000) / 3600;
		long minutes = (diff / 1000 % 3600) / 60;
		long seconds = (diff / 1000) % 60;
		long hundreths = (diff % 1000) / 10;

		if (hours != 0) {
			output.append(MessageFormat.format("{0}:{1}:{2} hours",
				new Object[] { df.format(hours), df.format(minutes), df.format(seconds) }));
		} else if (minutes != 0) {
			output.append(MessageFormat.format("{0}:{1} minutes",
				new Object[] { df.format(minutes), df.format(seconds) }));
		} else {
			output.append(MessageFormat.format("{0}:{1} seconds",
				new Object[] { df.format(seconds), df.format(hundreths) }));
		}

		return output.toString();
	}

	public static void main(String[] args) {
		if (args.length == 0) {
			System.err.println("usage: Timer millis");
			System.exit(1);
		}

		Timer t = new Timer();

		try {
			Thread.sleep(Integer.parseInt(args[0]));
		} catch (InterruptedException e) {
			;
		} catch (NumberFormatException e) {
			;
		}

		System.out.println(t);
	}

}
