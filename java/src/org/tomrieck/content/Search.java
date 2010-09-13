package org.tomrieck.content;

import org.tomrieck.util.Timer;
import org.w3c.dom.Document;

import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.OutputKeys;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerException;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;
import java.io.IOException;

public class Search {

    public Search() {
    }

    public void search(String db, String query) throws IOException,
            ParserConfigurationException, TransformerException {

        Content content = new Content();
        Document doc = content.search(db, query, 1, 25);

        TransformerFactory factory = TransformerFactory.newInstance();
        Transformer transformer = factory.newTransformer();
        transformer.setOutputProperty(OutputKeys.OMIT_XML_DECLARATION, "no");
        transformer.setOutputProperty("encoding", "UTF-8");
        transformer.setOutputProperty(OutputKeys.INDENT, "yes");

        DOMSource source = new DOMSource(doc);

        StreamResult result = new StreamResult(System.out);
        transformer.transform(source, result);
    }

    public static void main(String[] args) {
        if (args.length < 2) {
            System.err.println("usage: Search db \"phrase\"");
            System.exit(1);
        }

        Timer t = new Timer();

        Search search = new Search();

        try {
            search.search(args[0], args[1]);
        } catch (IOException e) {
            System.err.println(e);
            System.exit(1);
        } catch (TransformerException e) {
            System.err.println(e);
            System.exit(2);
        } catch (ParserConfigurationException e) {
            System.err.println(e);
            System.exit(3);
        }

        System.out.printf("\n    elapsed time %s\n", t);
    }
}
