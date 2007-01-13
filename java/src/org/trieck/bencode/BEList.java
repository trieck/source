package org.trieck.bencode;

import java.util.*;

public class BEList extends BEObject {

	private List<BEObject> list;
	
	@Override
	public int getType() { return BEObject.BET_LIST; }
	
	public BEList() {
		list = new ArrayList<BEObject>();
	}
	
	public void addObject(BEObject o) {
		list.add(o);
	}
	
	public BEObject getAt(int index) {
		if (index < 0 || index >= list.size())
			return null;
		
		return list.get(index);
	}
	
	public int size() { return list.size(); }	
	
}
