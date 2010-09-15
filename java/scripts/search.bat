@echo off
java -Dorg.pixielib.util.Config=c:\source\java\config\content.properties -cp ..\classes org.pixielib.content.Search %1 %2

