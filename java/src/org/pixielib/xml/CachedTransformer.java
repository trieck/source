package org.pixielib.xml;

import org.pixielib.util.Config;
import org.w3c.dom.Document;
import org.xml.sax.SAXException;

import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerConfigurationException;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import java.io.File;
import java.io.IOException;
import java.util.Hashtable;
import java.util.Map;

public class CachedTransformer {

    /**
     * the transformer factory
     */
    private final TransformerFactory factory;

    /**
     * underlying map of strings to transformers
     */
    private final Map<String, Transformer> table;

    private Config config;

    /**
     * the singleton instance
     */
    private static CachedTransformer instance = null;

    private CachedTransformer() throws IOException {
        factory = TransformerFactory.newInstance();
        table = new Hashtable<String, Transformer>();
        config = Config.getInstance();        
    }

    public static synchronized CachedTransformer getInstance()
            throws IOException {
        if (instance == null) {
            instance = new CachedTransformer();
        }

        return instance;
    }

    private Transformer createTransformer(File file)
            throws ParserConfigurationException, IOException, SAXException,
            TransformerConfigurationException {

        Transformer transformer;

        Document doc = XMLUtil.parseXML(file);
        DOMSource source = new DOMSource(doc);

        // TransfomerFactory is NOT guaranteed to be thread safe
        synchronized (factory) {
            transformer = factory.newTransformer(source);
        }

        String cacheStylesheets = config.getProperty("stylesheet-cache");
        if (cacheStylesheets.equals("on")) {
            table.put(file.getCanonicalPath(), transformer);
        }

        return transformer;
    }

    public Transformer getTransformer(File file)
            throws ParserConfigurationException, IOException, SAXException,
            TransformerConfigurationException {

        // use a normalized naming scheme
        String filename = file.getCanonicalPath();

        Transformer t = null;

        String cacheStylesheets = config.getProperty("stylesheet-cache");
        if (cacheStylesheets.equals("on")) {
            t = table.get(filename);
        } else {
            table.clear();
        }

        if (t == null) {
            t = createTransformer(file);
        }

        return t;
    }
}
