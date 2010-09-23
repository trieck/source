package org.pixielib.content;

import org.pixielib.xml.XMLTransformer;
import org.pixielib.xml.XMLUtil;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import org.xml.sax.Attributes;
import org.xml.sax.InputSource;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;

import javax.xml.parsers.ParserConfigurationException;
import javax.xml.parsers.SAXParser;
import javax.xml.parsers.SAXParserFactory;
import javax.xml.transform.TransformerException;
import javax.xml.transform.dom.DOMSource;
import java.io.IOException;
import java.io.StringReader;
import java.io.StringWriter;

public class Highlighter extends DefaultHandler {

    private static final SAXParserFactory factory = SAXParserFactory.newInstance();

    private Document output;    // output document
    private QueryTerms terms;   // query terms
    private String field;       // current field name while parsing
    private Element element;    // current element

    private Highlighter(QueryTerms terms) throws IOException, ParserConfigurationException {
        this.terms = terms;
        output = XMLUtil.newDocument();
    }

    @Override
    public void startElement(String namespaceURI, String localName, String rawName, Attributes atts)
            throws SAXException {
        field = rawName;
        org.w3c.dom.Element next = output.createElement(rawName);
        if (element == null) {
            element = (org.w3c.dom.Element) output.appendChild(next);
        } else {
            element = (org.w3c.dom.Element) element.appendChild(next);
        }

        for (int i = 0; i < atts.getLength(); i++) {
            element.setAttribute(atts.getLocalName(i), atts.getValue(i));
        }
    }

    @Override
    public void endElement(String namespaceURI, String localName, String rawName)
            throws SAXException {
        Node parent = element.getParentNode();
        if (parent.getNodeType() == Node.ELEMENT_NODE)
            element = (org.w3c.dom.Element) parent;
    }

    @Override
    public void characters(char[] ch, int start, int end) {
        String value = new String(ch, start, end);

        char[] buffer = value.toCharArray();

        StringBuilder token = new StringBuilder();
        StringBuilder builder = new StringBuilder();

        for (char c : buffer) {
            if (Character.isLetterOrDigit(c)) {
                token.append(c);
            } else if ((c == '_' || c == '\'') && token.length() > 0) {
                token.append(c);
            } else if (token.length() > 0) {
                if (match(token.toString())) {
                    builder.append("<highlight>");
                    builder.append(token.toString());
                    builder.append("</highlight>");
                } else {
                    builder.append(token.toString());
                }
                token.setLength(0);
                builder.append(c);
            } else {
                builder.append(c);
            }
        }

        if (token.length() > 0 && match(token.toString())) {
            builder.append("<highlight>");
            builder.append(token.toString());
            builder.append("</highlight>");
        } else if (token.length() > 0) {
            builder.append(token.toString());
        }

        StringBuilder xml = new StringBuilder();
        xml.append("<root>");
        xml.append(builder.toString());
        xml.append("</root>");

        Document doc;
        try {
            doc = XMLUtil.parseXML(xml.toString());
        } catch (Exception e) {
            return;
        }

        Element root = doc.getDocumentElement();
        NodeList list = root.getChildNodes();
        Node node;

        for (int i = 0; i < list.getLength(); i++) {
            node = list.item(i);
            XMLUtil.transferNode(element, output, node);
        }
    }

    private boolean match(String value) {

        String restriction = String.format("%s:%s", field, value.toLowerCase());

        return terms.match(restriction);
    }

    public static Document highlight(Document doc, QueryTerms terms)
            throws IOException, ParserConfigurationException, SAXException {

        Highlighter highlighter = new Highlighter(terms);

        SAXParser parser;
        synchronized (factory) {
            parser = factory.newSAXParser();
        }

        StringWriter writer = new StringWriter();
        try {
            XMLTransformer.transform(new DOMSource(doc), writer);
        } catch (TransformerException e) {
            throw new IOException(e);
        }

        StringReader reader = new StringReader(writer.toString());
        parser.parse(new InputSource(reader), highlighter);

        return highlighter.output;
    }    
}
