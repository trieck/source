<%@ page language="java" contentType="text/html" %>
<%@ page import="org.pixielib.content.beans.*" %>

<jsp:useBean id="context" scope="page" class="org.pixielib.content.beans.Context"/>
<jsp:setProperty name="context" property="context" value="<%= pageContext%>" />

<%
	String db = context.getSymbol("db");
	String query = context.getSymbol("query");
	String start = context.getSymbol("start");
	String style = "summary";
	int nstart = 1;

	try {
		nstart = Integer.parseInt(start);
	} catch (NumberFormatException e) {
		;
	}

	context.setTempCookie("SearchQuery",
					String.format("db=%s&query=%s&start=%d",
					db, Context.encode(query), nstart));

	String ModifyLink = String.format("search.jsp?db=%s&query=%s", db, Context.encode(query));

	String dbquery = String.format("text[%s]", query);
	Search search = Search.DatabaseSearch("bible", db, dbquery, nstart, style);
%>

<html>
	<head>
		<link href="style.css" rel="stylesheet" type="text/css" />
	</head>
	<h1>Bible Search Engine</h1>
	<body>
		<p/>

		<table border="0" cellspacing="0" cellpadding="3" width="100%">
			<tr bgcolor="#f1f1f1">
				<td valign="bottom" width="50%">
					<b class="searchresults"><%= search.getRecordCount()%></b>&#xa0;
					<b class="searchresults">matches found </b><span class="info">(<%= search.getQueryTime() / (double)1000%> seconds)</span>
				</td>
				<TD VALIGN="bottom" CLASS="normal" ALIGN="right" width="50%">
					Searching: query: <B CLASS="searchquery"><%= query%></B> | db : <B CLASS="searchquery"><%= db%></B>      
				</TD>
			</tr>
		</table>

		<table border="0" cellspacing="0" cellpadding="2" width="100%">
			<tr bgcolor="#00619c" height="25">
				<td border="1" valign="bottom" align="left" width="20%"><a href="search.jsp?db=<%=db%>" class="navigation">New Search</a></td>
				<td border="1" valign="bottom" align="left" width="20%"><a href="<%= ModifyLink%>" class="navigation">Modify Search</a></td>

				<td valign="bottom" width="60%">
					<% if (search.getPrevious().length() > 0) {%>
					&#xa0;<a title="Previous Page" href="<%= search.getPrevious()%>" class="navigation"><img src="../images/previous.png" border="0"/></a>&#xa0;&#xa0;
					<% }%>
					<% if (search.getNext().length() > 0) {%>
					&#xa0;<a title="Next Page"  href="<%= search.getNext()%>" class="navigation"><img src="../images/next.png" border="0"/></a> &#xa0;&#xa0;
					<% }%>
				</td>
			</tr>
		</table>

		<table border="0" cellspacing="1" cellpadding="0" width="100%">
			<tr>
				<td>
					<table border="0" cellspacing="1" cellpadding="1" width="100%">
						<tr>
							<td>
								<% search.getContent();%>
							</td>
						</tr>
					</table>
				</td>
			</tr>
		</table>

	</body>
</html>