package org.trieck.bencode;

import java.util.*;

public class BEDictionary extends BEObject {

	private Map<BEString, BEObject> map;	
	
	public BEDictionary() {
		map = new TreeMap<BEString, BEObject>();		
	}
	
	@Override
	public int getType() { return BEObject.BET_DICT; }
	
	public void set(BEString k, BEObject v) {
		map.put(k, v);
	}
	
	public void set(String k, BEObject v) {
		map.put(new BEString(k), v);
	}
	
	public void set(String k, String v) {
		map.put(new BEString(k), new BEString(v));
	}
	
	public void set(String k, long v) {
		map.put(new BEString(k), new BEInteger(v));
	}
	
	public BEObject get(BEString k) {
		return map.get(k);
	}
	
	public BEObject get(String k) {
		return map.get(new BEString(k));
	}

    public String getString(String k) {
        BEObject object = get(k);
        if (object == null || object.getType() != BEObject.BET_STRING)
            return "";
        return ((BEString)object).toString();
    }

    public long getInt(String k) {
        BEObject object = get(k);
        if (object == null || object.getType() != BEObject.BET_INTEGER)
            return -1;

        return ((BEInteger)object).getVal();        
    }

	public Iterator<Map.Entry<BEString, BEObject>> getIterator() {
		return map.entrySet().iterator();
	}

}
