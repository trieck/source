package org.pixielib.content;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

public interface ContentHandler {
    public void handle(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException;
}
