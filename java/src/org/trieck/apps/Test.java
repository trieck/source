package org.trieck.apps;

import java.util.TreeMap;
import java.util.Map;
import java.util.Iterator;

public class Test {

	public static void main(String[] args) {

		Map M = new TreeMap();
		M.put("a", "b");
		M.put("c", "d");
		M.put("e", "f");

		Iterator it = M.entrySet().iterator();
		while (it.hasNext()) {
			Map.Entry e = (Map.Entry)it.next();
			System.out.println((String)e.getKey() + '-' + (String)e.getValue());
		}
	}
}
