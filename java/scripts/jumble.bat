@echo off
java -Xms64m -Xmx512m -Dorg.pixielib.util.Config=d:\source\java\config\jumble.properties -cp ..\classes org.pixielib.games.jumble.Jumble %1
