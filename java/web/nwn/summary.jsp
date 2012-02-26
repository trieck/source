<%@ page language="java" contentType="text/html" %>
<%@ page import="org.pixielib.content.beans.*" %>

<jsp:useBean id="context" scope="page" class="org.pixielib.content.beans.Context"/>
<jsp:setProperty name="context" property="context" value="<%= pageContext %>" />

<%
    String title = context.getSymbol("title");
	String user = context.getSymbol("user");
   	String message = context.getSymbol("message");
   
    String start = context.getSymbol("start");
    String style = "summary";
    int nstart = 1;
    
    try {
        nstart = Integer.parseInt(start);
    } catch (NumberFormatException e) {
        ;
    }

    context.setTempCookie("SearchQuery",
        String.format("title=%s&user=%s&message=%s&start=%d", 
        	context.encode(title), 
        	context.encode(user), 
        	context.encode(message), 
        	nstart));

    String ModifyLink = String.format("search.jsp?title=%s&user=%s&message=%s", 
    	context.encode(title),
    	context.encode(user),
    	context.encode(message));

	String dbquery = "";
	if (title.length() > 0) {
		dbquery = String.format("title[%s]", title);
	}
	if (user.length() > 0) {
		if (dbquery.length() > 0)
			dbquery = dbquery + " ";
		dbquery = dbquery + String.format("user[%s]", user);
	}
	if (message.length() > 0) {
		if (dbquery.length() > 0)
			dbquery = dbquery + " ";
		dbquery = dbquery + String.format("message[%s]", message);
	}
	
	Search search = Search.DatabaseSearch("nwn", "nwn-script", dbquery, nstart, style);    
%>

<html>
<head>
<link href="style.css" rel="stylesheet" type="text/css" />
</head>
<h1>NWN Script Archive Search Engine</h1>
<body>
<p/>

<table border="0" cellspacing="0" cellpadding="3" width="100%">
  <tr class="bg1">
    <td valign="bottom" width="50%">
      <b class="blu14large"><%= search.getRecordCount() %></b>&#xa0;
      <b class="blu14large">matches found</b>
    </td>
    <TD VALIGN="bottom" CLASS="normal" ALIGN="right" width="50%">
      Searching: <B CLASS="yoursearch"><%= dbquery %></B>      
    </TD>
	</tr>
</table>

<table border="0" cellspacing="0" cellpadding="2" width="100%">
  <tr class="bg2" height="25">
    <td border="1" valign="bottom" align="left"><a href="search.jsp?" class="regtextw11">New Search</a></td>
    <td border="1" valign="bottom" align="left"><a href="<%= ModifyLink %>" class="regtextw11">Modify Search</a></td>

  	<td valign="bottom">
      <% if (search.getPrevious().length() > 0 ) { %>
         &#xa0;<img src="../images/page_rev.gif" border="0"/><a href="<%= search.getPrevious() %>" class="regtextw11">Previous Page</a>&#xa0;&#xa0;
      <% } %>
      <% if (search.getNext().length() > 0 ) { %>
         &#xa0;<a href="<%= search.getNext() %>" class="regtextw11">Next Page</a><img src="../images/page_arr.gif" border="0"/> &#xa0;&#xa0;
      <% } %>
    </td>
  </tr>
</table>

<table border="0" cellspacing="1" cellpadding="0" width="100%">
  <tr>
    <td class="bg1">
      <table border="0" cellspacing="1" cellpadding="1" width="100%">
        <tr>
          <td class="bg2">
            <% search.getContent(); %>
          </td>
        </tr>
      </table>
    </td>
  </tr>
</table>

</body>
</html>