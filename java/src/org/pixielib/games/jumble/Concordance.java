package org.pixielib.games.jumble;

import java.io.IOException;
import java.io.InputStreamReader;
import java.util.HashSet;

public class Concordance {

	private static Concordance theInstance;
	private HashSet<String> table;

	private Concordance() throws IOException {
		table = new HashSet<String>();
		load();
	}

	public static synchronized Concordance getInstance() throws IOException {
		if (theInstance == null) {
			theInstance = new Concordance();
		}

		return theInstance;
	}

	public boolean lookup(String word) {
		return table.contains(word.toLowerCase());
	}

	private void load() throws IOException {

		ConcordanceReader reader = new ConcordanceReader(new InputStreamReader(getClass().getResourceAsStream("/jumble.concordance")));

		String word;
		while ((word = reader.getWord()).length() > 0) {
			table.add(word);
		}
	}
}
