<%@ page language="java" contentType="text/html" %>
<%@ page import="org.pixielib.content.beans.*" %>

<jsp:useBean id="context" scope="page" class="org.pixielib.content.beans.Context"/>
<jsp:setProperty name="context" property="context" value="<%= pageContext %>" />

<%
   String title = context.getSymbol("title");
   String user = context.getSymbol("user");
   String message = context.getSymbol("message");
%>

<HTML>
<head>
<LINK HREF="style.css" REL="stylesheet" TYPE="text/css">
<h1>NWN Script Archive Search Engine</h1>
</HEAD>

<BODY>

<SPAN CLASS="directions">Enter query (surround phrases with double-quotes):</SPAN>
<p/>

<FORM METHOD="get" ACTION="summary.jsp">
<input type="hidden" name="function" value="search"/>
<input type="hidden" name="start" value="1"/>
<TABLE BORDER="0">
   <TR>
      <TD VALIGN="middle" CLASS="normal"><B CLASS="header">Title:</B></TD>
      <TD VALIGN="top">&nbsp;</TD>
      <TD VALIGN="top">
        <INPUT NAME="title" TYPE="text" SIZE="30" MAXLENGTH="128" value="<%= WebUtils.htmlEncode(title) %>"/>
      </TD>
   </TR>
   <TR>
      <TD VALIGN="middle" CLASS="normal"><B CLASS="header">User:</B></TD>
      <TD VALIGN="top">&nbsp;</TD>
      <TD VALIGN="top">
        <INPUT NAME="user" TYPE="text" SIZE="30" MAXLENGTH="128" value="<%= WebUtils.htmlEncode(user) %>"/>
      </TD>
   </TR>
   <TR>
      <TD VALIGN="middle" CLASS="normal"><B CLASS="header">Message:</B></TD>
      <TD VALIGN="top">&nbsp;</TD>
      <TD VALIGN="top">
        <INPUT NAME="message" TYPE="text" SIZE="30" MAXLENGTH="128" value="<%= WebUtils.htmlEncode(message) %>"/>
      </TD>
   </TR>
   <TR><TD>&nbsp;</TD></TR>
   <TR>
   		<TD>&nbsp;</TD>
   		<TD>&nbsp;</TD>
      <TD VALIGN="top">
        <table>
        	<tr>
					<td><INPUT TYPE="submit" VALUE="  Search  " CLASS="searchbutton"></td>
          </tr>
        </table>
      </TD>
   </TR>
</TABLE>
</FORM>

</BODY>
</HTML>
