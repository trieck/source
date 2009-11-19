package org.trieck.apps;

import java.util.Iterator;
import java.util.Map;
import java.util.TreeMap;

public class Test {

	public static void main(String[] args) {

		final Map<String, String> M = new TreeMap<String, String>();
		M.put("a", "b");
		M.put("c", "d");
		M.put("e", "f");

		final Iterator<Map.Entry<String, String>> it = M.entrySet().iterator();
		while (it.hasNext()) {
			final Map.Entry<String, String> e = it.next();
			System.out.println(e.getKey() + '-' + e.getValue());
		}
	}
}
