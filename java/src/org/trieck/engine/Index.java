package org.trieck.engine;

import java.io.IOException;

public class Index {

	private Parser parser = null;

	public Index(String filename) throws IOException {
		parser = new Parser(filename);
		parser.parse();
	}

	public Locality search(String query) {
		return adjacent(query.toLowerCase().split("[\r\n\t ]+"));
	}

	private Locality adjacent(String[] tokens) {
		Locality left = new Locality();

		if (tokens.length == 0) {
			return left;
		}
		if (tokens.length >= 1) {
			left = parser.get(tokens[0]);
		}
		left = left == null ? new Locality() : left;

		for (int i = 0; left.size() > 0 && i < tokens.length - 1;) {
			left = left.adjacent(parser.get(tokens[++i]));
		}

		return left;
	}
}
