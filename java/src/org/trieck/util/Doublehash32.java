package org.trieck.util;

public class Doublehash32 implements Hash32 {

	public int hash(String key) {
		
		Hash32 H = new FNVHash32();
		
		Integer v = H.hash(key);
		
		return H.hash(v.toString());
	}

}
