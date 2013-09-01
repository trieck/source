package org.pixielib.content;

import org.pixielib.util.Timer;
import org.pixielib.xml.XMLTransformer;
import org.w3c.dom.Document;

import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.TransformerException;
import javax.xml.transform.dom.DOMSource;
import java.io.IOException;

public class Search {

	public Search() {
	}

	public void search(String db, String query, int nrecs) throws IOException,
			ParserConfigurationException, TransformerException {

		Content content = new Content();
		Document doc = content.search(db, query, 1, nrecs);

		XMLTransformer.transform(new DOMSource(doc), System.out);
	}

	public static void main(String[] args) {

		int nrecs = 25;

		if (args.length < 2) {
			System.err.println("usage: Search db \"phrase\" [records]");
			System.exit(1);
		}

		if (args.length == 3) {
			try {
				nrecs = Integer.parseInt(args[2]);
			} catch (NumberFormatException e) {
				;
			}
		}

		Timer t = new Timer();

		Search search = new Search();

		try {
			search.search(args[0], args[1], nrecs);
		} catch (IOException e) {
			System.err.println(e);
			System.exit(1);
		} catch (TransformerException e) {
			System.err.println(e);
			System.exit(2);
		} catch (ParserConfigurationException e) {
			System.err.println(e);
			System.exit(3);
		}

		System.out.printf("\n    elapsed time %s\n", t);
	}
}
