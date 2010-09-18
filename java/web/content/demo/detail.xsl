<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    <xsl:strip-space elements="*"/>
    <xsl:output method="html" indent="yes" doctype-public="-//W3C//DTD HTML 4.0 Transitional//EN"/>

    <xsl:template match="/">
        <xsl:apply-templates/>
    </xsl:template>

    <xsl:template match="*">
    </xsl:template>

    <xsl:template match="record">
                
        <xsl:variable name="chapterlink">
            <xsl:text>/demo/chapter.jsp?db=</xsl:text><xsl:value-of select="@db"/>
            <xsl:text>&amp;book=</xsl:text><xsl:value-of select="book"/>
            <xsl:text>&amp;chapter=</xsl:text><xsl:value-of select="chapter"/>
            <xsl:text>&amp;start=1</xsl:text>
        </xsl:variable>

        <xsl:variable name="prevlink">
            <xsl:variable name="query">
                <xsl:text>book</xsl:text>
                [<xsl:value-of select="book"/>]
                <xsl:text>chapter</xsl:text>
                [<xsl:value-of select="chapter"/>]
                <xsl:text>verse</xsl:text>
                [<xsl:value-of select="verse - 1"/>]
            </xsl:variable>
            <xsl:variable name="expr">
                <xsl:text>//results/record[position()=1]/@docid</xsl:text>
            </xsl:variable>

            <xsl:variable name="prevdocid">
                <xsl:value-of select="java:org.pixielib.content.beans.Search.select(@db, normalize-space($query), $expr)"/>
            </xsl:variable>

            <xsl:if test="$prevdocid">
                <xsl:text>/demo/detail.jsp?db=</xsl:text><xsl:value-of select="@db"/>
                <xsl:text>&amp;docid=</xsl:text><xsl:value-of select="$prevdocid"/>
                <xsl:text>&amp;query=</xsl:text><xsl:value-of select="java:org.pixielib.content.beans.Context.encode(normalize-space($query))"/>
            </xsl:if>

        </xsl:variable>

        <xsl:variable name="nextlink">
            <xsl:variable name="query">
                <xsl:text>book</xsl:text>
                [<xsl:value-of select="book"/>]
                <xsl:text>chapter</xsl:text>
                [<xsl:value-of select="chapter"/>]
                <xsl:text>verse</xsl:text>
                [<xsl:value-of select="verse + 1"/>]
            </xsl:variable>
            <xsl:variable name="expr">
                <xsl:text>//results/record[position()=1]/@docid</xsl:text>
            </xsl:variable>

            <xsl:variable name="nextdocid">
                <xsl:value-of select="java:org.pixielib.content.beans.Search.select(@db, normalize-space($query), $expr)"/>
            </xsl:variable>

            <xsl:if test="$nextdocid">
                <xsl:text>/demo/detail.jsp?db=</xsl:text><xsl:value-of select="@db"/>
                <xsl:text>&amp;docid=</xsl:text><xsl:value-of select="$nextdocid"/>
                <xsl:text>&amp;query=</xsl:text><xsl:value-of select="java:org.pixielib.content.beans.Context.encode(normalize-space($query))"/>
            </xsl:if>
        </xsl:variable>

        <TABLE BORDER="0" CELLPADDING="1" CELLSPACING="0">
            <TR>
                <TD CLASS="regtext11" align="left">
                    <b>Source:</b>
                </TD>
                <TD>&#160;</TD>
                <TD CLASS="regtext11" align="left">
                    <b class="grey">
                        <xsl:value-of select="book"/>&#xa0;<xsl:value-of select="chapter"/>:<xsl:value-of select="verse"/>
                    </b>
                </TD>
            </TR>
            <TR>
                <TD WIDTH="25" CLASS="regtext11" align="left">
                    <b>Verse:</b>
                </TD>
                <TD>&#160;</TD>
                <TD CLASS="regtext11" align="left">
                    <xsl:value-of select="text"/>
                </TD>
            </TR>
            <TR>&#160;</TR>
            <TR>
                <TD>&#160;</TD>
                <TD>&#160;</TD>
                <TD CLASS="regtext11" align="left">
                    <span><a href="{$chapterlink}" class="blue">Read this chapter</a></span>
                    <xsl:if test="$prevlink">
                        &#160;<span><a href="{$prevlink}" class="blue">Previous Verse</a></span>
                    </xsl:if>
                    <xsl:if test="$nextlink">
                        &#160;<span><a href="{$nextlink}" class="blue">Next Verse</a></span>
                    </xsl:if>
                </TD>
            </TR>            
        </TABLE>
    </xsl:template>

</xsl:stylesheet>
