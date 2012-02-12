<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet version="1.0" 
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns:xhtml="http://www.w3.org/1999/xhtml"
	exclude-result-prefixes="xhtml">
<xsl:strip-space elements="*"/>
<xsl:output method="xml" indent="yes" omit-xml-declaration="yes"/>

<xsl:template match="/">
	<xsl:apply-templates />
</xsl:template>

<xsl:template match="xhtml:html">
	<record>
	<xsl:apply-templates />  
	</record>
</xsl:template>

<xsl:template match="xhtml:title">
	<title><xsl:value-of select="."/></title>
</xsl:template>

<xsl:template match="xhtml:tr">
	<xsl:if test="position() != 1">
		<post>
		<xsl:apply-templates select="xhtml:td"/>
		</post>
	</xsl:if>
</xsl:template>

<xsl:template match="xhtml:td[1]">
	<user><xsl:value-of select="."/></user>
</xsl:template>	

<xsl:template match="xhtml:td[2]">
	<xsl:element name="message">
		<xsl:apply-templates select="node()"/>
	</xsl:element>
</xsl:template>

<xsl:template match="xhtml:td/*">
	<xsl:element name="{local-name()}">
		<xsl:apply-templates select="@* | node()"/>
	</xsl:element>
</xsl:template>

<xsl:template match="xhtml:td/node() | @*">
	<xsl:copy>
  		<xsl:apply-templates select="node() | @*"/>
	</xsl:copy>
</xsl:template>


</xsl:stylesheet>
