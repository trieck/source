<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:strip-space elements="*"/>
<xsl:output method="xml" indent="yes" />

<xsl:template match="*">
</xsl:template>

<xsl:template match="/">
	<xsl:apply-templates />
</xsl:template>

<xsl:template match="PLAY">
	<records>
	<xsl:apply-templates />
	</records>
</xsl:template>

<xsl:template match="ACT">
	<xsl:apply-templates />
</xsl:template>

<xsl:template match="SCENE">
	<xsl:apply-templates />
</xsl:template>

<xsl:template match="SPEECH">
	<record>
	<act>		
		<xsl:value-of select="../../TITLE"/>
	</act>
	<scene>
		<xsl:value-of select="../TITLE"/>
	</scene>
	<speaker>
		<xsl:value-of select="SPEAKER"/>
	</speaker>
	<lines>
		<xsl:apply-templates select="LINE"/>
	</lines>
	</record>
</xsl:template>

<xsl:template match="LINE">
	<line>
		<xsl:value-of select="."/>
	</line>
</xsl:template>

</xsl:stylesheet>
