package org.pixielib.games.jumble;

import org.pixielib.util.Factorial;
import org.pixielib.util.Permutations;

import java.util.Arrays;

public class WordPerms {

    private Letters letters;
    private String word;
    private int size;       // number of permutations
    private int[] a;        // permutation

    public int getSize() {
        return size;
    }

    public WordPerms(String word) {
        this.word = word.toLowerCase();
        letters = new Letters();
        count();

        int f = Factorial.factorial(word.length());
        int d = divisor();
        size = f / d;
        a = new int[word.length()];
    }

    public String getFirstPerm() {

        char[] chars = word.toCharArray();

        Arrays.sort(chars);

        return String.valueOf(chars);
    }

    public String getNextPerm(String s) {
        toArray(s);

        if (!Permutations.getNextPerm(a))
            return null;

        return fromArray();
    }

    private void toArray(String s) {
        assert (a.length == s.length());
        for (int i = 0; i < s.length(); i++) {
            a[i] = s.charAt(i);
        }
    }

    private String fromArray() {
        StringBuilder builder = new StringBuilder();
        builder.setLength(a.length);
        for (int i = 0; i < a.length; i++) {
            builder.setCharAt(i, (char) a[i]);
        }

        return builder.toString();
    }

    private void count() {
        letters.clear();

        char c;
        for (int i = 0; i < word.length(); i++) {
            c = word.charAt(i);
            letters.put(c);
        }
    }

    // compute divisor by looking for duplicate letters
    private int divisor() {
        int d = 1;
        for (Letter l : letters) {
            if (l.count > 1) {
                d = d * Factorial.factorial(l.count);
            }
        }

        return d;
    }
}
