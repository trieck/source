package org.pixielib.xml;

import org.w3c.dom.Document;
import org.xml.sax.SAXException;

import javax.xml.parsers.ParserConfigurationException;
import java.io.IOException;
import java.net.URL;
import java.net.URLConnection;

public class XMLHttpRequest {

	public static Document request(String sURL)
			throws IOException {

		URL url = new URL(sURL);
		URLConnection uc = url.openConnection();

		try {
			return XMLUtil.parseXML(uc.getInputStream());
		} catch (ParserConfigurationException e) {
			throw new IOException(e);
		} catch (SAXException e) {
			throw new IOException(e);
		}
	}
}
