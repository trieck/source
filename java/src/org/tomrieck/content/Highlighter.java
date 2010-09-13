package org.tomrieck.content;

import org.tomrieck.xml.XMLTransformer;
import org.tomrieck.xml.XMLUtil;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
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
import java.util.ArrayList;
import java.util.List;

public class Highlighter {

    private class QueryTerms {
        public String[] terms(String query) throws IOException {

            List<String> strings = new ArrayList<String>();

            Lexer lexer = new Lexer(new StringReader(query));

            String term;
            while ((term = lexer.getToken()).length() > 0) {
                strings.add(term);
            }

            String[] aStrings = new String[strings.size()];
            strings.toArray(aStrings);

            return aStrings;
        }
    }

    private class DocHighlighter extends DefaultHandler {
        private Document output;    // output document
        private Element element;    // current element
        private String sElement;    // current element name
        private String[] terms;     // query terms

        public DocHighlighter(String query)
                throws ParserConfigurationException, IOException {
            output = XMLUtil.newDocument();
            QueryTerms qterms = new QueryTerms();
            terms = qterms.terms(query);
        }

        public Document getDocument() {
            return output;
        }

        public void startElement(String namespaceURI, String localName, String rawName, Attributes atts)
                throws SAXException {
            sElement = localName;
            org.w3c.dom.Element next = output.createElement(localName);
            if (element == null) {
                element = (org.w3c.dom.Element) output.appendChild(next);
            } else {
                element = (org.w3c.dom.Element) element.appendChild(next);
            }

            for (int i = 0; i < atts.getLength(); i++) {
                element.setAttribute(atts.getLocalName(i), atts.getValue(i));
            }
        }

        public void endElement(String namespaceURI, String localName, String rawName)
                throws SAXException {
            Node parent = element.getParentNode();
            if (parent.getNodeType() == Node.ELEMENT_NODE)
                element = (org.w3c.dom.Element) parent;
        }

        public void characters(char[] ch, int start, int end) {
            String value = new String(ch, start, end);
            highlight(value);
        }

        private void highlight(String value) {
        }

        private boolean match(String value) {
            for (String term : terms) {
                if (value.equalsIgnoreCase(term))
                    return true;
            }

            return false;
        }
    }

    public Document highlight(Document doc, String query)
            throws IOException {

        try {
            DocHighlighter handler = new DocHighlighter(query);
            SAXParserFactory parserFactory = SAXParserFactory.newInstance();
            SAXParser parser = parserFactory.newSAXParser();

            StringWriter writer = new StringWriter();
            XMLTransformer.transform(new DOMSource(doc), writer);
            String rep = writer.toString();

            StringReader reader = new StringReader(rep);

            parser.parse(new InputSource(reader), handler);

            return handler.getDocument();
        } catch (ParserConfigurationException e) {
            throw new IOException(e);
        } catch (SAXException e) {
            throw new IOException(e);
        } catch (TransformerException e) {
            throw new IOException(e);
        }
    }
}
