package org.pixielib.content;

import java.nio.LongBuffer;

public class InverterRecord implements Comparable<InverterRecord> {

    String term;            // record term
    LongBuffer buffer;      // anchor list

    public int compareTo(InverterRecord o) {
        return term.compareTo(o.term);
    }
}
