package org.tomrieck.bible;

import java.nio.ByteBuffer;
import java.nio.IntBuffer;
import java.util.ArrayList;
import java.util.List;

public class DocList {

	private final List<Integer> docs = new ArrayList<Integer>();

	public DocList() {
	}

	public DocList(byte[] bytes) {
		if (bytes.length % 4 != 0) {
			throw new IllegalArgumentException();
		}

		final IntBuffer ib = ByteBuffer.wrap(bytes).asIntBuffer();

		for (int i = 0; i < bytes.length / 4; i++) {
			docs.add(ib.get());
		}
	}

	public int length() {
		return docs.size();
	}

	public int getDoc(int i) {
		if (i < 0 || i >= docs.size()) {
			throw new IllegalArgumentException();
		}

		return docs.get(i);
	}

	public static DocList union(DocList lhs, DocList rhs) {
		final DocList results = new DocList();

		return results;
	}

	public static DocList intersection(DocList lhs, DocList rhs) {
		final DocList results = new DocList();

		int i = 0, j = 0;
		int leftdoc, rightdoc;

		for (;;) {
			if (i == lhs.length() || j == rhs.length()) {
				break;
			}

			leftdoc = lhs.getDoc(i);
			rightdoc = rhs.getDoc(j);

			if (leftdoc < rightdoc) {
				i++;
			} else if (leftdoc > rightdoc) {
				j++;
			} else { // equal
				results.docs.add(leftdoc);
				i++;
				j++;
			}
		}

		return results;
	}

}
