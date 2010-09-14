package org.tomrieck.content;

import org.tomrieck.util.Timer;
import org.tomrieck.xml.XMLTransformer;
import org.tomrieck.xml.XMLUtil;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import org.xml.sax.SAXException;

import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.TransformerException;
import javax.xml.transform.dom.DOMSource;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class XMLSplitter {

    private static final short MAX_RECS = 1000;   // number of records to split on, not greater than 2^15-1

    public XMLSplitter() {
    }

    public void split(String xml_file, String path)
            throws IOException, ParserConfigurationException,
            TransformerException, SAXException {

        Document doc = XMLUtil.parseXML(new File(xml_file));

        NodeList elements = doc.getElementsByTagName("record");
        if (elements.getLength() == 0)
            throw new IOException("no record elements found.");

        Document records = makeDocument();
        Node element;
        int i, j;
        for (i = 0, j = 0; i < elements.getLength(); i++) {
            element = elements.item(i);

            if (i > 0 && i % MAX_RECS == 0) {
                writeDoc(path, records, ++j);
                records = makeDocument();
            } else {
                XMLUtil.transferNode(records.getDocumentElement(), records, element);
            }
        }

        if (i > 0 && (i - 1) % MAX_RECS != 0) {
            writeDoc(path, records, ++j);
        }
    }

    private Document makeDocument() throws ParserConfigurationException {
        Document doc = XMLUtil.newDocument();
        Element element = doc.createElement("records");
        doc.appendChild(element);
        return doc;
    }

    private File makeFile(String path, int docnum) throws IOException {
        // ensure the root path exists
        File f = new File(path);
        if (!f.exists() && !f.mkdir()) {
            throw new IOException(
                    String.format("could not create directory \"%s\".\n", path));
        }

        String filename = String.format("%s/%04x.xml", path, docnum);

        return new File(filename);
    }

    private void writeDoc(String path, Document doc, int docnum)
            throws IOException, ParserConfigurationException,
            TransformerException {
        File file = makeFile(path, docnum);
        XMLTransformer.transform(new DOMSource(doc), new FileWriter(file));
    }

    public static void main(String[] args) {
        if (args.length != 2) {
            System.err.println("usage: XMLSplitter xml-file output-path");
            System.exit(1);
        }

        Timer t = new Timer();

        XMLSplitter splitter = new XMLSplitter();

        try {
            splitter.split(args[0], args[1]);
        } catch (IOException e) {
            System.err.println(e);
            System.exit(1);
        } catch (ParserConfigurationException e) {
            System.err.println(e);
            System.exit(2);
        } catch (SAXException e) {
            System.err.println(e);
            System.exit(3);
        } catch (TransformerException e) {
            System.err.println(e);
            System.exit(4);
        }

        System.out.printf("    elapsed time %s\n", t);
    }
}
