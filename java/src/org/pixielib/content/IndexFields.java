package org.pixielib.content;

import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.HashSet;
import java.util.Set;

/* Top-level fields for indexing
 * Every repository database must contain
 * an 'index.txt' file used for indexing
 */
public class IndexFields {
	
	private Set<String> fields;

	public IndexFields(String db) throws IOException {
		fields = new HashSet<String>();

		File dir = Repository.getInstance().mapPath(db);
		String filename = String.format("%s/index.txt", dir.getCanonicalPath());
		File file = new File(filename).getCanonicalFile();
		if (!file.canRead()) { 
			throw new IOException(String.format("Unable to read \"%s\".", file.getCanonicalPath()));
		}
		
		Lexer lexer = new Lexer(new FileReader(file));
		
		String token;
		while ((token = lexer.getToken()).length() > 0) {
			fields.add(token.toLowerCase());
		}
	}
	
	public boolean isTopLevel(String field) {
		return fields.contains(field);
	}
}
