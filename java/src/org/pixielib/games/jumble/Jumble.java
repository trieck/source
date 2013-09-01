package org.pixielib.games.jumble;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

public class Jumble {

	private Concordance concordance;

	public Jumble() throws IOException {
		concordance = Concordance.getInstance();
	}

	public List<String> solve(String word) {

		List<String> solutions = new ArrayList<String>();

		WordPerms wp = new WordPerms(word);

		String perm = wp.getFirstPerm();

		do {
			if (concordance.lookup(perm)) {
				solutions.add(perm);
			}
		} while ((perm = wp.getNextPerm(perm)) != null);

		return solutions;
	}

	public static void main(String[] args) {
		if (args.length == 0) {
			System.err.println("usage: Jumble word");
			System.exit(1);
		}

		Iterator<String> it;

		try {
			Jumble jumble = new Jumble();
			it = jumble.solve(args[0]).iterator();
			while (it.hasNext()) {
				System.out.println(it.next());
			}
		} catch (IOException e) {
			System.err.println(e);
			System.exit(1);
		}
	}
}
