package org.pixielib.xml;

import javax.xml.stream.XMLStreamException;
import javax.xml.stream.events.*;

public interface XMLEventHandler {
    void startElement(StartElement element) throws XMLStreamException;

    void endElement(EndElement element) throws XMLStreamException;

    void characters(Characters chars) throws XMLStreamException;

    void attribute(Attribute attrs) throws XMLStreamException;

    void namespace(Namespace namespace) throws XMLStreamException;

    void processingInstruction(ProcessingInstruction instr) throws XMLStreamException;

    void comment(Comment comment) throws XMLStreamException;

    void startDocument(StartDocument doc) throws XMLStreamException;

    void endDocument(EndDocument doc) throws XMLStreamException;

    void DTD(DTD dtd) throws XMLStreamException;
}
