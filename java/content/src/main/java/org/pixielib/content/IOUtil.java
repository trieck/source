package org.pixielib.content;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.Arrays;

public class IOUtil {

	private static final int BUF_SIZE = 16384;

	private IOUtil() {
	}

	/**
	 * Transfer bytes from input stream to output stream
	 *
	 * @param is, the input stream
	 * @param os, the output stream
	 * @param size, the number of bytes to transfer
	 * @throws IOException, if unable to transfer size bytes
	 */
	public static void transfer(InputStream is, OutputStream os, int size) throws IOException {

		byte[] buf = new byte[BUF_SIZE];

		int m;

		while (size > 0) {
			m = Math.min(BUF_SIZE, size);

			if (is.read(buf, 0, m) != m) {
				throw new IOException("unable to read from input stream.");
			}

			os.write(buf, 0, m);

			size -= m;
		}
	}

	/**
	 * Write a continuous series of bytes to output stream
	 *
	 * @param os, the output stream
	 * @param size, the number of bytes to write
	 * @param b, the byte to write
	 * @throws IOException, if the bytes cannot be written
	 */
	public static void fill(OutputStream os, long size, byte b) throws IOException {

		byte[] buf = new byte[BUF_SIZE];

		Arrays.fill(buf, b);

		int m;
		while (size > 0) {
			m = (int) Math.min(BUF_SIZE, size);
			os.write(buf, 0, m);
			size -= m;
		}
	}

	private static void warning(String format, Object... args) {
		String message = String.format(format, args);
		System.err.printf("   {WARNING} : %s\n", message);
	}
}
