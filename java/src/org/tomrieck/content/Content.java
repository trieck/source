package org.tomrieck.content;

import org.tomrieck.xml.XMLUtil;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.xml.sax.SAXException;

import javax.xml.parsers.ParserConfigurationException;
import java.io.File;
import java.io.IOException;

public class Content {

    private Repository repos;

    public Content() throws IOException {
        repos = Repository.getInstance();
    }

    public Document search(String db, String q, int start, int count) throws IOException {

        Query query = new Query(db);

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
            int docid;
            for (int i = 0; i < pagelist.size(); i++) {
                docid = pagelist.getDoc(i);
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
            Document doc = XMLUtil.parseXML(file);
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
