package org.tomrieck.content;

import org.tomrieck.xml.XMLUtil;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.xml.sax.SAXException;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.util.Set;

public class Content {

    private static final DocumentBuilderFactory dbfactory = DocumentBuilderFactory.newInstance();

    private Repository repos;
    
    public Content() throws IOException {
        repos = Repository.getInstance();
    }

    public Document search(String db, String q, int start, int count) throws IOException {

        Query query = new Query(db);

        AnchorList anchorlist = query.query(q);

        query.close();

        AnchorList pagelist = anchorlist.slice(start-1, count);
        Set<Integer> docset = pagelist.docSet();

        try {
            DocumentBuilder builder = dbfactory.newDocumentBuilder();
            Document root = builder.newDocument();
            Element results = root.createElement("results");

            results.setAttribute("db", db);
            results.setAttribute("query", q);
            results.setAttribute("start", Integer.toString(start));
            results.setAttribute("count", Integer.toString(anchorlist.size()));
            root.appendChild(results);
            
            Document doc;
            for (int docid : docset) {
                doc = getDoc(db, docid);
                XMLUtil.transferNode(results, root, doc.getDocumentElement());
            }

            return root;
        } catch (ParserConfigurationException e) {
            throw new IOException(e);
        } 
    }

    public Document getDoc(String db, int docid) throws IOException {

        File file = repos.getFile(db, docid);

        try {
            DocumentBuilder builder = dbfactory.newDocumentBuilder();

            Document doc = builder.parse(new FileInputStream(file));            
            Element record = doc.getDocumentElement();
            record.setAttribute("docid", Integer.toString(docid));
            
            return doc;
        } catch (ParserConfigurationException e) {
            throw new IOException(e);
        } catch (SAXException e) {
            throw new IOException(e);
        }
    }    
}
