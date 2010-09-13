package org.tomrieck.content;

import org.tomrieck.util.Timer;
import org.tomrieck.xml.XMLUtil;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import org.xml.sax.SAXException;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.OutputKeys;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerException;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class XMLSplitter {

    private static final DocumentBuilderFactory dbfactory = DocumentBuilderFactory.newInstance();
    private static final TransformerFactory transfactory = TransformerFactory.newInstance();

    public XMLSplitter() {
    }

    public void split(String xml_file, String sElement, String path)
            throws IOException, ParserConfigurationException,
            TransformerException, SAXException {

        DocumentBuilder builder = dbfactory.newDocumentBuilder();
        Document doc = builder.parse(new FileInputStream(xml_file));

        NodeList elements = doc.getElementsByTagName(sElement);
        if (elements.getLength() == 0)
            throw new IOException(String.format("element \"%s\" not found.", sElement));

        Node element;
        for (int i = 0; i < elements.getLength(); i++) {
            element = elements.item(i);
            writeElement(i + 1, path, (Element) element);
        }
    }

    private void writeElement(int docnum, String path, Element element)
            throws IOException, ParserConfigurationException,
            TransformerException {

        // ensure the root path exists
        File f = new File(path);
        if (!f.exists() && !f.mkdir()) {
            throw new IOException(
                    String.format("could not create directory \"%s\".\n", path));
        }

        String filename = String.format("%s/%04x.xml", path, docnum);

        writeDoc(filename, element);
    }

    private void writeDoc(String path, Element element)
            throws IOException, ParserConfigurationException,
            TransformerException {

        DocumentBuilder builder = dbfactory.newDocumentBuilder();
        Document doc = builder.newDocument();
        Element root = doc.createElement("document");
        doc.appendChild(root);

        XMLUtil.transferNode(root, doc, element);

        Transformer transformer = transfactory.newTransformer();
        transformer.setOutputProperty(OutputKeys.OMIT_XML_DECLARATION, "no");
        transformer.setOutputProperty("encoding", "UTF-8");
        transformer.setOutputProperty(OutputKeys.INDENT, "yes");

        DOMSource source = new DOMSource(doc);

        StreamResult result = new StreamResult(new FileOutputStream(path));
        transformer.transform(source, result);
    }

    public static void main(String[] args) {
        if (args.length != 3) {
            System.err.println("usage: XMLSplitter xml-file element-to-split output-path");
            System.exit(1);
        }

        Timer t = new Timer();

        XMLSplitter splitter = new XMLSplitter();

        try {
            splitter.split(args[0], args[1], args[2]);
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
