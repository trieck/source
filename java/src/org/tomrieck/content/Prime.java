package org.tomrieck.content;

public class Prime {

    /////////////////////////////////////////////////////////////////////////////
    // The delta table generates primes just less than a power of two. A prime
    // number is calculated by subtracting its delta value from its
    // corresponding power of two.
    private static final byte delta[] = {
            0, 0, 1, 3, 3, 1, 3, 1, 5, 3, 3, 9, 3, 1, 3, 19,
            15, 1, 5, 1, 3, 9, 3, 15, 3, 39, 5, 39, 57, 3, 35,
            1, 5, 9, 41, 31, 5, 25, 45, 7, 87, 21, 11, 57, 17,
            55, 21, 115, 59, 81, 27, (byte) 129, 47, 111, 33,
            55, 5, 13, 27, 55, 93, 1, 57, 25, 59
    };

    /////////////////////////////////////////////////////////////////////////////
    // Compute the largest prime less than a specified power of two
    public static long prime(long i) {
        int j = 1;

        while ((i >>= 1) > 0) {
            j++;
        }

        return ((long) 1 << j) - delta[j];
    }

}
