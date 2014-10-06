package org.pixielib.content;

import org.pixielib.util.Timer;
import org.pixielib.xml.XMLTransformer;
import org.pixielib.xml.XMLUtil;
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

    private static final int DEFAULT_REC_SIZE = 1000;   // number of records to split on

    public XMLSplitter() {
    }

    public static void main(String[] args) {
        if (args.length < 2) {
            System.err.println("usage: XMLSplitter xml-file output-path [record-size]");
            System.exit(1);
        }

        Timer t = new Timer();

        int nrecsize = DEFAULT_REC_SIZE;

        XMLSplitter splitter = new XMLSplitter();

        try {
            if (args.length > 2) {
                nrecsize = Integer.parseInt(args[2]);
            }
            splitter.split(args[0], args[1], nrecsize);
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
        } catch (NumberFormatException e) {
            System.err.println(e);
            System.exit(5);
        }

        System.out.printf("    elapsed time %s\n", t);
    }

    public void split(String xml_file, String path, int recsize)
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

            if (i > 0 && i % recsize == 0) {
                writeDoc(path, records, ++j);
                records = makeDocument();
            } else {
                XMLUtil.transferNode(records.getDocumentElement(), records, element);
            }
        }

        if (i > 0 && (i - 1) % recsize != 0) {
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

        String filename = String.format("%s/%04d.xml", path, docnum);

        return new File(filename);
    }

    private void writeDoc(String path, Document doc, int docnum)
            throws IOException, ParserConfigurationException,
            TransformerException {
        File file = makeFile(path, docnum);
        XMLTransformer.transform(new DOMSource(doc), new FileWriter(file));
    }
}
