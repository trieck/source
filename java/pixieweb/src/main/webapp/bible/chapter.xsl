<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
	<xsl:strip-space elements="*"/>
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
					<TD class="grey">
						<xsl:for-each select="record">
							<cite class="cite">
								<xsl:value-of select="verse"/>
							</cite>
							<xsl:value-of select="text"/>
							<br/>
						</xsl:for-each>
					</TD>
				</TR>
			</TABLE>
		</xsl:if>
	</xsl:template>

</xsl:stylesheet>
        