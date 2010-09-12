package org.tomrieck.xml;

import org.w3c.dom.*;
import org.xml.sax.SAXException;

import javax.xml.parsers.DocumentBuilder;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;

import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;

public class XMLUtil {

    private static final DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
    
    public static Document parseXML(File f)
        throws ParserConfigurationException, IOException, SAXException {
        DocumentBuilder builder;
        synchronized (factory) {
            builder = factory.newDocumentBuilder();
        }
        return builder.parse(f);
    }


    /**
     * * Convenience method to transfer a node (and all of its children) from one
     * * DOM XML document to another.
     * *
     * * Note: this method is recursive.
     * *
     * * @param current the current Element to append the transfer to
     * * @param target the target document for the transfer
     * * @param n the Node to transfer
     * * @return Element the current element.
     */
    public static Element transferNode(Element current, Document target, Node n) {
        String name = n.getNodeName();
        String value = n.getNodeValue();
        short type = n.getNodeType();

        if (type == n.ELEMENT_NODE) {
            // create a new element for this node in the target document
            Element e = target.createElement(name);

            // move all the attributes over to the target document
            NamedNodeMap attrs = n.getAttributes();
            for (int i = 0; i < attrs.getLength(); i++) {
                Node a = attrs.item(i);
                e.setAttribute(a.getNodeName(), a.getNodeValue());
            }

            // get the children for this node
            NodeList children = n.getChildNodes();
            for (int i = 0; i < children.getLength(); i++) {
                // transfer each of the children to the new document
                transferNode(e, target, children.item(i));
            }

            // append the node to the target document element
            current.appendChild(e);
        } else if (type == n.TEXT_NODE) {
            Text text = target.createTextNode(value);
            current.appendChild(text);
        } else {
            // unrecognized node type, don't copy anything
        }

        return current;
    }

    /**
     * * Merge two DOM XML documents.
     * *
     * * @param master the master document that will "absorb" the slave
     * * @param slave the slave document that will be "absorbed" into the master
     * * @return Document the master document with the slave document inside it
     */
    public static Document merge(Document master, Document slave) {
        // merge the slave document into the master
        transferNode(
                master.getDocumentElement(),
                master,
                slave.getDocumentElement()
        );

        // return the merged document
        return master;
	}	
}
