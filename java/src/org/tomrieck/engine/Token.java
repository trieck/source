package org.tomrieck.bible;

import java.util.ArrayList;
import java.util.List;

public class Token {

	public static final int TT_NONE = 0;
	public static final int TT_BOOK = 1;
	public static final int TT_VERSE = 2;
	public static final int TT_WORDS = 3;

	private final int tokenType;
	private final String tokenText;
	private String[] tokenWords;

	public Token(int type, String text) {
		tokenType = type;
		tokenText = text;
		parse();
	}

	private void parse() {
		final List<String> v = new ArrayList<String>();

		final String[] words = tokenText.split("\\s");

		final StringBuffer word = new StringBuffer();
		for (final String element : words) {
			word.setLength(0);
			for (int j = 0; j < element.length(); j++) {
				if (Character.isLetterOrDigit(element.charAt(j))) {
					word.append(Character.toLowerCase(element.charAt(j)));
				}
			}

			if (word.length() > 0) {
				v.add(word.toString());
			}
		}

		tokenWords = new String[v.size()];
		v.toArray(tokenWords);
	}

	public int getTokenType() {
		return tokenType;
	}

	public String getTokenWord(int index) {
		if (index >= tokenWords.length) {
			return "";
		}

		return tokenWords[index];
	}

	public int getTokenWordCount() {
		return tokenWords.length;
	}

	public String getTokenWords() {
		final StringBuffer buffer = new StringBuffer();

		for (int i = 0; i < tokenWords.length; i++) {
			if (i > 0) {
				buffer.append(' ');
			}
			buffer.append(tokenWords[i]);
		}
		return buffer.toString();
	}

	public String[] getTokenWords(int start, int length) {
		if (length <= 0) {
			return new String[0];
		}

		if (start < 0 || start + (length - 1) >= tokenWords.length) {
			throw new IllegalArgumentException();
		}

		final String[] words = new String[length];

		System.arraycopy(tokenWords, start, words, 0, length);

		return words;
	}

	public String getTokenText() {
		return tokenText;
	}
}
