package org.pixielib.content;

public class DocID {

    private long docid;  // document identifier

    public DocID(long docid) {
        this.docid = docid;
    }

    public short getFileNum() {
        return (short)(docid >>> Anchor.OFFSET_BITS);
    }

    public int getOffset() {
        return (int)(docid & 0x7FFFFFFF);
    }

    public static long makeDocID(short filenum, int offset) {
        return ((long)filenum << Anchor.OFFSET_BITS) | offset;
    }

}
