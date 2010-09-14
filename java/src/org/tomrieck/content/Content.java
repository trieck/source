package org.tomrieck.content;

import org.tomrieck.xml.XMLUtil;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.xml.sax.InputSource;

import javax.xml.parsers.ParserConfigurationException;
import javax.xml.xpath.*;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;

public class Content {

    private static final XPath xpath = XPathFactory.newInstance().newXPath();

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

            Element doc;
            int docid;
            for (int i = 0; i < pagelist.size(); i++) {
                docid = pagelist.getDoc(i);
                doc = getDoc(db, docid);
                XMLUtil.transferNode(results, root, doc);
            }

            return root;
        } catch (ParserConfigurationException e) {
            throw new IOException(e);
        }
    }

    public Element getDoc(String db, int ndocid) throws IOException {

        DocID docid = new DocID(ndocid);

        short filenum = docid.getFileNum();
        short recnum = docid.getRecNum();

        File file = repos.getFile(db, filenum);

        try {
            Element record = getRecord(file, recnum);
            record.setAttribute("docid", Integer.toString(ndocid));
            return record;
        } catch (ParserConfigurationException e) {
            throw new IOException(e);
        } catch (XPathExpressionException e) {
            throw new IOException(e);
        }
    }

    public Element getRecord(File file, short recnum)
            throws IOException, ParserConfigurationException,
            XPathExpressionException {

        String sExpr = String.format("//record/record[position()=%d]", recnum);

        XPathExpression expr = xpath.compile(sExpr);

        InputSource source = new InputSource(new FileReader(file));

        try {
            return (Element) expr.evaluate(source, XPathConstants.NODE);
        } catch (ClassCastException e) {
            throw new IOException(e);
        }
    }
}
