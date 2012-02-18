package org.pixielib.xml;

import org.pixielib.io.FileUtil;

import java.io.*;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.regex.Pattern;

public class XMLASCIIEncoder {

	private static final Pattern NOT_ASCII = Pattern.compile("[^\\p{ASCII}]");

	public void encode(File file) throws IOException {
		String contents = FileUtil.readFile(file.getCanonicalPath());
		contents = NOT_ASCII.matcher(contents).replaceAll("");
		
		OutputStreamWriter writer = new OutputStreamWriter(new FileOutputStream(file), "US-ASCII");
		writer.write(contents);
		writer.flush();
		writer.close();
	}

	private static List<File> expand(File dir) {
		List<File> result = new ArrayList<File>();

		// list xml files
		File[] files = dir.listFiles(new FilenameFilter() {
			public boolean accept(File dir, String name) {
				return name.endsWith(".xml");
			}
		}
		);

		result.addAll(Arrays.asList(files));

		return result;
	}

	public void encode(String path)
				throws IOException {

			File dir = new File(path);
			if (!dir.isDirectory()) {
				throw new IOException(String.format("\"%s\" is not a directory.",
						dir.getCanonicalPath()));
			}

			List<File> files = expand(dir);
			if (files.size() == 0) {
				throw new IOException(
						String.format("no xml files found in \"%s\".",
								dir.getCanonicalPath())
				);
			}

			for (File f : files) {
				encode(f);
			}
		}

	public static void main(String[] args) {
		if (args.length < 1) {
			System.err.println("usage: XMLASCIIEncoder path");
			System.exit(1);
		}

		XMLASCIIEncoder encoder = new XMLASCIIEncoder();

		try {
			encoder.encode(args[0]);
		} catch (IOException e) {
			System.err.println(e);
			System.exit(2);
		}
	}
}
