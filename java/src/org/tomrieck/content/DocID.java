package org.tomrieck.content;

public class DocID implements Comparable<DocID> {

    private int docid;  // document identifier

    public DocID(int docid) {
        this.docid = docid;
    }

    public int getDocID() {
        return docid;
    }

    public short getFileNum() {
        return (short) (docid >> 16);
    }

    public short getRecNum() {
        return (short) docid;
    }

    public int compareTo(DocID d) {
        return docid - d.docid;
    }

    public static int makeDocID(short filenum, short recnum) {
        return ((int) filenum << 16) | recnum;
    }

}
