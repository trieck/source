package org.tomrieck.content.beans;

import org.tomrieck.xml.CachedTransformer;
import org.tomrieck.xml.XMLTransformer;
import org.tomrieck.xml.XMLUtil;
import org.w3c.dom.Document;
import org.xml.sax.SAXException;

import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerException;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;
import java.io.File;
import java.io.IOException;

public abstract class Product {
   
    private String product;     // product
    private String db;          // database
    private String query;       // query
    private String style;       // style
    private int count;          // search record count
    private Document results;   // results XML document

    public Product(String product, String db, String query, String style) {
        this.product = product;
        this.db = db;
        this.query = query;
        this.style = style;
    }

    public String getProduct() {
        return product;
    }

    public String getDatabase() {
        return db;
    }

    public String getQuery() {
        return query;
    }

    public String getStyle() {
        return style;
    }

    public Document getResults() {
        return results;
    }

    protected void setResults(Document doc) {
        results = doc;
    }
    
    public void getContent() {

        Context context = Context.getContext();

        if (results != null) {
            try {
                File f = getStylesheet();
                CachedTransformer cache = CachedTransformer.getInstance();
                Transformer transformer = cache.getTransformer(f);
                transformer.transform(new DOMSource(results),
                        new StreamResult(context.getWriter()));
            } catch (IOException e) {
                e.printStackTrace();
            } catch (TransformerException e) {
                e.printStackTrace();
            } catch (ParserConfigurationException e) {
                e.printStackTrace();
            } catch (SAXException e) {
                e.printStackTrace();
            }
        }                  
    }

    private File getStylesheet() throws IOException {
		String path = getProductDir() + '/' + style.toLowerCase() + ".xsl";
		File file = new File(path).getCanonicalFile();
		if (!file.canRead()) {
            throw new IOException(String.format("can't read \"%s\".", path));
		}

        return file;
    }

    private String getProductDir() {
        Context context = Context.getContext();
		return context.getRealPath("/" + product);
    }

    public int getRecordCount() {
		return count;
	}

    protected void setRecordCount(int count) {
        this.count = count;
    }
    
}
