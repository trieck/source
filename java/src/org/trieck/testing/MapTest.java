package org.trieck.testing;

import java.util.Map;
import java.util.HashMap;

public class MapTest {

    private static int randomInt(int lo, int hi) {
	    return lo + (int)(Math.random() * (hi - lo));
    }

    private static int randomChar() {
	    return randomInt(32, 126);
    }

    private static String randomKey() {
	    int nlen = randomInt(28, 32);

        char[] buf = new char[nlen];

	    for (int i = 0; i < nlen; i++) {
		    buf[i] = (char)randomChar();
	    }

	    return new String(buf);
    }

    private static String randomVal() {
        int nlen = randomInt(35, 40);

        char[] buf = new char[nlen];

        for (int i = 0; i < nlen; i++) {
            buf[i] = (char)randomChar();
        }

        return new String(buf);
    }

    public static void main(String[] args) {

        long start = System.currentTimeMillis();

        Map<String, String> map = new HashMap<String, String>();

        String key, val;

	    int i, n = 100000;
	    for (i = 0; i < n; i++) {
		    key = randomKey();
		    val = randomVal();;
            map.put(key, val);
	    }

        long end = System.currentTimeMillis();

        float time = (end - start) / 1000.0f;

        System.out.println("   inserted " + n + " items.");        
        System.out.println("   elapsed time " + time + " seconds.");
    }
}
