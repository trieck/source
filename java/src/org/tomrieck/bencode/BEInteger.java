package org.tomrieck.bencode;

public class BEInteger extends BEObject {

    long iVal;

    public BEInteger(long val) {
        iVal = val;
    }

    public long getVal() {
        return iVal;
    }

    @Override
    public int getType() {
        return BEObject.BET_INTEGER;
    }
}
