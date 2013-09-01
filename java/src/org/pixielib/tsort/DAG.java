package org.pixielib.tsort;

import java.util.*;

/**
 * Directed acyclic graph
 *
 * @author trieck
 */
public class DAG {

	class Vertex {
		private final List<Vertex> edges;
		private final String label;

		public Vertex(String label) {
			this.label = label;
			edges = new ArrayList<Vertex>();
		}

		public String getLabel() {
			return label;
		}

		public void setEdge(Vertex v) {
			if (edges.contains(v)) {
				return; // edge already exists
			}

			edges.add(v);
		}

		@Override
		public boolean equals(Object o) {
			if (this == o) {
				return true;
			}

			if (o == null) {
				return false;
			}

			if (getClass() != o.getClass()) {
				return false;
			}

			final Vertex v = (Vertex) o;

			return label.equals(v.label);
		}

		@Override
		public int hashCode() {
			return label.hashCode();
		}

		@Override
		public String toString() {
			return label;
		}
	}

	/* adjacency list */
	private List<Vertex> vertices = null;

	public DAG() {
		vertices = new ArrayList<Vertex>();
	}

	public void addVertex(String label) {
		final Vertex v = new Vertex(label);
		if (vertices.contains(v)) {
			return;
		}

		vertices.add(v);
	}

	public void makeEdge(String from, String to) {

		Vertex v1, v2;

		if ((v1 = getVertex(from)) == null) {
			v1 = new Vertex(from);
			vertices.add(v1);
		}

		if ((v2 = getVertex(to)) == null) {
			v2 = new Vertex(to);
			vertices.add(v2);
		}

		v1.setEdge(v2);
	}

	public Vertex getVertex(String label) {

		for (final Vertex v : vertices) {
			if (v.getLabel().equals(label)) {
				return v;
			}
		}

		return null;
	}

	/**
	 * Topological sort of DAG
	 *
	 * @return sorted list of vertices
	 */
	public Iterator<Vertex> sort() {
		final List<Vertex> output = new ArrayList<Vertex>();
		final Set<Vertex> visited = new HashSet<Vertex>();

		for (final Vertex v : vertices) {
			visit(v, output, visited);
		}

		return output.iterator();
	}

	/**
	 * Visit each vertex
	 *
	 * @param v       the vertex to visit
	 * @param L       list to append to during sorting
	 * @param visited set of vertices seen
	 */
	private void visit(Vertex v, List<Vertex> L, Set<Vertex> visited) {

		if (visited.contains(v)) {
			return;
		}

		visited.add(v);

		for (final Vertex m : v.edges) {
			visit(m, L, visited);
		}

		L.add(v);
	}
}
