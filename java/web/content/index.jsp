<html>
<head>
<link href="/style.css" rel="stylesheet" type="text/css" />
</head>
<h1>Content Search Engine</h1>
<body>
<p/>
<div>Enter search query, surround phrases with double-quotes</div>
<p/>
<form action="/servlet/org.tomrieck.content.servlets.ContentServlet">
<input type="hidden" name="function" value="search"/>
<input type="hidden" name="start" value="1"/>
<input type="hidden" name="count" value="25"/>
<table>
<tr>
<td>Version:</td>
<td>
<select name="db">
  <option value="asv">American Standard Version</option>
  <option value="basic-english">Basic English Version</option>
  <option value="kjv">King James Version</option>  
</select>
</td>
</tr>
<tr>
<td>Query:</td>
<td><input type="text" size="40" name="query"/></td>
</tr>
<tr>
<td><input type="submit"/></td>
</tr>
</table>
<form>
	
</body>
</html>