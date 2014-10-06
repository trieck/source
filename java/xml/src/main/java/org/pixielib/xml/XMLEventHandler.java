package org.pixielib.xml;

import javax.xml.stream.XMLStreamException;
import javax.xml.stream.events.*;

public interface XMLEventHandler {
    public void startElement(StartElement element) throws XMLStreamException;

    public void endElement(EndElement element) throws XMLStreamException;

    public void characters(Characters chars) throws XMLStreamException;

    public void attribute(Attribute attrs) throws XMLStreamException;

    public void namespace(Namespace namespace) throws XMLStreamException;

    public void processingInstruction(ProcessingInstruction instr) throws XMLStreamException;

    public void comment(Comment comment) throws XMLStreamException;

    public void startDocument(StartDocument doc) throws XMLStreamException;

    public void endDocument(EndDocument doc) throws XMLStreamException;

    public void DTD(DTD dtd) throws XMLStreamException;
}
