package org.pixielib.xml;

import org.w3c.dom.Document;

import javax.xml.transform.Source;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerException;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;
import javax.xml.transform.stream.StreamSource;
import java.io.*;

public class XMLTransformer {

    private static final TransformerFactory factory = TransformerFactory.newInstance();

    public XMLTransformer() {
    }

    public static void transform(String xmlFile, String xslFile, OutputStream os)
            throws TransformerException {
        StreamSource xmlSource = new StreamSource(xmlFile);
        StreamSource xslSource = new StreamSource(xslFile);
        transform(xmlSource, xslSource, os);
    }

    public static void transform(String xmlFile, String xslFile, Writer writer)
            throws TransformerException {
        StreamSource xmlSource = new StreamSource(xmlFile);
        StreamSource xslSource = new StreamSource(xslFile);
        transform(xmlSource, xslSource, writer);
    }

    public static void transform(Document xml, Document xsl, OutputStream os)
            throws TransformerException {
        DOMSource xmlSource = new DOMSource(xml);
        DOMSource xslSource = new DOMSource(xsl);
        transform(xmlSource, xslSource, os);
    }

    public static void transform(Document xml, Document xsl, Writer writer)
            throws TransformerException {
        DOMSource xmlSource = new DOMSource(xml);
        DOMSource xslSource = new DOMSource(xsl);
        transform(xmlSource, xslSource, writer);
    }

    public static void transform(Source xml, Source xsl, OutputStream os)
            throws TransformerException {
        Transformer transformer;
        synchronized (factory) {
            transformer = factory.newTransformer(xsl);
        }
        transformer.transform(xml, new StreamResult(os));
    }

    public static void transform(Source xml, Source xsl, Writer writer)
            throws TransformerException {
        Transformer transformer;
        synchronized (factory) {
            transformer = factory.newTransformer(xsl);
        }
        transformer.transform(xml, new StreamResult(writer));
    }

    public static void transform(Document xml, OutputStream os)
            throws TransformerException {
        Transformer transformer;
        synchronized (factory) {
            transformer = factory.newTransformer();
        }
        transformer.transform(new DOMSource(xml), new StreamResult(os));
    }

    public static void transform(Document xml, Writer writer)
            throws TransformerException {
        Transformer transformer;
        synchronized (factory) {
            transformer = factory.newTransformer();
        }
        transformer.transform(new DOMSource(xml), new StreamResult(writer));
    }

    public static void transform(Source xml, OutputStream os)
            throws TransformerException {
        Transformer transformer;
        synchronized (factory) {
            transformer = factory.newTransformer();
        }
        transformer.transform(xml, new StreamResult(os));
    }

    public static void transform(Source xml, Writer writer)
            throws TransformerException {
        Transformer transformer;
        synchronized (factory) {
            transformer = factory.newTransformer();
        }
        transformer.transform(xml, new StreamResult(writer));
    }

    public static Reader asReader(Document doc) throws TransformerException {
        StringWriter writer = new StringWriter();
        transform(doc, writer);
        return new StringReader(writer.toString());
    }

    public static void main(String[] args) {
        if (args.length != 2) {
            System.err.println("usage: XMLTransformer xml-file xslt-file");
            System.exit(1);
        }

        try {
            XMLTransformer.transform(args[0], args[1], System.out);
        } catch (TransformerException e) {
            System.err.println(e);
            System.exit(1);
        }
    }
}
