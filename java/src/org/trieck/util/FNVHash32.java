package org.trieck.util;

public class FNVHash32 implements Hash32 {

	public int hash(String key) {
		int h, i, len = key.length();
		
		for (h = 0, i = 0; i < len; ++i) {
			h *= 16777619;
			h ^= key.charAt(i);
		}
		
		return h;
	}
}
