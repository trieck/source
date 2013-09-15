package org.pixielib.io;

import java.io.*;

public class FileUtil {

	private static final int BUF_SIZE = 8192;

	public static String readFile(String file)
			throws IOException {

		Reader reader = new BufferedReader(new FileReader(file));

		StringBuilder builder = new StringBuilder();
		char[] buffer = new char[BUF_SIZE];
		int read;
		while ((read = reader.read(buffer, 0, buffer.length)) > 0) {
			builder.append(buffer, 0, read);
		}

		reader.close();

		return builder.toString();
	}

	public static void writeFile(String filename, String contents)
			throws IOException {

		Writer writer = new FileWriter(filename);
		writer.write(contents);
		writer.flush();
		writer.close();
	}
}
