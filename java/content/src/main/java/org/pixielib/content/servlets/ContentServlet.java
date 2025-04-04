package org.pixielib.content.servlets;

import org.pixielib.content.ContentHandler;
import org.pixielib.content.DocumentHandler;
import org.pixielib.content.SearchHandler;

import javax.servlet.ServletConfig;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.HashMap;
import java.util.Map;

public class ContentServlet extends HttpServlet {

    private Map<String, ContentHandler> handlers;    // content handlers

    /**
     * * Construct an error description as an xml document
     * * @param error the error
     * * @return the xml document
     */
    private static String xmlerror(String error) {
        String output = "<?xml version=\"1.0\"?>" +
                "<error><![CDATA[ " +
                error +
                " ]]></error>";
        return output;
    }

    @Override
    public void init(ServletConfig config) {
        handlers = new HashMap<>();
        handlers.put("search", new SearchHandler());
        handlers.put("getdoc", new DocumentHandler());
    }

    /**
     * @param request
     * @param response
     * @throws ServletException
     * @throws IOException
     */
    @Override
    public void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        response.setContentType("text/xml");

        PrintWriter output = new PrintWriter(response.getOutputStream());

        try {
            String function = request.getParameter("function");
            if (function == null)
                throw new IllegalArgumentException("function not supplied.");

            ContentHandler handler = handlers.get(function);
            if (handler == null)
                throw new IllegalArgumentException("function not supported.");

            handler.handle(request, response);

        } catch (IllegalArgumentException | ServletException | IOException e) {
            output.print(xmlerror(e.toString()));
            System.err.println(e);
        } finally {
            output.flush();
            output.close();
        }
    }
}
