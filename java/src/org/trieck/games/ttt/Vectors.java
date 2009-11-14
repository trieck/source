package org.trieck.games.ttt;

import java.util.*;

public class Vectors implements Iterable<int[]> {
	
	private static final int[][] VECTORS = {
		{ 0, 1, 2 },
		{ 3, 4, 5 },
		{ 6, 7, 8 },
		{ 0, 3, 6 },
		{ 1, 4, 7 },
		{ 2, 5, 8 },
		{ 0, 4, 8 },
		{ 2, 4, 6 }
	};
	
	private static final List<int[]> VLIST = Arrays.asList(VECTORS);
	
	private static Vectors instance = null;
	
	private Vectors() {		
	}
	
	public static Vectors instance() {
		if (instance == null)
			instance = new Vectors();
		
		return instance;
	}
	
	public Iterator<int[]> iterator() {
		return VLIST.iterator();
	}	
	
}
