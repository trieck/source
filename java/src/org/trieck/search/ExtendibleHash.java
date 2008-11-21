package org.trieck.search;

public class ExtendibleHash {

    /* Number of bits used to index into the directory */
    private int d;

    /* Number of directory entries */
    private int D;

    public ExtendibleHash() {
        d = 0; D = 1;
    }
    public static void main(String[] args) {
        ExtendibleHash hash = new ExtendibleHash();
    }

}
