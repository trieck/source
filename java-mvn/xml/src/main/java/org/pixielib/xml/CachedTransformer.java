package org.pixielib.xml;

import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerConfigurationException;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.stream.StreamSource;
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
	/**
	 * the singleton instance
	 */
	private static CachedTransformer instance = null;

	private CachedTransformer() throws IOException {
		factory = TransformerFactory.newInstance();
		table = new Hashtable<String, Transformer>();
	}

	public static synchronized CachedTransformer getInstance()
					throws IOException {
		if (instance == null) {
			instance = new CachedTransformer();
		}

		return instance;
	}

	private Transformer createTransformer(File file)
					throws IOException, TransformerConfigurationException {

		Transformer transformer;

		// TransfomerFactory is NOT guaranteed to be thread safe
		synchronized (factory) {
			transformer = factory.newTransformer(new StreamSource(file));
		}

		table.put(file.getCanonicalPath(), transformer);

		return transformer;
	}

	public Transformer getTransformer(File file)
					throws IOException, TransformerConfigurationException {

		// use a normalized naming scheme
		String filename = file.getCanonicalPath();

		Transformer t = table.get(filename);

		if (t == null) {
			t = createTransformer(file);
		}

		return t;
	}
}
