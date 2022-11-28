package org.pixielib.util;

import java.util.List;

public class Transversal {

    private final List<Integer> A;        // cardinality of sets
    private int C;                  // cardinality
    private int[][] combinations;
    private int[] t;                // temp array during construction
    private int n;                  // counter during construction

    public Transversal(List<Integer> A) {
        this.A = A;
        this.C = 1;
        this.n = 0;
        for (int i : A) {
            C *= i;
        }
        generate();
    }

    public int[] get(int i) {
        return combinations[i];
    }

    public int cardinality() {
        return C;
    }

    private void generate() {
        combinations = new int[C][];
        for (int i = 0; i < C; i++) {
            combinations[i] = new int[A.size()];
        }

        t = new int[A.size()];
        generate(0);
    }

    private void generate(int k) {
        if (k == A.size()) {
            System.arraycopy(t, 0, combinations[n++], 0, A.size());
        } else {
            for (int m = 0; m < A.get(k); m++) {
                t[k] = m;
                generate(k + 1);
            }
            t[k] = 0;
        }
    }
}
