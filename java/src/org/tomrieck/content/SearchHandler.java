package org.tomrieck.content;

import org.w3c.dom.Document;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.xml.transform.*;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;
import java.io.IOException;

public class SearchHandler implements ContentHandler {

    public void handle(HttpServletRequest request, HttpServletResponse response)
        throws ServletException, IOException {

        String db = request.getParameter("db");
        String query = request.getParameter("query");
        String start = request.getParameter("start");
        String count = request.getParameter("count");

        if (db == null || query == null || start == null || count == null)
            throw new IllegalArgumentException("required argument not supplied.");

        int nstart = Integer.parseInt(start);
        int ncount = Integer.parseInt(count);

        Content content = new Content();
        Document doc = content.search(db, query, nstart, ncount);

        TransformerFactory factory = TransformerFactory.newInstance();
        Transformer transformer;

        try {
            transformer = factory.newTransformer();
        } catch (TransformerConfigurationException e) {
            throw new ServletException(e);
        }

        transformer.setOutputProperty(OutputKeys.OMIT_XML_DECLARATION, "no");
        transformer.setOutputProperty("encoding", "UTF-8");
        transformer.setOutputProperty(OutputKeys.INDENT, "yes");

        DOMSource source = new DOMSource(doc);

        StreamResult result = new StreamResult(response.getOutputStream());
        
        try {
            transformer.transform(source, result);
        } catch (TransformerException e) {
            throw new ServletException(e);
        }        
    }
}
