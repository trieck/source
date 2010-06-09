package org.tomrieck.engine;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.HashSet;
import java.util.Set;

public class NoiseList {

	private final Set<String> table = new HashSet<String>();
	private static NoiseList instance = null;

	private NoiseList() throws IOException {
		load();
	}

	public static NoiseList instance() throws IOException {
		if (instance == null) {
			instance = new NoiseList();
		}

		return instance;
	}

	private void load() throws IOException {
		final BufferedReader r = new BufferedReader(new FileReader(
				"d:/bible/noise.txt"));

		String line;
		String[] words;
		int i;

		while ((line = r.readLine()) != null) {
			words = line.split("\\s");
			for (i = 0; i < words.length; i++) {
				table.add(words[i].toLowerCase());
			}
		}

	}

	public boolean isNoise(String word) {
		return table.contains(word.toLowerCase());
	}

}
