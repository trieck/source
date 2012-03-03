package org.pixielib.xml;

import javax.xml.transform.Templates;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerException;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.stream.StreamResult;
import javax.xml.transform.stream.StreamSource;
import java.io.File;
import java.io.FilenameFilter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class XMLFilesTransformer {

    private static final TransformerFactory factory = TransformerFactory.newInstance();

    private static List<File> expand(File dir) {
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

    public static void transform(String inpath, String outpath, String xsl)
            throws TransformerException, IOException {

        File inDir = new File(inpath);
        if (!inDir.isDirectory()) {
            throw new IOException(String.format("\"%s\" is not a directory.",
                    inDir.getCanonicalPath()));
        }

        File outDir = new File(outpath);
        if (!outDir.isDirectory()) {
            if (!outDir.mkdir()) {
                throw new IOException(String.format("\"%s\" is not a directory, and unable to create it.",
                        outDir.getCanonicalPath()));
            }
        }

        List<File> files = expand(inDir);
        if (files.size() == 0) {
            throw new IOException(
                    String.format("no xml files found in \"%s\".",
                            inDir.getCanonicalPath())
            );
        }

        StreamSource xslSource = new StreamSource(xsl);
        Templates t = factory.newTemplates(new StreamSource(xsl));
        Transformer transformer;

        StreamSource xmlSource;
        StreamResult result;
        String outFile;
        for (File f : files) {
            xmlSource = new StreamSource(f);
            outFile = outDir.getCanonicalPath() + "/" + f.getName();
            result = new StreamResult(new File(outFile));
            transformer = t.newTransformer();
            transformer.transform(xmlSource, result);
        }
    }

    public static void main(String[] args) {
        if (args.length != 3) {
            System.err.println("usage: XMLFilesTransformer inpath outpath xslt-file");
            System.exit(1);
        }

        try {
            XMLFilesTransformer.transform(args[0], args[1], args[2]);
        } catch (TransformerException e) {
            System.err.println(e);
            System.exit(1);
        } catch (IOException e) {
            System.err.println(e);
            System.exit(2);
        }
    }

}
