package org.pixielib.content.beans;

import org.pixielib.util.Config;
import org.pixielib.xml.XMLHttpRequest;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.NodeList;

import java.io.IOException;

public class Search extends Product {

    int start;     // starting record
    int pagesize;   // page size

    private Search(String product, String db, String query, int start, String style) {
        super(product, db, query, style);

        Context ctxt = Context.getContext();

        this.start = Math.max(1, start);
        pagesize = ctxt.getIntProperty("pagesize");
    }

    public static Search DatabaseSearch(String product, String db, String query, int start, String style) {
        Search search = new Search(product, db, query, start, style);
        search.doSearch();
        return search;
    }

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
        Config config = Config.getInstance();

        StringBuffer url = new StringBuffer();
        url.append("http://");
        url.append(config.getProperty("content.host"));
        url.append(':');
        url.append(config.getProperty("content.port"));
        url.append('/');
        url.append(config.getProperty("content.uri"));
        url.append("?function=search&query=");
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
        if (getRecordCount() == 0)
            return "";

        int N = start - pagesize;
        if (N < 1)
            return "";

        return getPageLink(N);
    }

    /**
     * Retrieve the next page link
     *
     * @return String the next page link or empty
     */
    public String getNext() {

        if (getRecordCount() == 0)
            return "";

        int N = start + pagesize;
        if (N > getRecordCount())
            return "";

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
