package org.pixielib.content.beans;

import org.pixielib.xml.XMLHttpRequest;
import org.w3c.dom.Document;
import org.w3c.dom.NodeList;

import java.io.IOException;

public class Detail extends Product {

    private String docid;

    private Detail(String prod, String db, String docid, String query, String style) {
        super(prod, db, query, style);
        this.docid = docid;
    }

    /**
     * Class factory construction
     *
     * @param prod,  the product
     * @param db,    the database to search
     * @param docid, the document to retrieve
     * @param query, the search query
     * @param style, the style for display
     * @return the detail record
     */
    public static Detail DetailRecord(String prod, String db, String docid, String query, String style) {
        Detail detail = new Detail(prod, db, docid, query, style);
        detail.getDoc();
        return detail;
    }

    private void getDoc() {

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
            setRecordCount(1);
        }
    }

    private String getSearchUrl() throws IOException {
        StringBuilder url = new StringBuilder();

        url.append(getContentURI());
        url.append("function=getdoc&query=");
        url.append(Context.encode(getQuery()));
        url.append("&db=");
        url.append(getDatabase());
        url.append("&docid=");
        url.append(docid);

        return url.toString();
    }
}
