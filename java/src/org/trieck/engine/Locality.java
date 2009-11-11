package org.trieck.engine;

import java.util.ArrayList;
import java.util.List;

public class Locality {

    private List<Location> locations = new ArrayList<Location>();

    public Locality() {
    }

    public void add(Location l) {
        locations.add(l);
    }

    public List<Location> getLocations() {
        return locations;
    }

    public Location get(int index) {
        return locations.get(index);
    }

    public int getWord(int index) {
        return get(index).getWord();
    }

    public int getOffset(int index) {
        return get(index).getOffset();
    }

    public int size() {
        return locations.size();
    }

    public Locality adjacent(Locality rhs) {
        Locality output = new Locality(), lhs = this;
        if (rhs == null) return output;

        if (lhs.getWord(0) > rhs.getWord(0)) {
            Locality t = lhs;
            lhs = rhs;
            rhs = t;
        }

        for (int i = 0; i < lhs.size(); i++) {
            int l = lhs.getWord(i);
            for (int j = 0; j < rhs.size(); j++) {
                int r = rhs.getWord(j);
                if (r - l > 1) break;
                if (isAdjacent(l, r)) {
                    output.add(new Location(Math.max(l, r),
                            Math.min(lhs.getOffset(i), rhs.getOffset(j))));
                }
            }
        }

        return output;
    }

    private static boolean isAdjacent(int l, int r) {
        return Math.abs(l - r) == 1;
    }
}
