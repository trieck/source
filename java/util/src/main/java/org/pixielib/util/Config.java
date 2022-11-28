package org.pixielib.util;

import java.util.ResourceBundle;

public class Config {
    private final ResourceBundle bundle;

    public Config(String name) {
        bundle = ResourceBundle.getBundle(name);
    }

    public String getProperty(String k) {

        if (bundle == null)
            return "";

        String value = "";

        try {
            value = bundle.getString(k);
        } catch (Exception ignored) {
        }

        return value.trim();
    }

    public int getIntProperty(String key) {
        String value = getProperty(key);

        try {
            int nvalue = Integer.parseInt(value);
            return nvalue;
        } catch (NumberFormatException e) {
            e.printStackTrace();
        }

        return 0;
    }
}
