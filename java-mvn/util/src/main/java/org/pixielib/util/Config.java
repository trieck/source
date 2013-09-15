package org.pixielib.util;

import java.util.ResourceBundle;

public class Config {
	private ResourceBundle bundle;
	private static Config instance = null;

	private Config() {
		bundle = ResourceBundle.getBundle("pixie");
	}

	public static synchronized Config getInstance() {

		if (instance != null)
			return instance;

		instance = new Config();

		return instance;
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
}
