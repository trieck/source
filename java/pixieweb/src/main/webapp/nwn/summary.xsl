<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                xmlns:java="http://xml.apache.org/xslt/java"
                version="1.0">

    <xsl:output method="html" indent="yes" doctype-public="-//W3C//DTD HTML 4.0 Transitional//EN"/>

    <xsl:template match="/">
        <xsl:apply-templates/>
    </xsl:template>

    <xsl:template match="*">
    </xsl:template>

    <xsl:template match="results">
        <xsl:if test="//results/@count != 0">
            <TABLE CELLPADDING="0" CELLSPACING="0" BORDER="0" WIDTH="100%">
                <TR>
                    <TH WIDTH="25" align="left">&#xa0;</TH>
                    <TH WIDTH="125" align="left">
                        <b>Title</b>
                    </TH>
                </TR>
                <xsl:apply-templates select="record"/>
            </TABLE>
        </xsl:if>
    </xsl:template>

    <xsl:template match="record">
        <xsl:variable name="linkdetail">detail.jsp?db=<xsl:value-of select="//results/@db"/>&amp;docid=<xsl:value-of
                select="@docid"/>&amp;query=<xsl:value-of
                select="java:org.pixielib.content.beans.Context.encode(//results/@query)"/>
        </xsl:variable>
        <TR>
            <TD class="grey">
                <xsl:value-of select="//results/@start + position() - 1"/>.
            </TD>
            <TD align="left" class="grey">
                <a href="{$linkdetail}">
                    <xsl:apply-templates select="title"/>
                </a>
            </TD>
        </TR>
    </xsl:template>

    <xsl:template match="title">
        <xsl:apply-templates/>
    </xsl:template>

    <xsl:template match="highlight">
        <span class="highlight">
            <xsl:value-of select="."/>
        </span>
    </xsl:template>

</xsl:stylesheet>
        