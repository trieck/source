package org.tomrieck.content;

public class Anchor implements Comparable<Anchor> {

    private long anchorid;

    public Anchor(long anchorid) {
        this.anchorid = anchorid;
    }

    public Anchor(int docnum, int wordnum) {
        anchorid = Anchor.makeAnchorID(docnum, wordnum);
    }

    public long getAnchorID() {
        return anchorid;
    }

    public int getDocID() {
        return (int) (anchorid >> 32);
    }

    public int getWordNum() {
        return (int) anchorid;
    }

    public int compareTo(Anchor d) {
        if (getDocID() < d.getDocID())
            return Integer.MIN_VALUE;

        if (getDocID() > d.getDocID())
            return Integer.MAX_VALUE;

        return getWordNum() - d.getWordNum();
    }

    public static long makeAnchorID(int docid, int wordnum) {
        return ((long) docid << 32) | wordnum;
    }
}
