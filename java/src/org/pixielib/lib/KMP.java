package org.pixielib.lib;

public class KMP {

	private final int next[];

	public KMP(String str) {
		next = new int[str.length()];
		init(str);
	}

	void init(String str) {
		final char[] pat = str.toCharArray();
		int i = 0, j = next[0] = -1;
		final int m = pat.length;

		while (i < m) {
			if (j == -1 || pat[i] == pat[j]) {
				i++;
				j++;
				if (i <= m - 1) {
					next[i] = (pat[j] == pat[i]) ? next[j] : j;
				}
			} else {
				j = next[j];
			}
		}
	}

	public static void main(String[] args) {

		if (args.length == 0) {
			System.err.println("usage: KMP string");
			System.exit(-1);
		}
	}
}
