@echo off
java -Dorg.tomrieck.util.Config=c:\source\java\config\content.properties -cp ..\classes org.tomrieck.content.Search %1 %2

