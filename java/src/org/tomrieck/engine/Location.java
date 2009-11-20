package org.tomrieck.engine;

public class Location {

	private final int word;
	private final int offset;

	public int getWord() {
		return word;
	}

	public int getOffset() {
		return offset;
	}

	public Location(int word, int offset) {
		this.word = word;
		this.offset = offset;
	}
}
