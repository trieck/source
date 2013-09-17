package org.pixielib.content;

import org.pixielib.util.Timer;
import org.pixielib.xml.QParser;

import java.io.*;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Stack;

public class XMLIndexer extends QParser {

	private Repository repos;       // repository instance
	private Index index;            // index instance
	private short filenum;          // current file number while indexing
	private int offset;             // offset into current file
	private Stack<String> elements; // stack of elements seen
	private IndexFields fields;     // set of top-level fields for indexing

	public XMLIndexer() throws IOException {
		repos = Repository.getInstance();
		elements = new Stack<>();
	}

	/**
	 * Process an element while parsing
	 *
	 * @param name the name of the tag
	 * @param tag  the tag value
	 */
	@Override
	public void startElement(String name, String tag) {
		elements.push(name);
		if (name.equals("record")) {
			offset = (int) Math.max(0, getPosition() - tag.length());
			assert (offset < ((long) 1 << Anchor.OFFSET_BITS - 1));
		}
	}

	@Override
	public void endElement() {
		elements.pop();
	}

	/**
	 * Process a value while parsing
	 *
	 * @param text the text encountered
	 */
	@Override
	public void value(String text) {

		if (!isTopLevel())
			return;

		if ((text = text.trim()).length() == 0)
			return; // whitespace

		String field = elements.peek();

		Lexer lexer = new Lexer(new StringReader(text));
		long anchor;

		try {
			String term, tok;
			for (short i = 0; ((tok = lexer.getToken()).length()) != 0; i++) {
				term = String.format("%s:%s", field, tok);
				anchor = Anchor.makeAnchorID(filenum, offset, i);
				index.insert(term, anchor);
			}
		} catch (IOException e) {
		}
	}

	public void load(String db, String[] aFields) throws IOException {

		fields = new IndexFields(aFields);	// top-level index fields

		File dir = repos.mapPath(db);
		List<File> files = expand(dir);
		if (files.isEmpty())
			throw new IOException(
					String.format("no content files found in \"%s\".",
							dir.getCanonicalPath())
			);

		index = new Index();
		loadfiles(files);
		index.write(db, fields);
	}

	private void loadfiles(List<File> files)
			throws IOException {
		for (File f : files) {
			setPosition(0);
			loadfile(f);
			filenum++;
		}
	}

	private void loadfile(File file)
			throws IOException {
		setPosition(0);
		parse(new FileReader(file));
	}

	private List<File> expand(File dir) {
		List<File> result = new ArrayList<>();

		// list xml files
		File[] files = dir.listFiles(new FilenameFilter() {
			@Override
			public boolean accept(File dir, String name) {
				return name.endsWith(".xml");
			}
		}
		);

		result.addAll(Arrays.asList(files));

		return result;
	}

	private boolean isTopLevel() {
		if (elements.size() == 0)
			return false;

		String field = elements.peek();

		return fields.isTopLevel(field);
	}

	public static void main(String[] args) {

		if (args.length < 2) {
			System.err.println("usage: XMLIndexer database fields");
			System.exit(1);
		}

		Timer t = new Timer();

		try {
			XMLIndexer indexer = new XMLIndexer();
			indexer.load(args[0], Arrays.copyOfRange(args, 1, args.length));
		} catch (IOException e) {
			System.err.println(e);
			System.exit(1);
		}

		System.out.printf("    elapsed time %s\n", t);
	}
}
