package org.tomrieck.content;

import org.tomrieck.util.Timer;
import org.xml.sax.InputSource;

import javax.xml.xpath.XPath;
import javax.xml.xpath.XPathExpression;
import javax.xml.xpath.XPathExpressionException;
import javax.xml.xpath.XPathFactory;
import java.io.*;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class XMLIndexer {

    private static final XPathFactory factory = XPathFactory.newInstance();
    private static final XPath xpath = factory.newXPath();
    
    private Repository repos;   // repository instance
    private Index index;        // index instance
    private int currDoc;        // current document number while indexing

    public XMLIndexer() throws IOException {
        repos = Repository.getInstance();
    }

    public void load(String db)
            throws IOException, XPathExpressionException {

        File dir = repos.mapPath(db);

        List<File> files = expand(dir);
        if (files.size() == 0)
            throw new IOException(
                String.format("no content files found in \"%s\".",
                    dir.getCanonicalPath())
        );

        index = new Index();

        loadfiles(files);

        index.write(db, files.size());
    }

    private void loadfiles(List<File> files)
        throws IOException, XPathExpressionException {
        for (File f : files) {
            loadfile(f);
            currDoc++;
        }
    }

    private void loadfile(File file)
            throws IOException, XPathExpressionException {
        XPathExpression expr = xpath.compile("//document/*/text");

        InputSource source = new InputSource(
                new FileInputStream(file)
        );

        String text = expr.evaluate(source);
        if (text.length() == 0) {
            System.err.printf("empty text found for file \"%s\".\n", 
                file.getCanonicalPath());
        }

        Lexer lexer = new Lexer(new StringReader(text));

        String term;
        for (int i = 0; ((term = lexer.getToken()).length()) != 0; i++) {
            index.insert(term, currDoc+1, i);
        }
    }

    private List<File> expand(File dir) {
        List<File> result = new ArrayList<File>();

         // expand sub-directories
        File[] dirs = dir.listFiles(new FilenameFilter() {
                public boolean accept(File dir, String name) {
                    File f = new File(dir.getAbsolutePath(), name);
                    return f.isDirectory();
                }
            }
        );

        for (File d : dirs) {
            result.addAll(expand(d));
        }

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
        } catch (XPathExpressionException e) {
            System.err.println(e);
            System.exit(2);
        }

        System.out.printf("    elapsed time %s\n", t);
    }
}
