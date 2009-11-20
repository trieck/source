package org.tomrieck.testing;

import java.util.HashMap;
import java.util.Map;

public class MapTest {

	private static int randomInt(int lo, int hi) {
		return lo + (int) (Math.random() * (hi - lo));
	}

	private static int randomChar() {
		return randomInt(32, 126);
	}

	private static String randomKey() {
		final int nlen = randomInt(28, 32);

		final char[] buf = new char[nlen];

		for (int i = 0; i < nlen; i++) {
			buf[i] = (char) randomChar();
		}

		return new String(buf);
	}

	private static String randomVal() {
		final int nlen = randomInt(35, 40);

		final char[] buf = new char[nlen];

		for (int i = 0; i < nlen; i++) {
			buf[i] = (char) randomChar();
		}

		return new String(buf);
	}

	public static void main(String[] args) {

		final long start = System.currentTimeMillis();

		final Map<String, String> map = new HashMap<String, String>();

		String key, val;

		int i;
		final int n = 100000;
		for (i = 0; i < n; i++) {
			key = randomKey();
			val = randomVal();
			;
			map.put(key, val);
		}

		final long end = System.currentTimeMillis();

		final float time = (end - start) / 1000.0f;

		System.out.println("   inserted " + n + " items.");
		System.out.println("   elapsed time " + time + " seconds.");
	}
}
