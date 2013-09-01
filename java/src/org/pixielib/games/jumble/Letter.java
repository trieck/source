package org.pixielib.games.jumble;

public class Letter implements Comparable<Letter> {
	char c;     // character
	int count;  // count of letter in word

	public Letter(char c) {
		this.c = c;
		this.count = 1;
	}

	public int compareTo(Letter rhs) {
		return (this.c < rhs.c ? -1 : (this.c == rhs.c ? 0 : 1));
	}
}