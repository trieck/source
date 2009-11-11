package org.trieck.engine;

public class Location {

    private int word;
    private int offset;

    public int getWord() {
        return word;
    }

    public int getOffset() {
        return offset;
    }

    public Location(int word, int offset) {
        this.word = word;
        this.offset = offset;
    }
}
