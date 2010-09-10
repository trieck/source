package org.tomrieck.content;

import org.tomrieck.util.Timer;
import org.xml.sax.InputSource;

import java.io.*;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

import javax.xml.xpath.*;

public class XMLLoader {

    private static final XPathFactory factory = XPathFactory.newInstance();
    private static final XPath xpath = factory.newXPath();

    // current document number while indexing
    private int currDoc;

    private Index index;

    public XMLLoader() {
    }

    public void load(String path, String outfile)
            throws IOException, XPathExpressionException {
        File dir = new File(path);
        if (!dir.isDirectory()) {
            throw new IOException(
                String.format("\"%s\" not a directory.", path)
            );
        }

        List<File> files = expand(dir);
        
        List<String> indexFiles = new ArrayList<String>();
        for (File f : files) {
            indexFiles.add(f.getCanonicalPath());
        }
        indexFiles.add(outfile);

        String[] aFiles = new String[indexFiles.size()];
        indexFiles.toArray(aFiles);

        index = new Index(aFiles);

        loadfiles(files);

        index.write();        
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
        XPathExpression expr = xpath.compile("//root/text");

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
            index.insert(term, currDoc, i);
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
        if (args.length != 2) {
            System.err.println("usage: XMLLoader pathname outfile");
            System.exit(1);
        }

        Timer t = new Timer();
        
        try {
            XMLLoader loader = new XMLLoader();
            loader.load(args[0], args[1]);
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
