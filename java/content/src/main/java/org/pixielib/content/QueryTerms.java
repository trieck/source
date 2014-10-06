package org.pixielib.content;

import java.io.IOException;
import java.io.StringReader;
import java.util.HashSet;
import java.util.Set;

public class QueryTerms extends Query {

    private Set<String> terms = new HashSet<>();  // terms used in query

    public QueryTerms(String query) throws IOException {
        super();
        query(query);
    }

    /**
     * returns true if term matches query
     */
    public boolean match(String term) {
        return terms.contains(term);
    }

    @Override
    protected AnchorList lookup(String field, String term) throws IOException {
        Lexer lexer = new Lexer(new StringReader(term));

        String token, restriction;
        for (int i = 0; (token = lexer.getToken()).length() > 0; i++) {
            restriction = String.format("%s:%s", field, token);
            terms.add(restriction);
        }

        return new AnchorList();
    }

    @Override
    protected AnchorList lookup(String term) throws IOException {
        return new AnchorList();
    }
}
