package org.pixielib.xml;

import org.pixielib.io.FileUtil;

import java.io.File;
import java.io.FilenameFilter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.regex.Pattern;

public class XMLRepairer {

    private static final Pattern INVALID_XML_CHARS = Pattern.compile(
            "[^\u0009\\u000A\\u000D\\u0020-\\uD7FF\\uE000-\\uFFFD\\u10000-\\u10FFFF]");

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

    public static void main(String[] args) {
        if (args.length < 1) {
            System.err.println("usage: XMLRepairer path");
            System.exit(1);
        }

        XMLRepairer repairer = new XMLRepairer();

        try {
            repairer.repair(args[0]);
        } catch (IOException e) {
            System.err.println(e);
            System.exit(2);
        }
    }

    public void repair(String path)
            throws IOException {

        File dir = new File(path);
        if (!dir.isDirectory()) {
            throw new IOException(String.format("\"%s\" is not a directory.",
                    dir.getCanonicalPath()));
        }

        List<File> files = expand(dir);
        if (files.size() == 0) {
            throw new IOException(
                    String.format("no xml files found in \"%s\".",
                            dir.getCanonicalPath())
            );
        }

        for (File f : files) {
            repair(f);
        }
    }

    public void repair(File file)
            throws IOException {
        String xml = FileUtil.readFile(file.getCanonicalPath());
        xml = INVALID_XML_CHARS.matcher(xml).replaceAll("");
        FileUtil.writeFile(file.getCanonicalPath(), xml);
    }
}
