<%@ page language="java" contentType="text/html" %>
<%@ page import="org.tomrieck.content.beans.*" %>

<jsp:useBean id="context" scope="page" class="org.tomrieck.content.beans.Context"/>
<jsp:setProperty name="context" property="context" value="<%= pageContext %>" />

<%
    String db = request.getParameter("db");
    String query = request.getParameter("query");
    String start = request.getParameter("start");
    String count = request.getParameter("count");
    String style = "summary";

    int nstart = Integer.parseInt(start);
      
    Search search = Search.DatabaseSearch("demo", db, query, nstart, style);    
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
	</tr>
</table>

<table border="0" cellspacing="0" cellpadding="2" width="100%">
  <tr bgcolor="#00619c" height="25">
    <td border="1" valign="bottom" align="left"><a href="/demo/search.jsp?" class="regtextw11">New search</a></td>
      
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