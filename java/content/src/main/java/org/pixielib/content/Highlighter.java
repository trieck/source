package org.pixielib.content;

import org.pixielib.xml.XMLEventHandlerImpl;
import org.pixielib.xml.XMLEventParser;
import org.pixielib.xml.XMLTransformer;
import org.pixielib.xml.XMLUtil;
import org.w3c.dom.Document;
import org.xml.sax.SAXException;

import javax.xml.parsers.ParserConfigurationException;
import javax.xml.stream.*;
import javax.xml.stream.events.Attribute;
import javax.xml.stream.events.Characters;
import javax.xml.stream.events.EndElement;
import javax.xml.stream.events.StartElement;
import javax.xml.transform.TransformerException;
import java.io.IOException;
import java.io.Reader;
import java.io.StringWriter;
import java.io.Writer;
import java.util.Iterator;

public class Highlighter extends XMLEventHandlerImpl {

    private static final XMLInputFactory inFactory = XMLInputFactory.newInstance();
    private static final XMLOutputFactory outFactory = XMLOutputFactory.newInstance();

    static {
        inFactory.setProperty(XMLInputFactory.IS_REPLACING_ENTITY_REFERENCES, false);
    }

    private QueryTerms terms;
    private Writer writer;
    private XMLStreamWriter stream;
    private IndexFields fields;
    private String field = "";   // current element seen during parsing

    private Highlighter(QueryTerms terms, IndexFields fields) throws XMLStreamException {
        this.fields = fields;
        this.terms = terms;
        writer = new StringWriter();
        stream = outFactory.createXMLStreamWriter(writer);
    }

    public static Document highlight(Document doc, QueryTerms terms, IndexFields fields)
            throws ParserConfigurationException, IOException,
            SAXException, XMLStreamException, TransformerException {

        Reader r = XMLTransformer.asReader(doc);
        XMLEventReader reader = inFactory.createXMLEventReader(r);
        Highlighter highlighter = new Highlighter(terms, fields);

        XMLEventParser parser = new XMLEventParser();
        parser.parse(reader, highlighter);

        return highlighter.getOutput();
    }

    @Override
    public void startElement(StartElement element) throws XMLStreamException {
        String sElement = element.getName().toString();
        if (fields.isTopLevel(sElement))
            field = sElement;

        stream.writeStartElement(sElement);

        Attribute attr;
        String name, value;
        for (Iterator it = element.getAttributes(); it.hasNext(); ) {
            attr = (Attribute) it.next();
            name = attr.getName().getLocalPart();
            value = attr.getValue();
            stream.writeAttribute(name, value);
        }
    }

    @Override
    public void endElement(EndElement element) throws XMLStreamException {
        stream.writeEndElement();
    }

    @Override
    public void characters(Characters chars) throws XMLStreamException {

        String value = chars.toString();

        char[] buffer = value.toCharArray();

        StringBuilder token = new StringBuilder();

        for (char c : buffer) {
            if (Character.isLetterOrDigit(c)) {
                token.append(c);
            } else if ((c == '_' || c == '\'') && token.length() > 0) {
                token.append(c);
            } else if (token.length() > 0) {
                if (match(token.toString())) {
                    stream.writeStartElement("highlight");
                    stream.writeCharacters(token.toString());
                    stream.writeEndElement();
                } else {
                    stream.writeCharacters(token.toString());
                }
                token.setLength(0);
                stream.writeCharacters("" + c);
            } else {
                stream.writeCharacters("" + c);
            }
        }

        if (token.length() > 0 && match(token.toString())) {
            stream.writeStartElement("highlight");
            stream.writeCharacters(token.toString());
            stream.writeEndElement();
        } else if (token.length() > 0) {
            stream.writeCharacters(token.toString());
        }
    }

    private boolean match(String value) {

        String restriction = String.format("%s:%s", field, value.toLowerCase());

        return terms.match(restriction);
    }

    private Document getOutput()
            throws ParserConfigurationException, IOException, SAXException {
        return XMLUtil.parseXML(writer.toString());
    }

}
