package org.tomrieck.content.servlets;

import org.tomrieck.content.ContentHandler;
import org.tomrieck.content.DocumentHandler;
import org.tomrieck.content.SearchHandler;

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

    private Map<String, ContentHandler> handlers;	// content handlers

    public void init(ServletConfig config) {
        handlers = new HashMap<String, ContentHandler>();
        handlers.put("search", new SearchHandler());
        handlers.put("getdoc", new DocumentHandler());        
    }

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

        } catch (Exception e) {
            output.print(xmlerror(e.toString()));            
        } finally {
            output.flush();
            output.close();
        }
    }

    /**
	** Construct an error description as an xml document
	** @param error the error
	** @return the xml document
	*/
    private static String xmlerror(String error) {
        StringBuilder output = new StringBuilder();
        output.append("<?xml version=\"1.0\"?>");
        output.append("<error><![CDATA[ ");
        output.append(error);
        output.append(" ]]></error>");
        return output.toString();
    }
}
