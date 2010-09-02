package org.tomrieck.bible;

public class Hash32 {

	/** 32-bit Fowler/Noll/Vo hash */
	public static long hash(CharSequence key) {
		int i;
		int hash;

		for (hash = 0, i = 0; i < key.length(); i++) {
			hash *= 16777619;
			hash ^= key.charAt(i);
		}

		return (hash & 0xFFFFFFFFL);
	}
}
