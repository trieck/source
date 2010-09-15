package org.pixielib.content;

/**
 * An anchor is a virtual term-location identifier in the document repository.
 * Each anchor is 8-bytes long. The bit-layout of an anchor is:
 *
 * -------------ANCHOR-------------
 * 63.....48 47........16 15......0
 * {FILENUM} {FILEOFFSET} {WORDNUM}
 * ---------DOCID--------|---------
 *
 * FILENUM 	    : file # in repository (16-bits, 32,767 max number of files)
 * FILEOFFSET	: offset into file where record is located (32-bits, max file size ~2GB)
 * WORDNUM	    : word number of term in field (16-bits, 32,767 max words per field)
 * DOCID        : The upper 48-bits of the anchor represents the document id.
 *  
 */
public class Anchor implements Comparable<Anchor> {

    public static final int FILENUM_BITS = 16;
    public static final int OFFSET_BITS = 32;
    public static final int WORDNUM_BITS = 16;
    
    private long anchorid;

    public Anchor(long anchorid) {
        this.anchorid = anchorid;
    }

    public long getAnchorID() {
        return anchorid;
    }

    public long getDocID() {
        return anchorid >>> (WORDNUM_BITS);
    }

    public short getWordNum() {
        return (short)(anchorid & ((1 << WORDNUM_BITS)-1));
    }

    public int compareTo(Anchor d) {
        if (getDocID() < d.getDocID())
            return Integer.MIN_VALUE;

        if (getDocID() > d.getDocID())
            return Integer.MAX_VALUE;

        return getWordNum() - d.getWordNum();
    }

    public static long makeAnchorID(long docid, short wordnum) {
        return (docid << WORDNUM_BITS) | (wordnum & ((1 << WORDNUM_BITS)-1));
    }
}
