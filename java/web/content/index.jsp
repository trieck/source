<html>
<head>
<link href="/style.css" rel="stylesheet" type="text/css" />
</head>
<body>
<form action="/servlet/org.tomrieck.content.servlets.ContentServlet">
<input type="hidden" name="function" value="search"/>
<input type="hidden" name="db" value="kjv"/>
<input type="hidden" name="start" value="1"/>
<input type="hidden" name="count" value="25"/>
<table>
<tr>
<td>Phrase search:</td>
<td><input type="text" size="40" name="query"/></td>
</tr>
<tr>
<td><input type="submit"/></td>
</tr>
</table>
<form>
	
</body>
</html>