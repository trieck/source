<%@ page language="java" contentType="text/html" %>
<%@ page import="org.pixielib.content.beans.*" %>
<%@ page import="org.pixielib.games.jumble.*" %>
<%@ page import="java.util.*" %>

<jsp:useBean id="context" scope="page" class="org.pixielib.content.beans.Context"/>
<jsp:setProperty name="context" property="context" value="<%= pageContext %>" />

<%
   String word = context.getSymbol("word");
%>

<HTML>
<head>
<LINK HREF="style.css" REL="stylesheet" TYPE="text/css">
<h1>Jumble Solver</h1>
</HEAD>

<BODY BGCOLOR="#FFFFFF" BOTTOMMARGIN="0" LEFTMARGIN="0" RIGHTMARGIN="0" TOPMARGIN="0" MARGINHEIGHT="0" MARGINWIDTH="0">


<SPAN CLASS="directions">Enter word and click solve.</SPAN>
<p/>

<FORM METHOD="get" ACTION="solve.jsp">
<TABLE BORDER="0" CELLSPACING="0" CELLPADDING="1">
   <TR>
      <TD VALIGN="middle" CLASS="normal"><B CLASS="header">Word:</B></TD>
      <TD VALIGN="top">&nbsp;</TD>
      <TD VALIGN="top">
        <INPUT NAME="word" TYPE="text" SIZE="30" MAXLENGTH="128" value="<%= WebUtils.htmlEncode(word) %>"/>
      </TD>
      <td>&nbsp;</td>
	  <td><INPUT TYPE="submit" VALUE="  Solve  " CLASS="searchbutton"></td>
   </TR>

</TABLE>
</FORM>

<% if (word.length() > 0) {	 %>
<TABLE BORDER="0" CELLSPACING="0" CELLPADDING="1">
<%
	Jumble jumble = new Jumble();	
	Iterator<String> it = jumble.solve(word).iterator();
	while (it.hasNext()) {
%>
	<TR><TD VALIGN="middle" CLASS="normal"><%= it.next() %></TD></TR>
<%
	}
%>
</TABLE>
<% } %>


</BODY>
</HTML>
