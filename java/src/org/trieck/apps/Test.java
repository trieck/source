package org.trieck.apps;

import java.util.TreeMap;
import java.util.Map;
import java.util.Iterator;

public class Test {

	public static void main(String[] args) {

		Map<String, String> M = new TreeMap<String, String>();
		M.put("a", "b");
		M.put("c", "d");
		M.put("e", "f");

		Iterator<Map.Entry<String, String>> it = M.entrySet().iterator();
		while (it.hasNext()) {
			Map.Entry<String, String> e = it.next();
			System.out.println((String)e.getKey() + '-' + (String)e.getValue());
		}
	}
}
