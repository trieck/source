package org.tomrieck.content;

public class Anchor implements Comparable<Anchor> {

    private long anchorid;

    public Anchor() {
    }

    public Anchor(long anchorid) {
        this.anchorid = anchorid;
    }

    public Anchor(int docnum, int wordnum) {
        anchorid = (docnum << 32) | wordnum;
    }

    public long getAnchorID() {
        return anchorid;
    }
    
    public int getDocNum() {
        return (int)(anchorid >> 32);
    }

    public int getWordNum() {
        return (int)anchorid;
    }

    public int compareTo(Anchor d) {
        return (int)(anchorid - d.anchorid);
    }    
}
