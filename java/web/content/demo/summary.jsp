<%@ page language="java" contentType="text/html" %>
<%@ page import="org.pixielib.content.beans.*" %>

<jsp:useBean id="context" scope="page" class="org.pixielib.content.beans.Context"/>
<jsp:setProperty name="context" property="context" value="<%= pageContext %>" />

<%
    String db = context.getSymbol("db");
    String query = context.getSymbol("query");
    String start = context.getSymbol("start");
    String count = context.getSymbol("count");
    String style = "summary";
    int nstart = 1;
    
    try {
        nstart = Integer.parseInt(start);
    } catch (NumberFormatException e) {
        ;
    }

    String ModifyLink = String.format("/demo/search.jsp?db=%s&query=%s", db, context.encode(query));

	String dbquery = String.format("text[%s]", query);
    Search search = Search.DatabaseSearch("demo", db, dbquery, nstart, style);    
%>

<html>
<head>
<link href="/style.css" rel="stylesheet" type="text/css" />
</head>
<h1>Content Search Engine Demo</h1>
<body>
<p/>

<table border="0" cellspacing="0" cellpadding="3" width="100%">
  <tr bgcolor="#f1f1f1">
    <td valign="bottom" width="50%">
      <b class="blu14large"><%= search.getRecordCount() %></b>&#xa0;
      <b class="blu14large">matches found</b>
    </td>
    <TD VALIGN="bottom" CLASS="normal" ALIGN="right" width="50%">
      Searching: query: <B CLASS="yoursearch"><%= query %></B> | db : <B CLASS="yoursearch"><%= db %></B>      
    </TD>
	</tr>
</table>

<table border="0" cellspacing="0" cellpadding="2" width="100%">
  <tr bgcolor="#00619c" height="25">
    <td border="1" valign="bottom" align="left"><a href="/demo/search.jsp?" class="regtextw11">New search</a></td>
    <td border="1" valign="bottom" align="left"><a href="<%= ModifyLink %>" class="regtextw11">Modify search</a></td>

  	<td valign="bottom">
      <% if (search.getPrevious().length() > 0 ) { %>
         &#xa0;<img src="/images/page_rev.gif" border="0"/><a href="<%= search.getPrevious() %>" class="regtextw11">Previous page</a>&#xa0;&#xa0;
      <% } %>
      <% if (search.getNext().length() > 0 ) { %>
         &#xa0;<a href="<%= search.getNext() %>" class="regtextw11">Next page</a><img src="/images/page_arr.gif" border="0"/> &#xa0;&#xa0;
      <% } %>
    </td>
  </tr>
</table>

<table border="0" cellspacing="1" cellpadding="0" width="100%">
  <tr>
    <td bgcolor="#aaaaaa">
      <table border="0" cellspacing="1" cellpadding="1" width="100%">
        <tr>
          <td bgcolor="#ffffff">
            <% search.getContent(); %>
          </td>
        </tr>
      </table>
    </td>
  </tr>
</table>

</body>
</html>