package org.tomrieck.content;

import java.nio.LongBuffer;

public class IndexRecord implements Comparable<IndexRecord> {

    String term;            // record term
    LongBuffer buffer;      // document vector

    public int compareTo(IndexRecord o) {
        return term.compareTo(o.term);
    }
}
