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

    public int getDocNum() {
        return (int) (anchorid >> 32);
    }

    public int getWordNum() {
        return (int) anchorid;
    }

    public int compareTo(Anchor d) {
        if (getDocNum() < d.getDocNum())
            return Integer.MIN_VALUE;

        if (getDocNum() > d.getDocNum())
            return Integer.MAX_VALUE;

        return getWordNum() - d.getWordNum();
    }

    public static long makeAnchorID(int docnum, int wordnum) {
        return ((long)docnum << 32) | wordnum;        
    }
}
