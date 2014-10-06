package org.pixielib.content;

import org.pixielib.xml.XMLTransformer;
import org.w3c.dom.Document;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.xml.transform.TransformerException;
import javax.xml.transform.dom.DOMSource;
import java.io.IOException;

public class SearchHandler implements ContentHandler {

    @Override
    public void handle(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {

        String db = request.getParameter("db");
        String query = request.getParameter("query");
        String start = request.getParameter("start");
        String count = request.getParameter("count");

        if (db == null || query == null || start == null || count == null)
            throw new IllegalArgumentException("required argument not supplied.");

        int nstart, ncount;

        try {
            nstart = Integer.parseInt(start);
            ncount = Integer.parseInt(count);
        } catch (NumberFormatException e) {
            throw new ServletException(e);
        }

        Content content = new Content();
        Document doc = content.search(db, query, nstart, ncount);

        try {
            XMLTransformer.transform(new DOMSource(doc), response.getOutputStream());
        } catch (TransformerException e) {
            throw new ServletException(e);
        }
    }
}
