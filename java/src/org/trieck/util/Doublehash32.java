package org.trieck.util;

public class Doublehash32 implements Hash32 {

	public int hash(String key) {
		
		Hash32 H = new FNVHash32();
		
		return H.hash(String.valueOf(H.hash(key)));
	}

}
