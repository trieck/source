package org.pixielib.tsort;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Iterator;

/**
 * Topological sort of directed acyclic graph
 *
 * @author trieck
 */
public class TSort {

	private final DAG graph;

	public TSort() {
		graph = new DAG();
	}

	public void makeEdge(String[] tokens) {
		assert (tokens.length == 2);

		graph.makeEdge(tokens[0], tokens[1]);
	}

	public Iterator<DAG.Vertex> sort() {
		return graph.sort();
	}

	public static void main(String[] args) {
		final BufferedReader reader = new BufferedReader(new InputStreamReader(
				System.in));

		final TSort tsort = new TSort();

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
		} catch (final IOException e) {
			System.err.println(e);
			System.exit(1);
		}

		final Iterator<DAG.Vertex> vertices = tsort.sort();
		while (vertices.hasNext()) {
			System.out.println(vertices.next());
		}
	}
}
