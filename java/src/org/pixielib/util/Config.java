package org.pixielib.util;

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.util.Properties;

public class Config {
    private Properties props;
    private static Config instance = null;

    private String filename;    // property filename
    private long lastmodified;  // last modified time

    private Config() throws IOException {
        props = new Properties();
        String className = Config.class.getName();
        filename = System.getProperty(className);
        if (filename == null) {
            String message = String.format("System property not set for %s.",
                className);
                throw new IOException(message);
        }

        reload();        
    }

    private void reload() throws IOException {
        File file = new File(filename);
        lastmodified = file.lastModified();
        FileInputStream fis = new FileInputStream(file);
        props.clear();
        props.load(fis);
        fis.close();
    }
    
    public static synchronized Config getInstance() throws IOException {

        if (instance != null)
            return instance;

        instance = new Config();

        return instance;
    }

    // check whether the file has changed and reload
    private void checkReload() {
        File file = new File(filename);
        long modified = file.lastModified();
        if (modified > lastmodified) {
            try {
                reload();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    public String getProperty(String k) {
        if (props == null)
            return "";

        checkReload();

        String value = props.getProperty(k);
        if (value == null)
            return "";

        return value.trim();
    }
}
