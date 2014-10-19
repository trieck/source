package org.pixielib.content;

public class DocID {

    private long docid;  // document identifier

    public DocID(long docid) {
        this.docid = docid;
    }

    public int getFileNum() {
        return (int) (docid >>> (Anchor.OFFSET_BITS) & 0xFF);
    }

    public int getOffset() {
        return (int) (docid & 0x3FFFFFFFL);
    }
}
