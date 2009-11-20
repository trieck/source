package org.tomrieck.apps;

import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;

public class MakeArray {

	public static void main(String[] args) {
		if (args.length == 0) {
			usage();
		}

		try {
			final InputStream is = new FileInputStream(args[0]);

			System.out.println("private static final byte[] IMAGE = {");

			for (int i = 0, c = 0; ((c = is.read()) != -1); i++) {
				final String x = "(byte)0x" + Integer.toString(c & 0xff, 16);
				if (i > 0) {
					System.out.print(", ");
				}
				if ((i % 8) == 0) {
					System.out.println("");
				}
				System.out.print(x);
			}
			is.close();
			System.out.println("\n};");
		} catch (final IOException ioe) {
			System.err.println(ioe.toString());
			System.exit(-1);
		}
	}

	private static void usage() {
		System.err.println("usage: MakeArray file");
		System.exit(-1);
	}
}
