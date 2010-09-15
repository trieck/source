package org.pixielib.content.beans;

import org.pixielib.util.Config;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.http.Cookie;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import javax.servlet.jsp.JspWriter;
import javax.servlet.jsp.PageContext;
import java.io.IOException;
import java.io.Serializable;
import java.io.Writer;
import java.net.URLDecoder;
import java.net.URLEncoder;
import java.util.*;

public class Context implements Serializable {

    private static final long serialVersionUID = 1L;

    /**
     * mapping of threads to object instances
     */
    protected static final Map<Thread, Context> contextTable = Collections
            .synchronizedMap(new WeakHashMap<Thread, Context>());

    /**
     * the underlying page context
     */
    protected PageContext context;

    /**
     * global symbol table
     */
    protected Map<String, String> symbols;

    /**
     * local context map, used to maintain local symbol tables for JSPs
     */
    protected Map<String, Object> locals;

    /**
     * instance table
     */
    protected Map<String, Object> instances;

    /**
     * Public ctor
     */
    public Context() {
        symbols = new HashMap<String, String>();
        instances = new HashMap<String, Object>();
        locals = new HashMap<String, Object>();
    }

    /**
     * Retrieve the KnowX context associated with this thread
     *
     * @return the context
     */
    public static Context getContext() {
        return contextTable.get(Thread.currentThread());
    }

    /**
     * Set page context
     *
     * @param context the context
     */
    public void setContext(PageContext context) {
        this.context = context;
        contextTable.put(Thread.currentThread(), this);
    }

    /**
     * Lookup a symbol
     *
     * @param name symbol name
     * @return symbol value
     */
    public String getSymbol(String name) {
        // try the global symbol table
        String value = symbols.get(name);
        if (value != null) {
            return value;
        }

        // try request parameters
        value = getParam(name);
        if (value.length() != 0) {
            return value;
        }

        // try cookies
        return getCookieValue(name);
    }

    /**
     * Lookup a symbol
     *
     * @param name symbol name
     * @return symbol value
     */
    public static final String getContextSymbol(String name) {
        return getContext().getSymbol(name);
    }

    /**
     * Lookup a symbol and return as an integer
     *
     * @param name symbol name
     * @return symbol value as an integer
     */
    public int getIntSymbol(String name) {
        String value = getSymbol(name);

        int nrtn = 0;

        try {
            nrtn = Integer.parseInt(value);
        } catch (NumberFormatException e) {
            ; // not a number
        }

        return nrtn;
    }

    /**
     * Lookup a symbol and return as an integer
     *
     * @param name symbol name
     * @return symbol value as an integer
     */
    public float getFloatSymbol(String name) {
        String value = getSymbol(name);

        float nrtn = 0.0f;

        try {
            nrtn = Float.parseFloat(value);
        } catch (NumberFormatException e) {
            ; // not a number
        }

        return nrtn;
    }

    /**
     * Store a symbol in the symbol table
     *
     * @param name  the symbol name
     * @param value the symbol value
     * @return the value
     */
    public String putSymbol(String name, String value) {
        value = value.trim();
        symbols.put(name.trim(), value);
        return value;
    }

    /**
     * Lookup an object by key
     *
     * @param key the key
     * @return the instance
     */
    public Object getInstance(String key) {
        return instances.get(key);
    }

    /**
     * Store an object in the instance table
     *
     * @param key the key
     * @param val the value
     */
    public void putInstance(String key, Object val) {
        instances.put(key, val);
    }

    /**
     * Retrieve string parameter from request
     *
     * @param key the key
     * @return the parameter value
     */
    public String getParam(String key) {
        HttpServletRequest request = (HttpServletRequest) context.getRequest();

        String value = request.getParameter(key);

        return value == null ? "" : value.trim();
    }

    public String[] splitParam(String key, String delim) {

        String value = getParam(key);
        if (value.length() == 0)
            return new String[]{};

        StringTokenizer tokenizer = new StringTokenizer(value, delim);

        List<String> tokens = new ArrayList<String>();
        while (tokenizer.hasMoreTokens()) {
            tokens.add(tokenizer.nextToken().trim());
        }

        String[] array = new String[tokens.size()];
        tokens.toArray(array);

        return array;
    }

    /**
     * Retrieve parameter names from request
     *
     * @return the parameter names
     */
    public Enumeration<?> getParamNames() {
        HttpServletRequest request = (HttpServletRequest) context.getRequest();
        return request.getParameterNames();
    }

    /**
     * Retrieve parameter values for a name
     *
     * @param name the parameter name
     * @return the parameter values
     */
    public String[] getParamValues(String name) {
        HttpServletRequest request = (HttpServletRequest) context.getRequest();
        return request.getParameterValues(name);
    }

    /**
     * Retrieve request method
     *
     * @return the method
     */
    public String getMethod() {
        HttpServletRequest request = (HttpServletRequest) context.getRequest();
        return request.getMethod();
    }

    /**
     * Get IP address of user
     *
     * @return the method
     */
    public String getRemoteAddress() {
        HttpServletRequest request = (HttpServletRequest) context.getRequest();
        return request.getRemoteAddr();
    }

    /**
     * Retrieve request query string
     *
     * @return the query string
     */
    public String getQueryString() {
        HttpServletRequest request = (HttpServletRequest) context.getRequest();
        return request.getQueryString();
    }

    public static String getContextQuery() {
        return getContext().getQueryString();
    }

    /**
     * Retrieve request URI
     *
     * @return the request URI
     */
    public String getRequestURI() {
        HttpServletRequest request = (HttpServletRequest) context.getRequest();
        return request.getRequestURI();
    }

