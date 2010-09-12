<%@ page language="java" contentType="text/html" %>
<%@ page import="org.tomrieck.content.beans.*" %>

<%@ page language="java" contentType="text/html" %>
<%@ page import="com.kx.frontend.beans.*" %>
<%@ page import="com.kx.frontend.db.GetSEO" %>

<HTML>
<head>
<LINK HREF="/style.css" REL="stylesheet" TYPE="text/css">
<h1>Content Search Engine Demo</h1>
</HEAD>

<BODY BGCOLOR="#FFFFFF" BOTTOMMARGIN="0" LEFTMARGIN="0" RIGHTMARGIN="0" TOPMARGIN="0" MARGINHEIGHT="0" MARGINWIDTH="0">

<SPAN CLASS="directions">Enter query; surround phrases with double-quotes and then select a version.</SPAN>
<p/>

<FORM METHOD="get" ACTION="/demo/summary.jsp">
<input type="hidden" name="function" value="search"/>
<input type="hidden" name="start" value="1"/>
<TABLE BORDER="0" CELLSPACING="0" CELLPADDING="1">
   <TR>
      <TD VALIGN="middle" CLASS="normal"><B CLASS="header">Query:</B></TD>
      <TD VALIGN="top">&nbsp;</TD>
      <TD VALIGN="top"><INPUT NAME="query" TYPE="text" SIZE="30" MAXLENGTH="128"/></TD>
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
                <option value="asv">American Standard Version</option>
                <option value="basic-english">Basic English Version</option>
                <option value="kjv">King James Version</option>
                <option value="niv">New International Version</option>
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
