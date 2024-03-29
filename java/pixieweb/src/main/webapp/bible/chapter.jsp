<%@ page language="java" contentType="text/html" %>
<%@ page import="org.pixielib.content.beans.*" %>

<jsp:useBean id="context" scope="page" class="org.pixielib.content.beans.Context"/>
<jsp:setProperty name="context" property="context" value="<%= pageContext%>" />

<%
	String db = context.getSymbol("db");
	String book = context.getSymbol("book");
	String chapter = context.getSymbol("chapter");
	String start = context.getSymbol("start");
	String style = "chapter";
	int nstart = 1;
	int nchapter = 0;

	try {
		nstart = Integer.parseInt(start);
		nchapter = Integer.parseInt(chapter);
	} catch (NumberFormatException e) {
		;
	}

	String dbquery = String.format("book[%s] chapter[%d]", book, nchapter);
	Search search = Search.DatabaseSearch("bible", db, dbquery, nstart, style);

	String searchQuery = context.getSymbol("SearchQuery");

	String results = "";
	if (searchQuery.length() > 0) {
		results = String.format("summary.jsp?%s", searchQuery);
	}

	String prevQuery = String.format("book[%s] chapter[%d]", book, nchapter - 1);
	String nextQuery = String.format("book[%s] chapter[%d]", book, nchapter + 1);

	String expr = "//results/record[position()=1]/@docid";
	String prevDoc = Search.select(db, prevQuery, expr);
	String nextDoc = Search.select(db, nextQuery, expr);

	String prevChapter = "";
	if (prevDoc.length() > 0) {
		prevChapter = String.format("chapter.jsp?db=%s&book=%s&chapter=%d&start=1",
						db, book, nchapter - 1);
	}

	String nextChapter = "";
	if (nextDoc.length() > 0) {
		nextChapter = String.format("chapter.jsp?db=%s&book=%s&chapter=%d&start=1",
						db, book, nchapter + 1);
	}
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
					<b class="blu14large"><%= book%>&nbsp;Chapter&nbsp;<%= chapter%></b>
				</td>
			</tr>
		</table>

		<table border="0" cellspacing="0" cellpadding="2" width="100%">
			<tr bgcolor="#00619c" height="25">
				<td border="1" valign="bottom" align="left" width="20%"><a href="search.jsp?db=<%=db%>" class="navigation">New search</a></td>
				<% if (results.length() > 0) {%>
				<td border="1" valign="bottom" align="left" width="20%"><a href="<%= results%>" class="navigation">Back to Search Results</a></td>
				<% }%>

				<td valign="bottom" width="60%">
					<% if (prevChapter.length() > 0) {%>
					&#xa0;<a title="Previous Chapter" href="<%= prevChapter%>" class="navigation"><img src="../images/prevChapter.png" border="0"/></a>&#xa0;&#xa0;
					<% }%>
					<% if (search.getPrevious().length() > 0) {%>
					&#xa0;<a title="Previous Page" href="<%= search.getPrevious()%>" class="navigation"><img src="../images/previous.png" border="0"/></a>&#xa0;&#xa0;
					<% }%>
					<% if (search.getNext().length() > 0) {%>
					&#xa0;<a title="Next Page"  href="<%= search.getNext()%>" class="navigation"><img src="../images/next.png" border="0"/></a> &#xa0;&#xa0;
					<% }%>
					<% if (nextChapter.length() > 0) {%>
					&#xa0;<a title="Next Chapter"  href="<%= nextChapter%>" class="navigation"><img src="../images/nextChapter.png" border="0"/></a> &#xa0;&#xa0;
						<% }%>
				</td>
			</tr>
		</table>
		<p/>

		<table border="0" cellspacing="1" cellpadding="1" width="75%" align="center">
			<tr>
				<td class="grey">
					<% search.getContent();%>
				</td>
			</tr>
		</table>
	</td>
</tr>
</table>

</body>
</html>
