package org.pixielib.content;

import org.pixielib.xml.XMLTransformer;
import org.w3c.dom.Document;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.xml.transform.TransformerException;
import javax.xml.transform.dom.DOMSource;
import java.io.IOException;

public class DocumentHandler implements ContentHandler {

    @Override
    public void handle(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {

        String db = request.getParameter("db");
        String query = request.getParameter("query");
        String docid = request.getParameter("docid");

        query = query == null ? "" : query;

        if (db == null || docid == null)
            throw new IllegalArgumentException("required argument not supplied.");

        long ndocid;

        try {
            ndocid = Long.parseLong(docid);
        } catch (NumberFormatException e) {
            throw new ServletException(e);
        }

        Content content = new Content();
        Document doc = content.getDoc(db, query, ndocid);

        try {
            XMLTransformer.transform(new DOMSource(doc), response.getOutputStream());
        } catch (TransformerException e) {
            throw new ServletException(e);
        }
    }
}
