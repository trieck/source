package org.pixielib.util;

public class StringUtil {

	public static String comma(long i) {
		StringBuilder builder = new StringBuilder();

		String rep = Long.toString(i);

		int n = rep.length();

		for (int j = n - 1, k = 1; j >= 0; j--, k++) {
			builder.append(rep.charAt(j));
			if (k % 3 == 0 && j > 0 && j < n - 1)
				builder.append(',');
		}

		String output = StringUtil.reverse(builder.toString());

		return output;
	}

	public static String reverse(String input) {
		StringBuilder builder = new StringBuilder();

		int n = input.length() - 1;

		for (int i = n; i >= 0; i--) {
			builder.append(input.charAt(i));
		}

		return builder.toString();
	}
}
