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

		<TABLE BORDER="0" CELLPADDING="0" CELLSPACING="0">
		<TR>
		<TD class="grey">
        <TABLE BORDER="0" CELLPADDING="0" CELLSPACING="0">
            <TR>
                <TD align="left" class="grey" width="125">
                    <b>Title:</b>
                </TD>
                <TD align="left" class="grey">
                    <b>
                        <xsl:apply-templates select="title"/>
                    </b>
                </TD>
            </TR>
            <xsl:apply-templates select="post"/>
		</TABLE>
		</TD>
		</TR>
		<TR>
		<TD class="grey">
		<TABLE BORDER="0" CELLPADDING="1" CELLSPACING="0">
            <TR>&#160;</TR>
            <TR>&#160;</TR>
            <TR>
                <TD align="left" class="grey">
                    <span><a href="{$resultslink}" >Back to Search Results</a></span>                    
                </TD>
            </TR>            
        </TABLE>
        </TD>
        </TR>
        </TABLE>
    </xsl:template>

	<xsl:template match="post">
		<TR><TD colspan="2" class="grey"><HR/></TD></TR>
		<TR>
        	<TD align="left" class="grey">
            <b>User:</b>
			</TD>
            <TD align="left" class="grey">
            	<b>
                	<xsl:apply-templates select="user"/>
				</b>
			</TD>
		</TR>
		<TR><TD class="grey">&#160;</TD></TR>
		<TR>
        	<TD align="left" class="grey">
            <b>Message:</b>
			</TD>
            <TD align="left" class="grey">
            	<b>
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
