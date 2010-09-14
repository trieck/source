package org.tomrieck.content;

import org.tomrieck.util.Timer;
import org.xml.sax.Attributes;
import org.xml.sax.InputSource;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;

import javax.xml.parsers.ParserConfigurationException;
import javax.xml.parsers.SAXParser;
import javax.xml.parsers.SAXParserFactory;
import java.io.*;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class XMLIndexer extends DefaultHandler {

    private SAXParserFactory factory = SAXParserFactory.newInstance();

    private Repository repos;   // repository instance
    private Index index;        // index instance
    private String field;       // current tag while parsing
    private short docnum;       // current document number while indexing
    private short recnum;       // current record number while parsing
    
    public XMLIndexer() throws IOException {
        repos = Repository.getInstance();
    }

    public void startElement(String namespaceURI, String localName, String rawName, Attributes atts)
            throws SAXException {
        field = rawName;
        if (field.equals("record")) {
            recnum++;
        }        
    }

    public void characters(char[] ch, int start, int end) {
        String text = new String(ch, start, end);

        Lexer lexer = new Lexer(new StringReader(text));

        int docid = DocID.makeDocID(docnum, recnum);
        long anchor;

        try {
            String term, tok;
            for (int i = 0; ((tok = lexer.getToken()).length()) != 0; i++) {
                term = String.format("%s:%s", field, tok);
                anchor = Anchor.makeAnchorID(docid, i);                
                index.insert(term, anchor);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void load(String db)
            throws IOException, SAXException, ParserConfigurationException {

        File dir = repos.mapPath(db);

        List<File> files = expand(dir);
        if (files.size() == 0)
            throw new IOException(
                    String.format("no content files found in \"%s\".",
                            dir.getCanonicalPath())
            );

        index = new Index();
        loadfiles(files);
        index.write(db);
    }

    private void loadfiles(List<File> files)
            throws IOException, SAXException, ParserConfigurationException {
        for (File f : files) {
            loadfile(f);
            docnum++;
            recnum = 0;
        }
    }

    private void loadfile(File file)
            throws IOException, SAXException, ParserConfigurationException {
        SAXParser parser = factory.newSAXParser();
        parser.parse(new InputSource(new FileReader(file)), this);
    }

    private List<File> expand(File dir) {
        List<File> result = new ArrayList<File>();

        // list xml files
        File[] files = dir.listFiles(new FilenameFilter() {
            public boolean accept(File dir, String name) {
                return name.endsWith(".xml");
            }
        }
        );

        result.addAll(Arrays.asList(files));

        return result;
    }

    public static void main(String[] args) {
        if (args.length != 1) {
            System.err.println("usage: XMLIndexer database");
            System.exit(1);
        }

        Timer t = new Timer();

        try {
            XMLIndexer indexer = new XMLIndexer();
            indexer.load(args[0]);
        } catch (IOException e) {
            System.err.println(e);
            System.exit(1);
        } catch (SAXException e) {
            System.err.println(e);
            System.exit(2);
        } catch (ParserConfigurationException e) {
            System.err.println(e);
            System.exit(3);
        }

        System.out.printf("    elapsed time %s\n", t);
    }
}
