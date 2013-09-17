package org.pixielib.content.beans;

import org.pixielib.xml.XMLHttpRequest;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.NodeList;

import javax.xml.xpath.XPath;
import javax.xml.xpath.XPathExpression;
import javax.xml.xpath.XPathExpressionException;
import javax.xml.xpath.XPathFactory;
import java.io.IOException;
import org.pixielib.util.Config;

public class Search extends Product {

	private static final XPathFactory factory = XPathFactory.newInstance();
	private int start;			// starting record
	private int pagesize;   // page size
	private Config config;

	private Search(String product, String db, String query, int start, String style) {
		super(product, db, query, style);
		this.start = Math.max(1, start);
		config = new Config("web");
		pagesize = config.getIntProperty("pagesize");
	}

	public static Search DatabaseSearch(String product, String db, String query, int start, String style) {
		Search search = new Search(product, db, query, start, style);
		search.doSearch();
		return search;
	}

	public static String select(String db, String query, String expr) {
		Search search = new Search("", db, query, 1, "");
		search.doSearch();
		return search.select(expr);
	}

	private String select(String expr) {

		Document doc;
		if ((doc = getResults()) == null) {
			return "";
		}

		XPath xpath;
		synchronized (factory) {
			xpath = factory.newXPath();
		}

		XPathExpression xpathExpr;
		String results;

		try {
			xpathExpr = xpath.compile(expr);
			results = xpathExpr.evaluate(doc);
		} catch (XPathExpressionException e) {
			e.printStackTrace();
			return "";
		}

		return results;
	}

	@SuppressWarnings("empty-statement")
	private void doSearch() {

		Document doc;

		try {
			doc = XMLHttpRequest.request(getSearchUrl());
		} catch (IOException e) {
			e.printStackTrace();
			return;
		}

		setResults(doc);
		NodeList results = doc.getElementsByTagName("results");
		if (results != null && results.getLength() > 0) {
			Element element = (Element) results.item(0);

			try {
				int ncount = Integer.parseInt(element.getAttribute("count"));
				setRecordCount(ncount);
			} catch (NumberFormatException e) {
				;
			}
		}
	}

	private String getSearchUrl() throws IOException {
		StringBuilder url = new StringBuilder();

		url.append(getContentURI());
		url.append("function=search&query=");
		url.append(Context.encode(getQuery()));
		url.append("&db=");
		url.append(getDatabase());

		url.append("&start=");
		url.append(start);
		url.append("&count=");
		url.append(pagesize);

		return url.toString();
	}

	/**
	 * Retrieve the previous page link
	 *
	 * @return String the previous page link or empty
	 */
	public String getPrevious() {
		if (getRecordCount() == 0) {
			return "";
		}

		int N = start - pagesize;
		if (N < 1) {
			return "";
		}

		return getPageLink(N);
	}

	/**
	 * Retrieve the next page link
	 *
	 * @return String the next page link or empty
	 */
	public String getNext() {

		if (getRecordCount() == 0) {
			return "";
		}

		int N = start + pagesize;
		if (N > getRecordCount()) {
			return "";
		}

		return getPageLink(N);
	}

	/**
	 * Returns query string formattted for pagination
	 *
	 * @param N the starting record
	 * @return String the query formatted for pagination
	 */
	public String getPageLink(int N) {

		Context context = Context.getContext();

		String self = context.identity();

		return WebUtils.normalizeUrl(self + "&start=" + N);
	}
}
