<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:strip-space elements="*"/>
<xsl:output method="xml" indent="yes" />

<xsl:template match="/">
	<xsl:apply-templates />
</xsl:template>

<xsl:template match="bible">
	<records>
	<xsl:apply-templates />  
	</records>
</xsl:template>

<xsl:template match="book">
	<xsl:apply-templates />
</xsl:template>

<xsl:template match="chapter">
	<xsl:apply-templates />
</xsl:template>

<xsl:template match="verse">
	<record>
	<book>		
		<xsl:value-of select="../../@name"/>
  	</book>
  	<chapter>
  		<xsl:value-of select="../@number"/>
  	</chapter>  	
  	<verse>
		<xsl:value-of select="@number"/>
	</verse>
  	<text>
		<xsl:value-of select="."/>
	</text>
	</record>
</xsl:template>

</xsl:stylesheet>
