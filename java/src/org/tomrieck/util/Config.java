package org.tomrieck.util;

import java.io.FileInputStream;
import java.io.IOException;
import java.util.*;

public class Config {
	private Properties props;
    private static Config instance = null;

	private Config() throws IOException {
        props = new Properties();
        String className = Config.class.getName();
        String filename = System.getProperty(className);
        if (filename == null) {
            String message = String.format("System property not set for %s.",
                    className);
            throw new IOException(message);
        }

        FileInputStream fis = new FileInputStream(filename);
        props.load(fis);
		fis.close();
    }

    public static synchronized Config getInstance() throws IOException {

       if (instance != null)
           return instance;

       instance = new Config();
       
       return instance;
    }

	public String getProperty(String k) {
		if (props == null)
			return "";
			
		String value = props.getProperty(k);
		if (value == null)
			return "";

        return value.trim();
	}
}
