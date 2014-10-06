package org.pixielib.xml;

import javax.xml.stream.XMLEventReader;
import javax.xml.stream.XMLStreamException;
import javax.xml.stream.events.*;

public class XMLEventParser {

    public void parse(XMLEventReader reader, XMLEventHandler handler)
            throws XMLStreamException {
        XMLEvent event;

        while (reader.hasNext()) {
            event = reader.nextEvent();
            switch (event.getEventType()) {
                case XMLEvent.DTD:
                    handler.DTD((DTD) event);
                    break;
                case XMLEvent.START_DOCUMENT:
                    handler.startDocument((StartDocument) event);
                    break;
                case XMLEvent.END_DOCUMENT:
                    handler.endDocument((EndDocument) event);
                    break;
                case XMLEvent.ATTRIBUTE:
                    handler.attribute((Attribute) event);
                    break;
                case XMLEvent.START_ELEMENT:
                    handler.startElement(event.asStartElement());
                    break;
                case XMLEvent.END_ELEMENT:
                    handler.endElement(event.asEndElement());
                    break;
                case XMLEvent.CHARACTERS:
                    handler.characters(event.asCharacters());
                    break;
                case XMLEvent.NAMESPACE:
                    handler.namespace((Namespace) event);
                    break;
                case XMLEvent.PROCESSING_INSTRUCTION:
                    handler.processingInstruction((ProcessingInstruction) event);
                    break;
                case XMLEvent.COMMENT:
                    handler.comment((Comment) event);
                    break;
            }
        }
    }
}
