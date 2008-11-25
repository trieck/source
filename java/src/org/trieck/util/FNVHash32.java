package org.trieck.util;

public class FNVHash32 implements Hash32 {

	public int hash(byte[] v) {
						
		int h, i, len = v.length;
		
		for (h = 0, i = 0; i < len; ++i) {
			h *= 16777619;
			h ^= v[i];
		}
				
		return h;
	}
}