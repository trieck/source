package org.tomrieck.content;

import java.nio.LongBuffer;

public class IndexRecord implements Comparable<IndexRecord> {

    String term;
    LongBuffer buffer;

    public int compareTo(IndexRecord o) {
        return term.compareTo(o.term);
    }
}
