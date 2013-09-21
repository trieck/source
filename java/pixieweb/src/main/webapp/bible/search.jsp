<%@ page language="java" contentType="text/html" %>
<%@ page import="org.pixielib.content.beans.*" %>

<jsp:useBean id="context" scope="page" class="org.pixielib.content.beans.Context"/>
<jsp:setProperty name="context" property="context" value="<%= pageContext%>" />

<%
	String db = context.getSymbol("db");
	String query = context.getSymbol("query");
%>

<HTML>
	<head>
		<LINK HREF="style.css" REL="stylesheet" TYPE="text/css">
	<h1>Bible Search Engine</h1>
</HEAD>

<BODY BGCOLOR="#FFFFFF" BOTTOMMARGIN="0" LEFTMARGIN="0" RIGHTMARGIN="0" TOPMARGIN="0" MARGINHEIGHT="0" MARGINWIDTH="0">
	<SPAN CLASS="directions">Enter query (surround phrases with double-quotes) and select a version.</SPAN>
	<p/>

	<FORM METHOD="get" ACTION="summary.jsp">
		<input type="hidden" name="function" value="search"/>
		<input type="hidden" name="start" value="1"/>
		<TABLE BORDER="0" CELLSPACING="0" CELLPADDING="1">
			<TR>
				<TD VALIGN="middle" CLASS="normal"><B CLASS="header">Query:</B></TD>
				<TD VALIGN="top">&nbsp;</TD>
				<TD VALIGN="top">
					<INPUT NAME="query" TYPE="text" SIZE="30" MAXLENGTH="128" value="<%= WebUtils.htmlEncode(query)%>"/>
				</TD>
			</TR>

			<TR>
				<TD VALIGN="middle" CLASS="normal">
					<B CLASS="header">Version:</B>
				</TD>
				<TD VALIGN="top">&nbsp;</TD>
				<TD VALIGN="top">
					<table cellspacing="0" cellpadding="0">
						<tr>
							<td>
								<SELECT NAME="db" SIZE="1">
									<option <%= WebUtils.selected(db, "niv")%> value="niv">New International Version</option>                
									<option <%= WebUtils.selected(db, "kjv")%> value="kjv">King James Version</option>
									<option <%= WebUtils.selected(db, "asv")%> value="asv">American Standard Version</option>
									<option <%= WebUtils.selected(db, "basic-english")%> value="basic-english">Basic English Version</option>                
								</SELECT>
							</td>
							<td>&nbsp;</td>
							<td><INPUT TYPE="submit" VALUE="  Search  " CLASS="searchbutton"></td>
						</tr>
					</table>
				</TD>
			</TR>
		</TABLE>
	</FORM>

</BODY>
</HTML>
