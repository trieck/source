package org.pixielib.apps.jumble;

import java.util.ArrayList;
import java.util.List;

public class Arrangements {
    
    public static int arrangements(String word) {

        int N = factorial(word.length());
        int D = divisor(word);
        
        int A = N/D;

        return A;
    }
    
    private static class Letter implements Comparable<Letter> {
        char c;     // character
        int count;  // count of letter in word

        public Letter(char c) {
            this.c = c;
            this.count = 1;
        }

        public int compareTo(Letter rhs) {
            return (this.c < rhs.c ? -1 : (this.c == rhs.c ? 0 : 1));
        }
    }

    // compute divisor by looking for duplicate letters
    private static int divisor(String word) {

        List<Letter> letters = new ArrayList<Letter>();

        Letter letter;
        char c;
        for (int i = 0; i < word.length(); i++) {
            c = word.charAt(i);
            if ((letter = lookup(letters, c)) != null) {
                letter.count++;
            } else {
                letters.add(new Letter(c));
            }
        }
        
        int d = 1;
        for (Letter l : letters) {
            if (l.count > 1) {
                d = d * factorial(l.count);
            }            
        }

        return d;
    }
    
    private static Letter lookup(List<Letter> letters, char c) {
        for (Letter l : letters) {
            if (l.c == c)
                return l;
        }

        return null;
    }
    
    private static int factorial(int n) {
        if (n <= 0) return 1;
        return n * factorial(n-1);
    }
}
