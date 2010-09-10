package org.tomrieck.xml;

import org.tomrieck.util.Timer;
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
import java.util.Arrays;
import java.util.List;

public class XMLSplitter {

    private static final DocumentBuilderFactory dbfactory = DocumentBuilderFactory.newInstance();
    private static final TransformerFactory transfactory = TransformerFactory.newInstance();

    public XMLSplitter() {
    }

    public void split(String xml_file, String root)
            throws IOException, ParserConfigurationException,
                TransformerException, SAXException {

        DocumentBuilder builder = dbfactory.newDocumentBuilder();
        Document doc = builder.parse(new FileInputStream(xml_file));

        NodeList elements = doc.getElementsByTagName("text");
        if (elements.getLength() == 0)
            throw new IOException("no text elements found.");
        
        Node element;
        for (int i = 0; i < elements.getLength(); i++) {
            element = elements.item(i);
            writeElement(root, (Element)element);
        }
    }

    private void writeElement(String root, Element element)
        throws IOException, ParserConfigurationException,
            TransformerException {
        String sPath = getPath(element);

        List<String> pathlist = makePath(sPath);
        if (pathlist.size() < 1)
            throw new IOException(String.format("bad path %s specified.", sPath));

        // ensure the root path exists
        File f = new File(root);
        if (!f.exists() && !f.mkdir()) {
            throw new IOException(
                String.format("could not create directory \"%s\".\n", root));
        }

        // create subdirectories & file
        String path = root;
        for (int i = 0; i < pathlist.size(); i++) {
            path = path + "/" + pathlist.get(i);

            if (i < pathlist.size() - 1) {
               f = new File(path);
               if (!f.exists() && !f.mkdir()) {
                    throw new IOException(
                        String.format("could not create directory \"%s\".\n", path));
               }
            } else {    // last item is the filename
                path = path + ".xml";
                writeDoc(path, element);
            }
        } 
    }

    private void writeDoc(String path, Element element)
        throws IOException, ParserConfigurationException,
            TransformerException {

        DocumentBuilder builder = dbfactory.newDocumentBuilder();
        Document doc = builder.newDocument();
        Element root = doc.createElement("root");
        Element text = doc.createElement("text");

        text.setTextContent(element.getTextContent());
        root.appendChild(text);
        doc.appendChild(root);

        Transformer transformer = transfactory.newTransformer();
        transformer.setOutputProperty(OutputKeys.OMIT_XML_DECLARATION, "no");
        transformer.setOutputProperty("encoding", "UTF-8");        
        transformer.setOutputProperty(OutputKeys.INDENT, "yes");        

        DOMSource source = new DOMSource(doc);

        StreamResult result = new StreamResult(new FileOutputStream(path));
        transformer.transform(source, result);
    }

    private List<String> makePath(String sPath) {
        String[] aPath = sPath.split("/");
        return Arrays.asList(aPath);
    }
    
    private static String getPath(Element element) throws IOException {
        String path = element.getAttribute("path");
        if (path == null || path.length() == 0)
            throw new IOException("empty path attribute.");

        return path;
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
