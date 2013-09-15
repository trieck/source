package org.pixielib.content;

import org.pixielib.xml.XMLUtil;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.xml.sax.SAXException;

import javax.xml.parsers.ParserConfigurationException;
import javax.xml.stream.XMLStreamException;
import javax.xml.transform.TransformerException;
import java.io.File;
import java.io.IOException;
import java.io.RandomAccessFile;

public class Content {

	private Repository repos;

	public Content() throws IOException {
		repos = Repository.getInstance();
	}

	public Document search(String db, String q, int start, int count) throws IOException {

		Query query = new Query(db);
		IndexFields fields = new IndexFields(db);

		QueryTerms terms = new QueryTerms(q);

		AnchorList anchorlist = query.query(q);
		query.close();

		// set of unique documents for anchor list
		DocList doclist = anchorlist.documents();

		DocList pagelist = doclist.slice(start - 1, count);

		try {
			Document root = XMLUtil.newDocument();
			Element results = root.createElement("results");

			results.setAttribute("db", db);
			results.setAttribute("query", q);
			results.setAttribute("start", Integer.toString(start));
			results.setAttribute("count", Integer.toString(doclist.size()));
			root.appendChild(results);

			Document doc;
			long docid;
			for (int i = 0; i < pagelist.size(); i++) {
				docid = pagelist.getDoc(i);
				doc = getDoc(db, docid);
				doc = Highlighter.highlight(doc, terms, fields);
				XMLUtil.transferNode(results, root, doc.getDocumentElement());
			}

			return root;
		} catch (ParserConfigurationException | SAXException | XMLStreamException | TransformerException e) {
			throw new IOException(e);
		}
	}

	public Document getDoc(String db, String query, long ndocid) throws IOException {

		QueryTerms terms = new QueryTerms(query);
		IndexFields fields = new IndexFields(db);

		try {
			Document doc = getDoc(db, ndocid);
			doc = Highlighter.highlight(doc, terms, fields);
			Element root = doc.getDocumentElement();
			root.setAttribute("db", db);
			root.setAttribute("query", query);
			return doc;
		} catch (ParserConfigurationException | SAXException | XMLStreamException | TransformerException e) {
			throw new IOException(e);
		}
	}

	private Document getDoc(String db, long ndocid)
					throws IOException, ParserConfigurationException, SAXException {

		DocID docid = new DocID(ndocid);

		short filenum = docid.getFileNum();
		int offset = docid.getOffset();

		File file = repos.getFile(db, filenum);

		Document doc = getRecord(file, offset);
		Element root = doc.getDocumentElement();
		root.setAttribute("docid", Long.toString(ndocid));

		return doc;
	}

	public Document getRecord(File file, int offset)
					throws IOException, ParserConfigurationException, SAXException {

		// state machine to extract record in file
		StringBuilder output = new StringBuilder();
		try (RandomAccessFile raf = new RandomAccessFile(file, "r")) {
			raf.seek(offset);

			String pattern = "<record></record>";

			int jstar = pattern.lastIndexOf('<');

			int j = 0;
			int c;
			while ((c = raf.read()) != -1) {
				if (j == pattern.length()) {
					break;
				} else if (pattern.charAt(j) == c) {
					j++;
				} else if (j >= jstar) {
					j = jstar;
				} else {
					output.setLength(0);
					j = 0;
					continue;
				}
				output.append((char) c);
			}
		}

		return XMLUtil.parseXML(output.toString());
	}
}
