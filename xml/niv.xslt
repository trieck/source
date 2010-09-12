<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:strip-space elements="*"/>
<xsl:output method="xml" indent="yes" />

<xsl:template match="/">
	<xsl:apply-templates />
</xsl:template>

<xsl:template match="bible">
	<root>
	<xsl:apply-templates />  
	</root>
</xsl:template>

<xsl:template match="book">
	<xsl:apply-templates />
</xsl:template>

<xsl:template match="chapter">
	<xsl:apply-templates />
</xsl:template>

<xsl:template match="verse">
	<verse>
	<xsl:attribute name="book">
  		<xsl:value-of select="../../@name"/>
  	</xsl:attribute>
	<xsl:attribute name="chapter">
  		<xsl:value-of select="../@name"/>
  	</xsl:attribute>
	<xsl:attribute name="number">
  		<xsl:value-of select="@name"/>
  	</xsl:attribute>
	<text>
  	<xsl:value-of select="."/>
	</text>
	</verse>
</xsl:template>

</xsl:stylesheet>
