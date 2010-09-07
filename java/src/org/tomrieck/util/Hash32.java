package org.tomrieck.util;

public class Hash32 {

    public static long hash(String key) {
        return hash(key.getBytes());
    }

    /**
     * 32-bit Fowler/Noll/Vo hash
     */
    public static long hash(byte[] key) {
        int i;
        int hash;

        for (hash = 0, i = 0; i < key.length; i++) {
            hash *= 16777619;
            hash ^= key[i];
        }

        return (hash & 0xFFFFFFFFL);
    }
}
