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
        <TABLE BORDER="0" CELLPADDING="1" CELLSPACING="0">
            <TR>
                <TD CLASS="regtext11" align="left">
                    <b>Source:</b>
                </TD>
                <TD>&#xa0;</TD>
                <TD CLASS="regtext11" align="left">
                    <b class="grey">
                        <xsl:value-of select="book"/>&#xa0;<xsl:value-of select="chapter"/>:
                        <xsl:value-of select="verse"/>
                    </b>
                </TD>
            </TR>
            <TR>
                <TD WIDTH="25" CLASS="regtext11" align="left">
                    <b>Verse:</b>
                </TD>
                <TD>&#xa0;</TD>
                <TD CLASS="regtext11" align="left">
                    <xsl:value-of select="text"/>
                </TD>
            </TR>
        </TABLE>
    </xsl:template>

</xsl:stylesheet>