    /**
     * Retrieve server name
     *
     * @return the server name
     */
    public String getServerName() {
        HttpServletRequest request = (HttpServletRequest) context.getRequest();
        return request.getServerName();
    }

    /**
     * Retrieve a cookie by name
     *
     * @param name the cookie name
     * @return the cookie
     */
    public Cookie getCookie(String name) {

        HttpServletRequest request = (HttpServletRequest) context.getRequest();

        Cookie[] cookies = request.getCookies();
        if (cookies == null) {
            return null; // no cookies
        }

        for (int i = 0; i < cookies.length; i++) {
            String cname = cookies[i].getName();
            if (cname.equals(name))
                return cookies[i];
        }

        return null; // cookie not found
    }

    /**
     * Retrieve all cookies
     *
     * @return the cookies
     */
    public Cookie[] getCookies() {
        HttpServletRequest request = (HttpServletRequest) context.getRequest();

        return request.getCookies();
    }

    /**
     * Retrieve a cookie value by name
     *
     * @param name the cookie name
     * @return the cookie value
     */
    public String getCookieValue(String name) {
        Cookie cookie = getCookie(name);
        if (cookie == null)
            return "";

        return cookie.getValue();
    }

    /**
     * Forward to a url
     *
     * @param url the url to forward to
     */
    public void forward(String url) {
        HttpServletRequest request = (HttpServletRequest) context.getRequest();
        HttpServletResponse response = (HttpServletResponse) context
                .getResponse();

        try {
            RequestDispatcher dispatcher = request.getRequestDispatcher(url);
            dispatcher.forward(request, response);
        } catch (ServletException e) {
            e.printStackTrace();
        } catch (IOException ioe) {
            ioe.printStackTrace();
        }
    }

    /**
     * Encode a url
     *
     * @param url the url to encode
     * @return the encoded url
     */
    public static String encode(String url) {
        try {
            return URLEncoder.encode(url, "iso-8859-1");
        } catch (IOException e) {
            return url;
        }
    }

    /**
     * Decode a url
     *
     * @param url the url to decode
     * @return the decoded url
     */
    public static String decode(String url) {
        try {
            return URLDecoder.decode(url, "iso-8859-1");
        } catch (IOException e) {
            return url;
        }
    }

    /**
     * Redirect to another Url
     *
     * @param url the url
     */
    public void redirect(String url) {
        HttpServletResponse response = (HttpServletResponse) context
                .getResponse();
        try {
            response.sendRedirect(url);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    /**
     * Write output onto the page
     *
     * @param output the output to write
     */
    public void write(String output) {
        JspWriter writer = context.getOut();

        try {
            writer.print(output);
            writer.flush();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    /**
     * Set temporary cookie for the domain
     *
     * @param name  name of the cookie
     * @param value value of the cookie
     */
    public void setTempCookie(String name, String value) {

        setCookie(name, value, -1);
    }

    /**
     * Set Permanent cookie for the domain
     *
     * @param name    name of the cookie
     * @param value   value of the cookie
     * @param seconds duration for the cookie to last
     */
    public void setCookie(String name, String value, int seconds) {

        Cookie cookie = new Cookie(name, value);
        cookie.setMaxAge(seconds);
        cookie.setPath("/");

        // add cookie to response header
        HttpServletResponse response = (HttpServletResponse) context
                .getResponse();
        response.addCookie(cookie);
    }

    /**
     * Return a real path for a given URI
     *
     * @param uri the URI
     * @return the real path for the URI
     */
    public String getRealPath(String uri) {
        ServletContext scntxt = context.getServletContext();
        return scntxt.getRealPath(uri);
    }

    /**
     * The context's identity
     *
     * @return the identity
     */
    public String identity() {
        return getRequestURI() + '?' + getQueryString();
    }

    /**
     * Include a JSP page
     *
     * @param page the page
     * @return true if include was successful otherwise false
     */
    public boolean include(String page) {

        try {
            context.include(page);
        } catch (ServletException e) {
            e.printStackTrace();
            return false;
        } catch (IOException ioe) {
            ioe.printStackTrace();
            return false;
        }

        return true;
    }

    /**
     * Set an object as a request attribute
     *
     * @param name the name of the attribute
     * @param o    the attribute
     */
    public void setRequestAttribute(String name, Object o) {
        HttpServletRequest request = (HttpServletRequest) context.getRequest();
        request.setAttribute(name, o);
    }

    /**
     * Get an object as a request attribute
     *
     * @param name the name of the attribute
     */
    public Object getRequestAttribute(String name) {
        HttpServletRequest request = (HttpServletRequest) context.getRequest();
        return request.getAttribute(name);
    }

    /**
     * Get an object from the local symbol table.
     *
     * @param k the key for the object
     * @return the object if found, otherwise null
     */
    public Object getLocal(String k) {
        if (locals == null) {
            locals = new HashMap<String, Object>();
        }
        return locals.get(k.trim());
    }

    /**
     * Set an object in the local symbol table.
     *
     * @param k the key for the object
     * @param v the object to set
     * @return the object as put into the symbol table
     */
    public Object setLocal(String k, Object v) {
        if (locals == null) {
            locals = new HashMap<String, Object>();
        }
        return locals.put(k.trim(), v);
    }

    public HttpSession getSession() {
        return context.getSession();
    }

    public void setSessionAttribute(String attr, Object o) {
        getSession().setAttribute(attr, o);
    }

    public Object getSessionAttribute(String attr) {
        return getSession().getAttribute(attr);
    }

    public String getProperty(String key) {

        String value = "";

        try {
            Config config = Config.getInstance();
            value = config.getProperty(key);

        } catch (IOException e) {
            e.printStackTrace();
        }

        return value;
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

    public Writer getWriter() {
        return context.getOut();
    }
}
