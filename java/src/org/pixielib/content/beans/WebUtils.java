package org.pixielib.content.beans;

import java.text.MessageFormat;
import java.util.*;

public class WebUtils {

	/**
	 * Normalize url by combining duplicate variable definitions so that the
	 * last definition overides any earlier definitions.  Remove any trailing
	 * ampersand.  This function is intended to be used to update url parameters
	 * by appending the new value to the end
	 *
	 * @param input the url
	 * @return the normalized url
	 */
	public static String normalizeUrl(String input) {

		int n = input.indexOf('?');

		String prefix = input.substring(0, n + 1);
		String suffix = input.substring(n + 1);

		Hashtable table = parseQueryString(suffix);
		HashMap<String, String> processed = new HashMap<String, String>();
		String[] values;

		StringBuffer name = new StringBuffer();
		StringBuffer value = new StringBuffer();
		StringBuffer output = new StringBuffer();

		StringBuffer field = name;

		char c;
		for (int i = 0; i < suffix.length(); i++) {
			c = suffix.charAt(i);
			switch (c) {
				case '&':
					if (processed.get(name.toString()) == null) {
						if (output.length() > 0) output.append('&');
						output.append(name.toString());
						output.append('=');
						values = (String[]) table.get(name.toString());
						if (values != null && values.length > 0) {
							output.append(Context.encode(values[values.length - 1]));
						}
						processed.put(name.toString(), "1");
					}
					name.setLength(0);
					field = name;
					break;
				case '=':
					value.setLength(0);
					field = value;
					break;
				default:
					field.append(c);
					break;
			}
		}

		if (processed.get(name.toString()) == null) {
			if (output.length() > 0) output.append('&');
			output.append(name.toString());
			output.append('=');
			values = (String[]) table.get(name.toString());
			if (values != null && values.length > 0) {
				output.append(Context.encode(values[values.length - 1]));
			}
		}

		return prefix + output;
	}

	/**
	 * Local implementation of this deprecated method from HttpUtils.
	 * <p/>
	 * Parses a query string passed from the client to the server and builds a
	 * HashTable object with key-value pairs. The query string should be in the
	 * form of a string packaged by the GET or POST method, that is, it should
	 * have key-value pairs in the form key=value, with each pair separated from
	 * the next by a & character. A key can appear more than once in the query
	 * string with different values. However, the key appears only once in the
	 * hashtable, with its value being an array of strings containing the
	 * multiple values sent by the query string.
	 * <p/>
	 * The keys and values in the hashtable are stored in their decoded form, so
	 * any + characters are converted to spaces, and characters sent in
	 * hexadecimal notation (like %xx) are converted to ASCII characters.
	 *
	 * @param s a string containing the query to be parsed
	 * @return a HashTable object built from the parsed key-value pairs
	 * @throws IllegalArgumentException - if the query string is invalid
	 */
	private static Hashtable parseQueryString(String s)
			throws IllegalArgumentException {
		String valArray[];

		if (s == null) {
			throw new IllegalArgumentException();
		}
		Hashtable ht = new Hashtable();
		StringTokenizer st = new StringTokenizer(s, "&");
		while (st.hasMoreTokens()) {
			String key, val;

			String pair = st.nextToken();
			int pos = pair.indexOf('=');
			if (pos == -1) {    // give up
				key = Context.decode(pair);
				val = "";
			} else {
				key = Context.decode(pair.substring(0, pos));
				val = Context.decode(pair.substring(pos + 1, pair.length()));
			}

			if (ht.containsKey(key)) {
				String oldVals[] = (String[]) ht.get(key);
				valArray = new String[oldVals.length + 1];
				for (int i = 0; i < oldVals.length; i++) {
					valArray[i] = oldVals[i];
				}
				valArray[oldVals.length] = val;
			} else {
				valArray = new String[1];
				valArray[0] = val;
			}
			ht.put(key, valArray);
		}
		return ht;
	}

	/**
	 * Set selected option in combo box based on parameter
	 *
	 * @param value1 the first value
	 * @param value2 the second value to compare
	 * @return String; 'Selected' option
	 */
	public static String selected(String value1, String value2) {

		if (value1.equals(value2))
			return "Selected";

		return "";
	}

	/**
	 * Format string using entries from symbol table
	 *
	 * @param fmt the format string
	 * @param ids the symbol identifiers
	 */
	public static String formatString(String fmt, String ids) {
		Context context = Context.getContext();

		List<String> list = new ArrayList<String>();

		StringTokenizer tok = new StringTokenizer(ids, ";");
		while (tok.hasMoreTokens()) {
			String val = context.getSymbol(tok.nextToken().trim());
			list.add(val);
		}

		Object[] args = list.toArray();

		return MessageFormat.format(fmt, args);
	}

	public static String htmlEncode(String s) {
		StringBuilder output = new StringBuilder();
		for (int i = 0; i < s.length(); i++) {
			char c = s.charAt(i);
			if (c > 127 || c == '"' || c == '<' || c == '>') {
				output.append("&#");
				output.append((int) c);
				output.append(";");
			} else {
				output.append(c);
			}
		}
		return output.toString();
	}
}
