package org.tomrieck.xml;

import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerException;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.stream.StreamResult;
import javax.xml.transform.stream.StreamSource;
import java.io.OutputStream;

public class XMLTransformer {

    public XMLTransformer() {
    }

    public void transform(String xml_file, String xslt_file, OutputStream os)
        throws TransformerException {

        TransformerFactory factory = TransformerFactory.newInstance();
        
        Transformer transformer = factory.newTransformer(new StreamSource(xslt_file));
        transformer.transform(new StreamSource(xml_file), new StreamResult(os));
    }

    public static void main(String[] args) {
        if (args.length != 2) {
            System.err.println("usage: XMLTransformer xml-file xslt-file");
            System.exit(1);
        }

        XMLTransformer XMLTransformer = new XMLTransformer();
        try {
            XMLTransformer.transform(args[0], args[1], System.out);
        } catch (TransformerException e) {
            System.err.println(e);
            System.exit(1);
        }
        
    }
}
