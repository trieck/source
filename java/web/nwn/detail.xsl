<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet version="1.0" 
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns:java="http://xml.apache.org/xslt/java">
    <xsl:output method="html" indent="yes" doctype-public="-//W3C//DTD HTML 4.0 Transitional//EN"/>

    <xsl:template match="/">
        <xsl:apply-templates/>
    </xsl:template>

    <xsl:template match="*">
    </xsl:template>

    <xsl:template match="record">
        <xsl:variable name="SearchQuery">
            <xsl:value-of select="java:org.pixielib.content.beans.Context.getContextSymbol(&quot;SearchQuery&quot;)"/>
        </xsl:variable>

        <xsl:variable name="resultslink">
            <xsl:if test="$SearchQuery">
                <xsl:text>summary.jsp?</xsl:text><xsl:value-of select="$SearchQuery"/>
            </xsl:if>
        </xsl:variable>

		<TABLE BORDER="0" CELLPADDING="1" CELLSPACING="0">
		<TR>
		<TD>
        <TABLE BORDER="0" CELLPADDING="1" CELLSPACING="0">
            <TR>
                <TD CLASS="regtext11" align="left">
                    <b>Title:</b>
                </TD>
                <TD>&#160;</TD>
                <TD CLASS="regtext11" align="left">
                    <b class="normal">
                        <xsl:apply-templates select="title"/>
                    </b>
                </TD>
            </TR>
            <xsl:apply-templates select="post"/>
		</TABLE>
		</TD>
		</TR>
		<TR>
		<TD>
		<TABLE BORDER="0" CELLPADDING="1" CELLSPACING="0">
            <TR>&#160;</TR>
            <TR>&#160;</TR>
            <TR>
                <TD>&#160;</TD>
                <TD>&#160;</TD>
                <TD CLASS="regtext11" align="left">
                    <span><a href="{$resultslink}" class="blue">Back to Search Results</a></span>                    
                </TD>
            </TR>            
        </TABLE>
        </TD>
        </TR>
        </TABLE>
    </xsl:template>

	<xsl:template match="post">
		<TR><TD colspan="3"><HR/></TD></TR>
		<TR>
        	<TD CLASS="regtext11" align="left">
            <b>User:</b>
			</TD>
            <TD>&#160;</TD>
            <TD CLASS="regtext11" align="left">
            	<b class="normal">
                	<xsl:apply-templates select="user"/>
				</b>
			</TD>
		</TR>
		<TR>&#160;</TR>
		<TR>
        	<TD CLASS="regtext11" align="left">
            <b>Message:</b>
			</TD>
            <TD>&#160;</TD>
            <TD CLASS="regtext11" align="left">
            	<b class="normal">
                	<xsl:apply-templates select="message"/>
				</b>
			</TD>
		</TR>
	</xsl:template>
		
    <xsl:template match="title">
        <xsl:apply-templates/>
    </xsl:template>

	<xsl:template match="user">
        <xsl:apply-templates/>
    </xsl:template>
    
    <xsl:template match="message">
        <xsl:apply-templates/>
    </xsl:template>
    
    <xsl:template match="highlight">
        <strong class="highlight"><xsl:value-of select="."/></strong>
    </xsl:template>
    
    <xsl:template match="message/text()">
    	<span class="normal"><xsl:value-of select="."/></span>
    </xsl:template>	

	<xsl:template match="title/text()">
    	<b><xsl:value-of select="."/></b>
    </xsl:template>
    
    <xsl:template match="user/text()">
    	<b><xsl:value-of select="."/></b>
    </xsl:template>	
    
</xsl:stylesheet>
