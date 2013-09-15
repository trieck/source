package org.pixielib.webapps.jumble;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

public class Letters implements Iterable<Letter> {

	private List<Letter> letters;        // counts of each letter

	public Letters() {
		letters = new ArrayList<Letter>();
	}

	public void clear() {
		letters.clear();
	}

	public void put(char c) {
		Letter letter;
		if ((letter = lookup(c)) != null) {
			letter.count++;
		} else {
			letters.add(new Letter(c));
		}
	}

	public Letter get(int index) {
		if (index < 0 || index >= letters.size())
			return null;

		return letters.get(index);
	}


	public Iterator<Letter> iterator() {
		return letters.iterator();
	}

	public Letter lookup(char c) {
		for (Letter l : letters) {
			if (l.c == c)
				return l;
		}

		return null;
	}

}
