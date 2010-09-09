package org.tomrieck.content;

import java.io.DataInputStream;

public class ConcordRecord {

    String term;                // record term
    int size;                   // size of anchor list
    DataInputStream stream;     // input stream

    public ConcordRecord() {
    }

}
