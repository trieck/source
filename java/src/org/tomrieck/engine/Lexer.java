package org.tomrieck.engine;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.Reader;
import java.util.regex.Pattern;

public class Lexer {

	private static final Pattern BOOK_REGEX = Pattern
			.compile("Book\\s[0-9]+\\s+[0-9\\s]*[a-zA-Z0-9 ]+");

	private static final Pattern VERSE_REGEX = Pattern
			.compile("[0-9]{3}:[0-9]{3}.*");

	private final BufferedReader reader;

	public Lexer(Reader r) {
		reader = new BufferedReader(r);
	}

	public Token getToken() throws IOException {

		String line;
		while ((line = reader.readLine()) != null) {
			if (line.length() == 0) {
				continue;
			}

			if (BOOK_REGEX.matcher(line).matches()) { // book
				return new Token(Token.TT_BOOK, line);
			}

			if (VERSE_REGEX.matcher(line).matches()) { // verse
				return new Token(Token.TT_VERSE, line);
			}

			return new Token(Token.TT_WORDS, line); // words
		}

		return new Token(Token.TT_NONE, "");
	}
}
