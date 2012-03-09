package org.pixielib.apps;

import org.pixielib.util.Transversal;

import java.util.Arrays;

public class Test {

    public static void main(String[] args) {

        Integer[] A = { 2, 3, 2 };

        Transversal T = new Transversal(Arrays.asList(A));
        
        int[] s;
        for (int i = 0; i < T.cardinality(); i++) {
            s = T.get(i);
        }
    }
}
