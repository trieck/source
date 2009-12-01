package org.tomrieck.tsort;

import java.io.*;
import java.util.*;

/**
 * Topological sort of directed acyclic graph
 * @author trieck
 */
public class TSort {
	
	private DAG graph;
	
	public TSort() {
		graph = new DAG();		
	}
	
	public void makeEdge(String[] tokens) {
		assert(tokens.length == 2);
		
		graph.makeEdge(tokens[0], tokens[1]);
	}
	
	public Iterator<String> sort() {
		return graph.sort();
	}
	
	public static void main(String[] args) {
		final BufferedReader reader = new BufferedReader(new InputStreamReader(
				System.in));

		TSort tsort = new TSort();
		
		String line;
		String[] tokens;
		
		try {
			while ((line = reader.readLine()) != null) {
				tokens = line.split("\\s+");
				if (tokens.length != 2) {
					System.err.println("bad line.");
					continue;
				}
				
				tsort.makeEdge(tokens);
			}
		} catch (IOException e) {
			System.err.println(e);
			System.exit(1);
		}
		
		Iterator<String> strings = tsort.sort();
		while (strings.hasNext()) {
			System.out.println(strings.next()); 
		}
	}
}
