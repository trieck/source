<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    
    <xsl:output method="html" indent="yes" doctype-public="-//W3C//DTD HTML 4.0 Transitional//EN"/>

    <xsl:template match="/">
        <xsl:apply-templates/>
    </xsl:template>

    <xsl:template match="*">
    </xsl:template>

    <xsl:template match="results">
        <xsl:if test="//results/@count != 0">
            <TABLE CELLPADDING="0" CELLSPACING="0" BORDER="0" WIDTH="100%">
                <TR BGCOLOR="#FFFFCC">
                    <TD WIDTH="25" CLASS="regtext11" align="left">&#xa0;</TD>

                    <TD WIDTH="125" CLASS="regtext11" align="left">
                        <b>Source</b>
                    </TD>
                    <TD CLASS="regtext11" align="left">
                        <b>Verse</b>
                    </TD>
                </TR>
                <xsl:apply-templates select="record"/>
            </TABLE>
        </xsl:if>
    </xsl:template>

    <xsl:template match="record">
        <xsl:variable name="linkdetail">/demo/detail.jsp?db=<xsl:value-of select="//results/@db"/>&amp;docid=<xsl:value-of select="@docid"/>&amp;query=<xsl:value-of select="java:org.pixielib.content.beans.Context.encode(//results/@query)"/>
        </xsl:variable>
        <TR>
            <TD CLASS="regtext11">
                <xsl:value-of select="//results/@start + position() - 1"/>.
            </TD>
            <TD CLASS="regtext11" align="left">
                <a href="{$linkdetail}" class="blue">
                    <span class="grey">
                        <xsl:value-of select="book"/>&#xa0;<xsl:value-of select="chapter"/>:<xsl:value-of select="verse"/>
                    </span>
                </a>
            </TD>
            <TD CLASS="regtext11" align="left">
                <b class="grey">
                    <xsl:apply-templates select="text"/>
                </b>
            </TD>
        </TR>
    </xsl:template>

    <xsl:template match="text">
        <xsl:apply-templates/>
    </xsl:template>

    <xsl:template match="highlight">
        <span class="highlight">
            <xsl:value-of select="."/>
        </span>
    </xsl:template>

</xsl:stylesheet>
        