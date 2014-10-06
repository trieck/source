package org.pixielib.util;

// Generate all permutations in lexicographical order
// The method goes back to Narayana Pandita in 14th century India
public class Permutations {

    public static int size(int n) {
        return Factorial.factorial(n);
    }

    public static int[] getFirstPerm(int n) {
        int[] a = new int[n];

        for (int i = 0; i < n; i++) {
            a[i] = i;
        }

        return a;
    }

    public static boolean getNextPerm(int[] a) {

        int k, l, n = a.length;

        // Find the largest index k such that a[k] < a[k + 1].
        // If no such index exists, the permutation is the last permutation.
        for (k = n - 1; k > 0; k--) {
            if (a[k] > a[k - 1])
                break;
        }

        if (k == 0)
            return false;  // last permutation

        k--;

        // Find the largest index l such that a[k] < a[l].
        // Since k + 1 is such an index, l is well defined and satisfies k < l.
        for (l = n - 1; l > 0; l--) {
            if (a[k] < a[l])
                break;
        }

        assert (k < l);
        swap(a, k, l);
        reverse(a, k);

        return true;
    }

    private static void swap(int[] a, int k, int l) {
        int t = a[k];
        a[k] = a[l];
        a[l] = t;
    }

    // Reverse the sequence from a[k + 1] up to and including the final element a[n-1].
    private static void reverse(int[] a, int k) {
        int n = a.length;
        for (int i = k + 1, j = n - 1; i < n && i < j; i++, j--) {
            swap(a, i, j);
        }
    }
}
