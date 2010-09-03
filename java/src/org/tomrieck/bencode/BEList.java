package org.tomrieck.bencode;

import java.util.ArrayList;
import java.util.List;

public class BEList extends BEObject {

    private final List<BEObject> list;

    @Override
    public int getType() {
        return BEObject.BET_LIST;
    }

    public BEList() {
        list = new ArrayList<BEObject>();
    }

    public void addObject(BEObject o) {
        list.add(o);
    }

    public BEObject getAt(int index) {
        if (index < 0 || index >= list.size()) {
            return null;
        }

        return list.get(index);
    }

    public int size() {
        return list.size();
    }

}
