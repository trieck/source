package org.pixielib.util;

public class Hash64 {

	public static long hash(String key) {
		return hash(key.getBytes());
	}

	/**
	 * 64-bit Fowler/Noll/Vo hash
	 */
	public static long hash(byte[] key) {

		int i;
		long hash;

		for (hash = 0, i = 0; i < key.length; i++) {
			hash *= 1099511628211L;
			hash ^= key[i];
		}

		return hash;
	}
}
