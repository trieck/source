package org.pixielib.util;

public class Permutations {

    private int N;          // number of elements
    private int size;       // number of permutations
    private int[][] perms;  // the generated permutations
    private int[] a;        // temporary
    private int current;    // current index

    public Permutations(int n) {
        current = 0;
        this.N = n;
        size = Factorial.factorial(n);
        if (n > 0) generate();
    }

    public int size() {
        return this.size;
    }

    public int[] getPerm(int index) {
        return perms[index];
    }

    // Generate all permutations in lexicographical order
    // The method goes back to Narayana Pandita in 14th century India
    private void generate() {
        perms = new int[size][N];
        for (int i = 0; i < N; i++) {
            perms[0][i] = i;
        }

        a = new int[N];
        System.arraycopy(perms[0], 0, a, 0, N);

        int k, l;
        while (true) {
            // Find the largest index k such that a[k] < a[k + 1].
            // If no such index exists, the permutation is the last permutation.
            for (k = N - 1; k > 0; k--) {
                if (a[k] > a[k - 1])
                    break;
            }
            if (k == 0)
                break;  // last permutation

            k--;

            // Find the largest index l such that a[k] < a[l].
            // Since k + 1 is such an index, l is well defined and satisfies k < l.
            for (l = N - 1; l > 0; l--) {
                if (a[k] < a[l])
                    break;
            }

            assert (k < l);
            swap(k, l);
            reverse(k);
            System.arraycopy(a, 0, perms[++current], 0, N);
        }
    }

    private void swap(int k, int l) {
        int t = a[k];
        a[k] = a[l];
        a[l] = t;
    }

    // Reverse the sequence from a[k + 1] up to and including the final element a[n-1].
    private void reverse(int k) {
        for (int i = k + 1, j = N - 1; i < N && i < j; i++, j--) {
            swap(i, j);
        }
    }
}
