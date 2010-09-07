package org.tomrieck.content;

import java.io.DataInputStream;

public class ConcordRecord {

    String term;                // record term
    int size;                   // number of locations in the record
    DataInputStream stream;     // input stream

    public ConcordRecord() {
    }

}
