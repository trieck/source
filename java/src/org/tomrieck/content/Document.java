package org.tomrieck.content;

public class Document implements Comparable<Document> {

    private long docid;

    public Document() {
    }

    public Document(long docid) {
        this.docid = docid;
    }

    public Document(int docnum, int wordnum) {
        this.docid = (docnum << 32) | wordnum;
    }

    public long getDocID() {
        return docid;
    }
    
    public int getDocNum() {
        return (int)(docid >> 32);
    }

    public int getWordNum() {
        return (int)docid;
    }

    public int compareTo(Document d) {
        return (int)(docid - d.docid);
    }    
}
