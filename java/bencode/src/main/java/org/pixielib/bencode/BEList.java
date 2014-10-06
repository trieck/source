package org.pixielib.bencode;

import java.util.ArrayList;
import java.util.List;

public class BEList extends BEObject {

    private final List<BEObject> list;

    public BEList() {
        list = new ArrayList<BEObject>();
    }

    @Override
    public int getType() {
        return BEObject.BET_LIST;
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
