package org.trieck.engine;

import java.util.Map;
import java.util.TreeMap;

public class Inverter {

    private Map<String, Locality> table = new TreeMap<String, Locality>();

    public Inverter() {
    }

    public Locality get(String term) {
        return table.get(term);
    }

    public void put(String term, Locality locality) {
        table.put(term, locality);
    }
}
