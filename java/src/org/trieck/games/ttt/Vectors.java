package org.trieck.games.ttt;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

public class Vectors implements Iterable<Integer[]> {

	private static Vectors instance = null;

	public static synchronized Vectors instance() {
		if (instance == null) {
			instance = new Vectors();
		}

		return instance;
	}

	private final List<Integer[]> vlist;

	private Vectors() {
		vlist = new ArrayList<Integer[]>();
		generate();
	}

	public int size() {
		return vlist.size();
	}

	void generate() {

		final List<Integer> v = new ArrayList<Integer>();
		final Integer[] a = new Integer[Board.BOARD_SIZE];

		for (int i = 0; i < Board.BOARD_SIZE; i++) {
			v.clear();
			for (int j = 0; j < Board.BOARD_SIZE; j++) {
				v.add(i * Board.BOARD_SIZE + j);
			}

			v.toArray(a);
			vlist.add(a.clone());
		}

		for (int i = 0; i < Board.BOARD_SIZE; i++) {
			v.clear();
			for (int j = 0; j < Board.BOARD_SIZE; j++) {
				v.add(j * Board.BOARD_SIZE + i);
			}

			v.toArray(a);
			vlist.add(a.clone());
		}

		v.clear();
		for (int i = 0; i < Board.BOARD_SIZE; i++) {
			v.add(i * Board.BOARD_SIZE + i);
		}

		v.toArray(a);
		vlist.add(a.clone());

		v.clear();
		for (int i = 0; i < Board.BOARD_SIZE; i++) {
			v.add(i * Board.BOARD_SIZE + (Board.BOARD_SIZE - i - 1));
		}

		v.toArray(a);
		vlist.add(a.clone());
	}

	public Iterator<Integer[]> iterator() {
		return vlist.iterator();
	}

}
