package org.tomrieck.content;

import java.nio.LongBuffer;

public class InverterRecord implements Comparable<InverterRecord> {

    String term;            // record term
    LongBuffer buffer;      // document vector

    public int compareTo(InverterRecord o) {
        return term.compareTo(o.term);
    }
}