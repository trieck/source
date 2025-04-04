<%@ page language="java" contentType="text/html" %>
<%@ page import="org.pixielib.content.beans.*" %>

<jsp:useBean id="context" scope="page" class="org.pixielib.content.beans.Context"/>
<jsp:setProperty name="context" property="context" value="<%= pageContext %>" />

<%
    String db = context.getSymbol("db");
    String docid = context.getSymbol("docid");
    String query = context.getSymbol("query");    
    String style = "detail";

    Detail record = Detail.DetailRecord("nwn", db, docid, query, style);
%>

<html>
<head>
<link href="style.css" rel="stylesheet" type="text/css" />
</head>
<h1>NWN Script Archive Search Engine</h1>
<body>
<p/>

<table border="0" cellspacing="1" cellpadding="0" width="100%">
  <tr>
    <td class="grey">
      <table border="0" cellspacing="1" cellpadding="1" width="100%">
        <tr>
          <td>
            <% record.getContent(); %>
          </td>
        </tr>
      </table>
    </td>
  </tr>
</table>

</body>
</html>

